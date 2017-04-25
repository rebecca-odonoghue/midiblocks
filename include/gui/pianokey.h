#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <QLabel>
#include <QShortcut>
#include <QKeyEvent>
#include <QSizePolicy>

#include "note.h"
#include "scale.h"
#include "shortcuts.h"

// A GUI class representing each key on the virtual piano
class PianoKey : public QLabel
{
    Q_OBJECT

public:
    typedef enum {BLACK, WHITE} Colour;
    typedef enum {DISABLED, NORMAL, ACTIVE} State;
    PianoKey(QWidget *parent, Note note, int octave, int position);
    Note getNote();
    int getOctave();
    void setShortcut(Qt::Key);
    void draw();
    Qt::Key getShortcut();
    int getPosition();
    void keyOff();
    void keyOn();
    bool isBlack();
    PianoKey::State getState();

private:
    void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    Qt::Key shortcut_;
    Colour colour_;
    State state_;
    Note note_;
    QLabel* name_;
    int octave_;
    int position_;

signals:
    void keyPress(int);
    void keyRelease(int);

public slots:
    void disable();
    void enable();
};

#endif // PIANOKEY_H
