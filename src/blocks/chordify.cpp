#include "chordify.h"

Chordify::Chordify() : Block()
{    
}

// Recieves a note, adds or removes its chord notes from the list of notes on,
// if a note is already on, emit a note off and on again
void Chordify::receiveNote(int type, int note) {

    if(allowedNotes_.contains(note)) {
        switch((MessageType)type) {
            case NOTE_ON :
                foreach(int chordNote, getChord(note)) {
                    if(notesOn_.contains(chordNote)) {
                        emit sendNote((int)NOTE_OFF, chordNote);
                    }
                    notesOn_.append(chordNote);
                    emit sendNote((int)NOTE_ON, chordNote);
                }
                break;
            case NOTE_OFF :
                foreach (int chordNote, getChord(note)) {
                    if (notesOn_.indexOf(chordNote)
                            == notesOn_.lastIndexOf(chordNote)) {
                        emit sendNote((int)NOTE_OFF, chordNote);
                    }
                    notesOn_.removeOne(chordNote);
                }
                break;
            default:
                return;
        }
    }
}

// Clears all notes on
void Chordify::clear() {
    notesOn_.clear();
}

// Returns a list of notes that create a chord from the provided note
QList<int> Chordify::getChord(int note) {
    QList<int> chord;
    int index = allowedNotes_.indexOf(note);
    chord.append(note);

    if(index < allowedNotes_.size() - 2)
        chord.append(allowedNotes_.at(index + 2));
    if(index < allowedNotes_.size() - 4)
        chord.append(allowedNotes_.at(index + 4));
    return chord;
}

// Sets the scale by determining a list of allowed notes
void Chordify::setScale(Scale *scale) {
    allowedNotes_.clear();

    for (int i = 0; i < 84; i++) {
        if (scale->contains((Note)(i % 12))) {
            allowedNotes_.append(i + 1);
        }
    }
}
