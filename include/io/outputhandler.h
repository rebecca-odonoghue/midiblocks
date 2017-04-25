#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <windows.h>

#include <QBuffer>
#include <QObject>
#include <QLocalSocket>
#include <QStringList>
#include <QSerialPortInfo>

#include "iotypes.h"
#include "abstractoutput.h"
#include "serialoutput.h"
#include "midifileoutput.h"
#include "mididriveroutput.h"

// The processing class that receives messages from the processing chain
// and relays them to the current output
class OutputHandler : public QObject
{
    Q_OBJECT

public:
    OutputHandler(QObject *parent);
    void setOutputType(OutputType, QString);
    QStringList getMidiPortNames();
    QStringList getComPortNames();
    void start();
    void stop();
    void sendConfigInfo(QList<int>);

private:
    OutputType outputType_;
    AbstractOutput* handle_;
    QList<int> notesOn_;

public slots:
    void receiveNote(int, int);
    void clear();
};

#endif // OUTPUTHANDLER_H
