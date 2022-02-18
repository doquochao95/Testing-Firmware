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
void ethernet_init();
void setup_machine_hardware();
void ethernet_checking();
void sensors_checking();
void air_checking();

void udp_listening();

void udp_buffer_progress();
void parameter_checking(String name, String n_value);
void buffer_speed_check(String name, int value);
void picking_check (String position, int needleqty);
void funtions_check(String name, int value);

void buffer_ethernet_parameter_check(String name, String value);

int camera_checking();

#endif
