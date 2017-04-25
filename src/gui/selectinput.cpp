#include "selectinput.h"

SelectInput::SelectInput(QWidget *parent, QStringList portNames) :
    QDialog(parent),
    ui_(new Ui::SelectInput)
{
    ui_->setupUi(this);

    ui_->portSelect->addItems(portNames);
}

SelectInput::~SelectInput()
{
    delete ui_;
}

void SelectInput::accept() {
    if(ui_->midiFileButton->isChecked()) {
        emit inputSelected(MIDI_FILE_IN, ui_->fileSelect->text());
    } else if (ui_->midiDriverButton->isChecked()){
        emit inputSelected(MIDI_DRIVER_IN, QString::number(
                               ui_->portSelect->currentIndex() - 1));
    } else {
        emit inputSelected(PIANO, "");
    }
    QDialog::accept();
}

void SelectInput::checkValid() {
    if(ui_->midiFileButton->isChecked()) {
        if(ui_->fileSelect->text().size() > 0) {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
        else {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    }
    else if (ui_->midiDriverButton->isChecked()) {
        if(ui_->portSelect->currentIndex() > 0) {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
        else {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    }
    else {
        ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void SelectInput::browse() {
    QFileDialog dialog(this);
    QString homeDir = QStandardPaths::writableLocation(
                QStandardPaths::DocumentsLocation);
    QString fileName = dialog.getOpenFileName(this,
                                              tr("Select MIDI Input File"),
                                              homeDir,
                                              tr("MIDI Type 0 Files (*.mid)"));
    if(!fileName.isNull()) {
        ui_->fileSelect->setText(fileName);
    }
}
