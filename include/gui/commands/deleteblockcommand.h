#ifndef DELETEBLOCKCOMMAND_H
#define DELETEBLOCKCOMMAND_H

#include <QUndoCommand>

#include "blockframe.h"
#include "blockwidget.h"
#include "inputprocessor.h"
#include "block.h"

// Delete block command for the QUndo Framework, allows undoing and redoing of
// unlimited actions
class DeleteBlockCommand : public QUndoCommand
{
public:
    DeleteBlockCommand(int index,
                       BlockFrame* frame,
                       InputProcessor* processor,
                       QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    BlockWidget* widget_;
    Block* block_;
    int index_;
    BlockFrame* frame_;
    InputProcessor* processor_;
};

#endif // DELETEBLOCKCOMMAND_H
