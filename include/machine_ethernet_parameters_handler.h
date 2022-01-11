#ifndef machine_ethernet_parameters_handle_h
#define machine_ethernet_parameters_handle_h

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "eeprom_extension.h"
#include "global_config.h"

struct ethernet_parameters_def
{
private:
    int Storage_address;

    int eeprom_local_ip_addr = 0;
    int eeprom_remote_ip_addr = 0;
    int eeprom_port_addr = 0;
    int eeprom_mac_addr = 0;

    eeprom_extension eeprom;

    void eeprom_save_MAC(int address)
    {
        EEPROM.begin();
        for (size_t i = 0; i < 6; i++)
        {
            eeprom.eeprom_write<uint8_t>(MAC[i], address + i);
        }
        EEPROM.end();
    }
    void eeprom_read_MAC(int address)
    {
        EEPROM.begin();
        uint8_t mac[6]{0};
        for (size_t i = 0; i < sizeof(mac); i++)
        {
            mac[i] = eeprom.eeprom_read<uint8_t>(address + i);
        }
        EEPROM.end();
        memccpy(MAC, mac, 0, sizeof(MAC));
    }

    void eeprom_save_local_ip(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(local_ip_str); i++)
        {
            eeprom.eeprom_write<char>(local_ip_str[i], address + i);
        }
        EEPROM.end();
    }
    void eeprom_read_local_ip(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(local_ip_str); i++)
        {
            local_ip_str[i] = eeprom.eeprom_read<char>(address + i);
        }
        EEPROM.end();
    }

    void eeprom_save_remote_ip(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(remote_ip_str); i++)
        {
            eeprom.eeprom_write<char>(remote_ip_str[i], address + i);
        }
        EEPROM.end();
    }
    void eeprom_read_remote_ip(int address)
    {
        function_log();
        EEPROM.begin();
        for (size_t i = 0; i < sizeof(remote_ip_str); i++)
        {
            remote_ip_str[i] = eeprom.eeprom_read<char>(address + i);
        }
        EEPROM.end();
    }

    void eeprom_save_port(int address)
    {
        function_log();
        EEPROM.begin();
        eeprom.eeprom_write<int>(localPort, address);
        EEPROM.end();
    }
    void eeprom_read_port(int address)
    {
        function_log();
        EEPROM.begin();
        localPort = eeprom.eeprom_read<int>(address);
        EEPROM.end();
    }

public:
    char local_ip_str[15] = "192.168.1.177";
    IPAddress local_ip; //(192, 168, 1, 177);

    char remote_ip_str[15] = "192.168.1.103";
    IPAddress remote_ip; //(192, 168, 1, 103);

    unsigned int localPort = 8080;
    uint8_t MAC[6] = {0xF6, 0x6C, 0x08, 0x62, 0x05, 0x06};

    char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
    char ReplyBuffer[UDP_TX_PACKET_MAX_SIZE];

    EthernetUDP Udp;

    ethernet_parameters_def(int storage_address)
    {

        ethernet_init(storage_address);
    }
    void ethernet_init(int storage_address)
    {
        Storage_address = storage_address;
        memset(packetBuffer, 0, sizeof(packetBuffer));
        memset(ReplyBuffer, 0, sizeof(ReplyBuffer));
        storage_address_specify();
    }
    void set_ipaddress()
    {
        function_log();
        local_ip.fromString(local_ip_str);
        remote_ip.fromString(remote_ip_str);
        Serial.println("Remote IP str: " + String(remote_ip_str));
        Serial.println("Local IP str: " + String(local_ip_str));
    }
    void storage_address_specify()
    {
        // function_log();
        eeprom_mac_addr = Storage_address;
        eeprom_local_ip_addr = eeprom_mac_addr + sizeof(MAC);
        eeprom_remote_ip_addr = eeprom_local_ip_addr + sizeof(local_ip_str);
        eeprom_port_addr = eeprom_remote_ip_addr + sizeof(remote_ip_str);
    }
    void eeprom_read_ethernet_parameters()
    {
        function_log();
        eeprom_read_MAC(eeprom_mac_addr);
        eeprom_read_local_ip(eeprom_local_ip_addr);
        eeprom_read_remote_ip(eeprom_remote_ip_addr);
        eeprom_read_port(eeprom_port_addr);
        Serial.println("Read Remote IP: " + String(remote_ip_str));
        Serial.println("Read Local IP: " + String(local_ip_str));
        Serial.println("Read LocalPort IP: " + String(localPort));
        set_ipaddress();
    }
    void eeprom_save_MAC()
    {
        function_log();
        eeprom_save_MAC(eeprom_mac_addr);
        printf("Save MAC: %s\r\n", MAC);
    }
    void eeprom_save_ethernet_parameters()
    {
        function_log();
        eeprom_save_remote_ip(eeprom_remote_ip_addr);
        eeprom_save_local_ip(eeprom_local_ip_addr);
        eeprom_save_port(eeprom_port_addr);
    }
    void setup_machine_mac(uint8_t *mac)
    {
        function_log();
        memccpy(MAC, mac, 0, sizeof(MAC));
        printf("New machine MAC: %s\r\n", MAC);
    }
    void setup_ethernet_parameters(char *RemoteIP, char *LocalIP, uint16_t port)
    {
        function_log();
        localPort = port;
        memccpy(remote_ip_str, RemoteIP, 0, sizeof(remote_ip_str));
        memccpy(local_ip_str, LocalIP, 0, sizeof(local_ip_str));
        set_ipaddress();
        Serial.print("New Remote IP: ");
        Serial.println(remote_ip);
        Serial.print("New Local IP: ");
        Serial.println(local_ip);
        Serial.println("New LocalPort IP: " + String(localPort));
    }
    
};
#endif