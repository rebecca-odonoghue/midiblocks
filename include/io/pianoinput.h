#ifndef PIANOINPUT_H
#define PIANOINPUT_H

#include <QObject>

#include "abstractinput.h"

// PianoInput inherits AbstractInput and relays all messages received from the
// GUI Keyboard to the InputHandler
class PianoInput : public AbstractInput
{
    Q_OBJECT

public:
    PianoInput();
    void start();
    void stop();

private:
    bool isStopped_;

public slots:
    void noteOn(int);
    void noteOff(int);
};

#endif // PIANOINPUT_H
