#ifndef machine_properties_h
#define machine_properties_h

#include "global_config.h"
#include "global_scope.h"
#include "eeprom_extension.h"

struct axis_parameters_def
{
private:
    int Storage_addr;

    int x_offset_addr = 0;
    int y_offset_addr = 0;
    int z_offset_addr = 0;
    int w_offset_addr = 0;

    int x_plus_addr = 0;
    int y_plus_addr = 0;
    int z_plus_addr = 0;
    int w_plus_addr = 0;

    int x_speed_addr = 0;
    int y_speed_addr = 0;
    int z_speed_addr = 0;
    int w_speed_addr = 0;

    int x_acceleration_addr = 0;
    int y_acceleration_addr = 0;
    int z_acceleration_addr = 0;
    int w_acceleration_addr = 0;

    int x_position_addr = 0;
    int y_position_addr = 0;
    int z_position_addr = 0;

    int w_needle_table_status_addr = 0;

    eeprom_extension eeprom;

    void eeprom_read_offset_parameter(char axis, int addr)
    {
        function_log();
        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            x_offset = eeprom.eeprom_read<int>(addr);
            break;
        case 'y':
            y_offset = eeprom.eeprom_read<int>(addr);
            break;
        case 'z':
            z_offset = eeprom.eeprom_read<int>(addr);
            break;
        case 'w':
            w_offset = eeprom.eeprom_read<int>(addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_read_plus_parameter(char axis, int addr)
    {

        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            x_plus = eeprom.eeprom_read<int>(addr);
            break;
        case 'y':
            y_plus = eeprom.eeprom_read<int>(addr);
            break;
        case 'z':
            z_plus = eeprom.eeprom_read<int>(addr);
            break;
        case 'w':
            w_plus = eeprom.eeprom_read<int>(addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_read_speed_parameter(char axis, int addr)
    {

        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            x_speed = eeprom.eeprom_read<int>(addr);
            break;
        case 'y':
            y_speed = eeprom.eeprom_read<int>(addr);
            break;
        case 'z':
            z_speed = eeprom.eeprom_read<int>(addr);
            break;
        case 'w':
            w_speed = eeprom.eeprom_read<int>(addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_read_acceleration_parameter(char axis, int addr)
    {

        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            x_acceleration = eeprom.eeprom_read<int>(addr);
            break;
        case 'y':
            y_acceleration = eeprom.eeprom_read<int>(addr);
            break;
        case 'z':
            z_acceleration = eeprom.eeprom_read<int>(addr);
            break;
        case 'w':
            w_acceleration = eeprom.eeprom_read<int>(addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_write_offset_parameter(char axis, int addr)
    {
        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            eeprom.eeprom_write<int>(x_offset, addr);
            break;
        case 'y':
            eeprom.eeprom_write<int>(y_offset, addr);
            break;
        case 'z':
            eeprom.eeprom_write<int>(z_offset, addr);
            break;
        case 'w':
            eeprom.eeprom_write<int>(w_offset, addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_write_plus_parameter(char axis, int addr)
    {

        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            eeprom.eeprom_write<int>(x_plus, addr);
            break;
        case 'y':
            eeprom.eeprom_write<int>(y_plus, addr);
            break;
        case 'z':
            eeprom.eeprom_write<int>(z_plus, addr);
            break;
        case 'w':
            eeprom.eeprom_write<int>(w_plus, addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_write_speed_parameter(char axis, int addr)
    {

        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            eeprom.eeprom_write<int>(x_speed, addr);
            break;
        case 'y':
            eeprom.eeprom_write<int>(y_speed, addr);
            break;
        case 'z':
            eeprom.eeprom_write<int>(z_speed, addr);
            break;
        case 'w':
            eeprom.eeprom_write<int>(w_speed, addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_write_acceleration_parameter(char axis, int addr)
    {

        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            eeprom.eeprom_write<int>(x_acceleration, addr);
            break;
        case 'y':
            eeprom.eeprom_write<int>(y_acceleration, addr);
            break;
        case 'z':
            eeprom.eeprom_write<int>(z_acceleration, addr);
            break;
        case 'w':
            eeprom.eeprom_write<int>(w_acceleration, addr);
            break;
        }
        EEPROM.end();
    }
    void eeprom_put_w_needle_table_status()
    {
        EEPROM.begin();
        eeprom.eeprom_put(w_needle_table_status_flag, w_needle_table_status_addr);
        EEPROM.end();
    }
    void eeprom_get_w_needle_table_status()
    {
        EEPROM.begin();
        w_needle_table_status_flag = eeprom.eeprom_get(w_needle_table_status_flag, w_needle_table_status_addr);
        EEPROM.end();
    }

public:
    int x_offset = 0;
    int y_offset = 0;
    int z_offset = 0;
    int w_offset = 0;

    int x_plus = 0;
    int y_plus = 0;
    int z_plus = 0;
    int w_plus = 0;

    int x_speed = 0;
    int y_speed = 0;
    int z_speed = 0;
    int w_speed = 0;

    int x_acceleration = 0;
    int y_acceleration = 0;
    int z_acceleration = 0;
    int w_acceleration = 0;

    int xposition = 0;
    int yposition = 0;
    int zposition = 0;

    bool w_needle_table_status_flag = false;

    void reset()
    {
        xposition = 0;
        yposition = 0;
        zposition = 0;
    }
    void set_xposition(int value)
    {
        xposition = value;
    }
    void set_yposition(int value)
    {
        yposition = value;
    }
    void set_zposition(int value)
    {
        zposition = value;
    }
    void setup()
    {
        x_offset = 0;
        y_offset = 0;
        z_offset = 0;
        w_offset = 0;
    }
    void set_w_status(bool value)
    {
        function_log();
        w_needle_table_status_flag = value;
    }

    axis_parameters_def(int storage_address)
    {
        Serial.println("Initializing Axis Page");
        Storage_addr = storage_address;
        axis_storage_address_specific();
    }

    void axis_storage_address_specific()
    {
        x_offset_addr = Storage_addr;
        y_offset_addr = x_offset_addr + sizeof(x_offset);
        z_offset_addr = y_offset_addr + sizeof(y_offset);
        w_offset_addr = z_offset_addr + sizeof(z_offset);

        x_plus_addr = w_offset_addr + sizeof(w_offset);
        y_plus_addr = x_plus_addr + sizeof(x_plus);
        z_plus_addr = y_plus_addr + sizeof(y_plus);
        w_plus_addr = z_plus_addr + sizeof(z_plus);

        x_speed_addr = w_plus_addr + sizeof(w_plus);
        y_speed_addr = x_speed_addr + sizeof(x_speed);
        z_speed_addr = y_speed_addr + sizeof(y_speed);
        w_speed_addr = z_speed_addr + sizeof(z_speed);

        x_acceleration_addr = w_speed_addr + sizeof(w_speed);
        y_acceleration_addr = x_acceleration_addr + sizeof(x_acceleration);
        z_acceleration_addr = y_acceleration_addr + sizeof(y_acceleration);
        w_acceleration_addr = z_acceleration_addr + sizeof(z_acceleration);

        x_position_addr = w_acceleration_addr + sizeof(w_acceleration);
        y_position_addr = x_position_addr + sizeof(xposition);
        z_position_addr = y_position_addr + sizeof(yposition);

        w_needle_table_status_addr = z_position_addr + sizeof(zposition);
    }

    void axis_page_setup_offset_parameter(int xoffset, int yoffset, int zoffset, int woffset)
    {
        function_log();
        x_offset = xoffset;
        y_offset = yoffset;
        z_offset = zoffset;
        w_offset = woffset;
        Serial.println("New X offset:" + String(x_offset));
        Serial.println("New Y offset:" + String(y_offset));
        Serial.println("New Z offset:" + String(z_offset));
        Serial.println("New W offset:" + String(w_offset));
    }
    void axis_page_setup_plus_parameter(int xplus, int yplus, int zplus, int wplus)
    {
        function_log();
        x_plus = xplus;
        y_plus = yplus;
        z_plus = zplus;
        w_plus = wplus;
        Serial.println("New X plus: " + String(x_plus));
        Serial.println("New Y plus: " + String(y_plus));
        Serial.println("New Z plus: " + String(z_plus));
        Serial.println("New W plus: " + String(w_plus));
    }
    void axis_page_setup_speed_parameter(int xspeed, int yspeed, int zspeed, int wspeed)
    {
        function_log();
        x_speed = xspeed;
        y_speed = yspeed;
        z_speed = zspeed;
        w_speed = wspeed;
        Serial.println("New X speed: " + String(x_speed));
        Serial.println("New Y speed: " + String(y_speed));
        Serial.println("New Z speed: " + String(z_speed));
        Serial.println("New W speed: " + String(w_speed));
    }
    void axis_page_setup_acc_parameter(int xacc, int yacc, int zacc, int wacc)
    {
        function_log();
        x_acceleration = xacc;
        y_acceleration = yacc;
        z_acceleration = zacc;
        w_acceleration = wacc;
        Serial.println("New X acc: " + String(x_acceleration));
        Serial.println("New Y acc: " + String(y_acceleration));
        Serial.println("New Z acc: " + String(z_acceleration));
        Serial.println("New W acc: " + String(w_acceleration));
    }

    void eeprom_read_axis_parameter()
    {
        setup();
        eeprom_read_offset_parameters();
        eeprom_read_plus_parameters();
        eeprom_read_speed_parameters();
        eeprom_read_acceleration_parameters();
        eeprom_get_w_status();
    }

    void eeprom_read_offset_parameters()
    {
        function_log();
        eeprom_read_offset_parameter('x', x_offset_addr);
        eeprom_read_offset_parameter('y', y_offset_addr);
        eeprom_read_offset_parameter('z', z_offset_addr);
        eeprom_read_offset_parameter('w', w_offset_addr);
    }
    void eeprom_write_offset_parameters()
    {
        function_log();
        eeprom_write_offset_parameter('x', x_offset_addr);
        eeprom_write_offset_parameter('y', y_offset_addr);
        eeprom_write_offset_parameter('z', z_offset_addr);
        eeprom_write_offset_parameter('w', w_offset_addr);
    }

    void eeprom_read_plus_parameters()
    {
        function_log();
        eeprom_read_plus_parameter('x', x_plus_addr);
        eeprom_read_plus_parameter('y', y_plus_addr);
        eeprom_read_plus_parameter('z', z_plus_addr);
        eeprom_read_plus_parameter('w', w_plus_addr);
    }
    void eeprom_write_plus_parameters()
    {
        function_log();
        eeprom_write_plus_parameter('x', x_plus_addr);
        eeprom_write_plus_parameter('y', y_plus_addr);
        eeprom_write_plus_parameter('z', z_plus_addr);
        eeprom_write_plus_parameter('w', w_plus_addr);
    }

    void eeprom_read_speed_parameters()
    {
        function_log();
        eeprom_read_speed_parameter('x', x_speed_addr);
        eeprom_read_speed_parameter('y', y_speed_addr);
        eeprom_read_speed_parameter('z', z_speed_addr);
        eeprom_read_speed_parameter('w', w_speed_addr);
    }
    void eeprom_write_speed_parameters()
    {
        function_log();
        eeprom_write_speed_parameter('x', x_speed_addr);
        eeprom_write_speed_parameter('y', y_speed_addr);
        eeprom_write_speed_parameter('z', z_speed_addr);
        eeprom_write_speed_parameter('w', w_speed_addr);
    }

    void eeprom_read_acceleration_parameters()
    {
        function_log();
        eeprom_read_acceleration_parameter('x', x_acceleration_addr);
        eeprom_read_acceleration_parameter('y', y_acceleration_addr);
        eeprom_read_acceleration_parameter('z', z_acceleration_addr);
        eeprom_read_acceleration_parameter('w', w_acceleration_addr);
    }
    void eeprom_write_acceleration_parameters()
    {
        function_log();
        eeprom_write_acceleration_parameter('x', x_acceleration_addr);
        eeprom_write_acceleration_parameter('y', y_acceleration_addr);
        eeprom_write_acceleration_parameter('z', z_acceleration_addr);
        eeprom_write_acceleration_parameter('w', w_acceleration_addr);
    }

    void eeprom_write_position_parameter(char axis, int val)
    {
        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            eeprom.eeprom_write<int>(val, x_position_addr);
            break;
        case 'y':
            eeprom.eeprom_write<int>(val, y_position_addr);
            break;
        case 'z':
            eeprom.eeprom_write<int>(val, z_position_addr);
            break;
        }
        EEPROM.end();
    }

    void eeprom_put_w_status()
    {
        function_log();
        eeprom_put_w_needle_table_status();
        Serial.println(w_needle_table_status_flag ? "Put w_flag: true" : "Put w_flag: false");
    }

    void eeprom_get_w_status()
    {
        function_log();
        eeprom_get_w_needle_table_status();
        Serial.println(w_needle_table_status_flag ? "Get w_flag: true" : "Get w_flag: false");
    }

    int eeprom_read_position_parameters(char axis)
    {
        int pos;
        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            pos = eeprom.eeprom_read<int>(x_position_addr);
            return pos;
            break;
        case 'y':
            pos = eeprom.eeprom_read<int>(y_position_addr);
            return pos;
            break;
        case 'z':
            pos = eeprom.eeprom_read<int>(z_position_addr);
            return pos;
            break;
        }
        return 0;
        EEPROM.end();
    }
    int eeprom_get_speed_parameter(char axis)
    {
        int spe;
        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            spe = eeprom.eeprom_read<int>(x_speed_addr);
            return spe;
            break;
        case 'y':
            spe = eeprom.eeprom_read<int>(y_speed_addr);
            return spe;
            break;
        case 'z':
            spe = eeprom.eeprom_read<int>(z_speed_addr);
            return spe;
            break;
        case 'w':
            spe = eeprom.eeprom_read<int>(w_speed_addr);
            return spe;
            break;
        }
        return 0;
        EEPROM.end();
    }
    int eeprom_get_acc_parameter(char axis)
    {
        int acc;
        EEPROM.begin();
        switch (axis)
        {
        case 'x':
            acc = eeprom.eeprom_read<int>(x_acceleration_addr);
            return acc;
            break;
        case 'y':
            acc = eeprom.eeprom_read<int>(y_acceleration_addr);
            return acc;
            break;
        case 'z':
            acc = eeprom.eeprom_read<int>(z_acceleration_addr);
            return acc;
            break;
        case 'w':
            acc = eeprom.eeprom_read<int>(w_acceleration_addr);
            return acc;
            break;
        }
        return 0;
        EEPROM.end();
    }

    void eeprom_write_specific_speed_parameters(char axis)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            eeprom_write_speed_parameter('x', x_speed_addr);
            break;
        case 'y':
            eeprom_write_speed_parameter('y', y_speed_addr);
            break;
        case 'z':
            eeprom_write_speed_parameter('z', z_speed_addr);
            break;
        case 'w':
            eeprom_write_speed_parameter('w', w_speed_addr);
            break;
        }
    }
    void axis_page_setup_specific_speed_parameter(char axis, int value)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            x_speed = value;
            Serial.println("New X speed: " + String(x_speed));
            break;
        case 'y':
            y_speed = value;
            Serial.println("New Y speed: " + String(y_speed));
            break;
        case 'z':
            z_speed = value;
            Serial.println("New Z speed: " + String(z_speed));
            break;
        case 'w':
            w_speed = value;
            Serial.println("New W speed: " + String(w_speed));
            break;
        }
    }
};

#endif