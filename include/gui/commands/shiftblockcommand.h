#ifndef SHIFTBLOCKCOMMAND_H
#define SHIFTBLOCKCOMMAND_H

#include <QUndoCommand>

#include "blockframe.h"
#include "inputprocessor.h"

// Shift block command for the QUndo Framework, allows undoing and redoing of
// unlimited actions
class ShiftBlockCommand : public QUndoCommand
{
public:
    ShiftBlockCommand(int index,
                      bool left,
                      BlockFrame *frame,
                      InputProcessor* processor,
                      QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    int oldPos_, newPos_;
    bool isLeft_;
    BlockFrame* frame_;
    InputProcessor* processor_;
};

#endif // SHIFTBLOCKCOMMAND_H
