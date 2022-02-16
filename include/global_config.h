#ifndef global_config_h
#define global_config_h
#include <Arduino.h>

#define EEPROM_START_PARAMETERS_ADD 0
#define EEPROM_ETHERNET_START_ADD 60
#define EEPROM_IDENTITY_START_ADD 98

#ifndef function_log
// #define function_log(...) Serial.print(("[USER_DEBUG] ----> Func: %s at line: %d\r\n", __func__, __LINE__))
#define function_log(...) Serial.println("Func: " + String(__func__) + " At line: " + String(__LINE__))
#endif
//page 07
#define NEX_BUT_X_FORWARD_1 0x00
#define NEX_BUT_X_FORWARD_10 0x01
#define NEX_BUT_X_BACK_1 0x06
#define NEX_BUT_X_BACK_10 0x07

#define NEX_BUT_Y_FORWARD_1 0x02
#define NEX_BUT_Y_FORWARD_10 0x03
#define NEX_BUT_Y_BACK_1 0x08
#define NEX_BUT_Y_BACK_10 0x09

#define NEX_BUT_Z_FORWARD_1 0x04
#define NEX_BUT_Z_FORWARD_10 0x05
#define NEX_BUT_Z_BACK_1 0x10
#define NEX_BUT_Z_BACK_10 0x11

#define NEX_BUT_W_OPEN 0x17
#define NEX_BUT_W_CLOSE 0x18

#define NEX_BUT_SAVE_OFFSET 0x19
#define NEX_BUT_SAVE_PLUS 0x20
#define NEX_BUT_SAVE_SPEED 0x21
#define NEX_BUT_SAVE_ACC 0x22

#define NEX_BUT_RESET_ALL_AXIS 0x23
#define NEX_BUT_RESET_X 0x24
#define NEX_BUT_RESET_Y 0x25
#define NEX_BUT_RESET_Z 0x26
#define NEX_BUT_RESET_W 0x27

#define NEX_AXIS_PAGE_INIT 0xD0
#define NEX_AXIS_PAGE_EXIT 0xD1

#define NEX_KEYBOARD_PAGE_INIT 0xD2
#define NEX_KEYBOARD_PAGE_EXIT 0xD3

#define NEX_RESET_DEVICE1 0xE3


//page 08
#define NEX_CONNECTION_PAGE_INIT 0xD4
#define NEX_CONNECTION_PAGE_EXIT 0xD5
#define NX_BUT_SAVE_MAC 0x28
#define NX_BUT_SAVE_ETHERNET_PARAMETERS 0x29

#define NEX_KEYBOARD2_PAGE_INIT 0xD8
#define NEX_KEYBOARD2_PAGE_EXIT 0xD9

#define NEX_RESET_DEVICE2 0xE4


//page 10
#define NEX_ABOUT_PAGE_INIT 0xD6
#define NEX_ABOUT_PAGE_EXIT 0xD7
#define NX_BUT_SAVE_BUILDING 0x30
#define NX_BUT_SAVE_DEVICE_ID 0x31
#define NX_BUT_SAVE_DEVICE_NAME 0x32
#define NX_BUT_TABLE_LED 0x33
#define NX_BUT_FRAME_LED 0x34

#define NEX_KEYBOARD3_PAGE_INIT 0xE1
#define NEX_KEYBOARD3_PAGE_EXIT 0xE2

#define NEX_RESET_DEVICE3 0xE5

#define XdirPin 2
#define XstepPin 3

#define YdirPin 10
#define YstepPin 11

#define ZdirPin 6
#define ZstepPin 7

#define WdirPin 8
#define WstepPin 9

#define motorInterfaceType 1

#define HomeX 26
#define HomeY 27
#define HomeZ 28

#define OvertravelX1 30
#define OvertravelX2 31
#define OvertravelY1 32
#define OvertravelY2 33

#define OvertravelZ1 34
#define OvertravelZ2 35
#define OvertravelW1 36
#define OvertravelW2 37

#define PickerDetector 39
#define DropperDetector 40
#define NeedleSucked 41
#define AirSuplied 42

#define MachineLED 44
#define TableLED 45
#define DropCylinder 46
#define CameraCylinder 47

#define AirFlowPicker 22
#define AirSuckPicker 23
 

#endif