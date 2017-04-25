#ifndef SERIALOUTPUT_H
#define SERIALOUTPUT_H

#include <unistd.h>
#include <windows.h>

#include <QDebug>
#include <QSerialPort>
#include <QList>
#include <QString>

#include "abstractoutput.h"
#include "iotypes.h"

// SerialOutput inherits AbstractOutput and relays all messages received from
// the OutputHandler to a serial device
class SerialOutput : public AbstractOutput
{
public:
    SerialOutput(QString portName);
    void start();
    void stop();
    void sendNoteOn(int);
    void sendNoteOff(int);
    void sendConfigInfo(QList<int>);
    QSerialPort* getPort();

private:
    QSerialPort* port_;
};

#endif // SERIALOUTPUT_H
