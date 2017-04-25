#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <QString>
#include <QDataStream>

// A class containing the information about a processing block for the
// purposes of saving and loading.
class BlockData
{
public:
    BlockData();
    int type;
    QString firstParameter;
    QString secondParameter;
};

// Overriding operators to write class to and read class from stream for
// the purpose of saving and loading.
QDataStream &operator<<(QDataStream &out, const BlockData &block);
QDataStream &operator>>(QDataStream &in, BlockData &block);

#endif // BLOCKDATA_H
