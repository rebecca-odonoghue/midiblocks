#include "applychangescommand.h"

ApplyChangesCommand::ApplyChangesCommand(int index,
                                         QStringList newParams,
                                         BlockFrame *frame,
                                         InputProcessor *processor,
                                         QUndoCommand *parent)
    : QUndoCommand(parent)
{
    index_ = index;
    frame_ = frame;
    processor_ = processor;
    newParams_ = newParams;
    oldParams_ = getOldParams();

    setText("Apply Changes");
}

void ApplyChangesCommand::undo() {
    changeParams(oldParams_);
}

void ApplyChangesCommand::redo() {
    changeParams(newParams_);
}

QStringList ApplyChangesCommand::getOldParams() {
    QStringList params;
    Block* block = processor_->getBlock(index_);
    BlockWidget* blockWidget = frame_->getBlock(index_);
    switch(blockWidget->getBlockType()) {
        case PITCH_SHIFT:
            params.append(QString::number(((PitchShift*)block)->getShift()));
            params.append(blockWidget->getParameter(1));
            break;
        case ARPEGGIATOR:
            params.append(QString::number(((Arpeggiator*)block)->getPattern()));
            params.append(blockWidget->getParameter(1));
            break;
        case GATE:
            params.append(QString::number(((Gate*)block)->getNotesPerTick()));
            params.append(QString::number(((Gate*)block)->getMode()));
            params.append(blockWidget->getParameter(1));
            params.append(blockWidget->getParameter(2));
            break;
        case MONOPHONIC:
        case CHORDIFY:
            break;
    }

    return params;
}

void ApplyChangesCommand::changeParams(QStringList params) {
    Block* block = processor_->getBlock(index_);
    BlockWidget* blockWidget = frame_->getBlock(index_);
    switch(blockWidget->getBlockType()) {
            case PITCH_SHIFT:
                ((PitchShift*)block)->setShift(params.at(0).toInt());
                blockWidget->setParameter(1, params.at(1));
                break;
            case ARPEGGIATOR:
                ((Arpeggiator*)block)->setPattern(
                        (ArpeggiatorPattern)params.at(0).toInt());
                blockWidget->setParameter(1, params.at(1));
                break;
            case GATE:
                ((Gate*)block)->setNotesPerTick(params.at(0).toDouble());
                ((Gate*)block)->setMode((GateMode)params.at(1).toInt());
                blockWidget->setParameter(1, params.at(2));
                blockWidget->setParameter(2, params.at(3));
                break;
            case MONOPHONIC:
            case CHORDIFY:
                return;
    }
}
