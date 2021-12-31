#ifndef SCLI_H
#define SCLI_H

#include "Arduino.h"

class SerialCLI
{
private:
    Stream *_serial;

    void _read(String ops);
    void _write(String ops);
    int parsePin(String str);

public:
    SerialCLI();
    void begin(Stream &serial);
    void parse();
};

#endif