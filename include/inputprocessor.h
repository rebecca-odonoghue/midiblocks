#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <QThread>
#include <QIODevice>
#include <QObject>
#include <QList>

#include "iotypes.h"
#include "inputhandler.h"
#include "outputhandler.h"
#include "block.h"
#include "blocktypes.h"
#include "arpeggiator.h"
#include "chordify.h"
#include "gate.h"
#include "monophonic.h"
#include "pitchshift.h"

// InputProcessor defines and regulates the processing thread, managing all
// processing blocks, inputs and outputs.
class InputProcessor : public QThread
{
    Q_OBJECT

public:
    explicit InputProcessor(QObject *parent = 0);
    AbstractInput* getInput();
    QString getInputArg();
    QStringList getInputPortNames();
    QStringList getOutputMidiPortNames();
    QStringList getOutputComPortNames();
    Block* getBlock(int);
    int numBlocks();
    void addBlock(BlockType, QStringList);
    void insertBlock(int, Block*);
    void shiftBlockLeft(int);
    void shiftBlockRight(int);
    void deleteBlock(int);
    void setScale(const Scale*);
    void newProject();

private:
    OutputHandler* outputHandler_;
    InputHandler* inputHandler_;
    InputType inputType_;
    QString inputArg_;
    OutputType outputType_;
    QList<Block*> blocks_;
    Scale* scale_;
    QList<int> configInfo_;
    void connectChain();

public slots:
    void changeOutput(OutputType, QString);
    void changeInput(InputType, QString);
    void setConfigInfo(QList<int>);
    void startInput();
    void stopInput();
    void startOutput();
    void stopOutput();
    void onTick();

private slots:
    void catchIllegalWrite();
    void changeTempo(int);
    void endOfFile();

signals:
    void startMetronome();
    void stopMetronome();
    void illegalWrite();
    void inputChanged(InputType);
    void tempoChanged(int);
    void fileFinished();
};

#endif // INPUTPROCESSOR_H
