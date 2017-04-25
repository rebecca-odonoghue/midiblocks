#include "midifileinput.h"

#include <QDebug>

MidiFileInput::MidiFileInput(QString fileName) : AbstractInput()
{
    fileName_ = fileName;
    isStopped_ = true;
    inputFile_ = new MidiFile();
    inputFile_->deltaTicks();
    inputFile_->read(fileName.toStdString());
    ticksPerQuarter_ = inputFile_->getTicksPerQuarterNote();
    tempoSPT_ = 0.5/ticksPerQuarter_;
}

void MidiFileInput::start() {
    if(!inputFile_->status()) {
        qDebug() << "Error reading MIDI file.";
    } else {
        isStopped_ = false;
        readMessages();
    }
}

void MidiFileInput::readMessages() {
    int messageTime = 0;
    for (int i = 0; i < inputFile_[0][0].size(); i++) {
        MidiEvent event = inputFile_->getEvent(0, i);
        if (event.isNote() || event.isTempo()) {
            messageTime = event.tick*tempoSPT_*1000;
            messageIndexes_.enqueue(i);
            if (event.isTempo()) {
                tempoSPT_ = event.getTempoSeconds() / ticksPerQuarter_;
            }
            QTimer* timer = new QTimer(this);
            timer->setSingleShot(true);
            timer->setInterval(messageTime);
            connect(timer, &QTimer::timeout, this,
                    &MidiFileInput::emitMessage);
            timers_.append(timer);
            timer->start();
        }
    }
    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(messageTime);
    connect(timer, &QTimer::timeout, this, &MidiFileInput::endOfFile);
    timers_.append(timer);
    timer->start();
}

void MidiFileInput::emitMessage() {
    if(!isStopped_) {
        int eventIndex = messageIndexes_.dequeue();
        MidiEvent event = inputFile_->getEvent(0, eventIndex);
        if (event.isNoteOn()) {
            emit sendMessage((int)NOTE_ON, event.getKeyNumber() - 23);
        } else if (event.isNoteOff()) {
            emit sendMessage((int)NOTE_OFF, event.getKeyNumber() - 23);
        } else if (event.isTempo()) {
            emit sendMessage((int)TEMPO, event.getTempoBPM());
        }
    }
}

void MidiFileInput::endOfFile() {
    emit fileFinished();
}

void MidiFileInput::stop() {
    if(!isStopped_) {
        foreach(QTimer* timer, timers_) {
            timer->stop();
        }
        timers_.clear();
        messageIndexes_.clear();
        isStopped_ = true;
    }
}
