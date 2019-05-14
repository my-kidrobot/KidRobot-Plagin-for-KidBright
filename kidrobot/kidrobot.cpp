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


#endif
