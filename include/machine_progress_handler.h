#ifndef machine_progress_handler_h
#define machine_progress_handler_h

#include "machine_axis_parameters_handle.h"
#include "machine_ethernet_handler.h"
#include "machine_identity_parameters_handler.h"
#include <nextion_extension.h>

class machine_progress_class
{
private:
  nextion_extension nextion;

public:
  axis_parameters_def machine_axis_page = axis_parameters_def(EEPROM_START_PARAMETERS_ADD); // machine_axis_page_def(int storage_address)
  ethernet_module_def machine_connection_page = ethernet_module_def(EEPROM_ETHERNET_START_ADD);
  identity_parameters_def machine_about_page = identity_parameters_def(EEPROM_IDENTITY_START_ADD);

  const char *offset_array[4] = {"offsetx", "offsety", "offsetz", "offsetw"};
  const char *plus_array[4] = {"plusx", "plusy", "plusz", "plusw"};
  const char *speed_array[4] = {"speedx", "speedy", "speedz", "speedw"};
  const char *accel_array[4] = {"accelx", "accely", "accelz", "accelw"};
  const char *connection_array[3] = {"localip", "remoteip","localport"};

  const char *slot_array[40] = {"a1", "a2", "a3", "a4", "a5", "b1", "b2", "b3", "b4", "b5", "c1", "c2", "c3", "c4", "c5", "d1", "d2", "d3", "d4", "d5", "e1", "e2", "e3", "e4", "e5", "f1", "f2", "f3", "f4", "f5", "g1", "g2", "g3", "g4", "g5", "h1", "h2", "h3", "h4", "h5"};

  int character_count;
int c_character_count;
  char parameter_name[10];
  char parameter_value[10];

  int xresolution = 40; // step/mm
  int yresolution = 40;
  int zresolution = 100;
  int wresolution = 200;

  int droper_position[3] = {334, 346, 61}; //{x,y,z}
  int parking_pos[3] = {334, 100, 50}; //{x,y,z}
  bool park;

  bool init_flag = true;
  bool key_board_flag = false;

  void (*resetFunc)(void) = 0; // Reset funtion

  void init()
  {
    machine_axis_page.eeprom_read_axis_parameter();
    machine_connection_page.ethernet_parameters.eeprom_read_ethernet_parameters();
    machine_about_page.eeprom_read_identity_parameters();
  }
  // AXIS PAGE
  void nx_update_axis_page()
  {
    function_log();
    if (key_board_flag == false)
    {
      nx_clear_movement_page();
      nx_axis_page_init();
      nx_update_axis_parameters_page();
      nx_set_w_needle_table_button_status();
    }
    else
    {
      nx_axis_page_init();
      key_board_flag = false;
    }
  }
  void nx_clear_movement_page()
  {
    function_log();
    nextion.setNumberProperty("AXIS", "n0.txt", 0);
    nextion.setNumberProperty("AXIS", "n1.txt", 0);
    nextion.setNumberProperty("AXIS", "n2.txt", 0);
    nextion.setNumberProperty("AXIS", "n3.txt", 0);
    nextion.setNumberProperty("AXIS", "n4.txt", 0);
    nextion.setNumberProperty("AXIS", "n5.txt", 0);
    nextion.setNumberProperty("AXIS", "n6.txt", 0);
    nextion.setNumberProperty("AXIS", "n7.txt", 0);
    nextion.setNumberProperty("AXIS", "n8.txt", 0);
    nextion.setNumberProperty("AXIS", "n9.txt", 0);
    nextion.setNumberProperty("AXIS", "n10.txt", 0);
    nextion.setNumberProperty("AXIS", "n11.txt", 0);
    nextion.setNumberProperty("AXIS", "n12.txt", 0);
    nextion.setNumberProperty("AXIS", "n13.txt", 0);
    nextion.setNumberProperty("AXIS", "n14.txt", 0);
    nextion.setNumberProperty("AXIS", "n15.txt", 0);
    nextion.setNumberProperty("AXIS", "n16.txt", 0);
    nextion.setNumberProperty("AXIS", "n17.txt", 0);
    nextion.setNumberProperty("AXIS", "n18.txt", 0);
  }
  void nx_set_xyz_position()
  {
    function_log();
    // Serial.println("Funtion: " + String(__func__) + " xposition: " + String(machine_axis_page.xposition) + " yposition: " + String(machine_axis_page.yposition) + " zposition: " + String(machine_axis_page.zposition));
    nextion.setNumberProperty("AXIS", "n0.val", machine_axis_page.xposition);
    nextion.setNumberProperty("AXIS", "n1.val", machine_axis_page.yposition);
    nextion.setNumberProperty("AXIS", "n2.val", machine_axis_page.zposition);
  }
  void nx_axis_page_init()
  {
    function_log();
    int last_posX = machine_axis_page.eeprom_read_position_parameters('x');
    int last_posY = machine_axis_page.eeprom_read_position_parameters('y');
    int last_posZ = machine_axis_page.eeprom_read_position_parameters('z');
    // Serial.println("Funtion: " + String(__func__) + " Last position: " + String(last_posX) + " Last position: " + String(last_posY) + " Last position: " + String(last_posZ));
    nextion.setNumberProperty("AXIS", "n0.val", last_posX);
    nextion.setNumberProperty("AXIS", "n1.val", last_posY);
    nextion.setNumberProperty("AXIS", "n2.val", last_posZ);
  }
  void nx_update_axis_parameters_page()
  {
    function_log();
    if (init_flag == true)
    {
      nextion.setNumberProperty("AXIS", "n3.val", machine_axis_page.x_offset);
      nextion.setNumberProperty("AXIS", "n4.val", machine_axis_page.y_offset);
      nextion.setNumberProperty("AXIS", "n5.val", machine_axis_page.z_offset);
      nextion.setNumberProperty("AXIS", "n6.val", machine_axis_page.w_offset);

      nextion.setNumberProperty("AXIS", "n7.val", machine_axis_page.x_plus);
      nextion.setNumberProperty("AXIS", "n8.val", machine_axis_page.y_plus);
      nextion.setNumberProperty("AXIS", "n9.val", machine_axis_page.z_plus);
      nextion.setNumberProperty("AXIS", "n10.val", machine_axis_page.w_plus);

      nextion.setNumberProperty("AXIS", "n11.val", machine_axis_page.x_speed);
      nextion.setNumberProperty("AXIS", "n12.val", machine_axis_page.y_speed);
      nextion.setNumberProperty("AXIS", "n13.val", machine_axis_page.z_speed);
      nextion.setNumberProperty("AXIS", "n14.val", machine_axis_page.w_speed);

      nextion.setNumberProperty("AXIS", "n15.val", machine_axis_page.x_acceleration);
      nextion.setNumberProperty("AXIS", "n16.val", machine_axis_page.y_acceleration);
      nextion.setNumberProperty("AXIS", "n17.val", machine_axis_page.z_acceleration);
      nextion.setNumberProperty("AXIS", "n18.val", machine_axis_page.w_acceleration);
    }
  }
  void nx_set_w_needle_table_button_status()
  {
    function_log();
    machine_axis_page.eeprom_get_w_status();
    bool status = machine_axis_page.w_needle_table_status_flag;
    // Serial.println(status ? "W_needle_table_flag: true" : "W_needle_table_flag: false");
    if (status == false)
    {
      nextion.nex_set_vis("b17", 1);
      nextion.nex_set_vis("b18", 0);
    }
    else
    {
      nextion.nex_set_vis("b17", 0);
      nextion.nex_set_vis("b18", 1);
    }
  }
  void nx_save_axis_page_offset()
  {
    function_log();
    int x_offset;
    int y_offset;
    int z_offset;
    int w_offset;
    x_offset = nextion.getNumberProperty("AXIS", "n3.val");
    y_offset = nextion.getNumberProperty("AXIS", "n4.val");
    z_offset = nextion.getNumberProperty("AXIS", "n5.val");
    w_offset = nextion.getNumberProperty("AXIS", "n6.val");
    Serial.println(" x_offset: " + String(x_offset) + " y_offset: " + String(y_offset) + " z_offset: " + String(z_offset) + " w_offset: " + String(w_offset));
    if (x_offset < 0 || y_offset < 0 || z_offset < 0 || w_offset < 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_axis_page.axis_page_setup_offset_parameter(x_offset, y_offset, z_offset, w_offset);
    machine_axis_page.eeprom_write_offset_parameters();
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_axis_page_plus()
  {
    function_log();
    int x_plus = 0;
    int y_plus = 0;
    int z_plus = 0;
    int w_plus = 0;
    x_plus = nextion.getNumberProperty("AXIS", "n7.val");
    y_plus = nextion.getNumberProperty("AXIS", "n8.val");
    z_plus = nextion.getNumberProperty("AXIS", "n9.val");
    w_plus = nextion.getNumberProperty("AXIS", "n10.val");
    Serial.println(" x_plus: " + String(x_plus) + " y_plus: " + String(y_plus) + " z_plus: " + String(z_plus) + " w_plus: " + String(w_plus));
    if (x_plus < 0 || y_plus < 0 || z_plus < 0 || w_plus < 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_axis_page.axis_page_setup_plus_parameter(x_plus, y_plus, z_plus, w_plus);
    machine_axis_page.eeprom_write_plus_parameters();
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_axis_page_speed()
  {
    function_log();
    int x_speed = 0;
    int y_speed = 0;
    int z_speed = 0;
    int w_speed = 0;
    x_speed = nextion.getNumberProperty("AXIS", "n11.val");
    y_speed = nextion.getNumberProperty("AXIS", "n12.val");
    z_speed = nextion.getNumberProperty("AXIS", "n13.val");
    w_speed = nextion.getNumberProperty("AXIS", "n14.val");
    Serial.println(" x_speed: " + String(x_speed) + " y_speed: " + String(y_speed) + " z_speed: " + String(z_speed) + " w_speed: " + String(w_speed));
    if (x_speed < 0 || y_speed < 0 || z_speed < 0 || w_speed < 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_axis_page.axis_page_setup_speed_parameter(x_speed, y_speed, z_speed, w_speed);
    machine_axis_page.eeprom_write_speed_parameters();
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_axis_page_specific_speed(char axis, int value)
  {
    function_log();
    if (value < 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_axis_page.axis_page_setup_specific_speed_parameter(axis, value);
    machine_axis_page.eeprom_write_specific_speed_parameters(axis);
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_axis_page_acc()
  {
    function_log();
    int x_acc = 0;
    int y_acc = 0;
    int z_acc = 0;
    int w_acc = 0;
    x_acc = nextion.getNumberProperty("AXIS", "n15.val");
    y_acc = nextion.getNumberProperty("AXIS", "n16.val");
    z_acc = nextion.getNumberProperty("AXIS", "n17.val");
    w_acc = nextion.getNumberProperty("AXIS", "n18.val");
    Serial.println(" x_acc: " + String(nextion.getNumberProperty("AXIS", "n15.val")) + " y_acc: " + String(y_acc) + " z_acc: " + String(z_acc) + " w_acc: " + String(w_acc));
    if (x_acc < 0 || y_acc < 0 || z_acc < 0 || w_acc < 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_axis_page.axis_page_setup_acc_parameter(x_acc, y_acc, z_acc, w_acc);
    machine_axis_page.eeprom_write_acceleration_parameters();
    nextion.nex_send_message("Saved successfully");
  }
  // CONNECTION PAGE
  void nx_update_connection_page()
  {
    function_log();
    if (key_board_flag == false)
    {
      nextion.setStringProperty("CONNECTION", "t0.txt", machine_connection_page.ethernet_parameters.remote_ip_str);
      nextion.setStringProperty("CONNECTION", "t1.txt", machine_connection_page.ethernet_parameters.local_ip_str);
      nextion.setNumberProperty("CONNECTION", "n0.val", machine_connection_page.ethernet_parameters.localPort);

      const char *props[6] = {"n1.val", "n2.val", "n3.val", "n4.val", "n5.val", "n6.val"};
      for (uint8_t i = 0; i < sizeof(machine_connection_page.ethernet_parameters.MAC); i++)
      {
        nextion.setNumberProperty("CONNECTION", props[i], machine_connection_page.ethernet_parameters.MAC[i]);
      }
    }
    else
    {
      key_board_flag = false;
      return;
    }
  }
  void nx_save_machine_mac()
  {
    function_log();
    char remoteip[20]{0};
    nextion.nex_send_message("Saving...");
    nextion.getStringProperty("CONNECTION", "t0.txt", remoteip, sizeof(remoteip));
    const char *props[6] = {"n1.val", "n2.val", "n3.val", "n4.val", "n5.val", "n6.val"};
    uint8_t mac[6]{0};
    for (int i = 0; i < 6; i++)
    {
      int mac_element = nextion.getNumberProperty("CONNECTION", props[i]);
      Serial.println("mac[" + String(i) + "]: " + String(mac_element));
      if (mac_element > 255 || mac_element == 0 || mac_element == -1)
      {
        nextion.nex_send_message("Invalid MAC");
        return;
      }
      mac[i] = (uint8_t)mac_element;
    }
    machine_connection_page.ethernet_parameters.setup_machine_mac(mac);
    machine_connection_page.ethernet_parameters.eeprom_save_MAC();
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_ethernet_parameters()
  {
    function_log();

    char remoteip[20]{0};
    char localip[20]{0};
    int localport = 0;

    nextion.nex_send_message("Saving...");
    nextion.getStringProperty("CONNECTION", "t0.txt", remoteip, sizeof(remoteip));
    nextion.getStringProperty("CONNECTION", "t1.txt", localip, sizeof(localip));
    localport = nextion.getNumberProperty("CONNECTION", "n0.val");
    Serial.println("localport: " + String(localport));
    if (strlen(remoteip) == 0 || strlen(localip) == 0 || localport == 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_connection_page.ethernet_parameters.setup_ethernet_parameters(remoteip, localip, localport);
    machine_connection_page.ethernet_parameters.eeprom_save_ethernet_parameters();
    nextion.nex_send_message("Saved successfully");
  }
  // ABOUT PAGE
  void nx_update_about_page()
  {
    function_log();
    if (key_board_flag == false)
    {
      nextion.setStringProperty("ABOUT", "t0.txt", machine_about_page.building_name);
      nextion.setNumberProperty("ABOUT", "n0.val", machine_about_page.device_id);
      nextion.setStringProperty("ABOUT", "t1.txt", machine_about_page.device_name);
      if (machine_about_page.table_led_flag == true)
      {
        nextion.setNumberProperty("bt0.val", 1);
      }
      else
      {
        nextion.setNumberProperty("bt0.val", 0);
      }
      if (machine_about_page.frame_led_flag == true)
      {
        nextion.setNumberProperty("bt1.val", 1);
      }
      else
      {
        nextion.setNumberProperty("bt1.val", 0);
      }
    }
    else
    {
      key_board_flag = false;
      return;
    }
  }
  void nx_save_building_name()
  {
    function_log();

    char building_name[15]{0};

    nextion.nex_send_message("Saving...");
    nextion.getStringProperty("ABOUT", "t0.txt", building_name, sizeof(building_name));
    Serial.println("building_name: " + String(building_name));
    if (strlen(building_name) == 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_about_page.setup_building_name(building_name);
    machine_about_page.eeprom_save_building_name();
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_device_id()
  {
    int device_id = 0;
    char buildingname[20]{0};
    nextion.nex_send_message("Saving...");
    nextion.getStringProperty("ABOUT", "t0.txt", buildingname, sizeof(buildingname));
    device_id = nextion.getNumberProperty("ABOUT", "n0.val");
    Serial.println("device_id: " + String(device_id));
    if (device_id == 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_about_page.setup_device_id(device_id);
    machine_about_page.eeprom_save_device_id();
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_device_name()
  {
    function_log();

    char device_name[20]{0};

    nextion.nex_send_message("Saving...");
    nextion.getStringProperty("ABOUT", "t1.txt", device_name, sizeof(device_name));
    Serial.println("device_name: " + String(device_name));
    if (strlen(device_name) == 0)
    {
      nextion.nex_send_message("Invalid data");
      return;
    }
    machine_about_page.setup_device_name(device_name);
    machine_about_page.eeprom_save_device_name();
    nextion.nex_send_message("Saved successfully");
  }
  void nx_save_table_led_flag_status(bool value)
  {
    function_log();
    machine_about_page.setup_table_led_flag_status(value);
    machine_about_page.eeprom_put_table_led_flag_status();
  }
  void nx_save_frame_led_flag_status(bool value)
  {
    function_log();
    machine_about_page.setup_frame_led_flag_status(value);
    machine_about_page.eeprom_put_frame_led_flag_status();
  }

  String getParameter_fromBuffer(String string, char startSeparator, char endSeparator)
  {
    bool flag = false;
    int z = 0;
    int string_len = string.length() + 1;
    char char_array[string_len];
    string.toCharArray(char_array, string_len);
    char strtokIndx[string_len];
    memset(strtokIndx, 0, sizeof(strtokIndx));
    for (int i = 0; i < string_len - 1; i++)
    {
      if (!flag)
      {
        if (char_array[i] == startSeparator)
        {
          flag = true;
          continue;
        }
        else
        {
          continue;
        }
      }
      else
      {
        if (char_array[i] == endSeparator)
        {
          character_count = i;
          break;
        }
        else
        {
          strtokIndx[z] = char_array[i];
          z++;
          continue;
        }
      }
      break;
    }
    String data = String(strtokIndx);
    return data;
  }
  int getintValue_fromParameter(String string, char separator)
  {
    int data;
    int pos = string.indexOf(separator);
    String index = string.substring(pos + 1);
    const char *index_char;
    index_char = index.c_str();
    data = atoi(index_char);
    return data;
  }
  String getName_fromParameter(String string, char separator)
  {
    int pos = string.indexOf(separator);
    String index = string.substring(0, pos);
    return index;
  }
  String getstringValue_fromParameter(String string, char separator)
  {
    int pos = string.indexOf(separator);
    String index = string.substring(pos + 1);
    return index;
  }
};
#endif