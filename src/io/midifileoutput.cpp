#include "midifileoutput.h"

#include <QDebug>

MidiFileOutput::MidiFileOutput(QString fileName) : AbstractOutput()
{
    fileName_ = fileName;
    outputFile_ = new MidiFile();
    outputFile_->absoluteTicks();
    outputFile_->setTicksPerQuarterNote(48);
    time_ = new QTime();
}

void MidiFileOutput::start() {
    outputFile_->clear();
    outputFile_->write(fileName_.toStdString());
    time_->start();
    timeElapsed_ = 0.0;
    actionTime_ = 0;
}

void MidiFileOutput::stop() {
    timeElapsed_ = time_->elapsed() / 1000.0;
    actionTime_ = timeElapsed_*96;
    vector<unsigned char> midiEvent;
    midiEvent.resize(3);
    midiEvent[0] = 0xb0;
    midiEvent[1] = 123;
    midiEvent[2] = 0;
    outputFile_->addEvent(0, actionTime_, midiEvent);

    outputFile_->sortTracks();
    outputFile_->write(fileName_.toStdString());
}

void MidiFileOutput::sendNoteOn(int note) {
    timeElapsed_ = time_->elapsed() / 1000.0;
    actionTime_ = timeElapsed_*96;
    vector<unsigned char> midiEvent;
    midiEvent.resize(3);
    midiEvent[0] = 0x90;
    midiEvent[1] = note + 23;
    midiEvent[2] = 100;
    outputFile_->addEvent(0, actionTime_, midiEvent);
}

void MidiFileOutput::sendNoteOff(int note) {
    timeElapsed_ = time_->elapsed() / 1000;
    actionTime_ = timeElapsed_*96;
    vector<unsigned char> midiEvent;
    midiEvent.resize(3);
    midiEvent[0] = 0x80;
    midiEvent[1] = note + 23;
    midiEvent[2] = 100;
    outputFile_->addEvent(0, actionTime_, midiEvent);
}
