#include "blockdata.h"

BlockData::BlockData()
{
    type = 0;
    firstParameter = "";
    secondParameter = "";
}

// Writes the variable data to a stream
QDataStream &operator<<(QDataStream& out, const BlockData &block) {
    out << block.type;
    out << block.firstParameter;
    out << block.secondParameter;
    return out;
}

// Reads the variable data from a stream
QDataStream &operator>>(QDataStream& in, BlockData &block) {
    in >> block.type;
    in >> block.firstParameter;
    in >> block.secondParameter;
    return in;
}
