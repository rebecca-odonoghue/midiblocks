#include "pianokey.h"
#include <QDebug>

PianoKey::PianoKey(QWidget *parent, Note note, int octave, int position) : QLabel(parent)
{ 
    note_ = note;
    octave_ = octave;
    position_ = position;

    name_ = new QLabel(this);
    QSizePolicy fixedSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QString text;
    if(noteLetters.at(note).size() == 1) {
        text = noteLetters.at(note) + QString::number(octave);
        name_->setGeometry(QRect(10, 10, 25, 10));
    } else {
        QStringList names = noteLetters.at(note).split("/");
        text = names.at(0) + QString::number(octave) + "\n" + names.at(1)
                + QString::number(octave);
        name_->setGeometry(QRect(5, 10, 25, 24));
    }

    name_->setText(text);
    name_->setSizePolicy(fixedSizePolicy);

    if(isBlack()) {
        name_->setStyleSheet("QLabel { color: white; font: 9pt; }");
    } else {
        name_->setStyleSheet("QLabel { color: #3f3f3f; font: 9pt; }");
    }

    if (isBlack())
        colour_ = BLACK;
    else
        colour_ = WHITE;
    state_ = NORMAL;

    draw();
}

Note PianoKey::getNote() {
    return note_;
}

int PianoKey::getOctave() {
    return octave_;
}

int PianoKey::getPosition() {
    return position_;
}

PianoKey::State PianoKey::getState() {
    return state_;
}

void PianoKey::setShortcut(Qt::Key shortcut) {
    shortcut_ = shortcut;
}

Qt::Key PianoKey::getShortcut() {
    return shortcut_;
}

bool PianoKey::isBlack() {
    return note_ == Ab
            || note_ == Bb
            || note_ == Db
            || note_ == Eb
            || note_ == Gb;
}

void PianoKey::mousePressEvent(QMouseEvent* /*ev*/) {
    keyOn();
}

void PianoKey::mouseReleaseEvent(QMouseEvent* /*ev*/) {
    keyOff();
}

void PianoKey::draw() {
    if(colour_ == WHITE)
        setPixmap(QPixmap(":/keyboard/white_key.jpg"));
    else
        setPixmap(QPixmap(":/keyboard/black_key.jpg"));
}

void PianoKey::keyOff() {
    if(state_ == DISABLED)
        return;
    if(colour_ == WHITE) {
        setPixmap(QPixmap(":/keyboard/white_key.jpg"));
    } else {
        setPixmap(QPixmap(":/keyboard/black_key.jpg"));
    }
    state_ = NORMAL;
    emit keyRelease(position_);
}

void PianoKey::keyOn() {
    if(state_ == DISABLED)
        return;
    if(colour_ == WHITE) {
        setPixmap(QPixmap(":/keyboard/white_key_active.jpg"));
    } else {
        setPixmap(QPixmap(":/keyboard/black_key_active.jpg"));
    }
    state_ = ACTIVE;
    emit keyPress(position_);
}

void PianoKey::disable() {
    if(colour_ == WHITE) {
        setPixmap(QPixmap(":/keyboard/white_key_disabled.jpg"));
    } else {
        setPixmap(QPixmap(":/keyboard/black_key_disabled.jpg"));
    }
    name_->hide();
    state_ = DISABLED;
}

void PianoKey::enable() {
    if(colour_ == WHITE) {
        setPixmap(QPixmap(":/keyboard/white_key.jpg"));
    } else {
        setPixmap(QPixmap(":/keyboard/black_key.jpg"));
    }
    name_->show();
    state_ = NORMAL;
}
