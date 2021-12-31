#include "SerialCLI.h"

SerialCLI::SerialCLI() {}

void SerialCLI::begin(Stream &serial) { _serial = &serial; }

void SerialCLI::parse()
{
    if (_serial->available() > 0)
    {
        String inputStr = _serial->readStringUntil('\n');
        Serial.println(inputStr);

        int8_t s1 = inputStr.indexOf(" ");
        String comStr = inputStr.substring(0, s1);
        String opsStr = inputStr.substring(s1);

        if (comStr == "read")
        {
            analog_read(opsStr);
        }
        else
        {
            _serial->println("Invalid Command");
        }

        // switch
    }
}

void SerialCLI::analog_read(String options)
{
    
}