#include "scale.h"

// Instantates a scale with the provided mode and list of Notes,
// determines the root note from the list.
Scale::Scale(QString mode, QList<Note> notes)
{
    this->mode = mode;
    notes_ = notes;
    rootNote = notes_.at(0);
}

// Returns the mode of the scale
QString Scale::getMode() {
    return mode;
}

// Returns the notes contained in the scale
QList<Note> Scale::getNotes() {
    return notes_;
}

// Returns the root note of the scale
Note Scale::getRoot() {
    return rootNote;
}

// Returns the size of the scale (not including duplicate notes)
int Scale::size() {
    return notes_.size() - 1;
}

// Returns true if the scale contains note, false otherwise
bool Scale::contains(Note note) {
    return notes_.contains(note);
}

// Operator ==, returns true if the scales have the same mode and the
// same root note, false otherwise
bool Scale::operator==(const Scale &scale) const {
    bool result = ((scale.mode == this->mode)
            && (scale.rootNote == this->rootNote));
    return result;
}
