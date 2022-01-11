#ifndef sys_config_h
#define sys_config_h

#include "global_config.h"
#include "global_scope.h"
#include "stepper_handle.h"
extern machine_progress_class machine_progress;

void start_up();
void io_init();
// nextion callback fucntions
void PAGE_LOADING_EVENT_CALLBACK(uint8_t pageId, uint8_t componentId, uint8_t eventType);
void local_data_init();
void setup_machine_hardware();

#endif
