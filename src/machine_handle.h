#ifndef machine_handle_h
#define machine_handle_h

#include <AccelStepper.h>
#include "machine_progress_handler.h"
#include "eeprom_extension.h"

extern AccelStepper stepperX;
extern AccelStepper stepperY;
extern AccelStepper stepperZ;
extern AccelStepper stepperW;

extern machine_progress_class machine;
extern nextion_extension nextion;

// myStepper.currentPosition();
// stepperX.runToPosition(); //  finish when motor reahced to setted position
// stepperX.run(); //finish when done 1 pulse
// stepperX.moveTo(4000);
// stepperY.distanceToGo();

void motor_set_speed_init();
void motor_set_acc_init();

void motor_forward(char axis, int value);
void motor_back(char axis, int value);
void motor_move(char axis, int value);

void motor_W_open();
void motor_W_close();
void motor_position(int xvalue, int yvalue, int zvalue);

int get_current_position(char axis);
void nx_axis_page_exit_event();
void motor_reset_stepper_current_position();

void homing_x_axis();
void homing_y_axis();
void homing_z_axis();
void homing_w_axis();
void homing_IO();
void homing_box();


void homing_machine();

void homing_machine_before_pick();
void homing_w_axis_picking();
void homing_z_axis_picking();
void homing_x_axis_picking();
void homing_y_axis_picking();

void open_box();
void close_box();
void on_dropper();
void off_dropper();
void on_camcylinder1();
void off_camcylinder1();
void on_camcylinder2();
void off_camcylinder2();
void on_airsuck();
void off_airsuck();
void on_airflow();
void off_airdlow();
void stop_x_motor();
void stop_y_motor();
void stop_z_motor();
void on_frame_led();
void off_frame_led();
void on_table_led();
void off_table_led();

bool checking_x_limit();
bool checking_y_limit();
bool checking_z_limit();

bool machine_parking(int x, int y, int z);
bool machine_unparking();

#endif
