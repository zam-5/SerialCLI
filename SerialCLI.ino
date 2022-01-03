#include "SerialCLI.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int8_t currentLine = 0;

// void testCom(String ops, Stream *serial)
// {
//     serial->println("Ok");
// }

void blinkPin(String ops, Stream *serial)
{
    int pin = parseInt(ops);
    if (pin < 0)
    {
        serial->println(PARAM_ERROR);
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

void lcdPrint(String ops, Stream *_serial)
{
    lcd.clear();
    lcd.setCursor(0, currentLine);

    lcd.print(ops);
}

void lcdSetLine(String ops, Stream *serial)
{
    ops.trim();
    int line = parseInt(ops);
    serial->println(line);
    if (line < 0 || line > 2)
    {
        serial->println(PARAM_ERROR);
        return;
    }
    currentLine = line - 1;
}

void lcdClear(String ops, Stream *_serial)
{
    lcd.clear();
}

Command cList[] = {Command("blink", blinkPin), Command("lcd-clear", lcdClear), Command("lcd", lcdPrint), Command("lcd-line", lcdSetLine)};

// SerialCLI scli = buildDefault();
SerialCLI scli = buildCustom(cList, 4);
//SerialCLI scli = buildCustomNoDefault(cList, 2);

void setup()
{
    lcd.begin(16, 2);
    Serial.begin(9600);
    scli.begin(Serial);
}

void loop()
{
    scli.parse();
}
