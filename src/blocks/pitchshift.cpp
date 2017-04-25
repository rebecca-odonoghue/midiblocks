#include "pitchshift.h"

PitchShift::PitchShift(int shift) : Block()
{
    shift_ = shift;
}

// Returns the blocks shift property
int PitchShift::getShift() {
    return shift_;
}

// Sets the blocks shift property
void PitchShift::setShift(int shift) {
    shift_ = shift;
}

// Sets the scale and generates a list of allowed notes
void PitchShift::setScale(Scale *scale) {
    scale_ = scale;

    allowedNotes_.clear();
    for (int i = 0; i < 84; i++) {
        if (scale_->contains((Note)(i % 12))) {
            allowedNotes_.append(i + 1);
        }
    }
}

// Receives, shifts and emits a note
void PitchShift::receiveNote(int type, int note) {
    note = note + shift_;

    if(!allowedNotes_.contains(note)) {
        int i;
        for (i = 0; i < allowedNotes_.size(); i++) {
            if (allowedNotes_.at(i) > note) {
                break;
            }
        }
        if (i == allowedNotes_.size()) {
            note = allowedNotes_.at(i - 1);
        } else if (i == 0) {
            note = allowedNotes_.at(i);
        } else if (note - allowedNotes_.at(i - 1)
                   < allowedNotes_.at(i) - note ) {
            note = allowedNotes_.at(i - 1);
        } else {
            note = allowedNotes_.at(i);
        }
    }

    emit sendNote(type, note);
}
