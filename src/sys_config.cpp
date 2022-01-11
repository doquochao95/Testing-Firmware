#include "sys_config.h"

machine_progress_class machine_progress;
nextion_extension nextion;
void start_up()
{
  io_init();
  nextion.nex_init();
  PAGE_LOADING_EVENT.root_attachCallback(PAGE_LOADING_EVENT_CALLBACK);
  local_data_init();
  motor_set_speed_init();
  motor_set_acc_init();
  setup_machine_hardware();
}
void io_init()
{
  Serial.begin(115200); //debug baudrate
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
}
void local_data_init()
{
  Serial.println("Initialing local system");
  machine_progress.init();
}
void ethernet_init()
{
  Serial.println("Initializing ethernet module");
  nex_send_message("Setting up ethernet module...");
  knife_capture.ethernet_handle.init(ETHERNET_CS_PIN, ETHERNET_RST_PIN, ethernet_data_received_callback);
  //initialize ethernet module
  int exception = knife_capture.ethernet_handle.setting_up_ethernet_module();

  printf("Initialize ethernet module exception code: %d\r\n", exception);
  nex_send_message("Setting up done");
}
void PAGE_LOADING_EVENT_CALLBACK(uint8_t pageId, uint8_t componentId, uint8_t eventType)
{
  // function_log();
  //Serial.println("Nextion event callback: Page:" + String(pageId) + "ComponentId:" + String(componentId));
  switch (pageId)
  {
  case 7: //page AXIS
    if (componentId == NEX_AXIS_PAGE_INIT)
    {
      //update movemnt page
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
      digitalWrite(MachineLED, HIGH);
      digitalWrite(TableLED, HIGH);
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
      motor_reset_stepper_current_position();
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
    break;

  case 8: //page CONNECTION
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
    break;

  case 9: //page ABOUT
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
