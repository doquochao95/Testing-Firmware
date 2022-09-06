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

    // int x_position_addr = 0;
    // int y_position_addr = 0;
    // int z_position_addr = 0;

    eeprom_extension eeprom;

    void eeprom_read_offset_parameter(char axis, int addr)
    {
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
    bool needle_box_status_flag = false;
    bool dropper_status_flag = false;
    bool camcylinder1_status_flag = false;
    bool camcylinder2_status_flag = false;
    bool airsuck_status_flag = false;
    bool airflow_status_flag = false;

    void set_position_x(int value)
    {
        xposition = value;
    }
    void set_position_y(int value)
    {
        yposition = value;
    }
    void set_position_z(int value)
    {
        zposition = value;
    }
    void set_w_status(bool value)
    {
        w_needle_table_status_flag = value;
    }
    void set_box_status(bool value)
    {
        needle_box_status_flag = value;
    }
    void set_dropper_status(bool value)
    {
        dropper_status_flag = value;
    }
    void set_camcylinder1_status(bool value)
    {
        camcylinder1_status_flag = value;
    }
    void set_camcylinder2_status(bool value)
    {
        camcylinder2_status_flag = value;
    }
    void set_airsuck_status(bool value)
    {
        airsuck_status_flag = value;
    }
    void set_airflow_status(bool value)
    {
        airflow_status_flag = value;
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

        // x_position_addr = w_acceleration_addr + sizeof(w_acceleration);
        // y_position_addr = x_position_addr + sizeof(xposition);
        // z_position_addr = y_position_addr + sizeof(yposition);

    }

    void axis_page_setup_offset_parameter(int xoffset, int yoffset, int zoffset, int woffset)
    {
        function_log();
        x_offset = xoffset;
        y_offset = yoffset;
        z_offset = zoffset;
        w_offset = woffset;
    }
    void axis_page_setup_plus_parameter(int xplus, int yplus, int zplus, int wplus)
    {
        function_log();
        x_plus = xplus;
        y_plus = yplus;
        z_plus = zplus;
        w_plus = wplus;
    }
    void axis_page_setup_speed_parameter(int xspeed, int yspeed, int zspeed, int wspeed)
    {
        function_log();
        x_speed = xspeed;
        y_speed = yspeed;
        z_speed = zspeed;
        w_speed = wspeed;
    }
    void axis_page_setup_acc_parameter(int xacc, int yacc, int zacc, int wacc)
    {
        function_log();
        x_acceleration = xacc;
        y_acceleration = yacc;
        z_acceleration = zacc;
        w_acceleration = wacc;
    }

    void eeprom_read_axis_parameter()
    {
        eeprom_read_offset_parameters();
        eeprom_read_plus_parameters();
        eeprom_read_speed_parameters();
        eeprom_read_acceleration_parameters();
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

    // int eeprom_read_position_parameters(char axis)
    // {
    //     int pos;
    //     EEPROM.begin();
    //     switch (axis)
    //     {
    //     case 'x':
    //         pos = eeprom.eeprom_read<int>(x_position_addr);
    //         return pos;
    //         break;
    //     case 'y':
    //         pos = eeprom.eeprom_read<int>(y_position_addr);
    //         return pos;
    //         break;
    //     case 'z':
    //         pos = eeprom.eeprom_read<int>(z_position_addr);
    //         return pos;
    //         break;
    //     }
    //     return 0;
    //     EEPROM.end();
    // }
    // void eeprom_write_position_parameter(char axis, int val)
    // {
    //     EEPROM.begin();
    //     switch (axis)
    //     {
    //     case 'x':
    //         eeprom.eeprom_write<int>(val, x_position_addr);
    //         break;
    //     case 'y':
    //         eeprom.eeprom_write<int>(val, y_position_addr);
    //         break;
    //     case 'z':
    //         eeprom.eeprom_write<int>(val, z_position_addr);
    //         break;
    //     }
    //     EEPROM.end();
    // }

    // save specific parameter
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
            break;
        case 'y':
            y_speed = value;
            break;
        case 'z':
            z_speed = value;
            break;
        case 'w':
            w_speed = value;
            break;
        }
    }

    void eeprom_write_specific_accel_parameters(char axis)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            eeprom_write_acceleration_parameter('x', x_acceleration_addr);
            break;
        case 'y':
            eeprom_write_acceleration_parameter('y', y_acceleration_addr);
            break;
        case 'z':
            eeprom_write_acceleration_parameter('z', z_acceleration_addr);
            break;
        case 'w':
            eeprom_write_acceleration_parameter('w', w_acceleration_addr);
            break;
        }
    }
    void axis_page_setup_specific_accel_parameter(char axis, int value)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            x_acceleration = value;
            break;
        case 'y':
            y_acceleration = value;
            break;
        case 'z':
            z_acceleration = value;
            break;
        case 'w':
            w_acceleration = value;
            break;
        }
    }

    void eeprom_write_specific_offset_parameters(char axis)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            eeprom_write_offset_parameter('x', x_offset_addr);
            break;
        case 'y':
            eeprom_write_offset_parameter('y', y_offset_addr);
            break;
        case 'z':
            eeprom_write_offset_parameter('z', z_offset_addr);
            break;
        case 'w':
            eeprom_write_offset_parameter('w', w_offset_addr);
            break;
        }
    }
    void axis_page_setup_specific_offset_parameter(char axis, int value)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            x_offset = value;
            break;
        case 'y':
            y_offset = value;
            break;
        case 'z':
            z_offset = value;
            break;
        case 'w':
            w_offset = value;
            break;
        }
    }

    void eeprom_write_specific_plus_parameters(char axis)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            eeprom_write_plus_parameter('x', x_plus_addr);
            break;
        case 'y':
            eeprom_write_plus_parameter('y', y_plus_addr);
            break;
        case 'z':
            eeprom_write_plus_parameter('z', z_plus_addr);
            break;
        case 'w':
            eeprom_write_plus_parameter('w', w_plus_addr);
            break;
        }
    }
    void axis_page_setup_specific_plus_parameter(char axis, int value)
    {
        function_log();
        switch (axis)
        {
        case 'x':
            x_plus = value;
            break;
        case 'y':
            y_plus = value;
            break;
        case 'z':
            z_plus = value;
            break;
        case 'w':
            w_plus = value;
            break;
        }
    }
};
#endif