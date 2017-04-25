#include "monophonic.h"

Monophonic::Monophonic() : Block()
{
    currentNote_ = 0;
}

// Resets the current note to 0
void Monophonic::clear() {
    currentNote_ = 0;
}

// Receives a note, if a note was already playing send a note off for that note
// before a note on for the new note, if a note off is received for the current
// note, emit a note off
void Monophonic::receiveNote(int type, int note) {
    if((MessageType)type == NOTE_ON) {
        if (currentNote_ == 0) {
            currentNote_ = note;
        } else {
            emit sendNote((int)NOTE_OFF, currentNote_);
            emit sendNote((int)NOTE_ON, note);
            currentNote_ = note;
        }
    } else {
        if (note == currentNote_) {
            emit sendNote((int)NOTE_OFF, note);
        }
    }

}
