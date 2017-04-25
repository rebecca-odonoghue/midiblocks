#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QString>
#include <QDebug>

#include "iotypes.h"
#include "scale.h"

// An abstract class representing a processing block to be placed in the
// processing chain.
class Block : public QObject
{
    Q_OBJECT

public:
    ~Block() {}
    virtual void setScale(Scale*) = 0;
    virtual void clear() = 0;

signals:
    void sendNote(int, int);

public slots:
    virtual void receiveNote(int, int) = 0;
    virtual void onTick() = 0;
};

#endif // BLOCK_H

