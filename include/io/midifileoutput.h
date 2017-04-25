#ifndef MIDIFILEOUTPUT_H
#define MIDIFILEOUTPUT_H

#include <QTime>

#include "abstractoutput.h"
#include "MidiFile.h"

// MidiFileOutput inherits AbstractOutput and executes the writing to MIDI
// files of the messages it receives from the OutputHandler
class MidiFileOutput : public AbstractOutput
{
public:
    MidiFileOutput(QString fileName);
    void start();
    void stop();
    void sendNoteOn(int);
    void sendNoteOff(int);

private:
    MidiFile* outputFile_;
    QString fileName_;
    QTime* time_;
    double timeElapsed_;
    int actionTime_;
};

#endif // MIDIFILEOUTPUT_H
