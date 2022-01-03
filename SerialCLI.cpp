#include "SerialCLI.h"

Command::Command(String name, void (*execute)(String ops, Stream *serial))
{
    _name = name;
    _execute = execute;
}

SerialCLI::SerialCLI(Command *defaultComList, Command *customComList, int count)
    : _defaultComList{defaultComList}, _customComList{customComList}, _comCount{count}
{
}

void SerialCLI::begin(Stream &serial)
{
    _serial = &serial;
}

void SerialCLI::parse()
{
    if (_serial->available() > 0)
    {
        delay(10);
        String inputStr = _serial->readStringUntil('\n');

        int8_t spaceLoc = inputStr.indexOf(" ");
        String comStr = inputStr.substring(0, spaceLoc);
        String opsStr = inputStr.substring(spaceLoc + 1);
        for (int i = 0; i < DEFAULT_COMMAND_COUNT; ++i)
        {
            if (_defaultComList[i]._name == comStr)
            {
                _defaultComList[i].execute(opsStr, _serial);
                return;
            }
        }
        for (int i = 0; i < _comCount; ++i)
        {
            if (_customComList[i]._name == comStr)
            {
                _customComList[i].execute(opsStr, _serial);
                return;
            }
        }
        _serial->println(COMMAND_ERROR);
    }
}

void read_analog(String ops, Stream *serial)
{
    int pin = parseInt(ops);
    if (pin < 0)
    {
        serial->println(PARAM_ERROR);
        return;
    }

    serial->print(analogRead(pin) / 1023.0 * 5);
    serial->println(" V");
}

void read_digital(String ops, Stream *serial)
{
    int pin = parseInt(ops);
    if (pin < 0)
    {
        serial->println(PARAM_ERROR);
        return;
    }
    pinMode(pin, INPUT);
    serial->println(digitalRead(pin) ? HIGH_STR : LOW_STR);
}

void write_digital(String ops, Stream *serial)
{
    int8_t spaceLoc = ops.indexOf(" ");
    int pin = parseInt(ops.substring(0, spaceLoc));
    int value = parseVoltage(ops.substring(spaceLoc + 1));

    if (value < 0 || pin < 0)
    {
        serial->println(PARAM_ERROR);
        return;
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
}

void write_analog(String ops, Stream *serial)
{
    int8_t spaceLoc = ops.indexOf(" ");
    int pin = parseInt(ops.substring(0, spaceLoc));
    int value = parseInt(ops.substring(spaceLoc + 1));

    if (value < 0 || value > 256 || pin < 0)
    {
        serial->println(PARAM_ERROR);
        return;
    }
    pinMode(pin, OUTPUT);
    analogWrite(pin, value);
}

int parseInt(String str)
{
    int num = str.toInt();

    if (num == 0 && str != "0")
    {
        return -1; //negative indicates error parsing
    }
    return num;
}

float parseFloat(String str)
{
    float num = str.toFloat();

    if (num == 0.0)
    {
        if (str != "0" || str != "0.0" || str != "0.00")
        {
            return -1; //negative indicates error parsing
        }
    }
    return num;
}

int8_t parseVoltage(String str)
{
    if (str == HIGH_STR)
    {
        return HIGH;
    }
    else if (str == LOW_STR)
    {
        return LOW;
    }
    else
    {
        return -1; // negative indicates error parsing
    }
}

SerialCLI buildDefault()
{
    return SerialCLI(DEFAULT_COMMANDS, nullptr, 0);
}

SerialCLI buildCustom(Command customComList[], int count)
{
    return SerialCLI(DEFAULT_COMMANDS, customComList, count);
}