#ifndef stepper_handle_h
#define stepper_handle_h

#include <AccelStepper.h>
#include "machine_progress_handler.h"
#include "eeprom_extension.h"

extern AccelStepper stepperX;
extern AccelStepper stepperY;
extern AccelStepper stepperZ;
extern AccelStepper stepperW;

extern machine_progress_class machine;

//myStepper.currentPosition();
//stepperX.runToPosition(); //  finish when motor reahced to setted position
//stepperX.run(); //finish when done 1 pulse
//stepperX.moveTo(4000);
//stepperY.distanceToGo();

void motor_set_speed_init();
void motor_set_acc_init();

void motor_forward(char axis, int value);
void motor_back(char axis, int value);

void motor_W_open();
void motor_W_close();
void motor_position(int xvalue, int yvalue, int zvalue);

int get_current_position(char axis);
void nx_axis_page_exit_event();
void motor_reset_stepper_current_position();
void motor_reset_nx_position();

void homing_x_axis ();
void homing_y_axis ();
void homing_z_axis ();
void homing_w_axis ();

void homing_machine ();
#endif
