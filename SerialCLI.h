#ifndef SCLI_H
#define SCLI_H

#include "Arduino.h"

class SerialCLI
{
private:
    Stream *_serial;

    void analog_read(String options);

public:
    SerialCLI();
    void begin(Stream &serial);
    void parse();
};

#endif