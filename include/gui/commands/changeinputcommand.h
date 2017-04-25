#ifndef CHANGEINPUTCOMMAND_H
#define CHANGEINPUTCOMMAND_H

#include <QUndoCommand>
#include <QString>

#include "iotypes.h"
#include "inputprocessor.h"

// Change Input command for the QUndo Framework, allows undoing and redoing of
// unlimited actions
class ChangeInputCommand : public QUndoCommand
{
public:
    ChangeInputCommand(InputType oldInput,
                       InputType newInput,
                       QString newArg,
                       InputProcessor *processor,
                       QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    InputType oldInput_, newInput_;
    InputProcessor* processor_;
    QString oldArg_, newArg_;
};

#endif // CHANGEINPUTCOMMAND_H
