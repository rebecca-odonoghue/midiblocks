#ifndef MIDIDRIVERINPUT_H
#define MIDIDRIVERINPUT_H

#include <QObject>

#include "RtMidi.h"

#include "abstractinput.h"

// MidiDriverInput inherits AbstractInput and executes the receiving of MIDI
// messages from the Windows MIDI Driver, relaying them to the InputHandler
class MidiDriverInput : public AbstractInput
{
    Q_OBJECT

public:
    MidiDriverInput();
    void start();
    void stop();
    void noteOn(int);
    void noteOff(int);
    QStringList getPortNames();
    void setPort(QString);
    bool stopped();

private:
    RtMidiIn* midiIn_;
    bool isStopped_;
    int portNo_;
    QStringList portNames_;
};

#endif // MIDIDRIVERINPUT_H
