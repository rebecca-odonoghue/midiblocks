#include "pianoinput.h"

PianoInput::PianoInput() : AbstractInput()
{
    isStopped_ = true;
}

void PianoInput::noteOn(int note) {
    if(!isStopped_)
        emit sendMessage((int)NOTE_ON, note);
}

void PianoInput::noteOff(int note) {
    if(!isStopped_)
        emit sendMessage((int)NOTE_OFF, note);
}

void PianoInput::start() {
    isStopped_ = false;
}

void PianoInput::stop() {
    isStopped_ = true;
}
