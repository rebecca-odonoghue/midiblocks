#include "inputprocessor.h"

InputProcessor::InputProcessor(QObject* parent) : QThread(parent)
{
    // Initialise variables
    inputType_ = NO_INPUT;
    outputType_ = NO_OUTPUT;
    inputArg_ = "";
    scale_ = (Scale*)malloc(sizeof(Scale));
    inputHandler_ = new InputHandler(this);
    outputHandler_ = new OutputHandler(this);

    // Connect the signals sent from InputHandler to their appropriate slots
    connect(inputHandler_, &InputHandler::illegalWrite, this,
            &InputProcessor::catchIllegalWrite);
    connect(inputHandler_, &InputHandler::tempoChange, this,
            &InputProcessor::changeTempo);
    connect(inputHandler_, &InputHandler::fileFinished, this,
            &InputProcessor::endOfFile);

    // Connect the chain of input, blocks and output
    connectChain();
}

// Emits a tempoChanged signal whent the tempo is changed
void InputProcessor::changeTempo(int bpm) {
    emit tempoChanged(bpm);
}

// Returns the input
AbstractInput* InputProcessor::getInput() {
    return inputHandler_->getHandle();
}

// Returns the argument relevant to the input (port number or file name)
QString InputProcessor::getInputArg() {
    return inputArg_;
}

// Returns the list of MIDI input ports available
QStringList InputProcessor::getInputPortNames() {
    return inputHandler_->getPortNames();
}

// Returns the list of COM ports available
QStringList InputProcessor::getOutputComPortNames() {
    return outputHandler_->getComPortNames();
}

// Stores and sends the scale configuration information to the output
// handler
void InputProcessor::setConfigInfo(QList<int> notes) {
    configInfo_ = notes;
    outputHandler_->sendConfigInfo(configInfo_);
}

// Returns a list of MIDI output ports available
QStringList InputProcessor::getOutputMidiPortNames() {
    return outputHandler_->getMidiPortNames();
}

// Catches and emits an illegal write signal
void InputProcessor::catchIllegalWrite() {
    emit illegalWrite();
}

// Catches and emits an end of file signal
void InputProcessor::endOfFile() {
    emit fileFinished();
}

// Returns the block at position index in the chain
Block* InputProcessor::getBlock(int index) {
    return blocks_.at(index);
}

// Returns the number of blocks in the chain
int InputProcessor::numBlocks() {
    return blocks_.size();
}

// Receives and emits to each block, the metronome ticks
void InputProcessor::onTick() {
    foreach(Block* block, blocks_) {
        block->onTick();
    }
}

// Handles a change of scale and stores it
void InputProcessor::setScale(const Scale* scale) {
    memcpy(scale_, scale, sizeof(Scale));
    outputHandler_->clear();
    foreach(Block* block, blocks_) {
        block->clear();
        block->setScale(scale_);
    }
}

// Adds a block of a specified type with specified arguments to the end of the
// processing chain
void InputProcessor::addBlock(BlockType type, QStringList args) {
    Block* block = 0;
    switch(type) {
        case PITCH_SHIFT :
            block = new PitchShift(args.at(0).toInt());
            break;
        case ARPEGGIATOR :
            block = new Arpeggiator((ArpeggiatorPattern)patternNames.indexOf(args.at(0)));
            break;
        case MONOPHONIC :
            block = new Monophonic();
            break;
        case CHORDIFY :
            block = new Chordify();
            break;
        case GATE :
            block = new Gate(args.at(0).toDouble(), (GateMode)modeNames.indexOf(args.at(1)));
            break;
    }
    block->setScale(scale_);
    insertBlock(blocks_.size(), block);
}

// Inserts a block at index position in the processing chain
void InputProcessor::insertBlock(int index, Block* block) {
    blocks_.insert(index, block);
    connectChain();
}

// Shifts the block at the specified index left once
void InputProcessor::shiftBlockLeft(int index) {
    Block* block = blocks_.at(index);
    int newPos = index - 1;
    blocks_.removeAll(block);
    blocks_.insert(newPos, block);

    connectChain();
}

//Shifts the block at the specified index right one
void InputProcessor::shiftBlockRight(int index) {
    Block* block = blocks_.at(index);
    int newPos = index + 1;
    blocks_.removeAll(block);
    blocks_.insert(newPos, block);

    connectChain();
}

// Deletes the block at the specified index
void InputProcessor::deleteBlock(int index) {
    Block* block = blocks_.at(index);
    blocks_.removeAll(block);
    connectChain();
}

// Reinitialises all variables in the configuration
void InputProcessor::newProject() {
    stopInput();
    stopOutput();
    inputType_ = NO_INPUT;
    outputType_ = NO_OUTPUT;
    inputHandler_->setInputType(NO_INPUT, "");
    outputHandler_->setOutputType(NO_OUTPUT, "");
    blocks_.clear();
    connectChain();
}

// Connects the processing chain from input to each block to output
void InputProcessor::connectChain() {
    disconnect(inputHandler_, &InputHandler::sendNote, 0, 0);
    outputHandler_->clear();
    foreach (Block* block, blocks_) {
        disconnect(block, &Block::sendNote, 0, 0);
        block->clear();
    }

    if (blocks_.size() == 0) {
        connect(inputHandler_, &InputHandler::sendNote, outputHandler_,
                &OutputHandler::receiveNote);
    } else {
        for (int i = 0; i < blocks_.size(); i++) {
            if(i == 0) {
               connect(inputHandler_, &InputHandler::sendNote, blocks_.at(i),
                       &Block::receiveNote);
            } else {
               connect(blocks_.at(i - 1), &Block::sendNote, blocks_.at(i),
                       &Block::receiveNote);
            }

            if (i == blocks_.size() - 1) {
               connect(blocks_.at(i), &Block::sendNote, outputHandler_,
                       &OutputHandler::receiveNote);
            }
        }
    }
}

void InputProcessor::changeOutput(OutputType type, QString arg) {
    stopOutput();
    outputType_ = type;
    outputHandler_->setOutputType(type, arg);

    if(outputType_ == NO_OUTPUT) {
        inputHandler_->setAllowWrite(false);
    } else {
        inputHandler_->setAllowWrite(true);
    }

    if (outputType_ == MIDI_DRIVER_OUT || outputType_ == USB) {
        startOutput();
    }
}

// Changes the input type, determines if the input is allowed to send notes
// and if it should begin immediately or wait for a play signal
void InputProcessor::changeInput(InputType type, QString arg) {
    stopInput();
    inputType_ = type;
    inputArg_ = arg;
    inputHandler_->setInputType(type, arg);
    if(outputType_ == NO_OUTPUT) {
        inputHandler_->setAllowWrite(false);
    } else {
        inputHandler_->setAllowWrite(true);
    }
    if (inputType_ == PIANO || inputType_ == MIDI_DRIVER_IN) {
        startInput();
    }
    emit inputChanged(type);
}

// Allow the input to send messages
void InputProcessor::startInput() {
    inputHandler_->start();
    emit startMetronome();
}

// Disallow the input from sending messages, stop the metronome and
// clear all notes
void InputProcessor::stopInput(){
    inputHandler_->stop();
    emit stopMetronome();
    foreach (Block* block, blocks_) {
        block->clear();
    }
    outputHandler_->clear();
}

// Allow the output to receive notes
void InputProcessor::startOutput(){
    this->outputHandler_->start();
    outputHandler_->sendConfigInfo(configInfo_);
}

// Disallow the output to receive notes
void InputProcessor::stopOutput(){
    this->outputHandler_->stop();
}
