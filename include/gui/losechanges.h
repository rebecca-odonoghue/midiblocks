#ifndef LOSECHANGES_H
#define LOSECHANGES_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>

// A dialog displayed when there are unsaved changes existing in the project
// that will be lost if the user continues
namespace Ui {
class LoseChanges;
}

class LoseChanges : public QDialog
{
    Q_OBJECT

public:
    explicit LoseChanges(QWidget *parent = 0);
    ~LoseChanges();

private:
    Ui::LoseChanges* ui_;

private slots:
    void buttonClicked(QAbstractButton*);
};

#endif // LOSECHANGES_H
