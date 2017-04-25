#ifndef ABSTRACTOUTPUT_H
#define ABSTRACTOUTPUT_H

#include <windows.h>

// An abstract class describing a MIDI output
class AbstractOutput {

public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void sendNoteOn(int) = 0;
    virtual void sendNoteOff(int) = 0;
};

#endif // ABSTRACTOUTPUT_H

