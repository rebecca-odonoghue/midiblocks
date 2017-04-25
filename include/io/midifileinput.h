#ifndef MIDIFILEINPUT_H
#define MIDIFILEINPUT_H

#include <windows.h>

#include <QObject>
#include <QQueue>
#include <QTimer>

#include "MidiFile.h"

#include "abstractinput.h"


// MidiFileInput inherits AbstractInput and executes the reading of MIDI
// files, relaying them to the InputHandler
class MidiFileInput : public AbstractInput
{
    Q_OBJECT

public:
    MidiFileInput(QString fileName);
    void start();
    void stop();

private:
    void readMessages();
    QString fileName_;
    MidiFile* inputFile_;
    QQueue<int> messageIndexes_;
    QList<QTimer*> timers_;
    bool isStopped_;
    double tempoSPT_;
    int ticksPerQuarter_;

private slots:
    void emitMessage();
    void endOfFile();

signals:
    void fileFinished();
};

#endif // MIDIFILEINPUT_H
