#include "machine_handle.h"

// Create a new instance of the AccelStepper class:
AccelStepper stepperX = AccelStepper(motorInterfaceType, XstepPin, XdirPin); // 400 steps/rev, 10mm/rev => 10mm/1rev => 400steps/10mm
AccelStepper stepperY = AccelStepper(motorInterfaceType, YstepPin, YdirPin); // 400 Steps/rev, 10mm/rev => 10mm/1rev => 400steps/10mm
AccelStepper stepperZ = AccelStepper(motorInterfaceType, ZstepPin, ZdirPin); // 400 steps/rev, 4mm/rev => 4mm/1rev => 1000steps/10mm
AccelStepper stepperW = AccelStepper(motorInterfaceType, WstepPin, WdirPin); // 2000 steps/rev

machine_progress_class machine;
nextion_extension nextion;

// int xresolution = 1000; //step/cm
// int yresolution = 1000;
// int zresolution = 500;
// int wresolution = 2000;

bool press_flagX = false;
bool press_flagY = false;
bool press_flagZ = false;

void motor_set_speed_init()
{
  function_log();
  int speedx = machine.machine_axis_page.x_speed;
  int speedy = machine.machine_axis_page.y_speed;
  int speedz = machine.machine_axis_page.z_speed;
  int speedw = machine.machine_axis_page.w_speed;

  stepperX.setMaxSpeed(speedx * 30); // ?Steps/s
  Serial.println("Speed X: " + String(speedx));
  stepperY.setMaxSpeed(speedy * 30); // ?Steps/s
  Serial.println("Speed Y: " + String(speedy));
  stepperZ.setMaxSpeed(speedz * 10); // ?Steps/s
  Serial.println("Speed Z: " + String(speedz));
  stepperW.setMaxSpeed(speedw * 10); // ?Steps/s
  Serial.println("Speed W: " + String(speedw));
}
void motor_set_acc_init()
{
  function_log();
  int accx = machine.machine_axis_page.x_acceleration;
  int accy = machine.machine_axis_page.y_acceleration;
  int accz = machine.machine_axis_page.z_acceleration;
  int accw = machine.machine_axis_page.w_acceleration;

  stepperX.setAcceleration(accx * 30); // ?Step/s2
  Serial.println("Accel X: " + String(accx));
  stepperY.setAcceleration(accy * 30); // ?Step/s2
  Serial.println("Accel Y: " + String(accy));
  stepperZ.setAcceleration(accz * 10); // ?Step/s2
  Serial.println("Accel Z: " + String(accz));
  stepperW.setAcceleration(accw * 10); // ?Step/s2
  Serial.println("Accel W: " + String(accw));
}

void motor_move(char axis, int value)
{
  function_log();
  switch (axis)
  {
  case 'x':
  {
    if (machine.overtravel_flag)
    {
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      break;
    }
    else
    {
      bool status = true;
      stepperX.moveTo(stepperX.currentPosition() + value * machine.xresolution);
      machine.init_flag = false;
      press_flagX = true;
      while (stepperX.distanceToGo() != 0)
      {
        status = checking_x_limit();
        if (!status)
        {
          break;
        }
        else
        {
          stepperX.run();
        }
      }
      if (status)
      {
        machine.machine_axis_page.xposition = machine.machine_axis_page.xposition + value;
        machine.machine_connection_page.ethernet_parameters.set_parameter("xpos");
        machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.xposition);
        machine.machine_connection_page.udp_reply_para();
        machine.nx_set_xyz_position();
      }
      break;
    }
  }
  case 'y':
  {
    if (machine.overtravel_flag)
    {
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      break;
    }
    else
    {
      bool status = true;
      stepperY.moveTo(stepperY.currentPosition() + value * machine.yresolution);
      machine.init_flag = false;
      press_flagY = true;
      while (stepperY.distanceToGo() != 0)
      {
        status = checking_y_limit();
        if (!status)
        {
          break;
        }
        else
        {
          stepperY.run();
        }
      }
      if (status)
      {
        machine.machine_axis_page.yposition = machine.machine_axis_page.yposition + value;
        machine.machine_connection_page.ethernet_parameters.set_parameter("ypos");
        machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.yposition);
        machine.machine_connection_page.udp_reply_para();
        machine.nx_set_xyz_position();
      }
      break;
    }
  }
  case 'z':
  {
    if (machine.overtravel_flag)
    {
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      break;
    }
    else
    {
      bool status = true;
      stepperZ.moveTo(stepperZ.currentPosition() + value * machine.zresolution);
      machine.init_flag = false;
      press_flagZ = true;
      while (stepperZ.distanceToGo() != 0)
      {
        status = checking_z_limit();
        if (!status)
        {
          break;
        }
        else
        {
          stepperZ.run();
        }
      }
      if (status)
      {
        machine.machine_axis_page.zposition = machine.machine_axis_page.zposition + value;
        machine.machine_connection_page.ethernet_parameters.set_parameter("zpos");
        machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.zposition);
        machine.machine_connection_page.udp_reply_para();
        machine.nx_set_xyz_position();
      }
      break;
    }
  }
  }
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
void nx_axis_page_exit_event()
{
  function_log();
  if (press_flagX || press_flagY || press_flagZ)
  {
    // Serial.println("Funtion: " + String(__func__) + "machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
    // machine.machine_axis_page.eeprom_write_position_parameter('x', machine.machine_axis_page.xposition);
    // machine.machine_axis_page.eeprom_write_position_parameter('y', machine.machine_axis_page.yposition);
    // machine.machine_axis_page.eeprom_write_position_parameter('z', machine.machine_axis_page.zposition);
    press_flagZ = false;
  }
  else
  {
    // Serial.println("Funtion: " + String(__func__) + "machine.machine_axis_page.xposition: " + String(machine.machine_axis_page.xposition) + " machine.machine_axis_page.yposition: " + String(machine.machine_axis_page.yposition) + " machine.machine_axis_page.zposition: " + String(machine.machine_axis_page.zposition));
    // Serial.println("No Press, No change - At line: " + String(__LINE__));
    press_flagX = false;
    press_flagY = false;
    press_flagZ = false;
  }
  machine.init_flag = false;
  // machine.machine_axis_page.reset();
  // add_x = 0;
  // add_y = 0;
  // add_z = 0;
}

void homing_machine()
{
  homing_w_axis();
  homing_z_axis();
  homing_x_axis();
  homing_y_axis();
  homing_IO();
}
void homing_x_axis()
{
  long initial_homing = -1;
  stepperX.setMaxSpeed(1000);     // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperX.setAcceleration(1000); // Set Acceleration of Stepper
  Serial.print("Stepper X is Homing . . . ");
  while (!digitalRead(HomeX))
  {                                  // Make the Stepper move CCW until the switch is activated
    stepperX.moveTo(initial_homing); // Set the position to move to
    initial_homing--;                // Decrease by 1 for next move if needed
    stepperX.run();                  // Start moving the stepper
    delay(1);
  }
  stepperX.setCurrentPosition(0); // Set the current position as zero for now
  stepperX.setMaxSpeed(100);      // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperX.setAcceleration(100);  // Set Acceleration of Stepper
  initial_homing = 1;
  while (digitalRead(HomeX))
  { // Make the Stepper move CW until the switch is deactivated
    stepperX.moveTo(initial_homing);
    stepperX.run();
    initial_homing++;
    delay(1);
  }
  stepperX.setCurrentPosition(0);
  machine.machine_axis_page.set_position_x(0);
  Serial.println("Homing X Completed");
}
void homing_y_axis()
{
  long initial_homing = -1;
  stepperY.setMaxSpeed(1000);     // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperY.setAcceleration(1000); // Set Acceleration of Stepper

  // Start Homing procedure of Stepper Motor at startup

  Serial.print("Stepper Y is Homing . . . ");

  while (!digitalRead(HomeY))
  {                                  // Make the Stepper move CCW until the switch is activated
    stepperY.moveTo(initial_homing); // Set the position to move to
    initial_homing--;                // Decrease by 1 for next move if needed
    stepperY.run();                  // Start moving the stepper
    delay(1);
  }

  stepperY.setCurrentPosition(0); // Set the current position as zero for now
  stepperY.setMaxSpeed(100);      // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperY.setAcceleration(100);  // Set Acceleration of Stepper
  initial_homing = 1;

  while (digitalRead(HomeY))
  { // Make the Stepper move CW until the switch is deactivated
    stepperY.moveTo(initial_homing);
    stepperY.run();
    initial_homing++;
    delay(1);
  }

  stepperY.setCurrentPosition(0);
  machine.machine_axis_page.set_position_y(0);
  Serial.println("Homing Y Completed");
}
void homing_z_axis()
{
  long initial_homing = 1;
  stepperZ.setMaxSpeed(1000);     // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperZ.setAcceleration(1000); // Set Acceleration of Stepper

  // Start Homing procedure of Stepper Motor at startup

  Serial.print("Stepper Z is Homing . . . ");

  while (!digitalRead(HomeZ))
  {                                  // Make the Stepper move CCW until the switch is activated
    stepperZ.moveTo(initial_homing); // Set the position to move to
    initial_homing++;                // Decrease by 1 for next move if needed
    stepperZ.run();                  // Start moving the stepper
    delay(1);
  }

  stepperZ.setCurrentPosition(0); // Set the current position as zero for now
  stepperZ.setMaxSpeed(100);      // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperZ.setAcceleration(100);  // Set Acceleration of Stepper
  initial_homing = -1;

  while (digitalRead(HomeZ))
  { // Make the Stepper move CW until the switch is deactivated
    stepperZ.moveTo(initial_homing);
    stepperZ.run();
    initial_homing--;
    delay(1);
  }

  stepperZ.setCurrentPosition(0);
  machine.machine_axis_page.set_position_z(0);
  Serial.println("Homing Z Completed");
}
void homing_w_axis()
{
  stepperW.setMaxSpeed(5000);
  stepperW.setAcceleration(5000);
  stepperW.moveTo(stepperW.currentPosition() + machine.wresolution * 100);
  Serial.print("Stepper W is Homing . . . ");
  while (1)
  {
    if (digitalRead(OvertravelW2) == HIGH)
    {
      stepperW.stop();
      stepperW.setCurrentPosition(0);
      break;
    }
    stepperW.run();
  }
  machine.machine_axis_page.set_w_status(false);
  Serial.println("Homing W Completed");
}
void homing_IO()
{
  close_box();
  off_dropper();
  off_airdlow();
  off_airsuck();
  off_camcylinder1();
  off_camcylinder2();
  off_frame_led();
  off_table_led();
}

void open_box()
{
  digitalWrite(RecycleBox, HIGH);
  machine.machine_axis_page.set_box_status(true);
}
void close_box()
{
  digitalWrite(RecycleBox, LOW);
  machine.machine_axis_page.set_box_status(false);
}
void on_dropper()
{
  digitalWrite(DropCylinder, HIGH);
  machine.machine_axis_page.set_dropper_status(true);
}
void off_dropper()
{
  digitalWrite(DropCylinder, LOW);
  machine.machine_axis_page.set_dropper_status(false);
}
void on_camcylinder1()
{
  digitalWrite(CameradDropCylinder1, HIGH);
  machine.machine_axis_page.set_camcylinder1_status(true);
}
void off_camcylinder1()
{
  digitalWrite(CameradDropCylinder1, LOW);
  machine.machine_axis_page.set_camcylinder1_status(false);
}
void on_camcylinder2()
{
  digitalWrite(CameradDropCylinder2, HIGH);
  machine.machine_axis_page.set_camcylinder2_status(true);
}
void off_camcylinder2()
{
  digitalWrite(CameradDropCylinder2, LOW);
  machine.machine_axis_page.set_camcylinder2_status(false);
}
void on_airsuck()
{
  digitalWrite(AirSuckPicker, HIGH);
  machine.machine_axis_page.set_airsuck_status(true);
}
void off_airsuck()
{
  digitalWrite(AirSuckPicker, LOW);
  machine.machine_axis_page.set_airsuck_status(false);
}
void on_airflow()
{
  digitalWrite(AirFlowPicker, HIGH);
  machine.machine_axis_page.set_airflow_status(true);
}
void off_airdlow()
{
  digitalWrite(AirFlowPicker, LOW);
  machine.machine_axis_page.set_airflow_status(false);
}
void on_frame_led()
{
  digitalWrite(MachineLED, HIGH);
  machine.machine_about_page.set_frame_led_flag_status(true);
}
void off_frame_led()
{
  digitalWrite(MachineLED, LOW);
  machine.machine_about_page.set_frame_led_flag_status(false);
}
void on_table_led()
{
  digitalWrite(TableLED, HIGH);
  machine.machine_about_page.set_table_led_flag_status(true);
}
void off_table_led()
{
  digitalWrite(TableLED, LOW);
  machine.machine_about_page.set_table_led_flag_status(false);
}
void homing_machine_before_pick()
{
  homing_w_axis_picking();
  homing_z_axis_picking();
  homing_x_axis_picking();
  homing_y_axis_picking();
}
void homing_x_axis_picking()
{
  long initial_homing = -1;
  // Serial.print("Stepper X is Homing . . . ");
  while (!digitalRead(HomeX))
  {                                  // Make the Stepper move CCW until the switch is activated
    stepperX.moveTo(initial_homing); // Set the position to move to
    initial_homing--;                // Decrease by 1 for next move if needed
    stepperX.run();                  // Start moving the stepper
    delay(1);
  }
  stepperX.setCurrentPosition(0); // Set the current position as zero for now
  initial_homing = 1;
  while (digitalRead(HomeX))
  { // Make the Stepper move CW until the switch is deactivated
    stepperX.moveTo(initial_homing);
    stepperX.run();
    initial_homing++;
    delay(1);
  }
  stepperX.setCurrentPosition(0);
  Serial.println("Homing X Completed");
}
void homing_y_axis_picking()
{
  long initial_homing = -1;
  // Serial.print("Stepper Y is Homing . . . ");
  while (!digitalRead(HomeY))
  {                                  // Make the Stepper move CCW until the switch is activated
    stepperY.moveTo(initial_homing); // Set the position to move to
    initial_homing--;                // Decrease by 1 for next move if needed
    stepperY.run();                  // Start moving the stepper
    delay(1);
  }
  stepperY.setCurrentPosition(0); // Set the current position as zero for now
  initial_homing = 1;
  while (digitalRead(HomeY))
  { // Make the Stepper move CW until the switch is deactivated
    stepperY.moveTo(initial_homing);
    stepperY.run();
    initial_homing++;
    delay(1);
  }
  stepperY.setCurrentPosition(0);
  Serial.println("Homing Y Completed");
}
void homing_z_axis_picking()
{
  long initial_homing = 1;
  // Serial.print("Stepper Z is Homing . . . ");
  while (!digitalRead(HomeZ))
  {                                  // Make the Stepper move CCW until the switch is activated
    stepperZ.moveTo(initial_homing); // Set the position to move to
    initial_homing++;                // Decrease by 1 for next move if needed
    stepperZ.run();                  // Start moving the stepper
    delay(1);
  }
  stepperZ.setCurrentPosition(0); // Set the current position as zero for now
  initial_homing = -1;
  while (digitalRead(HomeZ))
  { // Make the Stepper move CW until the switch is deactivated
    stepperZ.moveTo(initial_homing);
    stepperZ.run();
    initial_homing--;
    delay(1);
  }
  stepperZ.setCurrentPosition(0);
  Serial.println("Homing Z Completed");
}
void homing_w_axis_picking()
{
  stepperW.moveTo(stepperW.currentPosition() + machine.wresolution * 100);
  // Serial.print("Stepper W is Homing . . . ");
  while (1)
  {
    if (digitalRead(OvertravelW2) == HIGH)
    {
      stepperW.stop();
      stepperW.setCurrentPosition(0);
      break;
    }
    stepperW.run();
  }
  Serial.println("Homing W Completed");
}

void motor_W_open()
{
  stepperW.moveTo(stepperW.currentPosition() - machine.wresolution * machine.machine_axis_page.w_offset);
  int count = 0;
  while (1)
  {
    Serial.println(count);
    if (count == 30000)
    {
      machine.machine_connection_page.ethernet_parameters.set_message("open_fail");
      machine.machine_axis_page.set_w_status(false);
      break;
    }
    if (digitalRead(OvertravelW1) == HIGH)
    {
      stepperW.stop();
      stepperW.setCurrentPosition(0);
      machine.machine_connection_page.ethernet_parameters.set_message("open_success");
      machine.machine_axis_page.set_w_status(true);
      break;
    }
    count++;
    stepperW.run();
  }
  machine.machine_connection_page.udp_reply_msg();
}
void motor_W_close()
{
  stepperW.moveTo(stepperW.currentPosition() + machine.wresolution * machine.machine_axis_page.w_offset);
  int count = 0;
  while (1)
  {
    Serial.println(count);
    if (count == 30000)
    {
      machine.machine_connection_page.ethernet_parameters.set_message("close_fail");
      machine.machine_axis_page.set_w_status(true);
      break;
    }
    if (digitalRead(OvertravelW2) == HIGH)
    {
      stepperW.stop();
      stepperW.setCurrentPosition(0);
      machine.machine_connection_page.ethernet_parameters.set_message("close_success");
      machine.machine_axis_page.set_w_status(false);
      break;
    }
    count++;
    stepperW.run();
  }
  machine.machine_connection_page.udp_reply_msg();
}

void stop_x_motor()
{
  int initial = stepperX.currentPosition();
  stepperX.stop();
  stepperX.moveTo(initial);
  while (stepperX.distanceToGo() != 0)
  {
    stepperX.setSpeed(1000);
    stepperX.runSpeed();
  }
  stepperX.setCurrentPosition(0);
}
void stop_y_motor()
{

  int initial = stepperY.currentPosition();
  stepperY.stop();
  stepperY.moveTo(initial);
  while (stepperY.distanceToGo() != 0)
  {
    stepperY.setSpeed(1000);
    stepperY.runSpeed();
  }
  stepperY.setCurrentPosition(0);
}
void stop_z_motor()
{
  int initial = stepperZ.currentPosition();
  stepperZ.stop();
  stepperZ.moveTo(initial);
  while (stepperZ.distanceToGo() != 0)
  {
    stepperZ.setSpeed(1000);
    stepperZ.runSpeed();
  }
  stepperZ.setCurrentPosition(0);
}

bool checking_x_limit()
{
  bool _status;
  if (stepperX.distanceToGo() == 0)
  {
    _status = true;
  }
  else
  {
    if (stepperX.currentPosition() > machine.limit_range_x * machine.xresolution || digitalRead(OvertravelX1))
    {
      stop_x_motor();
      machine.last_message = "x_at_limit+";
      machine.ns_set_visable_control_button(0);
      nextion.nex_send_message(machine.last_message);
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      machine.overtravel_flag = true;
      _status = false;
    }
    else if (stepperX.currentPosition() < 0 || digitalRead(OvertravelX2))
    {
      stop_x_motor();
      machine.last_message = "x_at_limit-";
      machine.ns_set_visable_control_button(0);
      nextion.nex_send_message(machine.last_message);
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      machine.overtravel_flag = true;
      _status = false;
    }
    else
    {
      _status = true;
    }
  }
  return _status;
}
bool checking_y_limit()
{
  bool _status;
  if (stepperY.distanceToGo() == 0)
  {
    _status = true;
  }
  else
  {
    if (stepperY.currentPosition() > machine.limit_range_y * machine.yresolution || digitalRead(OvertravelY1))
    {
      stop_y_motor();
      machine.last_message = "y_at_limit+";
      machine.ns_set_visable_control_button(0);
      nextion.nex_send_message(machine.last_message);
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      machine.overtravel_flag = true;
      _status = false;
    }
    else if (stepperY.currentPosition() < 0 || digitalRead(OvertravelY2))
    {
      stop_y_motor();
      machine.last_message = "y_at_limit-";
      machine.ns_set_visable_control_button(0);
      nextion.nex_send_message(machine.last_message);
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      machine.overtravel_flag = true;
      _status = false;
    }
    else
    {
      _status = true;
    }
  }
  return _status;
}
bool checking_z_limit()
{
  bool _status;
  if (stepperZ.distanceToGo() == 0)
  {
    _status = true;
  }
  else
  {
    if (stepperZ.currentPosition() < machine.limit_range_z * machine.zresolution || digitalRead(OvertravelZ1))
    {
      stop_z_motor();
      machine.last_message = "z_at_limit+";
      machine.ns_set_visable_control_button(0);
      nextion.nex_send_message(machine.last_message);
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      machine.overtravel_flag = true;
      _status = false;
    }
    else if (stepperZ.currentPosition() > 0 || digitalRead(OvertravelZ2))
    {
      stop_z_motor();
      machine.last_message = "z_at_limit-";
      machine.ns_set_visable_control_button(0);
      nextion.nex_send_message(machine.last_message);
      machine.machine_connection_page.ethernet_parameters.set_message(machine.last_message);
      machine.machine_connection_page.udp_reply_msg();
      machine.overtravel_flag = true;
      _status = false;
    }
    else
    {
      _status = true;
    }
  }
  return _status;
}

bool machine_parking(int x, int y, int z)
{
  stepperX.moveTo(x);
  stepperY.moveTo(y);
  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
  {
    stepperX.run();
    stepperY.run();
  }

  stepperZ.moveTo(-z);
  while (stepperZ.distanceToGo() != 0)
  {
    stepperZ.run();
  }
  return true;
}
bool machine_unparking()
{
  stepperZ.moveTo(0);
  while (stepperZ.distanceToGo() != 0)
  {
    stepperZ.run();
  }
  stepperX.moveTo(0);
  stepperY.moveTo(0);
  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
  {
    stepperX.run();
    stepperY.run();
  }

  return false;
}