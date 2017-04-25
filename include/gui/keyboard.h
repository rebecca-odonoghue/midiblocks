#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QSizePolicy>
#include <QRect>
#include <QPixmap>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QShortcut>

#include "pianokey.h"
#include "shortcuts.h"
#include "note.h"
#include "scale.h"
#include "pianoinput.h"

// A GUI component that holds the piano display and sends note messages to it's
// instance of PianoInput class
class Keyboard : public QWidget
{
    Q_OBJECT

public:
    Keyboard(QWidget *parent = 0, const Scale* scale = 0);
    void addPianoInput(PianoInput*);
    QList<PianoKey*> getDisplayedKeys();
    void setScale(const Scale*);
    Scale *getScale();
    QList<PianoKey*> getAllKeys();
    QList<int> getConfigNotes();

private:
    PianoInput* pianoInput_;
    QPushButton *shiftLeftButton_, *shiftRightButton_,
            *shiftLeftOctButton_, *shiftRightOctButton_;
    QFrame *keyboardFrame_;
    Scale *scale_;
    QList<PianoKey*> keys_;
    QList<PianoKey*> currentKeys_;
    QList<PianoKey*> displayedKeys_;
    QList<QShortcut*> shortcuts_;
    QList<QLabel*> labels_;
    QList<QLabel*> dots_;
    int currentIndex_;
    QList<int> configNotes_;
    int lowestRoot_;
    bool foundLowestRoot_;
    bool lowestRootChanged_;
    void drawPanel();
    void connectSlots();
    void generateKeys();
    void addLabels();
    void updateKeys();
    void updateBoard();

signals:
    void sendConfigInfo(QList<int>);

public slots:
    void activate();
    void deactivate();
    void shiftLeft();
    void shiftRight();
    void shiftLeftOctave();
    void shiftRightOctave();
};

#endif // KEYBOARD_H
