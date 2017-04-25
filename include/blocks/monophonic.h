#ifndef MONOPHONIC_H
#define MONOPHONIC_H

#include "block.h"
#include "blocktypes.h"

// Monophonic block class inherits abstract Block
class Monophonic : public Block
{
    Q_OBJECT

public:
    Monophonic();
    void setScale(Scale*) {}
    void clear();

private:
    int currentNote_;

public slots:
    void receiveNote(int, int);
    void onTick() {}
};

#endif // MONOPHONIC_H
