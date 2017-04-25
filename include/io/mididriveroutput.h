#ifndef MIDIDRIVEROUTPUT_H
#define MIDIDRIVEROUTPUT_H

#include <windows.h>
#include <cstdlib>
#include <vector>

#include <QStringList>

#include "RtMidi.h"

#include "abstractoutput.h"

// MidiDriverOutput inherits AbstractOutput and executes the output of MIDI
// messages to the Windows MIDI Driver that it receives from the OutputHandler
class MidiDriverOutput : public AbstractOutput
{
public:
    MidiDriverOutput();
    QStringList getPortNames();
    void setPort(QString);
    void start();
    void stop();
    void sendNoteOn(int);
    void sendNoteOff(int);

private:
    RtMidiOut* midiOut_;
    bool isStopped_;
    int portNo_;
    QStringList portNames_;
};

#endif // MIDIDRIVEROUTPUT_H
