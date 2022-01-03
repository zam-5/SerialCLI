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

class SerialCLI
{
private:
    Stream *_serial;

    void read_analog(String ops);
    void read_digital(String ops);
    void write_digital(String ops);
    void write_analog(String ops);
    int parseInt(String str);
    float parseFloat(String str);
    int8_t parseVoltage(String str);

public:
    SerialCLI();
    void begin(Stream &serial);
    void parse();
};

#endif