#ifndef SCLI_H
#define SCLI_H

#include "Arduino.h"

class SerialCLI
{
private:
    Stream *_serial;

    int analogRead(int pin);

public:
    SerialCLI();
    void begin(Stream &serial);
    void parse();
};

#endif