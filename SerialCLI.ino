#include "SerialCLI.h"

SerialCLI scli = buildDefault();

unsigned long ts = 0;

void setup()
{
    Serial.begin(9600);
    scli.begin(Serial);
}

void loop()
{
    //delay(4000);
    //Serial.println("test");
    scli.parse();
}
