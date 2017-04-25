#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QBuffer>
#include <QTimer>
#include <QObject>
#include <QBuffer>

#include "iotypes.h"
#include "abstractoutput.h"
#include "abstractinput.h"
#include "pianoinput.h"
#include "midifileinput.h"
#include "mididriverinput.h"

// The processing class that handles the current input and relays
// all input receieved to the processing chain
class InputHandler : public QObject
{
    Q_OBJECT

public:
    InputHandler(QObject *parent);
    void setInputType(InputType, QString);
    void start();
    void stop();
    AbstractInput* getHandle();
    QStringList getPortNames();
    void setAllowWrite(bool);

private:
    InputType inputType_;
    AbstractInput* handle_;
    bool isStopped_;
    bool allowWrite_;

public slots:
    void readMessage(int, int);

private slots:
    void endOfFile();

signals:
    void illegalWrite();
    void sendNote(int, int);
    void tempoChange(int);
    void startInputFailed();
    void fileFinished();

};

#endif // INPUTHANDLER_H
