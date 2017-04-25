#ifndef ABSTRACTINPUT_H
#define ABSTRACTINPUT_H

#include <windows.h>

#include <QObject>

#include "iotypes.h"

// An abstract class describing a MIDI input
class AbstractInput : public QObject
{
    Q_OBJECT

public:
    ~AbstractInput() {}
    virtual void start() = 0;
    virtual void stop() = 0;

signals:
    void sendMessage(int, int);
};

#endif // ABSTRACTINPUT_H

