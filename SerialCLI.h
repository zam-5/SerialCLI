#ifndef SCLI_H
#define SCLI_H

#include "Arduino.h"

class SerialCLI
{
private:
    Stream *_serial;

    void read_analog(String ops);
    void read_digital(String ops);
    void write_digital(String ops);
    int parsePin(String str);

public:
    SerialCLI();
    void begin(Stream &serial);
    void parse();
};

#endif