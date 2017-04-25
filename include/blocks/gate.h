#ifndef GATE_H
#define GATE_H

#include <QVector>
#include <QList>

#include "block.h"
#include "blocktypes.h"

// Gate block class inherits abstract Block
class Gate : public Block
{
    Q_OBJECT

public:
    Gate(double notesPerTick, GateMode mode);
    double getNotesPerTick();
    void setNotesPerTick(double);
    GateMode getMode();
    void setMode(GateMode);
    void setScale(Scale*) {}
    void clear();

private:
    double notesPerTick_;
    GateMode mode_;
    QVector<int> queue_;
    QList<int> notesOn_, notesOff_;
    int tickCount_, tickFreq_, nPerTick_;

public slots:
    void receiveNote(int, int);
    void onTick();

};

#endif // GATE_H
