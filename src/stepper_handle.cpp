#include "stepper_handle.h"

// Create a new instance of the AccelStepper class:
AccelStepper stepperX = AccelStepper(motorInterfaceType, XstepPin, XdirPin); // 800 steps/rev,
AccelStepper stepperY = AccelStepper(motorInterfaceType, YstepPin, YdirPin); // 800 Steps/rev, 4mm/rev => 10mm/2.5rev => 2000steps/10mm
AccelStepper stepperZ = AccelStepper(motorInterfaceType, ZstepPin, ZdirPin);
AccelStepper stepperW = AccelStepper(motorInterfaceType, WstepPin, WdirPin); // 2000 steps/rev, =>> maxspeed 1 rev/s

machine_progress_class machine;
nextion_extension nextions;
// int xresolution = 1000; //step/cm
// int yresolution = 1000;
// int zresolution = 500;
// int wresolution = 2000;

bool press_flagX = false;
bool press_flagY = false;
bool press_flagZ = false;
int add_x = 0;
int add_y = 0;
int add_z = 0;

void motor_set_speed_init()
{
  function_log();
  int speedx = machine.machine_axis_page.eeprom_get_speed_parameter('x');
  int speedy = machine.machine_axis_page.eeprom_get_speed_parameter('y');
  int speedz = machine.machine_axis_page.eeprom_get_speed_parameter('z');
  int speedw = machine.machine_axis_page.eeprom_get_speed_parameter('w');

  stepperX.setMaxSpeed(speedx * 30); // ?Steps/s
  Serial.println(" Speed X: " + String(speedx));

  stepperY.setMaxSpeed(speedy * 30); // ?Steps/s
  Serial.println(" Speed Y: " + String(speedy));

  stepperZ.setMaxSpeed(speedz * 10); // ?Steps/s
  Serial.println(" Speed Z: " + String(speedz));

  stepperW.setMaxSpeed(speedw * 10); // ?Steps/s
  Serial.println(" Speed W: " + String(speedw));
}
void motor_set_acc_init()
{
  function_log();
  int accx = machine.machine_axis_page.eeprom_get_acc_parameter('x');
  int accy = machine.machine_axis_page.eeprom_get_acc_parameter('y');
  int accz = machine.machine_axis_page.eeprom_get_acc_parameter('z');
  int accw = machine.machine_axis_page.eeprom_get_acc_parameter('w');

  stepperX.setAcceleration(accx * 30); // ?Step/s2
  Serial.println(" Acceleration X: " + String(accx));

  stepperY.setAcceleration(accy * 30); // ?Step/s2
  Serial.println(" Acceleration Y: " + String(accy));

  stepperZ.setAcceleration(accz * 10); // ?Step/s2
  Serial.println(" Acceleration Z: " + String(accz));

  stepperW.setAcceleration(accw * 10); // ?Step/s2
  Serial.println(" Acceleration W: " + String(accw));
}

void motor_forward(char axis, int value)
{
  function_log();
  int last_posx = machine.machine_axis_page.eeprom_read_position_parameters('x');
  int last_posy = machine.machine_axis_page.eeprom_read_position_parameters('y');
  int last_posz = machine.machine_axis_page.eeprom_read_position_parameters('z');

  int x_value = nextions.getNumberProperty("AXIS", "n0.val");
  int y_value = nextions.getNumberProperty("AXIS", "n1.val");
  int z_value = nextions.getNumberProperty("AXIS", "n2.val");
  Serial.println("x_value " + String(x_value) +
                 " y_value: " + String(y_value) +
                 " z_value: " + String(z_value) +
                 " value: " + String(value));
  switch (axis)
  {
  case 'x':
  {
    if (machine.init_flag == true) // First opening
    {
      Serial.println("Axis: " + String(axis) + " Value: " + String(value));
      Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
      Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
      Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
      Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
      stepperX.moveTo(stepperX.currentPosition() + value * machine.xresolution);
      machine.machine_axis_page.set_xposition(last_posx + value);
      machine.machine_axis_page.set_yposition(last_posy);
      machine.machine_axis_page.set_zposition(last_posz);
      machine.init_flag = false;
      press_flagX = true;
      add_x = add_x + value;
      machine.nx_set_xyz_position();
      break;
    }
    if (machine.init_flag == false) // Next openings
    {
      Serial.println("Axis: " + String(axis) + " Value: " + String(value));
      Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
      Serial.println(press_flagX ? "press_flagX: true" : "press_flagX: false");
      Serial.println(press_flagY ? "press_flagY: true" : "press_flagY: false");
      Serial.println(press_flagZ ? "press_flagZ: true" : "press_flagZ: false");
      Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
      Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
      Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
      stepperX.moveTo(stepperX.currentPosition() + value * machine.xresolution);
      if (press_flagX == false && press_flagY == false && press_flagZ == false) // 0 0 0
      {
        machine.machine_axis_page.set_xposition(last_posx + value);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      else if (press_flagX == true && press_flagY == false && press_flagZ == false) // 1 0 0
      {
        machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition + value);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      else if (press_flagX == false && press_flagY == true && press_flagZ == true) // 0 1 1
      {
        machine.machine_axis_page.set_xposition(last_posx + value);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == true && press_flagY == true && press_flagZ == true) // 1 1 1
      {
        machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition + value);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == false && press_flagY == false && press_flagZ == true) // 0 0 1
      {
        machine.machine_axis_page.set_xposition(last_posx + value);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == true && press_flagY == false && press_flagZ == true) // 1 0 1
      {
        machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition + value);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == false && press_flagY == true && press_flagZ == false) // 0 1 0
      {
        machine.machine_axis_page.set_xposition(last_posx + value);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      else // if (press_flagX == true && press_flagY == true && press_flagZ == false) // 1 1 0
      {
        machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition + value);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      press_flagX = true;
      add_x = add_x + value;
      machine.nx_set_xyz_position();
      break;
    }
  }
  case 'y':
  {
    if (machine.init_flag == true) // First opening
    {
      Serial.println("Axis: " + String(axis) + " Value: " + String(value));
      Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
      Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
      Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
      Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
      stepperY.moveTo(stepperY.currentPosition() + value * machine.yresolution);
      machine.machine_axis_page.set_xposition(last_posx);
      machine.machine_axis_page.set_yposition(last_posy + value);
      machine.machine_axis_page.set_zposition(last_posz);
      machine.init_flag = false;
      press_flagY = true;
      add_y = add_y + value;
      machine.nx_set_xyz_position();
      break;
    }
    if (machine.init_flag == false) // Next openings
    {
      Serial.println("Axis: " + String(axis) + " Value: " + String(value));
      Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
      Serial.println(press_flagX ? "press_flagX: true" : "press_flagX: false");
      Serial.println(press_flagY ? "press_flagY: true" : "press_flagY: false");
      Serial.println(press_flagZ ? "press_flagZ: true" : "press_flagZ: false");
      Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
      Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
      Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
      stepperY.moveTo(stepperY.currentPosition() + value * machine.yresolution);
      if (press_flagX == false && press_flagY == false && press_flagZ == false) //0 0 0
      {
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(last_posy + value);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      else if (press_flagX == false && press_flagY == true && press_flagZ == false) //0 1 0
      {
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition + value);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      else if (press_flagX == true && press_flagY == false && press_flagZ == true) //1 0 1
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(last_posy + value);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == true && press_flagY == true && press_flagZ == true) // 1 1 1
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition + value);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == false && press_flagY == false && press_flagZ == true) // 0 0 1
      {
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(last_posy + value);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == false && press_flagY == true && press_flagZ == true) // 0 1 1
      {
        machine.machine_axis_page.set_xposition(last_posz);
        machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition + value);
        machine.machine_axis_page.set_zposition(last_posz + add_z);
      }
      else if (press_flagX == true && press_flagY == false && press_flagZ == false) // 1 0 0
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(last_posy + value);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      else // if (press_flagX == true && press_flagY == true && press_flagZ == false) // 1 1 0
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition + value);
        machine.machine_axis_page.set_zposition(last_posz);
      }
      press_flagY = true;
      add_y = add_y + value;
      machine.nx_set_xyz_position();
      break;
    }
  }
  case 'z':
  {
    if (z_value >= 0 || (z_value + value) > 0)
    {
      Serial.println("RETURN");
      return;
    }
    else
    {
      if (machine.init_flag == true) // First opening
      {
        Serial.println("Axis: " + String(axis) + " Value: " + String(value));
        Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
        Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
        Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
        Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
        stepperZ.moveTo(stepperZ.currentPosition() + value * machine.zresolution);
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz + value);
        machine.init_flag = false;
        press_flagZ = true;
        add_z = add_z + value;
        machine.nx_set_xyz_position();
        break;
      }
      if (machine.init_flag == false) // Next openings
      {
        Serial.println("Axis: " + String(axis) + " Value: " + String(value));
        Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
        Serial.println(press_flagX ? "press_flagX: true" : "press_flagX: false");
        Serial.println(press_flagY ? "press_flagY: true" : "press_flagY: false");
        Serial.println(press_flagZ ? "press_flagZ: true" : "press_flagZ: false");
        Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
        Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
        Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
        stepperZ.moveTo(stepperZ.currentPosition() + value * machine.zresolution);
        if (press_flagX == false && press_flagY == false && press_flagZ == false) // 0 0 0
        {
          machine.machine_axis_page.set_xposition(last_posx);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(last_posz + value);
        }
        else if (press_flagX == false && press_flagY == false && press_flagZ == true) // 0 0 1
        {
          machine.machine_axis_page.set_xposition(last_posx);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition + value);
        }
        else if (press_flagX == true && press_flagY == true && press_flagZ == false) // 1 1 0
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(last_posz + value);
        }
        else if (press_flagX == true && press_flagY == true && press_flagZ == true) // 1 1 1
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition + value);
        }
        else if (press_flagX == true && press_flagY == false && press_flagZ == false) // 1 0 0
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(last_posz + value);
        }
        else if (press_flagX == true && press_flagY == false && press_flagZ == true) // 1 0 1
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition + value);
        }
        else if (press_flagX == false && press_flagY == true && press_flagZ == false) // 0 1 0
        {
          machine.machine_axis_page.set_xposition(last_posz);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(last_posz + value);
        }
        else if (press_flagX == false && press_flagY == true && press_flagZ == true) // 0 1 1
        {
          machine.machine_axis_page.set_xposition(last_posx);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition + value);
        }
        press_flagZ = true;
        add_z = add_z + value;
        machine.nx_set_xyz_position();
        break;
      }
    }
  }
  }
  stepperX.runToPosition();
  stepperY.runToPosition();
  stepperZ.runToPosition();
}
void motor_back(char axis, int value)
{
  function_log();
  int last_posx = machine.machine_axis_page.eeprom_read_position_parameters('x');
  int last_posy = machine.machine_axis_page.eeprom_read_position_parameters('y');
  int last_posz = machine.machine_axis_page.eeprom_read_position_parameters('z');

  int x_value = nextions.getNumberProperty("AXIS", "n0.val");
  int y_value = nextions.getNumberProperty("AXIS", "n1.val");
  int z_value = nextions.getNumberProperty("AXIS", "n2.val");
  Serial.println("x_value " + String(x_value) +
                 " y_value: " + String(y_value) +
                 " z_value: " + String(z_value) +
                 " value: " + String(value));
  switch (axis)
  {
  case 'x':
  {
    if (x_value <= 0 || (x_value - value) < 0)
    {
      Serial.println("RETURN");
      return;
    }
    else
    {
      if (machine.init_flag == true) // First opening
      {
        Serial.println("Axis: " + String(axis) + " Value: " + String(value));
        Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
        Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
        Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
        Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
        stepperX.moveTo(stepperX.currentPosition() - value * machine.xresolution);
        machine.machine_axis_page.set_xposition(last_posx - value);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz);
        machine.init_flag = false;
        press_flagX = true;
        add_x = add_x - value;
        machine.nx_set_xyz_position();
        break;
      }
      if (machine.init_flag == false) // Next openings
      {
        Serial.println("Axis: " + String(axis) + " Value: " + String(value));
        Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
        Serial.println(press_flagX ? "press_flagX: true" : "press_flagX: false");
        Serial.println(press_flagY ? "press_flagY: true" : "press_flagY: false");
        Serial.println(press_flagZ ? "press_flagZ: true" : "press_flagZ: false");
        Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
        Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
        Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
        stepperX.moveTo(stepperX.currentPosition() - value * machine.xresolution);
        if (press_flagX == false && press_flagY == false && press_flagZ == false) // 0 0 0
        {
          machine.machine_axis_page.set_xposition(last_posx - value);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        else if (press_flagX == true && press_flagY == false && press_flagZ == false) // 1 0 0
        {
          machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition - value);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        else if (press_flagX == false && press_flagY == true && press_flagZ == true) // 0 1 1
        {
          machine.machine_axis_page.set_xposition(last_posx - value);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == true && press_flagY == true && press_flagZ == true) // 1 1 1
        {
          machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition - value);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == false && press_flagY == false && press_flagZ == true) // 0 0 1
        {
          machine.machine_axis_page.set_xposition(last_posx - value);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == true && press_flagY == false && press_flagZ == true) // 1 0 1
        {
          machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition - value);
          machine.machine_axis_page.set_yposition(last_posy);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == false && press_flagY == true && press_flagZ == false) // 0 1 0
        {
          machine.machine_axis_page.set_xposition(last_posx - value);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        else // if (press_flagX == true && press_flagY == true && press_flagZ == false) // 1 1 0
        {
          machine.machine_axis_page.set_xposition(machine.machine_axis_page.xposition - value);
          machine.machine_axis_page.set_yposition(last_posy + add_y);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        press_flagX = true;
        add_x = add_x - value;
        machine.nx_set_xyz_position();
        break;
      }
    }
  }
  case 'y':
  {
    if (y_value <= 0 || (y_value - value) < 0)
    {
      Serial.println("RETURN");
      return;
    }
    else
    {
      if (machine.init_flag == true) // First opening
      {
        Serial.println("Axis: " + String(axis) + " Value: " + String(value));
        Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
        Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
        Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
        Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
        stepperY.moveTo(stepperY.currentPosition() - value * machine.yresolution);
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(last_posy - value);
        machine.machine_axis_page.set_zposition(last_posz);
        machine.init_flag = false;
        press_flagY = true;
        add_y = add_y - value;
        machine.nx_set_xyz_position();
        break;
      }
      if (machine.init_flag == false) // Next openings
      {
        Serial.println("Axis: " + String(axis) + " Value: " + String(value));
        Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
        Serial.println(press_flagX ? "press_flagX: true" : "press_flagX: false");
        Serial.println(press_flagY ? "press_flagY: true" : "press_flagY: false");
        Serial.println(press_flagZ ? "press_flagZ: true" : "press_flagZ: false");
        Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
        Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
        Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
        stepperY.moveTo(stepperY.currentPosition() - value * machine.yresolution);
        if (press_flagX == false && press_flagY == false && press_flagZ == false) //0 0 0
        {
          machine.machine_axis_page.set_xposition(last_posx);
          machine.machine_axis_page.set_yposition(last_posy - value);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        else if (press_flagX == false && press_flagY == true && press_flagZ == false) //0 1 0
        {
          machine.machine_axis_page.set_xposition(last_posx);
          machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition - value);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        else if (press_flagX == true && press_flagY == false && press_flagZ == true) //1 0 1
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(last_posy - value);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == true && press_flagY == true && press_flagZ == true) // 1 1 1
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition - value);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == false && press_flagY == false && press_flagZ == true) // 0 0 1
        {
          machine.machine_axis_page.set_xposition(last_posx);
          machine.machine_axis_page.set_yposition(last_posy - value);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == false && press_flagY == true && press_flagZ == true) // 0 1 1
        {
          machine.machine_axis_page.set_xposition(last_posz);
          machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition - value);
          machine.machine_axis_page.set_zposition(last_posz + add_z);
        }
        else if (press_flagX == true && press_flagY == false && press_flagZ == false) // 1 0 0
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(last_posy - value);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        else // if (press_flagX == true && press_flagY == true && press_flagZ == false) // 1 1 0
        {
          machine.machine_axis_page.set_xposition(last_posx + add_x);
          machine.machine_axis_page.set_yposition(machine.machine_axis_page.yposition - value);
          machine.machine_axis_page.set_zposition(last_posz);
        }
        press_flagY = true;
        add_y = add_y - value;
        machine.nx_set_xyz_position();
        break;
      }
    }
  }
  case 'z':
  {

    if (machine.init_flag == true) // First opening
    {
      Serial.println("Axis: " + String(axis) + " Value: " + String(value));
      Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
      Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
      Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
      Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
      stepperZ.moveTo(stepperZ.currentPosition() - value * machine.zresolution);
      machine.machine_axis_page.set_xposition(last_posx);
      machine.machine_axis_page.set_yposition(last_posy);
      machine.machine_axis_page.set_zposition(last_posz - value);
      machine.init_flag = false;
      press_flagZ = true;
      add_z = add_z - value;
      machine.nx_set_xyz_position();
      break;
    }
    if (machine.init_flag == false) // Next openings
    {
      Serial.println("Axis: " + String(axis) + " Value: " + String(value));
      Serial.println(machine.init_flag ? "machine.init_flag: true" : "machine.init_flag: false");
      Serial.println(press_flagX ? "press_flagX: true" : "press_flagX: false");
      Serial.println(press_flagY ? "press_flagY: true" : "press_flagY: false");
      Serial.println(press_flagZ ? "press_flagZ: true" : "press_flagZ: false");
      Serial.println("Funtion: " + String(__func__) + " Last posx: " + String(last_posx) + " Last posy: " + String(last_posy) + " Last posz: " + String(last_posz));
      Serial.println("Funtion: " + String(__func__) + " machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
      Serial.println("Funtion: " + String(__func__) + " addx: " + String(add_x) + " addy: " + String(add_y) + " addz: " + String(add_z));
      stepperZ.moveTo(stepperZ.currentPosition() - value * machine.zresolution);
      if (press_flagX == false && press_flagY == false && press_flagZ == false) // 0 0 0
      {
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz - value);
      }
      else if (press_flagX == false && press_flagY == false && press_flagZ == true) // 0 0 1
      {
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition - value);
      }
      else if (press_flagX == true && press_flagY == true && press_flagZ == false) // 1 1 0
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(last_posz - value);
      }
      else if (press_flagX == true && press_flagY == true && press_flagZ == true) // 1 1 1
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition - value);
      }
      else if (press_flagX == true && press_flagY == false && press_flagZ == false) // 1 0 0
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(last_posz - value);
      }
      else if (press_flagX == true && press_flagY == false && press_flagZ == true) // 1 0 1
      {
        machine.machine_axis_page.set_xposition(last_posx + add_x);
        machine.machine_axis_page.set_yposition(last_posy);
        machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition - value);
      }
      else if (press_flagX == false && press_flagY == true && press_flagZ == false) // 0 1 0
      {
        machine.machine_axis_page.set_xposition(last_posz);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(last_posz - value);
      }
      else if (press_flagX == false && press_flagY == true && press_flagZ == true) // 0 1 1
      {
        machine.machine_axis_page.set_xposition(last_posx);
        machine.machine_axis_page.set_yposition(last_posy + add_y);
        machine.machine_axis_page.set_zposition(machine.machine_axis_page.zposition - value);
      }
      press_flagZ = true;
      add_z = add_z - value;
      machine.nx_set_xyz_position();
      break;
    }
  }
  }
  stepperX.runToPosition();
  stepperY.runToPosition();
  stepperZ.runToPosition();
}

void motor_W_open()
{
  function_log();
  stepperW.moveTo(stepperW.currentPosition() - machine.wresolution * 11);
  stepperW.runToPosition();
  machine.machine_axis_page.set_w_status(true);
  machine.machine_axis_page.eeprom_put_w_status();
  machine.nx_set_w_needle_table_button_status();
}
void motor_W_close()
{
  function_log();
  stepperW.moveTo(stepperW.currentPosition() + machine.wresolution * 11);
  stepperW.runToPosition();
  machine.machine_axis_page.set_w_status(false);
  machine.machine_axis_page.eeprom_put_w_status();
  machine.nx_set_w_needle_table_button_status();
}
int get_current_position(char axis)
{
  function_log();
  if (axis == 'x')
  {
    return stepperX.currentPosition();
  }
  if (axis == 'y')
  {
    return stepperY.currentPosition();
  }
  else
  {
    return stepperZ.currentPosition();
  }
}
void motor_reset_stepper_current_position()
{
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  stepperZ.setCurrentPosition(0);
}
void nx_axis_page_exit_event()
{
  function_log();
  // EEPROM.begin();
  if (press_flagX == true)
  {
    //machine.machine_axis_page.set_xposition(get_current_position('x')/machine.xresolution;
    Serial.println("Funtion: " + String(__func__) + "machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
    machine.machine_axis_page.eeprom_write_position_parameter('x', machine.machine_axis_page.xposition);
    machine.machine_axis_page.eeprom_write_position_parameter('y', machine.machine_axis_page.yposition);
    machine.machine_axis_page.eeprom_write_position_parameter('z', machine.machine_axis_page.zposition);
    // eeprom_write<int>(machine.machine_axis_page.xposition, X_POSITION_EEPROM_ADD);
    // eeprom_write<int>(machine.machine_axis_page.yposition, Y_POSITION_EEPROM_ADDR);
    // eeprom_write<int>(machine.machine_axis_page.zposition, Z_POSITION_EEPROM_ADDRE);
    press_flagX = false;
  }
  if (press_flagY == true)
  {
    //machine.machine_axis_page.set_yposition(get_current_position('y')/machine.yresolution;
    Serial.println("Funtion: " + String(__func__) + "machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
    machine.machine_axis_page.eeprom_write_position_parameter('x', machine.machine_axis_page.xposition);
    machine.machine_axis_page.eeprom_write_position_parameter('y', machine.machine_axis_page.yposition);
    machine.machine_axis_page.eeprom_write_position_parameter('z', machine.machine_axis_page.zposition);
    // eeprom_write<int>(machine.machine_axis_page.xposition, X_POSITION_EEPROM_ADD);
    // eeprom_write<int>(machine.machine_axis_page.yposition, Y_POSITION_EEPROM_ADDR);
    // eeprom_write<int>(machine.machine_axis_page.zposition, Z_POSITION_EEPROM_ADDRE);
    press_flagY = false;
  }
  if (press_flagZ == true)
  {
    //machine.machine_axis_page.set_zposition(get_current_position('z')/machine.zresolution;
    Serial.println("Funtion: " + String(__func__) + "machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
    machine.machine_axis_page.eeprom_write_position_parameter('x', machine.machine_axis_page.xposition);
    machine.machine_axis_page.eeprom_write_position_parameter('y', machine.machine_axis_page.yposition);
    machine.machine_axis_page.eeprom_write_position_parameter('z', machine.machine_axis_page.zposition);
    // eeprom_write<int>(machine.machine_axis_page.xposition, X_POSITION_EEPROM_ADD);
    // eeprom_write<int>(machine.machine_axis_page.yposition, Y_POSITION_EEPROM_ADDR);
    // eeprom_write<int>(machine.machine_axis_page.zposition, Z_POSITION_EEPROM_ADDRE);
    press_flagZ = false;
  }
  else
  {
    Serial.println("Funtion: " + String(__func__) + "machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
    Serial.println("No Press, No change - At line: " + String(__LINE__));
    press_flagX = false;
    press_flagY = false;
    press_flagZ = false;
  }
  // EEPROM.end();
  machine.init_flag = false;
  machine.machine_axis_page.reset();
  add_x = 0;
  add_y = 0;
  add_z = 0;
}
void motor_reset_nx_position()
{
  function_log();
  machine.machine_axis_page.reset();
  add_x = 0;
  add_y = 0;
  add_z = 0;
  Serial.println("Funtion: " + String(__func__) + " Reset xposition: " + String(machine.machine_axis_page.xposition) + " Reset yposition: " + String(machine.machine_axis_page.yposition) + " Reset zposition: " + String(machine.machine_axis_page.zposition));
  machine.machine_axis_page.eeprom_write_position_parameter('x', machine.machine_axis_page.xposition);
  machine.machine_axis_page.eeprom_write_position_parameter('y', machine.machine_axis_page.yposition);
  machine.machine_axis_page.eeprom_write_position_parameter('z', machine.machine_axis_page.zposition);
  // eeprom_write<int>(machine.machine_axis_page.xposition, X_POSITION_EEPROM_ADD);
  // eeprom_write<int>(machine.machine_axis_page.yposition, Y_POSITION_EEPROM_ADDR);
  // eeprom_write<int>(machine.machine_axis_page.zposition, Z_POSITION_EEPROM_ADDRE);
}