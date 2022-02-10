#ifndef eeprom_extension_h
#define eeprom_extension_h

#include <EEPROM.h>
#include <Arduino.h>

struct eeprom_extension
{
    template <typename T>
    void eeprom_write(T val, int addr)
    {
        T last_val = 0;
        while (1)
        {
            uint8_t size = sizeof(T);
            for (uint8_t i = size; i > 0; i--)
            {
                T v = (T)EEPROM.read(addr + (size - i));
                // printf("byte index %d, val %d\r\n", i, v);

                last_val |= (T)(v << ((i - 1) * 8));
            }
            Serial.println("Read " + String(sizeof(T)) + " bytes from address " + String(addr) + " return " + String(last_val));
            break;
        }
        if (last_val == val)
        {
            Serial.println("The data is remaining");
        }
        else
        {
            if (last_val == 0)
            {
                uint8_t size = sizeof(T);
                Serial.println("Write " + String(size) + " bytes have value " + String(val) + " to address " + String(addr));
                for (uint8_t i = size; i > 0; i--)
                {
                    uint8_t value = 0;
                    value = uint8_t(val >> ((i - 1) * 8));
                    EEPROM.write(addr + (size - i), value);
                    // printf("byte index %d, val %d\r\n", i, value);
                }
            }
            else
            {
                uint8_t size = sizeof(T);
                Serial.println("Update " + String(size) + " bytes have value " + String(val) + " to address " + String(addr));
                for (uint8_t i = size; i > 0; i--)
                {
                    uint8_t value = 0;
                    value = uint8_t(val >> ((i - 1) * 8));
                    EEPROM.update(addr + (size - i), value);
                    // printf("byte index %d, val %d\r\n", i, value);
                }
            }
        }
    }

    template <typename T>
    T eeprom_read(int addr)
    {
        T result = 0;
        uint8_t size = sizeof(T);
        for (uint8_t i = size; i > 0; i--)
        {
            T v = (T)EEPROM.read(addr + (size - i));
            // printf("byte index %d, val %d\r\n", i, v);

            result |= (T)(v << ((i - 1) * 8));
        }
        Serial.println("Read " + String(sizeof(T)) + " bytes from address " + String(addr) + " return " + String(result));
        return result;
    }

    template <typename T>
    void eeprom_put(T data, int addr)
    {
        uint8_t size = sizeof(T);
        EEPROM.put(addr, data);
        Serial.println("Put " + String(size) + " bytes value of " + String(data) + " to address " + String(addr));
    }

    template <typename T>
    T eeprom_get(T data, int addr)
    {
        uint8_t size = sizeof(T);
        EEPROM.get(addr, data);
        Serial.println("Get " + String(size) + " bytes from address " + String(addr) + " return " + String(data));
        return data;
    }
};

#endif