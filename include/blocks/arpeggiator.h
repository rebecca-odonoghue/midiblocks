#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

#include <stdlib.h>

#include "block.h"
#include "blocktypes.h"

// Arpeggiator block, inherits abstract Block class
class Arpeggiator : public Block
{
    Q_OBJECT

public:
    Arpeggiator(ArpeggiatorPattern pattern);
    ArpeggiatorPattern getPattern();
    void setPattern(ArpeggiatorPattern);
    void setScale(Scale*) {}
    void clear();

private:
    ArpeggiatorPattern pattern_;
    QList<int> notesOn_;
    int currentNote_, nextNote_;
    bool ascending_;
    int getNextNote();

public slots:
    void receiveNote(int, int);
    void onTick();
};

#endif // ARPEGGIATOR_H
