#include "SerialCLI.h"

SerialCLI scli;

void setup()
{
    Serial.begin(9600);
    scli.begin(Serial);
}

void loop()
{
    scli.parse();
}
