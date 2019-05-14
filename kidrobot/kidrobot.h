#ifndef __KIBROBOT_H__
#define __KIBROBOT_H__

#include <math.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "driver/uart.h"
#include "kidbright32.h"

// #define IKB_1_DEBUG
// #define IKB_1_I2C_CLOCK 100E3

class KidRobot : public Device {
	private:		
		enum {
			s_detect,
			s_runing,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;

		// method


	public:
		// constructor
		KidRobot(int bus_ch, int dev_addr) ;
		
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		bool reset() ;
		bool motor(uint8_t ch, uint8_t dir, uint8_t speed) ;
		double ultrasonic() ;
		bool line_sensor(uint8_t ch, uint8_t color) ;
		double ir_sensor() ;
		void led(uint8_t num, uint32_t color) ;

		
};

#endif
