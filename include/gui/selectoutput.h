#ifndef SELECTOUTPUT_H
#define SELECTOUTPUT_H

#include <QDialog>
#include <QFileDialog>
#include <QStandardPaths>

#include "iotypes.h"
#include "ui_selectoutput.h"

// A dialog that shows the MIDI output options available to the user
namespace Ui {
class SelectOutput;
}

class SelectOutput : public QDialog
{
    Q_OBJECT

public:
    SelectOutput(QWidget* parent, QStringList comPortNames,
                 QStringList midiPortNames);
    ~SelectOutput();

private:
    Ui::SelectOutput* ui_;
    OutputType output_;
    QString args_;

private slots:
    void accept();
    void checkValid();
    void browse();

signals:
    outputSelected(OutputType, QString);
};

#endif // SELECTOUTPUT_H
