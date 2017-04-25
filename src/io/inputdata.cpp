#include "inputdata.h"

InputData::InputData()
{
    type = 0;
    arg = "";
}

QDataStream &operator<<(QDataStream& out, const InputData &input) {
    out << input.type;
    out << input.arg;
    return out;
}

QDataStream &operator>>(QDataStream& in, InputData &input) {
    in >> input.type;
    in >> input.arg;
    return in;
}
