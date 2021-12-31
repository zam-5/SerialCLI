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

        if (comStr == "read-analog")
        {
            read_analog(opsStr);
        }
        else if (comStr == "read-digital")
        {
            read_digital(opsStr);
        }
        else if (comStr == "write-digital")
        {
            write_digital(opsStr);
        }
        else
        {
            _serial->println("Invalid Command");
        }
    }
}

void SerialCLI::read_analog(String ops)
{
    int pin = parseNum(ops);
    if (pin < 0)
    {
        _serial->println("pin# missing");
        return;
    }

    _serial->print(analogRead(pin) / 1023.0 * 5);
    _serial->println(" V");
}

void SerialCLI::read_digital(String ops)
{
    int pin = parseNum(ops);
    if (pin < 0)
    {
        _serial->println("pin# missing");
        return;
    }
    pinMode(pin, INPUT);
    _serial->println(digitalRead(pin) ? "HIGH" : "LOW");
}

void SerialCLI::write_digital(String ops)
{
    int8_t spaceLoc = ops.indexOf(" ");
    int pin = parseNum(ops.substring(0, spaceLoc));
    int value = parseVoltage(ops.substring(spaceLoc + 1));

    if (value < 0 || pin < 0)
    {
        _serial->println("pin or voltage missing");
        return;
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
}

int SerialCLI::parseNum(String str)
{
    int pinNumber;
    pinNumber = str.toInt();

    if (pinNumber == 0 && str != "0")
    {
        return -1; //negative indicates error parsing
    }
    return pinNumber;
}

int8_t SerialCLI::parseVoltage(String str)
{
    if (str == "HIGH")
    {
        return HIGH;
    }
    else if (str == "LOW")
    {
        return LOW;
    }
    else
    {
        return -1; // negative indicates error parsing
    }
}