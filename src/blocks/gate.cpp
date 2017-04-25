#include "gate.h"

Gate::Gate(double notesPerTick, GateMode mode) : Block()
{
    // Instantiate all parameters depending on whether the value of notes per
    // tick is greater or less than 1
    notesPerTick_ = notesPerTick;
    mode_ = mode;
    tickCount_ = 1;
    if (notesPerTick_ < 1.0) {
        nPerTick_ = 1;
        tickFreq_ = (int)(1.0 / notesPerTick_);
    } else {
        nPerTick_ = (int)(notesPerTick_ + 0.5);
        tickFreq_ = 1;
    }
}

// Returns the notes per tick property
double Gate::getNotesPerTick() {
    return notesPerTick_;
}

// Sets the notes per tick property and instantates all variables appropriately
void Gate::setNotesPerTick(double notesPerTick) {
    notesPerTick_ = notesPerTick;
    tickCount_ = 1;
    if (notesPerTick_ < 1.0) {
        tickFreq_ = (int)(1.0 / notesPerTick_);
        nPerTick_ = 1;
    } else {
        tickFreq_ = 1;
        nPerTick_ = (int)(notesPerTick_ + 0.5);
    }
}

// Returns the mode property
GateMode Gate::getMode() {
    return mode_;
}

// Sets the mode property and resets the queue and current notes
void Gate::setMode(GateMode mode) {
    mode_ = mode;
    queue_.clear();
    notesOn_.clear();
    notesOff_.clear();
}

// Resets the queue and all current notes
void Gate::clear() {
    queue_.clear();
    notesOn_.clear();
    notesOff_.clear();
}

// Receieve a note and add it to the queue
void Gate::receiveNote(int type, int note) {
    if((MessageType)type == NOTE_ON) {
        queue_.append(note);
    } else if ((MessageType)type == NOTE_OFF) {
        if (notesOn_.contains(note)) {
            notesOff_.append(note);
        } else if (queue_.contains(note)) {
            queue_.removeOne(note);
        }
    }
}

// Called on metronome tick, releases the appropriate amount of notes on
// depending on the notes per tick property, from the front or end of the
// queue depending on the mode property, also sends all notes off that have
// been receieved for notes currently playing
void Gate::onTick() {
    if(tickCount_ == tickFreq_) {
        tickCount_ = 1;

        foreach(int note, notesOff_) {
            emit sendNote((int)NOTE_OFF, note);
        }

        notesOff_.clear();

        if(!queue_.isEmpty()) {
            int count = 0;
            switch(mode_) {
                case QUEUE :
                    while (!queue_.isEmpty() && count < nPerTick_) {
                        emit sendNote((int)NOTE_ON, queue_.first());
                        notesOn_.append(queue_.first());
                        queue_.removeFirst();
                        count++;
                    }
                    break;
                case FIRST_HOLD :
                    emit sendNote((int)NOTE_ON, queue_.first());
                    notesOn_.append(queue_.first());
                    queue_.clear();
                    break;
                case LAST_HOLD :
                    emit sendNote((int)NOTE_ON, queue_.last());
                    notesOn_.append(queue_.last());
                    queue_.clear();
                    break;
            }
        }

    } else {
        tickCount_++;
    }
}
