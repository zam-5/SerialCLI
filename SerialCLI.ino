#include "SerialCLI.h"

void testCom(String ops, Stream *_serial)
{
    _serial->println("Ok");
}

void blinkPin(String ops, Stream *_serial)
{
    int pin = parseInt(ops);
    if (pin < 0)
    {
        _serial->println(PARAM_ERROR);
        return;
    }
    pinMode(pin, OUTPUT);
    for (int i = 0; i < 5; ++i)
    {
        digitalWrite(pin, HIGH);
        delay(1000);
        digitalWrite(pin, LOW);
        delay(1000);
    }
}

Command cList[] = {Command("test", testCom), Command("blink", blinkPin)};

// SerialCLI scli = buildDefault();
// SerialCLI scli = buildCustom(cList, 2);
SerialCLI scli = buildCustomNoDefault(cList, 2);

void setup()
{
    Serial.begin(9600);
    scli.begin(Serial);
}

void loop()
{
    scli.parse();
}
