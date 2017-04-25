#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <QString>
#include <QDataStream>

// A class describing the parameters of a MIDI input device for the purposes
// of saving and loading.
class InputData
{
public:
    InputData();
    int type;
    QString arg;
};

// Operators overriden to allow saving and loading by writing and reading from
// a stream
QDataStream &operator<<(QDataStream &out, const InputData &input);
QDataStream &operator>>(QDataStream &in, InputData &input);

#endif // INPUTDATA_H
