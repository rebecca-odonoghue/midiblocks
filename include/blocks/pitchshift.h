#ifndef PITCHSHIFT_H
#define PITCHSHIFT_H

#include "block.h"
#include "blocktypes.h"

// Pitch Shift block class inherits abstract Block
class PitchShift : public Block
{
    Q_OBJECT

public:
    PitchShift(int shift);
    int getShift();
    void setShift(int);
    void setScale(Scale*);
    void clear() {}

private:
    Scale* scale_;
    QList<int> allowedNotes_;
    int shift_;

public slots:
    void receiveNote(int, int);
    void onTick() {}
};

#endif // PITCHSHIFT_H
