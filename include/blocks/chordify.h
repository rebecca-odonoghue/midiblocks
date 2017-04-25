#ifndef CHORDIFY_H
#define CHORDIFY_H

#include "block.h"
#include "blocktypes.h"

//Chordify block class inherits abstract Block
class Chordify : public Block
{
    Q_OBJECT

public:
    Chordify();
    void setScale(Scale*);
    void clear();

private:
    Scale* scale_;
    QList<int> allowedNotes_;
    QList<int> notesOn_;
    QList<int> getChord(int);

public slots:
    void receiveNote(int, int);
    void onTick() {}
};

#endif // CHORDIFY_H
