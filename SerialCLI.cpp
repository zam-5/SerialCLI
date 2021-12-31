#include "SerialCLI.h"

SerialCLI::SerialCLI() {}

void SerialCLI::begin(Stream &serial) { _serial = &serial; }

void SerialCLI::parse()
{
    if (_serial->available() > 0)
    {
        String inputStr = _serial->readStringUntil('\n');
        Serial.println(inputStr);

        int8_t spaceLoc = inputStr.indexOf(" ");
        String comStr = inputStr.substring(0, spaceLoc);
        String opsStr = inputStr.substring(spaceLoc + 1);

        if (comStr == "read")
        {
            _read(opsStr);
        }
        else
        {
            _serial->println("Invalid Command");
        }

        // switch
    }
}

void SerialCLI::_read(String ops)
{
    if (ops.substring(0, 2) == "-a")
    {
        //Modify to only accept string of the number
        int pin = parsePin(ops);
        if (pin < 0)
        {
            _serial->println("pin# missing");
            return;
        }

        _serial->print(analogRead(pin) / 1023.0 * 5);
        _serial->println(" V");
    }
    else if (ops.substring(0, 2) == "-d")
    {
        int pin = parsePin(ops);
        if (pin < 0)
        {
            _serial->println("pin# missing");
            return;
        }
        pinMode(pin, INPUT);
        _serial->println(digitalRead(pin) ? "HIGH" : "LOW");
    }
    else
    {
        _serial->println("Invalid Option. Use read -a PIN# or read -d PIN#");
    }
}

void SerialCLI::_write(String ops)
{
    
}

int SerialCLI::parsePin(String str)
{
    int pinNumber;
    int8_t spaceLoc = str.indexOf(" ");

    pinNumber = str.substring(spaceLoc).toInt();

    if (pinNumber == 0 && str.substring(spaceLoc + 1) != "0")
    {
        return -1; //negative indicates error parsing
    }
    return pinNumber;
}