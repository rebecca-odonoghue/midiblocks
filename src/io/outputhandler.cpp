#include "outputhandler.h"

OutputHandler::OutputHandler(QObject* parent) : QObject(parent) {
    handle_ = NULL;
}

// Sets the output type by instantiating a new AbstractOutput instance
void OutputHandler::setOutputType(OutputType outputType, QString arg) {
    outputType_ = outputType;
    switch(outputType) {
    case NO_OUTPUT:
        handle_ = NULL;
        break;
    case MIDI_FILE_OUT:
        handle_ = new MidiFileOutput(arg);
        break;
    case USB:
        handle_ = new SerialOutput(arg);
        break;
    case MIDI_DRIVER_OUT:
        handle_ = new MidiDriverOutput();
        ((MidiDriverOutput*)handle_)->setPort(arg);
    }
}

// Returns a list of available MIDI output ports
QStringList OutputHandler::getMidiPortNames() {
    MidiDriverOutput* midiDriver = new MidiDriverOutput();
    return midiDriver->getPortNames();
}

// Returns a list of available COM ports
QStringList OutputHandler::getComPortNames() {
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QStringList portNames;
    foreach(QSerialPortInfo port, ports) {
        portNames.append(port.portName());
    }
    return portNames;
}

// Start the output
void OutputHandler::start() {
   if(handle_ != NULL) {
       handle_->start();
   }
}

// Stop the output
void OutputHandler::stop() {
    if(handle_ != NULL) {
        clear();
        handle_->stop();
    }   
}

// Receive a note, add or remove it from the list of notes on,
// and send it to the output
void OutputHandler::receiveNote(int type, int note) {
    MessageType msgType = (MessageType)type;
    if(handle_ != NULL) {
        if (msgType == NOTE_ON) {
            if (notesOn_.contains(note)) {
                handle_->sendNoteOff(note);
            } else {
                notesOn_.append(note);
            }
            handle_->sendNoteOn(note);
        } else if (msgType == NOTE_OFF) {
            if(notesOn_.contains(note)) {
                notesOn_.removeAll(note);
                handle_->sendNoteOff(note);
            }
        }
    }
}

// Send configuration information to the SerialOutput
void OutputHandler::sendConfigInfo(QList<int> notes) {
    if(outputType_ == USB) {
        ((SerialOutput*)handle_)->sendConfigInfo(notes);
    }
}

// Send note off messages for every on note
void OutputHandler::clear() {
    if(handle_ != NULL) {
        foreach (int note, notesOn_) {
            handle_->sendNoteOff(note);
        }
        notesOn_.clear();
    }
}

