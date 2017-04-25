#ifndef IOTYPES
#define IOTYPES

#include <QString>
#include <QList>

// MIDI input types
typedef enum {NO_INPUT, MIDI_FILE_IN, PIANO, MIDI_DRIVER_IN} InputType;

// MIDI output types
typedef enum {NO_OUTPUT, MIDI_FILE_OUT, USB, MIDI_DRIVER_OUT} OutputType;

// The different types of messages to be processed by the application
typedef enum {NOTE_ON = 86, NOTE_OFF = 87, CONFIG = 88, TEMPO = 89} MessageType;

// MIDI input descriptions
const static QList<QString> inputStrings = {"None", "MIDI File", "Piano", "Windows MIDI Driver"};

// MIDI output descriptions
const static QList<QString> outputStrings = {"None", "MIDI File", "USB", "Windows MIDI Driver"};

#endif // IOTYPES

