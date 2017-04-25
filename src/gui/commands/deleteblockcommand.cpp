#include "deleteblockcommand.h"
#include <QDebug>
#include <QString>

DeleteBlockCommand::DeleteBlockCommand(int index,
                                       BlockFrame *frame,
                                       InputProcessor *processor,
                                       QUndoCommand *parent)
    : QUndoCommand(parent)
{
    widget_ = frame->getBlock(index);
    block_ = processor->getBlock(index);
    index_ = index;
    frame_ = frame;
    processor_ = processor;

    setText("Delete Block");
}

void DeleteBlockCommand::undo() {
    frame_->insertBlock(index_, widget_);
    processor_->insertBlock(index_, block_);
}

void DeleteBlockCommand::redo() {
    frame_->deleteBlock(index_);
    processor_->deleteBlock(index_);
}
