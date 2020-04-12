#ifndef __IR_REMOTE_H__
#define __IR_REMOTE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "driver.h"
#include "device.h"
#include "kidbright32.h"

#include "xtensa/core-macros.h"

class IR : public Device {
	private:		
		

	public:
		// constructor
		IR(int pin) ;
		
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
		int read() ;
		
		// user can't  use
		uint32_t ccount = 0;
		
		gpio_num_t pin;
		
		xQueueHandle gpio_evt_queue = NULL;
		xQueueHandle ir_data_queue = NULL;
};

#endif
