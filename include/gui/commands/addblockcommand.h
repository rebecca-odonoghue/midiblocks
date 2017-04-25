#ifndef ADDBLOCKCOMMAND_H
#define ADDBLOCKCOMMAND_H

#include <QUndoCommand>

#include "blockframe.h"
#include "inputprocessor.h"

// Add block command for the QUndo Framework, allows undoing and redoing of
// unlimited actions
class AddBlockCommand : public QUndoCommand
{
public:
    AddBlockCommand(BlockType type,
                    QStringList blockArgs,
                    BlockFrame* frame,
                    InputProcessor *processor,
                    QUndoCommand *parent = 0);

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    BlockType type_;
    QStringList blockArgs_;
    int index_;
    BlockFrame* frame_;
    InputProcessor* processor_;
};

#endif // ADDBLOCKCOMMAND_H
