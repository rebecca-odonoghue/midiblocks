#ifndef SCALE_H
#define SCALE_H

#include <QString>
#include <QList>

#include "note.h"

// A class representing a scale consisting of a mode, and a list of notes
class Scale
{
public:
    Scale(QString mode, QList<Note> notes);
    QString getMode();
    QString mode;
    QList<Note> getNotes();
    Note getRoot();
    Note rootNote;
    int size();
    bool contains(Note);
    bool operator==(const Scale &scale) const;

private:
    QList<Note> notes_;
};



#endif // SCALE_H
