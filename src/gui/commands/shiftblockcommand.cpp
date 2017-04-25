#include "shiftblockcommand.h"

ShiftBlockCommand::ShiftBlockCommand(int index,
                                     bool left,
                                     BlockFrame* frame,
                                     InputProcessor *processor,
                                     QUndoCommand *parent)
    : QUndoCommand(parent)
{
    oldPos_ = index;
    newPos_ = left ? index - 1 : index + 1;
    isLeft_ = left;
    frame_ = frame;
    processor_ = processor;

    setText("Shift Block");
}

void ShiftBlockCommand::undo() {
    if (isLeft_) {
        frame_->shiftBlockRight(newPos_);
        processor_->shiftBlockRight(newPos_);
    } else {
        frame_->shiftBlockLeft(newPos_);
        processor_->shiftBlockLeft(newPos_);
    }
}

void ShiftBlockCommand::redo() {
    if (isLeft_) {
        frame_->shiftBlockLeft(oldPos_);
        processor_->shiftBlockLeft(oldPos_);
    } else {
        frame_->shiftBlockRight(oldPos_);
        processor_->shiftBlockRight(oldPos_);
    }
}
