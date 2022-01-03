#ifndef SERIALCLI_H
#define SERIALCLI_H

#include "Arduino.h"
#include "Command.h"

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

Command DEFAULT_COMMANDS[]{
    Command(WRITE_ANALOG, write_analog),
    Command(WRITE_DIGITAL, write_digital),
    Command(READ_ANALOG, read_analog),
    Command(READ_DIGITAL, read_digital)};

#define DEFAULT_COMMAND_COUNT 4

class SerialCLI
{
private:
    Stream *_serial;
    int _comCount;
    bool _useDefault;
    Command *_customComList;
    Command *_defaultComList;

public:
    SerialCLI(Command defaultComList[], Command customComList[], int count, bool _useDefault);
    void begin(Stream &serial);
    void parse();
};

SerialCLI buildDefault();
SerialCLI buildCustom(Command customComList[], int count);
SerialCLI buildCustomNoDefault(Command customComList[], int count);

#endif