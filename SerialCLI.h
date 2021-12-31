#ifndef SCLI_H
#define SCLI_H

#include "Arduino.h"

class SerialCLI
{
private:
    Stream *_serial;

    void _read(String options);
    int parsePin(String str);

public:
    SerialCLI();
    void begin(Stream &serial);
    void parse();
};

#endif