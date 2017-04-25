#ifndef SELECTINPUT_H
#define SELECTINPUT_H

#include <QDialog>
#include <QFileDialog>
#include <QStandardPaths>

#include "iotypes.h"
#include "ui_selectinput.h"

// A dialog that shows the MIDI input options available to the user
namespace Ui {
class SelectInput;
}

class SelectInput : public QDialog
{
    Q_OBJECT

public:
    SelectInput(QWidget* parent, QStringList portNames);
    ~SelectInput();

private:
    Ui::SelectInput* ui_;
    InputType input_;
    QString args_;

private slots:
    void accept();
    void checkValid();
    void browse();

signals:
    void inputSelected(InputType, QString);
};

#endif // SELECTINPUT_H
