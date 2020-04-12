#ifndef __IR_REMOTE_CPP__
#define __IR_REMOTE_CPP__

#include "ir.h"
#include "esp_log.h"

uint32_t startCCOUNT = 0;

static void IRAM_ATTR ir_gpio_isr_handler(void* arg) {
	IR *obj = (IR*) arg;
	if (gpio_get_level(obj->pin) == 1) {
		uint32_t t = xthal_get_ccount() - obj->ccount;
		xQueueSendFromISR(obj->gpio_evt_queue, &t, NULL);
	} else {
		obj->ccount = xthal_get_ccount();
	}
}

static void ir_process_task(void* arg) {
	IR *obj = (IR*) arg;
	
	uint32_t t = 0;
	uint16_t data = 0;
	uint8_t dataBitIndex = 0;

	for (;;) {
		if (xQueueReceive(obj->gpio_evt_queue, &t, portMAX_DELAY)) {
			t /= CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ;
			if (t > 2000 && t < 3000) { // start signal
				data = 0;
				dataBitIndex = 0;
			} else {
				data |= ((t > 1000 && t < 2000) ? 1 : 0) << dataBitIndex;
				dataBitIndex++;
				if (dataBitIndex == 12) {
					xQueueSend(obj->ir_data_queue, &data, 0);
				}
			}
		}
	}
}

IR::IR(int pin) {
	this->pin = (gpio_num_t) pin;
}

void IR::init(void) {
	this->gpio_evt_queue = xQueueCreate(200, sizeof(uint32_t));
	this->ir_data_queue = xQueueCreate(50, sizeof(uint16_t));
	
	gpio_set_direction(this->pin, GPIO_MODE_INPUT);
	gpio_set_pull_mode(this->pin, GPIO_PULLUP_ONLY);
	gpio_set_intr_type(this->pin, GPIO_INTR_ANYEDGE);
	
	xTaskCreate(ir_process_task, "ir_process_task", 512, (void*) this, 10, NULL);
	
	gpio_install_isr_service(0);
	gpio_isr_handler_add(this->pin, ir_gpio_isr_handler, (void*) this);
	
	// set initialized flag
	this->initialized = true;
	// clear error flag
	this->error = false;
	
	esp_log_level_set("*", ESP_LOG_INFO);
}

int IR::prop_count(void) {
	// not supported
	return 0;
}

bool IR::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool IR::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool IR::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool IR::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool IR::prop_write(int index, char *value) {
	// not supported
	return false;
}

void IR::process(Driver *drv) {
	
}
// --------------------------------------

// Method
int IR::read() {
	uint16_t data;

	if (xQueueReceive(this->ir_data_queue, &data, 0)) {
		return data;
	}
	
	return -1;
}

#endif
