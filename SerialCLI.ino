#include "SerialCLI.h"

SerialCLI scli;

void setup()
{
    Serial.begin(9600);
    scli.begin(Serial);
}

void loop()
{
    if (Serial.available() > 0)
    {
        String com = Serial.readStringUntil('\n');
        Serial.println(com);
    }
    scli.parse();
}