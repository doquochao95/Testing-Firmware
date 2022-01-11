
#include "nextion_extension.h"

const char *NexPropertyType[5] = {"txt", "val", "bco", "pic", "pco"};
Nextion nex(NextionSerial);
INextionTouchable PAGE_LOADING_EVENT = INextionTouchable(nex);

void nextion_extension::nex_listening()
{
  nex.poll();
}

void nextion_extension::sendCommand(const char *commandStr)
{
  NextionSerial.print(commandStr);
  NextionSerial.write(0xFF);
  NextionSerial.write(0xFF);
  NextionSerial.write(0xFF);
  Serial.println("nextion cmd:" + String(commandStr));
}
void nextion_extension::nex_set_vis(const char *propertyName, uint32_t value)
{
  size_t commandLen = 8 + strlen(propertyName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "vis %s,%ld", propertyName, value);
  sendCommand(commandBuffer);
}
void nextion_extension::nex_goto_page(const char *page_name)
{
  size_t commandLen = 6 + strlen(page_name);
  char command[commandLen];
  snprintf(command, commandLen, "page %s", page_name);
  sendCommand(command);
}

void nextion_extension::setNumberProperty(const char *pageName,const char *propertyName, uint32_t value)
{
  size_t commandLen = 8 + strlen(pageName) + strlen(propertyName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.%s=%ld", pageName, propertyName, value);
  sendCommand(commandBuffer);
}
void nextion_extension::setNumberProperty(const char *propertyName, uint32_t value)
{
  size_t commandLen = 8 + strlen(propertyName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s=%ld", propertyName, value);
  sendCommand(commandBuffer);
}

uint32_t nextion_extension::getNumberProperty(const char *pageName,const char *propertyName)
{
  size_t commandLen = 7 + strlen(pageName) + strlen(propertyName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.%s", pageName, propertyName);
  sendCommand(commandBuffer);
  uint32_t id;
  if (nex.receiveNumber(&id))
    return id;
  else
    return 0;
}
uint32_t nextion_extension::getNumberProperty(const char *propertyName)
{
  size_t commandLen = 7 + strlen(propertyName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s", propertyName);
  sendCommand(commandBuffer);
  uint32_t id;
  if (nex.receiveNumber(&id))
    return id;
  else
    return 0;
}

void nextion_extension::setStringProperty(const char *pageName,const char *propertyName,const char *value)
{
  size_t commandLen = 7 + strlen(pageName) + strlen(propertyName) + strlen(value);
  char command[commandLen];
  snprintf(command, commandLen, "%s.%s=\"%s\"", pageName, propertyName, value);
  sendCommand(command);
}
void nextion_extension::setStringProperty(const char *propertyName,const char *value)
{
  size_t commandLen = 7 + strlen(propertyName) + strlen(value);
  char command[commandLen];
  snprintf(command, commandLen, "%s=\"%s\"", propertyName, value);
  sendCommand(command);
}

size_t nextion_extension::getStringProperty(const char *pageName,const char *propertyName,const char *value, size_t len)
{
  size_t commandLen = 6 + strlen(pageName) + strlen(propertyName);
  char command[commandLen];
  snprintf(command, commandLen, "get %s.%s", pageName, propertyName);
  sendCommand(command);
  return nex.receiveString(const_cast<char*>(value), len);
}
size_t nextion_extension::getStringProperty(const char *propertyName,const char *value, size_t len)
{
  size_t commandLen = 6 + strlen(propertyName);
  char command[commandLen];
  snprintf(command, commandLen, "get %s", propertyName);
  sendCommand(command);
  return nex.receiveString(const_cast<char*>(value), len);
}

void nextion_extension::nex_send_message(const char *message)
{
  
  setStringProperty("HOME", "msg.txt", message);
  setStringProperty("PAGE1", "msg.txt", message);
  setStringProperty("AXIS", "msg.txt", message);
  setStringProperty("CONNECTION", "msg.txt", message);
  setStringProperty("ADJUSTMENT", "msg.txt", message);
}

void nextion_extension::nex_init()
{
  NextionSerial.begin(115200);
  Serial.println("Initialize nextion screen");
  nex_goto_page("page1");
}

