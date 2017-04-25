#include "changeinputcommand.h"

ChangeInputCommand::ChangeInputCommand(InputType oldInput,
                                       InputType newInput,
                                       QString newArg,
                                       InputProcessor* processor,
                                       QUndoCommand* parent)
    : QUndoCommand(parent)
{
    oldInput_ = oldInput;
    newInput_ = newInput;
    newArg_ = newArg;
    oldArg_ = processor->getInputArg();
    processor_ = processor;

    setText("Change Input");
}

void ChangeInputCommand::undo() {
    processor_->changeInput(oldInput_, oldArg_);
}

void ChangeInputCommand::redo() {
    processor_->changeInput(newInput_, newArg_);
}
