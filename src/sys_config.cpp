#include "sys_config.h"

void start_up()
{
  io_init();
  delay(500);
  nextion.nex_init();
  delay(500);
  PAGE_LOADING_EVENT.root_attachCallback(PAGE_LOADING_EVENT_CALLBACK);
  delay(500);
  local_data_init();
  delay(500);
  ethernet_init();
  delay(500);
  homing_machine();
  delay(500);
  motor_set_speed_init();
  delay(500);
  motor_set_acc_init();
  delay(500);
  machine.machine_connection_page.ethernet_parameters.set_parameter("buildingname");
  machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.building_name);
  machine.machine_connection_page.udp_reply_para();
  delay(500);
  machine.machine_connection_page.ethernet_parameters.set_parameter("devicename");
  machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.device_name);
  machine.machine_connection_page.udp_reply_para();
  delay(500);
  machine.machine_connection_page.ethernet_parameters.set_parameter("deviceid");
  machine.machine_connection_page.ethernet_parameters.set_parameter_value(String(machine.machine_about_page.device_id));
  machine.machine_connection_page.udp_reply_para();
  delay(500);
  machine.machine_connection_page.ethernet_parameters.set_message("setting_success");
  machine.machine_connection_page.udp_reply_msg();
  delay(500);
  nextion.nex_goto_page("HOME");
}
void io_init()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  // Serial.println("Initializes system IO");
  pinMode(HomeX, INPUT);
  pinMode(HomeY, INPUT);
  pinMode(HomeZ, INPUT);

  pinMode(OvertravelX1, INPUT);
  pinMode(OvertravelX2, INPUT);
  pinMode(OvertravelY1, INPUT);
  pinMode(OvertravelY2, INPUT);

  pinMode(OvertravelZ1, INPUT);
  pinMode(OvertravelZ2, INPUT);
  pinMode(OvertravelW1, INPUT);
  pinMode(OvertravelW2, INPUT);

  pinMode(PickerDetector, INPUT);
  pinMode(DropperDetector, INPUT);
  pinMode(NeedleSucked, INPUT);
  pinMode(AirSuplied, INPUT);

  pinMode(MachineLED, OUTPUT);
  pinMode(TableLED, OUTPUT);
  pinMode(DropCylinder, OUTPUT);
  pinMode(RecycleBox, OUTPUT);
  pinMode(AirFlowPicker, OUTPUT);
  pinMode(AirSuckPicker, OUTPUT);
  pinMode(CameradDropCylinder1, OUTPUT);
  pinMode(CameradDropCylinder2, OUTPUT);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  air_checking();
}
void local_data_init()
{
  // Serial.println("Initialing local parameters");
  machine.init();
}
void ethernet_init()
{
  // Serial.println("Initializing ethernet module");
  nextion.nex_send_message("Setting up ethernet module...");
  // initialize ethernet module
  machine.machine_connection_page.setting_up_ethernet_module();
}
void PAGE_LOADING_EVENT_CALLBACK(uint8_t pageId, uint8_t componentId, uint8_t eventType)
{
  // function_log();
  // Serial.println("Nextion event callback: Page:" + String(pageId) + "ComponentId:" + String(componentId));
  switch (pageId)
  {
  case 7: // page AXIS
    if (componentId == NEX_AXIS_PAGE_INIT)
    {
      machine.init_flag = true;
      machine.nx_update_axis_page();
    }
    if (componentId == NEX_AXIS_PAGE_EXIT)
    {
      nx_axis_page_exit_event();
    }
    if (componentId == NEX_BUT_X_FORWARD_1)
    {
      motor_move('x', 1);
    }
    if (componentId == NEX_BUT_X_FORWARD_10)
    {
      motor_move('x', 10);
    }
    if (componentId == NEX_BUT_X_BACK_1)
    {
      motor_move('x', -1);
    }
    if (componentId == NEX_BUT_X_BACK_10)
    {
      motor_move('x', -10);
    }

    if (componentId == NEX_BUT_Y_FORWARD_1)
    {
      motor_move('y', 1);
    }

    if (componentId == NEX_BUT_Y_FORWARD_10)
    {
      motor_move('y', 10);
    }

    if (componentId == NEX_BUT_Y_BACK_1)
    {
      motor_move('y', -1);
    }

    if (componentId == NEX_BUT_Y_BACK_10)
    {
      motor_move('y', -10);
    }

    if (componentId == NEX_BUT_Z_FORWARD_1)
    {
      motor_move('z', 1);
    }

    if (componentId == NEX_BUT_Z_FORWARD_10)
    {
      motor_move('z', 10);
    }

    if (componentId == NEX_BUT_Z_BACK_1)
    {
      motor_move('z', -1);
    }

    if (componentId == NEX_BUT_Z_BACK_10)
    {
      motor_move('z', -10);
    }

    if (componentId == NEX_BUT_TABLE_ON)
    {
      motor_W_open();
    }

    if (componentId == NEX_BUT_TABLE_OFF)
    {
      motor_W_close();
    }

    if (componentId == NEX_BUT_SAVE_OFFSET)
    {
      machine.nx_save_axis_page_offset();
    }
    if (componentId == NEX_BUT_SAVE_PLUS)
    {
      machine.nx_save_axis_page_plus();
    }
    if (componentId == NEX_BUT_SAVE_SPEED)
    {
      machine.nx_save_axis_page_speed();
      motor_set_speed_init();
    }
    if (componentId == NEX_BUT_SAVE_ACC)
    {
      machine.nx_save_axis_page_acc();
      motor_set_acc_init();
    }
    if (componentId == NEX_KEYBOARD_PAGE_INIT)
    {
      machine.key_board_flag = true;
    }
    if (componentId == NEX_BUT_RESET_ALL_AXIS)
    {
      homing_machine();
      motor_set_acc_init();
      motor_set_speed_init();
      machine.overtravel_flag = false;
      machine.last_message = NULL;
      machine.ns_set_visable_control_button(1);
      machine.nx_set_xyz_position();
      nextion.nex_send_message(machine.last_message);
    }
    if (componentId == NEX_BUT_DROPPER_ON)
    {
      on_dropper();
    }
    if (componentId == NEX_BUT_DROPPER_OFF)
    {
      off_dropper();
    }
    if (componentId == NEX_BUT_AIRSUCK_ON)
    {
      on_airsuck();
    }
    if (componentId == NEX_BUT_AIRSUCK_OFF)
    {
      off_airsuck();
    }
    if (componentId == NEX_BUT_AIRFLOW_ON)
    {
      on_airflow();
    }
    if (componentId == NEX_BUT_AIRFLOW_OFF)
    {
      off_airdlow();
    }
    if (componentId == NEX_BUT_CAM_CYLINDER1_ON)
    {
      on_camcylinder1();
    }
    if (componentId == NEX_BUT_CAM_CYLINDER1_OFF)
    {
      off_camcylinder1();
    }
    if (componentId == NEX_BUT_CAM_CYLINDER2_ON)
    {
      on_camcylinder2();
    }
    if (componentId == NEX_BUT_CAM_CYLINDER2_OFF)
    {
      off_camcylinder2();
    }
    if (componentId == NEX_BUT_BOX_ON)
    {
      open_box();
    }
    if (componentId == NEX_BUT_BOX_OFF)
    {
      close_box();
    }
    if (componentId == NEX_RESET_DEVICE1)
    {
      machine.resetFunc();
    }

    break;

  case 8: // page CONNECTION
    if (componentId == NEX_CONNECTION_PAGE_INIT)
    {
      machine.nx_update_connection_page();
    }
    if (componentId == NX_BUT_SAVE_MAC)
    {
      machine.nx_save_machine_mac();
    }
    if (componentId == NX_BUT_SAVE_ETHERNET_PARAMETERS)
    {
      machine.nx_save_ethernet_parameters();
      ethernet_init();
    }
    if (componentId == NEX_KEYBOARD2_PAGE_INIT)
    {
      machine.key_board_flag = true;
    }
    if (componentId == NEX_RESET_DEVICE2)
    {
      machine.resetFunc();
    }
    break;

  case 9: // page ABOUT
    if (componentId == NEX_ABOUT_PAGE_INIT)
    {
      machine.nx_update_about_page();
    }
    if (componentId == NEX_ABOUT_PAGE_EXIT)
    {
    }
    if (componentId == NX_BUT_SAVE_BUILDING)
    {
      machine.nx_save_building_name();
    }
    if (componentId == NX_BUT_SAVE_DEVICE_ID)
    {
      machine.nx_save_device_id();
    }
    if (componentId == NX_BUT_SAVE_DEVICE_NAME)
    {
      machine.nx_save_device_name();
    }
    if (componentId == NX_BUT_TABLE_LED)
    {
      if (!machine.machine_about_page.table_led_flag)
      {
        on_table_led();
      }
      else
      {
        off_table_led();
      }
    }
    if (componentId == NX_BUT_FRAME_LED)
    {
      if (!machine.machine_about_page.frame_led_flag)
      {
        on_frame_led();
      }
      else
      {
        off_frame_led();
      }
    }
    if (componentId == NEX_RESET_DEVICE3)
    {
      machine.resetFunc();
    }
    break;
  }
}
void ethernet_checking()
{
  machine.machine_connection_page.check_ethernet_module_status();
}
void sensors_checking()
{
  if (digitalRead(OvertravelW1) == HIGH || digitalRead(OvertravelW2) == HIGH)
  {
    nextion.nex_set_vis("b43", 1);
  }
  else
  {
    nextion.nex_set_vis("b43", 0);
  }
  if (digitalRead(HomeX) == HIGH)
  {
    nextion.nex_set_vis("b40", 1);
  }
  else
  {
    nextion.nex_set_vis("b40", 0);
  }
  if (digitalRead(HomeY) == HIGH)
  {
    nextion.nex_set_vis("b41", 1);
  }
  else
  {
    nextion.nex_set_vis("b41", 0);
  }
  if (digitalRead(HomeZ) == HIGH)
  {
    nextion.nex_set_vis("b42", 1);
  }
  else
  {
    nextion.nex_set_vis("b42", 0);
  }
}
void air_checking()
{
  int air_status = 0;
  digitalWrite(AirSuckPicker, HIGH);
  delay(100);
  while (digitalRead(AirSuplied))
  {
    if (air_status == 0)
    {
      machine.machine_connection_page.ethernet_parameters.set_message("air_failed");
      machine.machine_connection_page.udp_reply_msg();
    }
    air_status++;
    Serial.println("Airpressure faild");
    delay(100);
  }
  if (air_status != 0)
  {
    machine.machine_connection_page.ethernet_parameters.set_message("air_success");
    machine.machine_connection_page.udp_reply_msg();
  }
  Serial.println("Airpressure success");
  digitalWrite(AirSuckPicker, LOW);
}

void udp_listening()
{
  machine.machine_connection_page.udp_checking();
  udp_buffer_progress();
}
void udp_buffer_progress()
{
  String buffer_string(machine.machine_connection_page.ethernet_parameters.packetBuffer);
  buffer_string = machine.machine_connection_page.ethernet_parameters.packetBuffer;
  int count = 0;
  int string_len = buffer_string.length() + 1;

  if (buffer_string != NULL)
  {
    machine.machine_connection_page.ethernet_parameters.set_message("receive_success");
    machine.machine_connection_page.udp_reply_msg();
    for (int i = 0; i < string_len; i++)
    {
      count += (buffer_string[i] == ':');
    }
    for (int i = 0; i < count; i++)
    {
      String parameter = machine.getParameter_fromBuffer(buffer_string, '<', '>');
      String name = machine.getName_fromParameter(parameter, ':');
      String value = machine.getstringValue_fromParameter(parameter, ':');
      parameter_checking(name, value);

      buffer_string = buffer_string.substring(machine.character_count + 1);
    }
  }
  memset(machine.machine_connection_page.ethernet_parameters.packetBuffer, 0, sizeof(machine.machine_connection_page.ethernet_parameters.packetBuffer));
}
void parameter_checking(String name, String n_value)
{
  const char *index_char;
  index_char = n_value.c_str();
  int value = atoi(index_char);
  buffer_get_para_checking(name, n_value);
  buffer_connection_parameter_check(name, n_value);
  buffer_ethernet_parameter_check(name, n_value);
  buffer_speed_check(name, value);
  buffer_accel_check(name, value);
  buffer_offset_check(name, value);
  buffer_plus_check(name, value);
  picking_check(name, value);
  funtions_check(name, value);
}

void buffer_get_para_checking(String name, String parameters)
{
  if (name == "get")
  {
    if (parameters == "localip")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("localip");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_connection_page.ethernet_parameters.local_ip_str);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "remoteip")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("remoteip");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_connection_page.ethernet_parameters.remote_ip_str);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "port")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("port");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_connection_page.ethernet_parameters.localPort);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "buildingname")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("buildingname");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.building_name);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "devicename")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("devicename");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.device_name);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "deviceid")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("deviceid");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(String(machine.machine_about_page.device_id));
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "wstatus")
    {
      if (digitalRead(OvertravelW2) == HIGH && digitalRead(OvertravelW1) == LOW)
      {
        machine.machine_connection_page.ethernet_parameters.set_message("table_closed");
        machine.machine_connection_page.udp_reply_msg();
      }
      else if (digitalRead(OvertravelW2) == LOW && digitalRead(OvertravelW1) == HIGH)
      {
        machine.machine_connection_page.ethernet_parameters.set_message("table_opened");
        machine.machine_connection_page.udp_reply_msg();
      }
      else
      {
        machine.machine_connection_page.ethernet_parameters.set_message("table_error");
        machine.machine_connection_page.udp_reply_msg();
      }
    }
    if (parameters == "xpos")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("xpos");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.xposition);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "ypos")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("ypos");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.yposition);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "zpos")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("zpos");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.zposition);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "table")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("table");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(digitalRead(OvertravelW1));
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "parking")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("park");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.park);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "led1")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("led1");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.frame_led_flag);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "led2")
    {
      machine.machine_connection_page.ethernet_parameters.set_parameter("led2");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.table_led_flag);
      machine.machine_connection_page.udp_reply_para();
    }
    if (parameters == "load")
    {
      machine.machine_connection_page.ethernet_parameters.set_message("load_success");
      machine.machine_connection_page.udp_reply_msg();
    }
  }
  char para_char = parameters.charAt(0);
  if (name == "speed")
  {
    switch (para_char)
    {
    case 'x':
      machine.machine_connection_page.ethernet_parameters.set_parameter("speedx");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.x_speed);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'y':
      machine.machine_connection_page.ethernet_parameters.set_parameter("speedy");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.y_speed);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'z':
      machine.machine_connection_page.ethernet_parameters.set_parameter("speedz");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.z_speed);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'w':
      machine.machine_connection_page.ethernet_parameters.set_parameter("speedw");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.w_speed);
      machine.machine_connection_page.udp_reply_para();
      break;
    }
  }
  if (name == "accel")
  {
    switch (para_char)
    {
    case 'x':
      machine.machine_connection_page.ethernet_parameters.set_parameter("accelx");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.x_acceleration);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'y':
      machine.machine_connection_page.ethernet_parameters.set_parameter("accely");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.y_acceleration);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'z':
      machine.machine_connection_page.ethernet_parameters.set_parameter("accelz");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.z_acceleration);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'w':
      machine.machine_connection_page.ethernet_parameters.set_parameter("accelw");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.w_acceleration);
      machine.machine_connection_page.udp_reply_para();
      break;
    }
  }
  if (name == "offset")
  {
    switch (para_char)
    {
    case 'x':
      machine.machine_connection_page.ethernet_parameters.set_parameter("offsetx");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.x_offset);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'y':
      machine.machine_connection_page.ethernet_parameters.set_parameter("offsety");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.y_offset);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'z':
      machine.machine_connection_page.ethernet_parameters.set_parameter("offsetz");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.z_offset);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'w':
      machine.machine_connection_page.ethernet_parameters.set_parameter("offsetw");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.w_offset);
      machine.machine_connection_page.udp_reply_para();
      break;
    }
  }
  if (name == "plus")
  {
    switch (para_char)
    {
    case 'x':
      machine.machine_connection_page.ethernet_parameters.set_parameter("plusx");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.x_plus);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'y':
      machine.machine_connection_page.ethernet_parameters.set_parameter("plusy");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.y_plus);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'z':
      machine.machine_connection_page.ethernet_parameters.set_parameter("plusz");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.z_plus);
      machine.machine_connection_page.udp_reply_para();
      break;
    case 'w':
      machine.machine_connection_page.ethernet_parameters.set_parameter("plusw");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.w_plus);
      machine.machine_connection_page.udp_reply_para();
      break;
    }
  }
  delay(200);
}

void buffer_speed_check(String name, int value)
{
  bool save_status;
  for (int i = 0; i < 4; i++)
  {
    if (strcmp(machine.speed_array[i], name.c_str()) == 0)
    {
      char axis = name.charAt(name.length() - 1);
      machine.init_flag = true;
      save_status = machine.buffer_save_axis_page_specific_speed(axis, value);
      motor_set_speed_init();
      machine.nx_update_axis_page();
      if (save_status)
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_success");
        machine.machine_connection_page.udp_reply_msg();
      }
      else
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_failed");
        machine.machine_connection_page.udp_reply_msg();
      }
      break;
    }
  }
}
void buffer_accel_check(String name, int value)
{
  bool save_status;
  for (int i = 0; i < 4; i++)
  {
    if (strcmp(machine.accel_array[i], name.c_str()) == 0)
    {
      char axis = name.charAt(name.length() - 1);
      machine.init_flag = true;
      save_status = machine.buffer_save_axis_page_specific_accel(axis, value);
      motor_set_acc_init();
      machine.nx_update_axis_page();
      if (save_status)
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_success");
        machine.machine_connection_page.udp_reply_msg();
      }
      else
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_failed");
        machine.machine_connection_page.udp_reply_msg();
      }
      break;
    }
  }
}
void buffer_offset_check(String name, int value)
{
  bool save_status;
  for (int i = 0; i < 4; i++)
  {
    if (strcmp(machine.offset_array[i], name.c_str()) == 0)
    {
      char axis = name.charAt(name.length() - 1);
      machine.init_flag = true;
      save_status = machine.buffer_save_axis_page_specific_offset(axis, value);
      machine.nx_update_axis_page();
      if (save_status)
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_success");
        machine.machine_connection_page.udp_reply_msg();
      }
      else
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_failed");
        machine.machine_connection_page.udp_reply_msg();
      }
      break;
    }
  }
}
void buffer_plus_check(String name, int value)
{
  bool save_status;
  for (int i = 0; i < 4; i++)
  {
    if (strcmp(machine.plus_array[i], name.c_str()) == 0)
    {
      char axis = name.charAt(name.length() - 1);
      machine.init_flag = true;
      save_status = machine.buffer_save_axis_page_specific_plus(axis, value);
      machine.nx_update_axis_page();
      if (save_status)
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_success");
        machine.machine_connection_page.udp_reply_msg();
      }
      else
      {
        machine.machine_connection_page.ethernet_parameters.set_message("save_failed");
        machine.machine_connection_page.udp_reply_msg();
      }
      break;
    }
  }
}
void picking_check(String position, int needleqty)
{
  if (machine.park)
  {
    machine.machine_connection_page.ethernet_parameters.set_message("in_parking_place");
    machine.machine_connection_page.udp_reply_msg();
    return;
  }
  bool complete_status = true;
  int position_name_len = position.length();
  if (position_name_len == 2 && needleqty <= 5)
  {
    int x_scale = 0;
    int y_scale = 0;
    int z_scale = 0;
    int int_camera = 0;

    char x_label_char = position.charAt(0);
    char y_label_char = position.charAt(1);
    const char *y_label_const_char = &y_label_char;
    int y_label_int = atoi(y_label_const_char);
    for (char c = 'a'; c <= 'z'; c++)
    {
      if (x_label_char == c)
      {
        break;
      }
      else
      {
        x_scale++;
      }
    }
    for (int i = 1; i <= 100; i++)
    {
      if (y_label_int == i)
      {
        break;
      }
      else
      {
        y_scale++;
      }
    }
    for (int z = 1; z <= 5; z++)
    {
      if (needleqty == z)
      {
        break;
      }
      else
      {
        z_scale++;
      }
    }
    Serial.println(x_scale);
    Serial.println(y_scale);
    Serial.println(z_scale);

    homing_machine_before_pick();
    delay(500);
    // Move XY to picking position and Z to prepairing posittion
    stepperX.moveTo((machine.machine_axis_page.x_offset + machine.machine_axis_page.x_plus * x_scale) * machine.xresolution);
    stepperY.moveTo((machine.machine_axis_page.y_offset + machine.machine_axis_page.y_plus * y_scale) * machine.yresolution);
    stepperZ.moveTo(0 - 15 * machine.zresolution);
    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0 || stepperZ.distanceToGo() != 0)
    {
      bool xstatus = checking_x_limit();
      bool ystatus = checking_y_limit();
      bool zstatus = checking_z_limit();

      if (!xstatus || !ystatus || !zstatus)
      {
        stop_x_motor();
        stop_y_motor();
        stop_z_motor();
        break;
      }
      else
      {
        stepperX.run();
        stepperY.run();
        stepperZ.run();
      }
    }
    if (!machine.overtravel_flag)
    {
      // Turn on picker
      digitalWrite(AirSuckPicker, HIGH);
      // Move Z to needle position
      stepperZ.moveTo(0 - (machine.machine_axis_page.z_offset - machine.machine_axis_page.z_plus * z_scale) * machine.zresolution);
      while (stepperZ.distanceToGo() != 0)
      {
        stepperZ.run();
        // Check for higher needle qty
        if (!digitalRead(NeedleSucked) && stepperZ.distanceToGo() < (-6 * machine.zresolution))
        {
          stepperZ.stop();
          digitalWrite(AirSuckPicker, LOW);
          stepperZ.moveTo(0);
          while (stepperZ.distanceToGo() != 0)
          {
            stepperZ.setSpeed(1000);
            stepperZ.runSpeed();
          }
          stepperZ.setCurrentPosition(0);
          stepperX.moveTo(0);
          stepperY.moveTo(0);
          while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
          {
            stepperX.run();
            stepperY.run();
          }
          stepperX.setCurrentPosition(0);
          stepperY.setCurrentPosition(0);
          machine.machine_connection_page.ethernet_parameters.set_message("higher_needle_qty_" + position);
          complete_status = false;
          break;
        }
      }
      if (complete_status && !machine.overtravel_flag) // Needle on picker
      {
        bool z_sucked = true;
        bool xy_sucked = true;
        bool z_picked = true;
        // move Z to prepairing position
        if (!digitalRead(NeedleSucked) && stepperZ.distanceToGo() == 0) // check for needle is sucked or empty
        {
          z_picked = true;
        }
        else
        {
          z_picked = false;
        }

        if (!z_picked) // needle stock is empty
        {
          // turn off picker
          digitalWrite(AirSuckPicker, LOW);
          // move z back to zero
          stepperZ.moveTo(0);
          while (stepperZ.distanceToGo() != 0)
          {
            stepperZ.run();
          }
          stepperZ.setCurrentPosition(0);
          // move xy back to zero
          stepperX.moveTo(0);
          stepperY.moveTo(0);
          while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
          {
            stepperX.run();
            stepperY.run();
          }
          stepperX.setCurrentPosition(0);
          stepperY.setCurrentPosition(0);
          machine.machine_connection_page.ethernet_parameters.set_message("needle_stock_empty_" + position);
          complete_status = false;
        }
        else // needle is sucked
        {
          // move z to prepairing porition
          stepperZ.moveTo(0 - 15 * machine.zresolution);
          while (stepperZ.distanceToGo() != 0)
          {
            // Check for needle still on picker or dropped
            if (digitalRead(NeedleSucked)) // needle is dropped when z back
            {
              digitalWrite(AirSuckPicker, LOW);
              stepperZ.stop();
              while (stepperZ.distanceToGo() != 0)
              {
                stepperZ.run();
              }
              z_sucked = false;
              break;
            }
            else // needle still on picker
            {
              stepperZ.run();
            }
          }
          if (z_sucked) // needle is still on picker
          {
            if (digitalRead(PickerDetector)) // needle is still on picker again
            {
              // move XY to dropper position
              stepperX.moveTo(machine.droper_position[0] * machine.xresolution);
              stepperY.moveTo(machine.droper_position[1] * machine.yresolution);
              while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
              {
                // Check for needle still on picker or dropped
                if (digitalRead(NeedleSucked))
                {
                  xy_sucked = false;
                  break;
                }
                else
                {
                  stepperX.run();
                  stepperY.run();
                }
              }
              if (xy_sucked) // needle is still on picker
              {
                bool needle_stucked = false;
                int count = 0;
                // move Z to dropping position
                stepperZ.moveTo(0 - machine.droper_position[2] * machine.zresolution);
                while (stepperZ.distanceToGo() != 0)
                {
                  stepperZ.run();
                }
                // turn off picker
                digitalWrite(AirSuckPicker, LOW);
                // move z to Zero
                stepperZ.moveTo(0);
                while (stepperZ.distanceToGo() != 0)
                {
                  stepperZ.run();
                }
                stepperZ.setCurrentPosition(0);
                // check for camera permission
                machine.machine_connection_page.ethernet_parameters.set_message("check_camera");
                machine.machine_connection_page.udp_reply_msg();
                delay(1000);
                digitalWrite(CameradDropCylinder1, HIGH);
                while (1)
                {
                  // get camera permisstion status
                  int_camera = camera_checking();
                  if (int_camera == 1)
                  {
                    // digitalWrite(CameradDropCylinder1, HIGH);
                    // turn of droper cylinder
                    stepperX.moveTo(0);
                    stepperY.moveTo(0);
                    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                    {
                      stepperX.run();
                      stepperY.run();
                    }
                    stepperX.setCurrentPosition(0);
                    stepperY.setCurrentPosition(0);
                    digitalWrite(DropCylinder, HIGH);
                    // check for needle is stucked or not
                    while (!digitalRead(DropperDetector))
                    {
                      count++;
                      if (count == 300)
                      {
                        needle_stucked = true;
                        break;
                      }
                      delay(100);
                    }
                    if (needle_stucked) // needle is stuck
                    {
                      digitalWrite(DropCylinder, LOW);

                      machine.machine_connection_page.ethernet_parameters.set_message("needle_stucked");
                      complete_status = false;
                      digitalWrite(CameradDropCylinder1, LOW);
                    }
                    else // needle supplied success
                    {
                      digitalWrite(DropCylinder, LOW);

                      machine.machine_connection_page.ethernet_parameters.set_message("needle_supplied");
                      complete_status = true;
                      digitalWrite(CameradDropCylinder2, HIGH);
                    }
                    machine.machine_connection_page.udp_reply_msg();
                    break;
                  }
                  else if (int_camera == 2)
                  {
                    // move z to dropper posotion
                    stepperZ.moveTo(0 - machine.droper_position[2] * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    // turn on picker
                    digitalWrite(AirSuckPicker, HIGH);
                    // move z to preparing positon
                    stepperZ.moveTo(0 - 15 * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    delay(300);
                    // move xy back to picking position
                    stepperX.moveTo((machine.machine_axis_page.x_offset + machine.machine_axis_page.x_plus * x_scale) * machine.xresolution);
                    stepperY.moveTo((machine.machine_axis_page.y_offset + machine.machine_axis_page.y_plus * y_scale) * machine.yresolution);
                    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                    {
                      stepperX.run();
                      stepperY.run();
                    }
                    // move z to last needle position
                    stepperZ.moveTo(0 - (machine.machine_axis_page.z_offset - machine.machine_axis_page.z_plus * z_scale) * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    // drop needle back
                    digitalWrite(AirSuckPicker, LOW);
                    // move z back to zero
                    stepperZ.moveTo(0);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    stepperZ.setCurrentPosition(0);
                    // move xy back to zero
                    stepperX.moveTo(0);
                    stepperY.moveTo(0);
                    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                    {
                      stepperX.run();
                      stepperY.run();
                    }
                    stepperX.setCurrentPosition(0);
                    stepperY.setCurrentPosition(0);
                    machine.machine_connection_page.ethernet_parameters.set_message("camera_failed");
                    machine.machine_connection_page.udp_reply_msg();
                    complete_status = false;
                    break;
                  }
                  else if (int_camera == 3)
                  {
                    // move z to dropper posotion
                    stepperZ.moveTo(0 - machine.droper_position[2] * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    // turn on picker
                    digitalWrite(AirSuckPicker, HIGH);
                    // move z to preparing positon
                    stepperZ.moveTo(0 - 15 * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    delay(300);
                    // move xy back to picking position
                    stepperX.moveTo((machine.machine_axis_page.x_offset + machine.machine_axis_page.x_plus * x_scale) * machine.xresolution);
                    stepperY.moveTo((machine.machine_axis_page.y_offset + machine.machine_axis_page.y_plus * y_scale) * machine.yresolution);
                    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                    {
                      stepperX.run();
                      stepperY.run();
                    }
                    // move z to last needle position
                    stepperZ.moveTo(0 - (machine.machine_axis_page.z_offset - machine.machine_axis_page.z_plus * z_scale) * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    // drop needle back
                    digitalWrite(AirSuckPicker, LOW);
                    // move z back to zero
                    stepperZ.moveTo(0);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    stepperZ.setCurrentPosition(0);
                    // move xy back to zero
                    stepperX.moveTo(0);
                    stepperY.moveTo(0);
                    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                    {
                      stepperX.run();
                      stepperY.run();
                    }
                    stepperX.setCurrentPosition(0);
                    stepperY.setCurrentPosition(0);
                    machine.machine_connection_page.ethernet_parameters.set_message("camera_time_out");
                    machine.machine_connection_page.udp_reply_msg();
                    complete_status = false;
                    break;
                  }
                  else if (int_camera == 4)
                  {
                    // move z to dropper posotion
                    stepperZ.moveTo(0 - machine.droper_position[2] * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    // turn on picker
                    digitalWrite(AirSuckPicker, HIGH);
                    // move z to preparing positon
                    stepperZ.moveTo(0 - 15 * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    delay(300);
                    // move xy back to picking position
                    stepperX.moveTo((machine.machine_axis_page.x_offset + machine.machine_axis_page.x_plus * x_scale) * machine.xresolution);
                    stepperY.moveTo((machine.machine_axis_page.y_offset + machine.machine_axis_page.y_plus * y_scale) * machine.yresolution);
                    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                    {
                      stepperX.run();
                      stepperY.run();
                    }
                    // move z to last needle position
                    stepperZ.moveTo(0 - (machine.machine_axis_page.z_offset - machine.machine_axis_page.z_plus * z_scale) * machine.zresolution);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    // drop needle back
                    digitalWrite(AirSuckPicker, LOW);
                    // move z back to zero
                    stepperZ.moveTo(0);
                    while (stepperZ.distanceToGo() != 0)
                    {
                      stepperZ.run();
                    }
                    stepperZ.setCurrentPosition(0);
                    // move xy back to zero
                    stepperX.moveTo(0);
                    stepperY.moveTo(0);
                    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                    {
                      stepperX.run();
                      stepperY.run();
                    }
                    stepperX.setCurrentPosition(0);
                    stepperY.setCurrentPosition(0);
                    machine.machine_connection_page.ethernet_parameters.set_message("camera_canceled");
                    machine.machine_connection_page.udp_reply_msg();
                    complete_status = false;
                    break;
                  }
                  else
                  {
                    delay(100);
                    continue;
                  }
                }
              }
              else // needle is dropped when go xy
              {
                // stop xy immediately
                stepperX.stop();
                stepperY.stop();
                while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                {
                  stepperX.run();
                  stepperY.run();
                }
                // turn off picker
                digitalWrite(AirSuckPicker, LOW);
                delay(500);
                // move z back to zero
                stepperZ.moveTo(0);
                while (stepperZ.distanceToGo() != 0)
                {
                  stepperZ.run();
                }
                stepperZ.setCurrentPosition(0);
                delay(100);
                // move xy back to zero
                stepperX.moveTo(0);
                stepperY.moveTo(0);
                while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                {
                  stepperX.run();
                  stepperY.run();
                }
                stepperX.setCurrentPosition(0);
                stepperY.setCurrentPosition(0);
                machine.machine_connection_page.ethernet_parameters.set_message("needle_dropped_xy");
                complete_status = false;
              }
            }
            else // needle is not on picker
            {
              // turn off picker
              digitalWrite(AirSuckPicker, LOW);
              // move z back to zero
              stepperZ.moveTo(0);
              while (stepperZ.distanceToGo() != 0)
              {
                stepperZ.run();
              }
              stepperZ.setCurrentPosition(0);
              // move xy back to zero
              stepperX.moveTo(0);
              stepperY.moveTo(0);
              while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
              {
                stepperX.run();
                stepperY.run();
              }
              stepperX.setCurrentPosition(0);
              stepperY.setCurrentPosition(0);
              machine.machine_connection_page.ethernet_parameters.set_message("needle_stock_problem");
              complete_status = false;
            }
          }
          else // needle is dropped when go z
          {
            delay(500);
            stepperZ.moveTo(0);
            while (stepperZ.distanceToGo() != 0)
            {
              stepperZ.run();
            }
            stepperZ.setCurrentPosition(0);
            delay(100);
            stepperX.moveTo(0);
            stepperY.moveTo(0);
            while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
            {
              stepperX.run();
              stepperY.run();
            }
            stepperX.setCurrentPosition(0);
            stepperY.setCurrentPosition(0);
            machine.machine_connection_page.ethernet_parameters.set_message("needle_dropped_z");
            complete_status = false;
          }
        }
      }
      // machine.machine_connection_page.ethernet_parameters.set_parameter("status");
      // machine.machine_connection_page.ethernet_parameters.set_parameter_value(complete_status);
      // machine.machine_connection_page.udp_reply_para();
      delay(1000);
      if (int_camera == 0)
      {
        machine.machine_connection_page.udp_reply_msg();
      }
      digitalWrite(CameradDropCylinder1, LOW);
      digitalWrite(CameradDropCylinder2, LOW);
    }
  }
}
void funtions_check(String name, int value)
{
  if (name == "reset")
  {
    machine.resetFunc();
  }
  if (name == "home")
  {
    homing_machine();
    motor_set_acc_init();
    motor_set_speed_init();
    machine.overtravel_flag = false;
    machine.park = false;
    machine.last_message = NULL;
    machine.ns_set_visable_control_button(1);
    machine.nx_set_xyz_position();
    nextion.nex_send_message(machine.last_message);
    delay(500);
    machine.machine_connection_page.ethernet_parameters.set_parameter("xpos");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.xposition);
    machine.machine_connection_page.udp_reply_para();
    delay(500);
    machine.machine_connection_page.ethernet_parameters.set_parameter("ypos");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.yposition);
    machine.machine_connection_page.udp_reply_para();
    delay(500);
    machine.machine_connection_page.ethernet_parameters.set_parameter("zpos");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.zposition);
    machine.machine_connection_page.udp_reply_para();
    delay(500);
    machine.machine_connection_page.ethernet_parameters.set_parameter("table");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.w_needle_table_status_flag);
    machine.machine_connection_page.udp_reply_para();
    delay(500);
    machine.machine_connection_page.ethernet_parameters.set_parameter("park");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.park);
    machine.machine_connection_page.udp_reply_para();
  }
  if (name == "led1")
  {
    if (value == 1)
    {
      on_frame_led();
    }
    else
    {
      off_frame_led();
    }
    machine.machine_connection_page.ethernet_parameters.set_parameter("led1");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.frame_led_flag);
    machine.machine_connection_page.udp_reply_para();
  }
  if (name == "led2")
  {
    if (value == 1)
    {
      on_table_led();
    }
    else
    {
      off_table_led();
    }
    machine.machine_connection_page.ethernet_parameters.set_parameter("led2");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_about_page.table_led_flag);
    machine.machine_connection_page.udp_reply_para();
  }
  if (name == "table")
  {
    if (value == 1)
    {
      motor_W_open();
    }
    else
    {
      motor_W_close();
    }
    machine.machine_connection_page.ethernet_parameters.set_parameter("table");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.w_needle_table_status_flag);
    machine.machine_connection_page.udp_reply_para();
  }
  if (name == "park")
  {
    if (machine.park == true && value == 1)
    {
      return;
    }
    else if (machine.park == true && value == 0)
    {
      machine.park = machine_unparking();
      machine.machine_connection_page.ethernet_parameters.set_parameter("park");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.park);
      machine.machine_connection_page.udp_reply_para();
    }
    else if (machine.park == false && value == 1)
    {
      machine.park = machine_parking(machine.parking_pos[0] * machine.xresolution, machine.parking_pos[1] * machine.yresolution, machine.parking_pos[2] * machine.zresolution);
      machine.machine_connection_page.ethernet_parameters.set_parameter("park");
      machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.park);
      machine.machine_connection_page.udp_reply_para();
    }
    else
    {
      return;
    }
  }
  if (name == "box")
  {
    if (value == 1)
    {
      open_box();
    }
    else
    {
      close_box();
    }
    machine.machine_connection_page.ethernet_parameters.set_parameter("box");
    machine.machine_connection_page.ethernet_parameters.set_parameter_value(machine.machine_axis_page.needle_box_status_flag);
    machine.machine_connection_page.udp_reply_para();
  }
  if (name == "movex")
  {
    motor_move('x', value);
  }
  if (name == "movey")
  {
    motor_move('y', value);
  }
  if (name == "movez")
  {
    motor_move('z', value);
  }
}
int camera_checking()
{
  machine.machine_connection_page.udp_c_checking();
  String c_buffer_string(machine.machine_connection_page.ethernet_parameters.c_packetBuffer);
  c_buffer_string = machine.machine_connection_page.ethernet_parameters.c_packetBuffer;

  int c_count = 0;
  int c_string_len = c_buffer_string.length() + 1;

  if (c_buffer_string != NULL)
  {
    for (int i = 0; i < c_string_len; i++)
    {
      c_count += (c_buffer_string[i] == ':');
    }
    for (int i = 0; i < c_count; i++)
    {
      String c_parameter = machine.getParameter_fromBuffer(c_buffer_string, '<', '>');
      String c_name = machine.getName_fromParameter(c_parameter, ':');
      String c_value = machine.getstringValue_fromParameter(c_parameter, ':');
      const char *c_index_char;
      c_index_char = c_value.c_str();
      int c_int_value = atoi(c_index_char);
      if (c_name == "camera")
      {
        if (c_int_value == 1) // Confirmation is success
        {
          memset(machine.machine_connection_page.ethernet_parameters.c_packetBuffer, 0, sizeof(machine.machine_connection_page.ethernet_parameters.c_packetBuffer));
          c_buffer_string = c_buffer_string.substring(machine.c_character_count + 1);
          return 1;
        }
        else if (c_int_value == 2) // Confirmation is failed
        {
          memset(machine.machine_connection_page.ethernet_parameters.c_packetBuffer, 0, sizeof(machine.machine_connection_page.ethernet_parameters.c_packetBuffer));
          c_buffer_string = c_buffer_string.substring(machine.c_character_count + 1);
          return 2;
        }
        else if (c_int_value == 3) // Confirmation is time out
        {
          memset(machine.machine_connection_page.ethernet_parameters.c_packetBuffer, 0, sizeof(machine.machine_connection_page.ethernet_parameters.c_packetBuffer));
          c_buffer_string = c_buffer_string.substring(machine.c_character_count + 1);
          return 3;
        }
        else if (c_int_value == 4) // Confirmation is canceled
        {
          memset(machine.machine_connection_page.ethernet_parameters.c_packetBuffer, 0, sizeof(machine.machine_connection_page.ethernet_parameters.c_packetBuffer));
          c_buffer_string = c_buffer_string.substring(machine.c_character_count + 1);
          return 4;
        }
      }
    }
  }
  return 0;
}
bool timer_checking()
{
  machine.machine_connection_page.udp_t_checking();
  String t_buffer_string(machine.machine_connection_page.ethernet_parameters.t_packetBuffer);
  t_buffer_string = machine.machine_connection_page.ethernet_parameters.t_packetBuffer;
  int t_count = 0;
  int t_string_len = t_buffer_string.length() + 1;
  if (t_buffer_string != NULL)
  {
    for (int i = 0; i < t_string_len; i++)
    {
      t_count += (t_buffer_string[i] == ':');
    }
    for (int i = 0; i < t_count; i++)
    {
      String t_parameter = machine.getParameter_fromBuffer(t_buffer_string, '<', '>');
      String t_name = machine.getName_fromParameter(t_parameter, ':');
      String t_value = machine.getstringValue_fromParameter(t_parameter, ':');
      const char *t_index_char;
      t_index_char = t_value.c_str();
      int t_int_value = atoi(t_index_char);
      if (t_name == "timer")
      {
        if (t_int_value == 1)
        {
          memset(machine.machine_connection_page.ethernet_parameters.t_packetBuffer, 0, sizeof(machine.machine_connection_page.ethernet_parameters.t_packetBuffer));
          t_buffer_string = t_buffer_string.substring(machine.t_character_count + 1);
          return true;
        }
        else
        {
          memset(machine.machine_connection_page.ethernet_parameters.t_packetBuffer, 0, sizeof(machine.machine_connection_page.ethernet_parameters.t_packetBuffer));
          t_buffer_string = t_buffer_string.substring(machine.t_character_count + 1);
          return false;
        }
      }
    }
  }
  return false;
}
void buffer_ethernet_parameter_check(String name, String value)
{
  for (int i = 0; i <= 2; i++)
  {
    if (strcmp(machine.connection_array[i], name.c_str()) == 0)
    {
      if (name == "localip")
      {
        const char *c_value = value.c_str();
        machine.machine_connection_page.ethernet_parameters.setup_ethernet_local_ip(c_value);
        machine.machine_connection_page.ethernet_parameters.eeprom_save_ethernet_local_ip();
        ethernet_init();
      }
      else if (name == machine.connection_array[1])
      {
        const char *c_value = value.c_str();
        machine.machine_connection_page.ethernet_parameters.setup_ethernet_remote_ip(c_value);
        machine.machine_connection_page.ethernet_parameters.eeprom_save_ethernet_remote_ip();
        ethernet_init();
      }
      else
      {
        const char *c_value = value.c_str();
        int c_int_value = atoi(c_value);
        machine.machine_connection_page.ethernet_parameters.setup_ethernet_port(c_int_value);
        machine.machine_connection_page.ethernet_parameters.eeprom_save_ethernet_port();
        ethernet_init();
      }
      machine.nx_update_connection_page();
      Serial.println(name);
      Serial.println(value);
    }
  }
}
void buffer_connection_parameter_check(String name, String value)
{
  if (name == "buildingname")
  {
    machine.udp_save_buildingname(value);
  }
  if (name == "devicename")
  {
    machine.udp_save_devicename(value);
  }
  if (name == "deviceid")
  {
    machine.udp_save_deviceid(value);
  }
}
