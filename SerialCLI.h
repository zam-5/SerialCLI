#ifndef SERIALCLI_H
#define SERIALCLI_H

#include "Arduino.h"

const String READ_ANALOG = "0";
const String READ_DIGITAL = "1";
const String WRITE_ANALOG = "2";
const String WRITE_DIGITAL = "3";
const String COMMAND_ERROR = "Invalid Command";
const String PARAM_ERROR = "Invalid Params";
const String HIGH_STR = "HIGH";
const String LOW_STR = "LOW";

void read_analog(String ops, Stream *serial);
void read_digital(String ops, Stream *serial);
void write_digital(String ops, Stream *serial);
void write_analog(String ops, Stream *serial);
int parseInt(String str);
float parseFloat(String str);
int8_t parseVoltage(String str);

class Command
{
private:
    void (*_execute)(String ops, Stream *serial);

public:
    String _name;
    Command(String name, void (*execute)(String ops, Stream *serial));
    void execute(String ops, Stream *serial)
    {
        (*_execute)(ops, serial);
    }
};

class SerialCLI
{
private:
    Stream *_serial;
    int _comCount;
    Command *_comList;

public:
    SerialCLI(Command commandList[], int count);
    void begin(Stream &serial);
    void parse();
};

SerialCLI buildDefault();

#endif