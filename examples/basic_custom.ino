/*
    basic_custom.ino
    This is an example sketch for the a_sh library. It will
    demonstrate how to add custom commands the shell.

    Circuit: it can be anything that can be controlled
    with the follow commands.For example, a 10K potentiometer
    can have its fixed ended wired to a 5V source and GND,
    with the vairable end connected to A0. The variable end 
    can be measured with `read-analog 0`. Commands are sent 
    to the arduino from the a_sh CLI. See repository for 
    instructions to use the Arduino IDE Serial Monitor.

    Commands:
    Default (these commands are in the shell by default and do 
    not need to be added):
    read-digital <PIN>
    read-analog <PIN>
    write-digital <PIN> <VALUE>     VALUE can be HIGH or LOW
    write-analog <PIN> <VALUE>      VALUE can be 0-255

    Custom (These commands are made in this sketch and given 
    to the shell's constructor function):
    blink <PIN>
    test
*/

#include "../a_sh-lib.h"

//  Custom commands are defined with a function. Custom
//  command fuinctions must have this function signature,
//  even if it doesn't use the arguments passed to it.
void testCom(String ops, Stream *serial)
{
    //  In order to send a response to the shell from the
    //  arduino, custom commands are passed a pointer to
    //  a Stream type. To send a response, use
    //  operator-> to access println, print, and any
    //  other method from the Stream class.
    serial->println("Ok");
}

//  blinkPin is the second custom command function, this
//  command will require a single argument, the pin which
//  will be flipped from HIGH to LOW 5 times.
void blinkPin(String ops, Stream *serial)
{
    //  This library contains a few function which help
    //  with parsing arguments, such as parseInt.
    int pin = parseInt(ops);

    //  It is important to ensure the arguments are valid,
    //  and return from the function if they are not.
    if (pin < 0) // parseInt will return -1 if it fails
    {
        serial->println(PARAM_ERROR);
        return;
    }
    //  If the input is valid, blink that pin
    pinMode(pin, OUTPUT);
    for (int i = 0; i < 5; ++i)
    {
        digitalWrite(pin, HIGH);
        delay(1000);
        digitalWrite(pin, LOW);
        delay(1000);
    }
}

//  Create an array of the custom commands withh the Command Constructor.
Command cList[] = {Command("blink", blinkPin), Command("test", testCom)};

//  There are two options for creating a shell with custom
//  commands. In this example buildCustom is used, but
//  buildCustomNoDefault can be used if the default
//  commmands are unwanted. Both functions take two
//  arguments, an array of commands, and the number
//  of commands in that array.
ArduinoShell shell = buildCustom(cList, 2);

void setup()
{
    //  Start the serial port on the arduino at the
    //  default baud rate. Then begin the shell with
    //  the stream over which the shell is communicating.
    //  In this example it is the serial port but it can
    //  be any Stream object.
    Serial.begin(9600);
    shell.begin(Serial);
}

void loop()
{
    //  The shell will parse any available input each time this is called.
    shell.parse();
}
