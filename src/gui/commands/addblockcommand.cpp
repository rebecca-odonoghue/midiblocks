#include "addblockcommand.h"

#include <QDebug>
#include <QString>

AddBlockCommand::AddBlockCommand(BlockType type,
                                 QStringList blockArgs,
                                 BlockFrame* frame,
                                 InputProcessor* processor,
                                 QUndoCommand* parent)
    : QUndoCommand(parent)
{
    type_ = type;
    blockArgs_ = blockArgs;
    frame_ = frame;
    processor_ = processor;

    index_ = frame_->blockCount();

    setText("Add Block");
}

void AddBlockCommand::undo() {
    frame_->deleteBlock(index_);\
    processor_->deleteBlock(index_);
}

void AddBlockCommand::redo() {
    frame_->addBlock(type_, blockArgs_);
    processor_->addBlock(type_, blockArgs_);
}
