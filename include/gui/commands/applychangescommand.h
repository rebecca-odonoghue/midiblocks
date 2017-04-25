#ifndef APPLYCHANGESCOMMAND_H
#define APPLYCHANGESCOMMAND_H

#include <QUndoCommand>

#include "inputprocessor.h"
#include "blockframe.h"

// Apply changes command for the QUndo Framework, allows undoing and redoing of
// unlimited actions, refers to changes applied to block parameters
class ApplyChangesCommand : public QUndoCommand
{
public:
    ApplyChangesCommand(int index,
                        QStringList newParams,
                        BlockFrame* frame,
                        InputProcessor* processor,
                        QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    int index_;
    QStringList oldParams_, newParams_;
    BlockFrame* frame_;
    InputProcessor* processor_;
    QStringList getOldParams();
    void changeParams(QStringList);
};

#endif // APPLYCHANGESCOMMAND_H
