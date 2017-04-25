#include "mididriverinput.h"

#include <QDebug>

void getMessage(double /*deltatime*/, std::vector< unsigned char > *message, void* userData) {
    MidiDriverInput* inputHandler = (MidiDriverInput*)userData;
    if(message->size() > 0 && !(inputHandler->stopped())) {
        if((message->at(0) & 0xf0) == 0x80) {
            int note = (int)message->at(1) - 23;
            (inputHandler)->noteOff(note);
        } else if ((message->at(0) & 0xf0) == 0x90) {
            int note = (int)message->at(1) - 23;
            (inputHandler)->noteOn(note);
        }
    }
}

MidiDriverInput::MidiDriverInput() : AbstractInput() {
    midiIn_ = 0;
    try {
        midiIn_ = new RtMidiIn(RtMidi::WINDOWS_MM);
        midiIn_->setCallback(&getMessage, (void*)this);
    } catch (RtMidiError &error) {
        qDebug() << QString::fromStdString(error.getMessage());
    }

    unsigned int nPorts = midiIn_->getPortCount();
    qDebug() << "\nThere are " << QString::number(nPorts) << " MIDI input sources available.";

    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        portNames_.append(QString::fromStdString(midiIn_->getPortName(i)));
      }
      catch ( RtMidiError &error ) {
        qDebug() << QString::fromStdString(error.getMessage());
        delete midiIn_;
      }
    }
}

void MidiDriverInput::setPort(QString port) {
    portNo_ = port.toInt();
}

bool MidiDriverInput::stopped() {
    return isStopped_;
}

QStringList MidiDriverInput::getPortNames() {
    return portNames_;
}

void MidiDriverInput::start() {
    try {
      midiIn_->openPort(portNo_);
      isStopped_ = false;
    }
    catch (RtMidiError &error) {
      qDebug() << QString::fromStdString(error.getMessage());
      stop();
    }
}

void MidiDriverInput::stop() {
    if(!isStopped_) {
        isStopped_ = true;
        midiIn_->closePort();
    }
}

void MidiDriverInput::noteOn(int note) {
    emit sendMessage((int)NOTE_ON, note);
}

void MidiDriverInput::noteOff(int note) {
    emit sendMessage((int)NOTE_OFF, note);
}
