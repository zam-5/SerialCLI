#include "SerialCLI.h"

Command::Command(String name, void (*execute)(String ops, Stream *serial))
{
    _name = name;
    _execute = execute;
}

SerialCLI::SerialCLI(Command *commandList, int count)
{
    _comCount = count;
    _comList = commandList;
}

void SerialCLI::begin(Stream &serial) { _serial = &serial; }

void SerialCLI::parse()
{
    if (_serial->available() > 0)
    {
        String inputStr = _serial->readStringUntil('\n');
        // _serial->print("inputStr: ");
        // _serial->println(inputStr);

        int8_t spaceLoc = inputStr.indexOf(" ");
        String comStr = inputStr.substring(0, spaceLoc);
        String opsStr = inputStr.substring(spaceLoc + 1);
        // _serial->print("  comStr: ");
        // _serial->print(comStr);
        // _serial->print("  opsStr: ");
        // _serial->println(opsStr);
        for (int i = 0; i < _comCount; ++i)
        {
            if (_comList[i]._name == comStr)
            {
                _serial->println(comStr);
                _comList[i].execute(opsStr, _serial);
            }
        }
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
    Command comList[] = {
        Command(WRITE_ANALOG, write_analog),
        Command(WRITE_DIGITAL, write_digital),
        Command(READ_ANALOG, read_analog),
        Command(READ_DIGITAL, read_digital)};
    return SerialCLI(comList, 4);
}
