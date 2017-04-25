#include "inputhandler.h"

#include <QDebug>

InputHandler::InputHandler(QObject* parent) : QObject(parent)
{
    isStopped_ = true;
    allowWrite_ = false;
}

// Set whether the input is allowed to send messages along the processing chain
void InputHandler::setAllowWrite(bool allowed) {
    allowWrite_ = allowed;
}

// Set the input type by instantiating a new AbstractInput
void InputHandler::setInputType(InputType inputType, QString args) {
    inputType_ = inputType;
    switch(inputType_) {
    case NO_INPUT:
        handle_ = NULL;
        return;
    case MIDI_FILE_IN:
        handle_ = new MidiFileInput(args);
        connect((MidiFileInput*)handle_, &MidiFileInput::fileFinished, this,
                &InputHandler::endOfFile);
        break;
    case PIANO:
        handle_ = new PianoInput();
        break;
    case MIDI_DRIVER_IN:
        handle_ = new MidiDriverInput();
        ((MidiDriverInput*)handle_)->setPort(args);
        break;
    }    
    connect(handle_, &AbstractInput::sendMessage, this,
            &InputHandler::readMessage);
}

// Return the input
AbstractInput *InputHandler::getHandle() {
    return handle_;
}

// Get a list of MIDI port names
QStringList InputHandler::getPortNames() {
    MidiDriverInput* midiDriver = new MidiDriverInput();
    return midiDriver->getPortNames();
}

void InputHandler::start() {
    if(isStopped_) {
        handle_->start();
        isStopped_ = false;
    }
}

void InputHandler::stop() {
    if(!isStopped_) {
        handle_->stop();
        isStopped_ = true;
    }
}

void InputHandler::readMessage(int type, int data) {
    MessageType msgType = (MessageType)type;
    if(allowWrite_) {
        if (msgType == NOTE_ON) {
            emit sendNote(NOTE_ON, data);
        } else if (msgType == NOTE_OFF) {
            emit sendNote(NOTE_OFF, data);
        } else if (msgType == TEMPO) {
            emit tempoChange(data);
        }
    } else if (msgType == NOTE_ON && inputType_ != MIDI_FILE_IN) {
        emit illegalWrite();
    }
}

void InputHandler::endOfFile() {
    emit fileFinished();
}
