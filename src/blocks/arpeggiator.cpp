#include "arpeggiator.h"

Arpeggiator::Arpeggiator(ArpeggiatorPattern pattern) : Block()
{
    pattern_ = pattern;
    ascending_ = true;
    currentNote_ = 0;
    nextNote_ = 0;
}

// Returns the pattern property of the block
ArpeggiatorPattern Arpeggiator::getPattern() {
    return pattern_;
}

// Sets the pattern property of the block
void Arpeggiator::setPattern(ArpeggiatorPattern pattern) {
    pattern_ = pattern;
}

// Resets all notes to 0
void Arpeggiator::clear() {
    currentNote_ = 0;
    nextNote_ = 0;
    notesOn_.clear();
}

// Receives note message and either adds or removes a note from the
// list of on notes
void Arpeggiator::receiveNote(int type, int note) {
    if((MessageType)type == NOTE_ON) {
        if(nextNote_ == 0) {
            nextNote_ = note;
        }
        notesOn_.append(note);
    } else { 
        notesOn_.removeAll(note);
    }
}

// Called on metronome beat, emits a note off for the current note
// and a note on for the next note, if no notes are on, resets both
// values to 0
void Arpeggiator::onTick() {
    if (currentNote_ != 0) {
        emit sendNote((int)NOTE_OFF, currentNote_);
    }
    if (notesOn_.size() > 0) {
        emit sendNote((int)NOTE_ON, nextNote_);
        currentNote_ = nextNote_;
        nextNote_ = getNextNote();
    } else {
        currentNote_ = 0;
        nextNote_ = 0;
    }
}

// Determines the next note to be played based on the current note and
// the pattern
int Arpeggiator::getNextNote() {
    std::sort(notesOn_.begin(), notesOn_.end());

    int currentIndex = notesOn_.indexOf(currentNote_);
    if (notesOn_.size() == 1) {
        return currentNote_;
    }

    switch(pattern_) {
        case ASCENDING :
            if (currentIndex < notesOn_.size() - 1) {
                return notesOn_.at(currentIndex + 1);
            } else {
                return notesOn_.at(0);
            }
        case DESCENDING :
            if (currentIndex > 0) {
                return notesOn_.at(currentIndex - 1);
            } else {
                return notesOn_.at(notesOn_.size() - 1);
            }
        case PING_PONG :
            if (ascending_){
                if (currentIndex < notesOn_.size() - 1) {
                    return notesOn_.at(currentIndex + 1);
                } else {
                    ascending_ = false;
                    return notesOn_.at(currentIndex - 1);
                }
            } else {
                if (currentIndex > 0) {
                    return notesOn_.at(currentIndex - 1);
                } else {
                    ascending_ = true;
                    return notesOn_.at(currentIndex + 1);
                }
            }
            break;
        case RANDOM :
            int nextNoteIndex = currentIndex;
            while (nextNoteIndex == currentIndex) {
                nextNoteIndex = std::rand() % notesOn_.size();
            }
            return notesOn_.at(nextNoteIndex);
            break;
    }
    return currentNote_;
}
