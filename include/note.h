#ifndef NOTE_H
#define NOTE_H

#include <QStringList>

// Enum describing a note
typedef enum {C,
              Db,
              D,
              Eb,
              E,
              F,
              Gb,
              G,
              Ab,
              A,
              Bb,
              B}
             Note;

// Descriptions of notes for the GUI
static const QStringList noteLetters = {"C",
                                        "C#/Db",
                                        "D",
                                        "D#/Eb",
                                        "E",
                                        "F",
                                        "F#/Gb",
                                        "G",
                                        "G#/Ab",
                                        "A",
                                        "A#/Bb",
                                        "B"};

#endif // NOTE_H

