#ifndef nextion_extension_h
#define nextion_extension_h

#include "NextionVariableString.h"
#include "NextionVariableNumeric.h"
#include "NextionText.h"
#include "NextionPicture.h"
#include "NextionPage.h"
#include "NextionNumber.h"
#include "NextionButton.h"
#include "Nextion.h"
#include "INextionTouchable.h"
#include "NextionCheckbox.h"

#define NextionSerial Serial3

extern const char *NexPropertyType[5];
extern Nextion nex;
extern INextionTouchable PAGE_LOADING_EVENT;

class nextion_extension
{
public:
    void nex_listening();

    void sendCommand(const char *commandStr);
    void nex_goto_page(const char *page_name);
    void nex_set_vis(const char *propertyName, uint32_t value);

    void setNumberProperty(const char *pageName, const char *propertyName, uint32_t value);
    void setNumberProperty(const char *propertyName, uint32_t value);
    
    uint32_t getNumberProperty(const char *pageName, const char *propertyName);
    uint32_t getNumberProperty(const char *propertyName);

    void setStringProperty(const char *pageName, const char *propertyName, const char *value);
    void setStringProperty(const char *propertyName, const char *value);
    
    size_t getStringProperty(const char *pageName, const char *propertyName, const char *value, size_t len);
    size_t getStringProperty(const char *propertyName, const char *value, size_t len);

    void nex_send_message(const char *message);
    void nex_init();
};

#endif
