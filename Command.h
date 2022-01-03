#ifndef COMMAND_H
#define COMMAND_H

class Command
{
private:
    void (*_execute)(String ops, Stream *serial);

public:
    String _name;
    Command(String name, void (*execute)(String ops, Stream *serial));
    void execute(String ops, Stream *serial)
    {
        (*_execute)(ops, serial);
    }
};

#endif