#ifndef __KIBROBOT_CPP__
#define __KIBROBOT_CPP__

#include "kidrobot.h"

KidRobot::KidRobot(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 40; // Not not use
}

void KidRobot::init(void) {
	// clear initialized flag
	initialized = false;
	
	// Debug
	esp_log_level_set("*", ESP_LOG_INFO);
	
	// Set new timeout of i2c
	i2c_set_timeout(I2C_NUM_1, 40000);
	
	// Start initialized
	state = s_detect;
}

int KidRobot::prop_count(void) {
	// not supported
	return 0;
}

bool KidRobot::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool KidRobot::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool KidRobot::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool KidRobot::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool KidRobot::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

// Start here
void KidRobot::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// clear error flag
				error = false;
				// set initialized flag
				initialized = true;
				
				// Go to main state
				state = s_reset;
			} else {
				state = s_error;
			}
			break;
		
		case s_reset: {
			// Reset
			uint8_t data[20];
			memset(data, 0, 20);
			
			// Fill 0 to all register
			write_reg(0, data, 20);
			
			// Trig LED
			write_reg(14, 0x01);
			
			state = s_runing;
		}
		
		case s_runing: {

		}
		
		case s_wait:
			if (error) {
				// wait polling_ms timeout
				if (is_tickcnt_elapsed(this->tickcnt, this->polling_ms)) {
					state = s_detect;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

	}
}

// Method
bool KidRobot::write_reg(uint8_t offset, uint8_t data) {
	return write_reg(offset, &data, 1);
}

bool KidRobot::write_reg(uint8_t offset, uint8_t *data, int size) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, offset, true);
	i2c_master_write(cmd, data, size, true);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	return ret == ESP_OK;
}

bool KidRobot::read_reg(uint8_t offset, uint8_t *data, int size) {
	i2c_cmd_handle_t cmd;
	esp_err_t ret;
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, offset, true);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	if (ret != ESP_OK) {
		return false;
	}
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, true);
	if (size > 1) {
        i2c_master_read(cmd, data, size - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, data + size - 1, I2C_MASTER_LAST_NACK);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
		
	return ret == ESP_OK;
}

bool KidRobot::motor(uint8_t ch, uint8_t dir, uint8_t speed) {
	return write_reg(ch == 1 ? 0 : 1, (dir ? 0x80 : 0)|(speed&0x7F));
}

double KidRobot::ultrasonic() {
	if (!write_reg(15, 0x80)) {
		return 0;
	}
	
	uint8_t data[2];
	
	uint16_t time_counter = 0;
	while (time_counter < 1000) {
		vTaskDelay(10 / portTICK_RATE_MS);
		
		if (!read_reg(15, data, 2)) {
			return 0;
		}

		if ((data[0] & 0x80) == 0) {
		  return (((data[0] & 0x07)<<8) | data[1]) / 10.0;
		}
		
		time_counter += 10;
	}
	
	return 0;
}

bool KidRobot::line_sensor(uint8_t ch, uint8_t color) {
	uint8_t data[2];
	
	if (!read_reg(17, data, 2)) {
		return false;
	}
	
	uint8_t left_value = data[0];
	uint8_t right_value = data[1];
	
	// White = ค่าน้อย, Black = ค่าเยอะ
	uint8_t leftside = left_value < 100 ? 2 : 1; 
	uint8_t rightside = right_value < 100 ? 2 : 1; 
	
	if (ch == 1) {
		return leftside == color;
	} else if (ch == 2) {
		return rightside == color;
	} else if (ch == 3) {
		return (leftside == color) && (rightside == color);
	} else if (ch == 4) {
		return (leftside != color) && (rightside != color);
	}
	
	return false;
}

double KidRobot::ir_sensor() {
	uint8_t ir_data;
	
	if (!read_reg(20, &ir_data, 1)) {
		return false;
	}
	
	if (ir_data != 0) {
		write_reg(20, 0);
	}
	
	return ir_data;
}

void KidRobot::led(uint8_t num, uint32_t color) {
	uint8_t data[3] = {
		(uint8_t)(color>>16),
		(uint8_t)(color>>8),
		(uint8_t)(color&0xFF)
	};
	
	// write color
	if (!write_reg(((num - 1) * 3) + 2, data, 3)) {
		return;
	}

	// set flag
	write_reg(14, 0x01);
}


#endif
