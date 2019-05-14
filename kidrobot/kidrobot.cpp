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
				state = s_runing;
			} else {
				state = s_error;
			}
			break;
		
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
bool KidRobot::motor(uint8_t ch, uint8_t dir, uint8_t speed) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, ch == 1 ? 0 : 1, true);
	i2c_master_write_byte(cmd, (dir ? 0x80 : 0)|(speed&0x7F), true);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	return ret == ESP_OK;
}

double KidRobot::ultrasonic() {
	i2c_cmd_handle_t cmd;
	esp_err_t ret;
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, 15, true);
	i2c_master_write_byte(cmd, 0x80, true);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	if (ret != ESP_OK) {
		return 0;
	}
	
	uint16_t time_counter = 0;
	while (time_counter < 1000) {
		vTaskDelay(10 / portTICK_RATE_MS);

		cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
		i2c_master_write_byte(cmd, 15, true);
		i2c_master_stop(cmd);
		ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
		i2c_cmd_link_delete(cmd);
		
		if (ret != ESP_OK) {
			return 0;
		}
		
		uint8_t data1, data2;
		
		cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, true);
		i2c_master_read_byte(cmd, &data1, I2C_MASTER_ACK); // ACK
		i2c_master_read_byte(cmd, &data2, I2C_MASTER_LAST_NACK);  // NACK
		i2c_master_stop(cmd);
		ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
		i2c_cmd_link_delete(cmd);
		
		if (ret != ESP_OK) {
			return 0;
		}

		if ((data1 & 0x80) == 0) {
		  return (((data1 & 0x07)<<8) | data2) / 10.0;
		}
		
		time_counter += 10;
	}
	
	return 0;
}

bool KidRobot::line_sensor(uint8_t ch, uint8_t color) {
	i2c_cmd_handle_t cmd;
	esp_err_t ret;
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, 17, true);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
		
	if (ret != ESP_OK) {
		return false;
	}
		
	uint8_t left_value, right_value;
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, true);
	i2c_master_read_byte(cmd, &left_value, I2C_MASTER_ACK); // ACK
	i2c_master_read_byte(cmd, &right_value, I2C_MASTER_LAST_NACK);  // NACK
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	if (ret != ESP_OK) {
		return false;
	}
	
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
	i2c_cmd_handle_t cmd;
	esp_err_t ret;
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, 20, true);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
		
	if (ret != ESP_OK) {
		return false;
	}
		
	uint8_t ir_data;
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, true);
	i2c_master_read_byte(cmd, &ir_data, I2C_MASTER_LAST_NACK);  // NACK
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	if (ret != ESP_OK) {
		return false;
	}
	
	if (ir_data != 0) {
		cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
		i2c_master_write_byte(cmd, 20, true);
		i2c_master_write_byte(cmd, 0, true);
		i2c_master_stop(cmd);
		ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
		i2c_cmd_link_delete(cmd);
		
		if (ret != ESP_OK) {
			// return false;
		}
	}
	
	return ir_data;
}

void KidRobot::led(uint8_t num, uint32_t color) {
	i2c_cmd_handle_t cmd;
	esp_err_t ret;
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, ((num - 1) * 3) + 2, true);
	i2c_master_write_byte(cmd, (uint8_t)(color>>16), true);
	i2c_master_write_byte(cmd, (uint8_t)(color>>8), true);
	i2c_master_write_byte(cmd, (uint8_t)(color&0xFF), true);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	if (ret != ESP_OK) {
		return;
	}
	
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, 14, true);
	i2c_master_write_byte(cmd, 0x01, true);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	if (ret != ESP_OK) {
		return;
	}
	
}


#endif
