#include "losechanges.h"
#include "ui_losechanges.h"

LoseChanges::LoseChanges(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::LoseChanges)
{
    ui_->setupUi(this);
    setWindowTitle("Lose Changes");
    connect(ui_->buttonBox, &QDialogButtonBox::clicked, this,
            &LoseChanges::buttonClicked);
}

LoseChanges::~LoseChanges() {
    delete ui_;
}

void LoseChanges::buttonClicked(QAbstractButton* button) {
    QDialogButtonBox::ButtonRole role = ui_->buttonBox->buttonRole(button);
    if(role == QDialogButtonBox::DestructiveRole) {
        QDialog::done(2);
    }
}
