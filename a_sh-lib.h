#ifndef A_SH_LIB_H
#define A_SH_LIB_H

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

static Command DEFAULT_COMMANDS[]{
    Command(WRITE_ANALOG, write_analog),
    Command(WRITE_DIGITAL, write_digital),
    Command(READ_ANALOG, read_analog),
    Command(READ_DIGITAL, read_digital)};

#define DEFAULT_COMMAND_COUNT 4

class ArduinoShell
{
private:
    Stream *_serial;
    int _comCount;
    bool _useDefault;
    Command *_customComList;
    Command *_defaultComList;

public:
    ArduinoShell(Command defaultComList[], Command customComList[], int count, bool _useDefault);
    void begin(Stream &serial);
    void parse();
};

ArduinoShell buildDefault();
ArduinoShell buildCustom(Command customComList[], int count);
ArduinoShell buildCustomNoDefault(Command customComList[], int count);

#endif