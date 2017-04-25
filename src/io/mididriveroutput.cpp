#include "mididriveroutput.h"
#include <QDebug>

MidiDriverOutput::MidiDriverOutput() : AbstractOutput()
{
    try {
      midiOut_ = new RtMidiOut(RtMidi::WINDOWS_MM);
    }
    catch ( RtMidiError &error ) {
        qDebug() << QString::fromStdString(error.getMessage());
    }

    unsigned int nPorts = midiOut_->getPortCount();
    qDebug() << "There are " << QString::number(nPorts) << " MIDI output ports available.";

    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        portNames_.append(QString::fromStdString(midiOut_->getPortName(i)));
      }
      catch ( RtMidiError &error ) {
        qDebug() << QString::fromStdString(error.getMessage());
        delete midiOut_;
      }
    }
}

QStringList MidiDriverOutput::getPortNames() {
    return portNames_;
}

void MidiDriverOutput::setPort(QString port) {
    portNo_ = port.toInt();
}

void MidiDriverOutput::start(){
    if(isStopped_) {
        try {
          midiOut_->openPort(portNo_);
          isStopped_ = false;
        }
        catch (RtMidiError &error) {
          qDebug() << QString::fromStdString(error.getMessage());
          stop();
          isStopped_ = true;
        }
    }
}

void MidiDriverOutput::stop(){
    midiOut_->closePort();
    isStopped_ = true;
}

void MidiDriverOutput::sendNoteOn(int note){
    std::vector<unsigned char> message;
    message.resize(3);
    message[0] = 0x90;
    message[1] = note + 23;
    message[2] = 120;

    try {
        midiOut_->sendMessage( &message );
    }
    catch (RtMidiError &error) {
      qDebug() << QString::fromStdString(error.getMessage());
      stop();
    }
}

void MidiDriverOutput::sendNoteOff(int note){
    std::vector<unsigned char> message;
    message.resize(3);
    message[0] = 0x80;
    message[1] = note + 23;
    message[2] = 120;

    try {
        midiOut_->sendMessage( &message );
    }
    catch (RtMidiError &error) {
      qDebug() << QString::fromStdString(error.getMessage());
      stop();
    }
}
