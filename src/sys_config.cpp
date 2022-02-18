#include "sys_config.h"

machine_progress_class machine_progress;
nextion_extension nextion;

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
  setup_machine_hardware();
  delay(500);
  homing_machine();
  delay(500);
  motor_set_speed_init();
  delay(500);
  motor_set_acc_init();
  delay(500);
  nextion.nex_goto_page("HOME");
  machine_progress.machine_connection_page.ethernet_parameters.set_message("setting_success");
  machine_progress.machine_connection_page.udp_reply_msg();
}
void io_init()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Initializes system IO");
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
  pinMode(CameraCylinder, OUTPUT);
  pinMode(AirFlowPicker, OUTPUT);
  pinMode(AirSuckPicker, OUTPUT);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  air_checking();
}
void local_data_init()
{
  Serial.println("Initialing local parameters");
  machine_progress.init();
}
void ethernet_init()
{
  Serial.println("Initializing ethernet module");
  nextion.nex_send_message("Setting up ethernet module...");
  // initialize ethernet module
  machine_progress.machine_connection_page.setting_up_ethernet_module();
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
      // update movemnt page
      machine_progress.nx_update_axis_page();
    }
    if (componentId == NEX_AXIS_PAGE_EXIT)
    {
      nx_axis_page_exit_event();
    }
    if (componentId == NEX_BUT_X_FORWARD_1)
    {
      motor_forward('x', 1);
    }
    if (componentId == NEX_BUT_X_FORWARD_10)
    {
      motor_forward('x', 10);
    }
    if (componentId == NEX_BUT_X_BACK_1)
    {
      motor_back('x', 1);
    }
    if (componentId == NEX_BUT_X_BACK_10)
    {
      motor_back('x', 10);
    }

    if (componentId == NEX_BUT_Y_FORWARD_1)
    {
      motor_forward('y', 1);
    }

    if (componentId == NEX_BUT_Y_FORWARD_10)
    {
      motor_forward('y', 10);
    }

    if (componentId == NEX_BUT_Y_BACK_1)
    {
      motor_back('y', 1);
    }

    if (componentId == NEX_BUT_Y_BACK_10)
    {
      motor_back('y', 10);
    }

    if (componentId == NEX_BUT_Z_FORWARD_1)
    {
      motor_forward('z', 1);
    }

    if (componentId == NEX_BUT_Z_FORWARD_10)
    {
      motor_forward('z', 10);
    }

    if (componentId == NEX_BUT_Z_BACK_1)
    {
      motor_back('z', 1);
    }

    if (componentId == NEX_BUT_Z_BACK_10)
    {
      motor_back('z', 10);
    }

    if (componentId == NEX_BUT_W_OPEN)
    {
      motor_W_open();
    }

    if (componentId == NEX_BUT_W_CLOSE)
    {
      motor_W_close();
    }

    if (componentId == NEX_BUT_SAVE_OFFSET)
    {
      machine_progress.nx_save_axis_page_offset();
    }
    if (componentId == NEX_BUT_SAVE_PLUS)
    {
      machine_progress.nx_save_axis_page_plus();
    }
    if (componentId == NEX_BUT_SAVE_SPEED)
    {
      machine_progress.nx_save_axis_page_speed();
      motor_set_speed_init();
    }
    if (componentId == NEX_BUT_SAVE_ACC)
    {
      machine_progress.nx_save_axis_page_acc();
      motor_set_acc_init();
    }
    if (componentId == NEX_KEYBOARD_PAGE_INIT)
    {
      machine_progress.key_board_flag = true;
    }
    if (componentId == NEX_BUT_RESET_ALL_AXIS)
    {
      homing_machine();
      motor_set_acc_init();
      motor_set_speed_init();
      motor_reset_nx_position();
      machine_progress.nx_axis_page_init();
    }
    if (componentId == NEX_BUT_RESET_X)
    {
      digitalWrite(AirSuckPicker, HIGH);
    }
    if (componentId == NEX_BUT_RESET_Y)
    {
      digitalWrite(AirSuckPicker, LOW);
    }
    if (componentId == NEX_BUT_RESET_Z)
    {
      digitalWrite(DropCylinder, HIGH);
      delay(1000);
      digitalWrite(DropCylinder, LOW);
    }
    if (componentId == NEX_RESET_DEVICE1)
    {
      machine_progress.resetFunc();
    }

    break;

  case 8: // page CONNECTION
    if (componentId == NEX_CONNECTION_PAGE_INIT)
    {
      machine_progress.nx_update_connection_page();
    }
    if (componentId == NX_BUT_SAVE_MAC)
    {
      machine_progress.nx_save_machine_mac();
    }
    if (componentId == NX_BUT_SAVE_ETHERNET_PARAMETERS)
    {
      machine_progress.nx_save_ethernet_parameters();
    }
    if (componentId == NEX_KEYBOARD2_PAGE_INIT)
    {
      machine_progress.key_board_flag = true;
    }
    if (componentId == NEX_RESET_DEVICE2)
    {
      machine_progress.resetFunc();
    }
    break;

  case 9: // page ABOUT
    if (componentId == NEX_ABOUT_PAGE_INIT)
    {
      machine_progress.nx_update_about_page();
    }
    if (componentId == NEX_ABOUT_PAGE_EXIT)
    {
    }
    if (componentId == NX_BUT_SAVE_BUILDING)
    {
      machine_progress.nx_save_building_name();
    }
    if (componentId == NX_BUT_SAVE_DEVICE_ID)
    {
      machine_progress.nx_save_device_id();
    }
    if (componentId == NX_BUT_SAVE_DEVICE_NAME)
    {
      machine_progress.nx_save_device_name();
    }
    if (componentId == NX_BUT_TABLE_LED)
    {
      if (!machine_progress.machine_about_page.table_led_flag)
      {
        Serial.println("TABLE on");
        digitalWrite(TableLED, HIGH);
        machine_progress.nx_save_table_led_flag_status(true);
      }
      else
      {
        Serial.println("TABLE off");
        digitalWrite(TableLED, LOW);
        machine_progress.nx_save_table_led_flag_status(false);
      }
    }
    if (componentId == NX_BUT_FRAME_LED)
    {
      if (!machine_progress.machine_about_page.frame_led_flag)
      {
        Serial.println("FRAME on");
        digitalWrite(MachineLED, HIGH);
        machine_progress.nx_save_frame_led_flag_status(true);
      }
      else
      {
        Serial.println("FRAME off");
        digitalWrite(MachineLED, LOW);
        machine_progress.nx_save_frame_led_flag_status(false);
      }
    }
    if (componentId == NEX_RESET_DEVICE3)
    {
      machine_progress.resetFunc();
    }
    break;
  }
}
void setup_machine_hardware()
{
  if (machine_progress.machine_about_page.table_led_flag == true)
  {
    digitalWrite(TableLED, HIGH);
  }
  else
  {
    digitalWrite(TableLED, LOW);
  }
  if (machine_progress.machine_about_page.frame_led_flag == true)
  {
    digitalWrite(MachineLED, HIGH);
  }
  else
  {
    digitalWrite(MachineLED, LOW);
  }
}
void ethernet_checking()
{
  machine_progress.machine_connection_page.check_ethernet_module_status();
}
void sensors_checking()
{
  if (digitalRead(OvertravelW1) == HIGH || digitalRead(OvertravelW2) == HIGH)
  {
    nextion.nex_set_vis("b31", 1);
  }
  else
  {
    nextion.nex_set_vis("b31", 0);
  }
  if (digitalRead(HomeX) == HIGH)
  {
    nextion.nex_set_vis("b28", 1);
  }
  else
  {
    nextion.nex_set_vis("b28", 0);
  }
  if (digitalRead(HomeY) == HIGH)
  {
    nextion.nex_set_vis("b29", 1);
  }
  else
  {
    nextion.nex_set_vis("b29", 0);
  }
  if (digitalRead(HomeZ) == HIGH)
  {
    nextion.nex_set_vis("b30", 1);
  }
  else
  {
    nextion.nex_set_vis("b30", 0);
  }
}
void air_checking()
{
  digitalWrite(AirSuckPicker, HIGH);
  delay(100);
  while (digitalRead(AirSuplied))
  {
    Serial.println("Please supply airpressure");
    delay(100);
  }
  Serial.println("Airpressure success");
  digitalWrite(AirSuckPicker, LOW);
}

void udp_listening()
{
  machine_progress.machine_connection_page.udp_checking();
  udp_buffer_progress();
}
void udp_buffer_progress()
{
  String buffer_string(machine_progress.machine_connection_page.ethernet_parameters.packetBuffer);
  buffer_string = machine_progress.machine_connection_page.ethernet_parameters.packetBuffer;

  int count = 0;
  int string_len = buffer_string.length() + 1;

  if (buffer_string != NULL)
  {
    for (int i = 0; i < string_len; i++)
    {
      count += (buffer_string[i] == ':');
    }
    for (int i = 0; i < count; i++)
    {
      String parameter = machine_progress.getParameter_fromBuffer(buffer_string, '<', '>');
      String name = machine_progress.getName_fromParameter(parameter, ':');
      String value = machine_progress.getstringValue_fromParameter(parameter, ':');
      parameter_checking(name, value);

      buffer_string = buffer_string.substring(machine_progress.character_count + 1);
    }
  }
  memset(machine_progress.machine_connection_page.ethernet_parameters.packetBuffer, 0, sizeof(machine_progress.machine_connection_page.ethernet_parameters.packetBuffer));
}
void parameter_checking(String name, String n_value)
{
  const char *index_char;
  index_char = n_value.c_str();
  int value = atoi(index_char);
  buffer_speed_check(name, value);
  picking_check(name, value);
  funtions_check(name, value);
  buffer_ethernet_parameter_check(name, n_value);
}

void buffer_speed_check(String name, int value)
{
  for (int i = 0; i < 4; i++)
  {
    if (strcmp(machine_progress.speed_array[i], name.c_str()) == 0)
    {
      char axis = name.charAt(name.length() - 1);
      machine_progress.nx_save_axis_page_specific_speed(axis, value);
      motor_set_speed_init();
      machine_progress.nx_update_axis_page();
      break;
    }
  }
}
void picking_check(String position, int needleqty)
{
  if (machine_progress.park)
  {
    machine_progress.machine_connection_page.ethernet_parameters.set_message("in_parking_place");
    machine_progress.machine_connection_page.udp_reply_msg();
    return;
  }
  bool complete_status = true;
  int position_name_len = position.length();
  if (position_name_len == 2 && needleqty <= 5)
  {
    int x_scale = 0;
    int y_scale = 0;
    int z_scale = 0;

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
    homing_machine_before_pick();
    delay(500);
    stepperX.moveTo((machine_progress.machine_axis_page.x_offset + machine_progress.machine_axis_page.x_plus * x_scale) * machine_progress.xresolution);
    stepperY.moveTo((machine_progress.machine_axis_page.y_offset + machine_progress.machine_axis_page.y_plus * y_scale) * machine_progress.yresolution);
    stepperZ.moveTo(0 - 15 * machine_progress.zresolution);
    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0 || stepperZ.distanceToGo() != 0)
    {
      stepperX.run();
      stepperY.run();
      stepperZ.run();
    }

    digitalWrite(AirSuckPicker, HIGH);

    stepperZ.moveTo(0 - (machine_progress.machine_axis_page.z_offset - machine_progress.machine_axis_page.z_plus * z_scale) * machine_progress.zresolution);
    while (stepperZ.distanceToGo() != 0)
    {
      stepperZ.run();
      if (!digitalRead(NeedleSucked) && stepperZ.distanceToGo() < (-6 * machine_progress.zresolution))
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
        machine_progress.machine_connection_page.ethernet_parameters.set_message("Higher quantity in stock");
        complete_status = false;
        break;
      }
    }
    if (complete_status)
    {
      bool sucked = true;
      stepperZ.moveTo(0 - 15 * machine_progress.zresolution);
      while (stepperZ.distanceToGo() != 0)
      {
        if (digitalRead(NeedleSucked))
        {
          digitalWrite(AirSuckPicker, LOW);
          stepperZ.stop();
          while (stepperZ.distanceToGo() != 0)
          {
            stepperZ.run();
          }
          sucked = false;
          break;
        }
        else
        {
          stepperZ.run();
        }
      }
      if (sucked)
      {
        if (digitalRead(PickerDetector))
        {
          stepperX.moveTo(machine_progress.droper_position[0] * machine_progress.xresolution);
          stepperY.moveTo(machine_progress.droper_position[1] * machine_progress.yresolution);
          while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
          {
            if (digitalRead(NeedleSucked))
            {
              sucked = false;
              break;
            }
            else
            {
              stepperX.run();
              stepperY.run();
            }
          }
          if (sucked)
          {
            bool needle_stucked = false;
            int int_camera = 0; // 0: null , 1: true, 3: false
            bool camera;
            int count = 0;
            stepperZ.moveTo(0 - machine_progress.droper_position[2] * machine_progress.zresolution); // machine_progress.droper_position[2] <=> droperZ position
            while (stepperZ.distanceToGo() != 0)
            {
              stepperZ.run();
            }

            digitalWrite(AirSuckPicker, LOW);

            stepperZ.moveTo(0);
            while (stepperZ.distanceToGo() != 0)
            {
              stepperZ.run();
            }
            stepperZ.setCurrentPosition(0);
            ///////////
            Serial.println("camera checking");
            machine_progress.machine_connection_page.ethernet_parameters.set_message("check_camera");
            machine_progress.machine_connection_page.udp_reply_msg();
            while (1)
            {
              int_camera = camera_checking();
              if (int_camera == 0)
              {
                count++;
                if (count == 100)
                {
                  camera = false;
                  break;
                }
              }
              else if (int_camera == 1)
              {
                camera = true;
                break;
              }
              else
              {
                camera = false;
                break;
              }
              delay(100);
            }
            //////////
            Serial.println(camera ? "camera: true" : "camera: false");
            if (camera)
            {
              digitalWrite(DropCylinder, HIGH);
              while (!digitalRead(DropperDetector))
              {
                count++;
                if (count == 100)
                {
                  needle_stucked = true;
                  break;
                }
                delay(100);
              }
              if (needle_stucked)
              {
                digitalWrite(DropCylinder, LOW);
                stepperX.moveTo(0);
                stepperY.moveTo(0);
                while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                {
                  stepperX.run();
                  stepperY.run();
                }
                stepperX.setCurrentPosition(0);
                stepperY.setCurrentPosition(0);
                machine_progress.machine_connection_page.ethernet_parameters.set_message("needle_stucked");
                complete_status = false;
              }
              else
              {
                digitalWrite(DropCylinder, LOW);
                stepperX.moveTo(0);
                stepperY.moveTo(0);
                while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
                {
                  stepperX.run();
                  stepperY.run();
                }
                stepperX.setCurrentPosition(0);
                stepperY.setCurrentPosition(0);
                machine_progress.machine_connection_page.ethernet_parameters.set_message("needle_supplied");
                complete_status = true;
                ////////
              }
            }
            else
            {
              stepperZ.moveTo(0 - machine_progress.droper_position[2] * machine_progress.zresolution);
              while (stepperZ.distanceToGo() != 0)
              {
                stepperZ.run();
              }
              digitalWrite(AirSuckPicker, HIGH);
              stepperZ.moveTo(0 - 15 * machine_progress.zresolution);
              while (stepperZ.distanceToGo() != 0)
              {
                stepperZ.run();
              }
              delay(300);
              stepperX.moveTo((machine_progress.machine_axis_page.x_offset + machine_progress.machine_axis_page.x_plus * x_scale) * machine_progress.xresolution);
              stepperY.moveTo((machine_progress.machine_axis_page.y_offset + machine_progress.machine_axis_page.y_plus * y_scale) * machine_progress.yresolution);
              while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
              {
                stepperX.run();
                stepperY.run();
              }
              stepperZ.moveTo(0 - (machine_progress.machine_axis_page.z_offset - machine_progress.machine_axis_page.z_plus * z_scale) * machine_progress.zresolution);
              while (stepperZ.distanceToGo() != 0)
              {
                stepperZ.run();
              }
              digitalWrite(AirSuckPicker, LOW);
              stepperZ.moveTo(0);
              while (stepperZ.distanceToGo() != 0)
              {
                stepperZ.run();
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
              machine_progress.machine_connection_page.ethernet_parameters.set_message("camera_failed");
              complete_status = false;
            }
          }
          else
          {
            stepperX.stop();
            stepperY.stop();
            while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
            {
              stepperX.run();
              stepperY.run();
            }
            digitalWrite(AirSuckPicker, LOW);
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
            machine_progress.machine_connection_page.ethernet_parameters.set_message("needle_dropped");
            complete_status = false;
          }
        }
        else
        {
          digitalWrite(AirSuckPicker, LOW);
          stepperZ.moveTo(0);
          while (stepperZ.distanceToGo() != 0)
          {
            stepperZ.run();
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
          machine_progress.machine_connection_page.ethernet_parameters.set_message("needle_stock_empty");
          complete_status = false;
        }
      }
      else
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
        machine_progress.machine_connection_page.ethernet_parameters.set_message("needle_dropped");
        complete_status = false;
      }
    }
    machine_progress.machine_connection_page.ethernet_parameters.set_parameter("status");
    machine_progress.machine_connection_page.ethernet_parameters.set_parameter_value(complete_status);
    machine_progress.machine_connection_page.udp_reply_para();
    machine_progress.machine_connection_page.udp_reply_msg();
  }
}
void funtions_check(String name, int value)
{
  if (name == "reset")
  {
    machine_progress.resetFunc();
  }

  if (name == "led1")
  {
    if (value == 1)
    {
      digitalWrite(MachineLED, HIGH);
      machine_progress.nx_save_frame_led_flag_status(true);
    }
    else
    {
      digitalWrite(MachineLED, LOW);
      machine_progress.nx_save_frame_led_flag_status(false);
    }
  }
  if (name == "led2")
  {
    if (value == 1)
    {
      digitalWrite(TableLED, HIGH);
      machine_progress.nx_save_table_led_flag_status(true);
    }
    else
    {
      digitalWrite(TableLED, LOW);
      machine_progress.nx_save_table_led_flag_status(false);
    }
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
  }
  if (name == "parking")
  {
    if (machine_progress.park == true && value == 1)
    {
      return;
    }
    else if (machine_progress.park == true && value == 0)
    {
      machine_progress.park = machine_unparking();
      machine_progress.machine_connection_page.ethernet_parameters.set_message("unparking_success");
      machine_progress.machine_connection_page.udp_reply_msg();
    }
    else if (machine_progress.park == false && value == 1)
    {
      machine_progress.park = machine_parking(machine_progress.parking_pos[0] * machine_progress.xresolution, machine_progress.parking_pos[1] * machine_progress.yresolution, machine_progress.parking_pos[2] * machine_progress.zresolution);
      machine_progress.machine_connection_page.ethernet_parameters.set_message("parking_success");
      machine_progress.machine_connection_page.udp_reply_msg();
    }
    else
    {
      return;
    }
  }
}
int camera_checking()
{
  machine_progress.machine_connection_page.udp_c_checking();
  String c_buffer_string(machine_progress.machine_connection_page.ethernet_parameters.c_packetBuffer);
  c_buffer_string = machine_progress.machine_connection_page.ethernet_parameters.c_packetBuffer;

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
      String c_parameter = machine_progress.getParameter_fromBuffer(c_buffer_string, '<', '>');
      String c_name = machine_progress.getName_fromParameter(c_parameter, ':');
      String c_value = machine_progress.getstringValue_fromParameter(c_parameter, ':');
      const char *c_index_char;
      c_index_char = c_value.c_str();
      int c_int_value = atoi(c_index_char);
      if (c_name == "camera")
      {
        if (c_int_value == 1)
        {
          memset(machine_progress.machine_connection_page.ethernet_parameters.c_packetBuffer, 0, sizeof(machine_progress.machine_connection_page.ethernet_parameters.c_packetBuffer));
          c_buffer_string = c_buffer_string.substring(machine_progress.c_character_count + 1);
          return 1;
        }
        else
        {
          memset(machine_progress.machine_connection_page.ethernet_parameters.c_packetBuffer, 0, sizeof(machine_progress.machine_connection_page.ethernet_parameters.c_packetBuffer));
          c_buffer_string = c_buffer_string.substring(machine_progress.c_character_count + 1);
          return 2;
        }
      }
    }
  }
  else
  {
    return 0;
  }
}
void buffer_ethernet_parameter_check(String name, String value)
{
  for (int i = 0; i <= 2; i++)
  {
    if (strcmp(machine_progress.connection_array[i], name.c_str()) == 0)
    {
      Serial.println(name);
      Serial.println(value);
    }
  }
}
