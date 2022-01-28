# a_sh Library

## About

a_sh, short for arduino_shell, is a WIP Arduino library that allows user to create custom commands in an Arduino sketch, which can be executed via serial communication. For the most integrated experience, use the [a_sh CLI](https://github.com/zam-5/a_sh-CLI) (WIP).

## Installation

[Download](https://github.com/zam-5/a_sh-lib/releases/download/v0.1.0/a_sh-lib.zip) the zipped version of the library here. Follow these [instructions](https://www.arduino.cc/en/Guide/Libraries) for installation.

## Usage

This section will contain a basic overview of how to use a_sh. Read through the basic_custom.ino example in order for a step-by-step guide to using a_sh.

There are two types included with this library, `ArduinoShell` and `Command`. The shell can be created with one of three builder functions: `buildDefault`, `buildCustom`, or `buildCustomNoDefault`.

### Default Shell

If you don't plan to add custom commands, a sketch running the default shell can be created as follows:

```c++
  #include "a_sh-lib.h"
  
  ArduinoShell shell = buildDefault();
  
  void setup()
  {
    Serial.begin(9600);
    shell.begin(Serial);
  }
  
  void loop()
  {
    shell.parse();
  }
```

The sketch starts by including the a_sh library, and creating the default shell. In the setup function, the transmission rate is set to 9600 baud on the default serial port. Then the `begin` method is called on the shell. `begin` requires one argument, the `Stream` object (`Serial` inherits from the `Stream` class) which will be used for communication.

Once the shell and serial interface are setup, simply call the `parse` method on the shell inside `loop()`. Each time `parse` is called, it will check if any data has been recieved from the serial interface. Running the shell is now just requires uploading the sketch, and runnning [a_sh CLI](https://github.com/zam-5/a_sh-CLI).

### Custom Shell

Custom commands are created with the following template

```C++
  void funcName(String ops, Stream *serial);
```

Custom function must have two parameters: a String, which will contain the arguments passed to the command, and a pointer to a Stream, the serial interface over which the shell is comminicating. 

To build a shell with custom commands, first create an array of `Command` objects. Then, call your builder function, `buildCustom` or `buildCustomNoDefault` with the command array and the number of custom commands.

```c++
  Command commandList[] = {Command("com-1", customFunc1), Command("com-2", customFunc2)};
  ArduinoShell shell = buildCustom(commandList, 2);
```

The `setup()` and `loop()` functions will look the same as in the default example above.


## Default Commands

The following commands are included by default:

```
  read-analog <PIN>
  read-digital <PIN>
  write-analog <PIN> <0-255>
  write-digital <PIN> <HIGH or LOW>
```

The usage of these commands is self explanatory, however the way the shell parses them is not, which can lead to confusion when using the Arduino IDE Serial Monitor. The default commands are parsed from `"read-analog"`, `"read-digital"`, `"write-analog"`, and `"write-digital"`. Instead, they are `"0"`, `"1"`, `"2"`, and `"3"`, respectively. These are automatically converted when using [a_sh CLI](https://github.com/zam-5/a_sh-CLI), but not the Arduino Serial Monitor.

#### a_sh CLI:

```
  write-analog 3 200
```

#### Arduino IDE Serial Monitor:

```
  0 3 200
```


