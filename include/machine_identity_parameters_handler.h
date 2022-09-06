#ifndef machine_identity_parameters_handler_h
#define machine_identity_parameters_handler_h

#include "global_config.h"
#include "eeprom_extension.h"

struct identity_parameters_def
{
private:
    int Storage_addr;
    int eeprom_building_name_addr = 0;
    int eeprom_device_id_addr = 0;
    int eeprom_device_name_addr = 0;

    eeprom_extension eeprom;

    void eeprom_save_building_name(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(building_name); i++)
        {
            eeprom.eeprom_write<char>(building_name[i], address + i);
        }
        EEPROM.end();
    }
    void eeprom_read_building_name(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(building_name); i++)
        {
            building_name[i] = eeprom.eeprom_read<char>(address + i);
        }
        EEPROM.end();
    }

    void eeprom_save_device_id(int address)
    {
        function_log();
        EEPROM.begin();
        eeprom.eeprom_write<int>(device_id, address);
        EEPROM.end();
    }
    void eeprom_read_device_id(int address)
    {
        function_log();
        EEPROM.begin();
        device_id = eeprom.eeprom_read<int>(address);
        EEPROM.end();
    }

    void eeprom_save_device_name(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(device_name); i++)
        {
            eeprom.eeprom_write<char>(device_name[i], address + i);
        }
        EEPROM.end();
    }
    void eeprom_read_device_name(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(device_name); i++)
        {
            device_name[i] = eeprom.eeprom_read<char>(address + i);
        }
        EEPROM.end();
    }

public:
    char building_name[15] = "Building L";
    int device_id;
    char device_name[15] = "Machine L1";

    bool table_led_flag = false;
    bool frame_led_flag = false;
    identity_parameters_def(int storage_addr)
    {
        identity_parameters_intit(storage_addr);
    }
    void identity_parameters_intit(int storage_addr)
    {
        Storage_addr = storage_addr;
        storage_address_specify();
    }
    void storage_address_specify()
    {
        eeprom_building_name_addr = Storage_addr;
        eeprom_device_id_addr = eeprom_building_name_addr + sizeof(building_name);
        eeprom_device_name_addr = eeprom_device_id_addr + sizeof(device_id);
    }
    void eeprom_read_identity_parameters()
    {
        function_log();
        eeprom_read_building_name(eeprom_building_name_addr);
        eeprom_read_device_id(eeprom_device_id_addr);
        eeprom_read_device_name(eeprom_device_name_addr);
        Serial.println("Building Name: " + String(building_name));
        Serial.println("Device ID: " + String(device_id));
        Serial.println("Device Name: " + String(device_name));
    }

    void eeprom_save_building_name()
    {
        function_log();
        eeprom_save_building_name(eeprom_building_name_addr);
    }
    void eeprom_save_device_id()
    {
        function_log();
        eeprom_save_device_id(eeprom_device_id_addr);
    }
    void eeprom_save_device_name()
    {
        function_log();
        eeprom_save_device_name(eeprom_device_name_addr);
    }

    void setup_building_name(const char *BuildingName)
    {
        function_log();
        memccpy(building_name, BuildingName, 0, sizeof(building_name));
        Serial.println("New Building Name: " + String(building_name));
    }
    void setup_device_id(int DeviceID)
    {
        function_log();
        device_id = DeviceID;
        Serial.println("New Device ID: " + String(device_id));
    }
    void setup_device_name(const char *DeviceName)
    {
        function_log();
        memccpy(device_name, DeviceName, 0, sizeof(device_name));
        Serial.println("New Device Name: " + String(device_name));
    }
    void set_table_led_flag_status(bool value)
    {
        function_log();
        table_led_flag = value;
    }
    void set_frame_led_flag_status(bool value)
    {
        function_log();
        frame_led_flag = value;
    }
};

#endif