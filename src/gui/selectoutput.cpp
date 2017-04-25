#include "selectoutput.h"

SelectOutput::SelectOutput(QWidget *parent, QStringList comPortNames,
                           QStringList midiPortNames) :
    QDialog(parent),
    ui_(new Ui::SelectOutput)
{
    ui_->setupUi(this);
    ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui_->midiPortSelect->addItems(midiPortNames);
    ui_->comPortSelect->addItems(comPortNames);
}

SelectOutput::~SelectOutput()
{
    delete ui_;
}

void SelectOutput::accept() {
    if(ui_->midiFileButton->isChecked()) {
        emit outputSelected(MIDI_FILE_OUT, ui_->fileSelect->text());
    } else if (ui_->USBButton->isChecked()) {
        emit outputSelected(USB, ui_->comPortSelect->currentText());
    } else {
        emit outputSelected(MIDI_DRIVER_OUT, QString::number(
                                ui_->midiPortSelect->currentIndex() - 1));
    }
    QDialog::accept();
}

void SelectOutput::checkValid() {
    if(ui_->midiFileButton->isChecked()) {
        if(ui_->fileSelect->text().size() > 0) {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        } else {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    } else if (ui_->midiDriverButton->isChecked()) {
        if(ui_->midiPortSelect->currentIndex() > 0) {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        } else {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    } else if (ui_->USBButton->isChecked()) {
        if(ui_->comPortSelect->currentIndex() > 0) {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        } else {
            ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    }
}

void SelectOutput::browse() {
    QFileDialog dialog(this);
    QString homeDir = QStandardPaths::writableLocation(
                QStandardPaths::DocumentsLocation);
    QString fileName = dialog.getSaveFileName(this,
                                              tr("Specify MIDI Output File"),
                                              homeDir + "/Output.mid",
                                              tr("MIDI Type 0 Files (*.mid)"));
    if(!fileName.isNull()) {
        ui_->fileSelect->setText(fileName);
    }
}
