#include "keyboard.h"
#include <QDebug>

Keyboard::Keyboard(QWidget *parent, const Scale *scale) : QWidget(parent)
{
    scale_ = (Scale*)malloc(sizeof(Scale));
    memcpy(scale_, scale, sizeof(Scale));
    currentIndex_ = scale_->size() * 3;
    lowestRoot_ = 84;

    // Generate the GUI
    drawPanel();
    generateKeys();
    addLabels();
    updateKeys();
    updateBoard();
    connectSlots();
}


void Keyboard::setScale(const Scale* scale) {
    memcpy(scale_, scale, sizeof(Scale));
    currentIndex_ = scale_->size() * 3;
    // Update the board to display the new scale
    updateKeys();
    updateBoard();
}

// Returns the current scale
Scale* Keyboard::getScale() {
    return scale_;
}

// Returns the lowest root note and the 7 consecutive notes above
QList<int> Keyboard::getConfigNotes() {
    return configNotes_;
}

// Connects each piano key to the input of the processing chain
void Keyboard::addPianoInput(PianoInput *pianoInput) {
    pianoInput_ = pianoInput;

    foreach(PianoKey* key, keys_) {
        if(key->getOctave() > 0 && key->getOctave() < 8) {
            connect(key, &PianoKey::keyPress, pianoInput_, &PianoInput::noteOn);
            connect(key, &PianoKey::keyRelease, pianoInput_, &PianoInput::noteOff);
        }
    }
}

// Draw the keyboard panel
void Keyboard::drawPanel() {
    QHBoxLayout* panelLayout = new QHBoxLayout(this);
    panelLayout->setSpacing(0);
    panelLayout->setContentsMargins(2, 2, 2, 2);

    shiftLeftOctButton_ = new QPushButton(this);
    QSizePolicy buttonSizePolicy(QSizePolicy::MinimumExpanding,
                                 QSizePolicy::MinimumExpanding);
    shiftLeftOctButton_->setSizePolicy(buttonSizePolicy);
    QIcon leftOctIcon;
    leftOctIcon.addFile(QStringLiteral(":/icons/double_arrow_left.png"),
                        QSize(), QIcon::Normal, QIcon::Off);
    shiftLeftOctButton_->setIcon(leftOctIcon);

    panelLayout->addWidget(shiftLeftOctButton_);

    shiftLeftButton_ = new QPushButton(this);
    shiftLeftButton_->setSizePolicy(buttonSizePolicy);
    QIcon leftIcon;
    leftIcon.addFile(QStringLiteral(":/icons/arrow_left.png"), QSize(),
                     QIcon::Normal, QIcon::Off);
    shiftLeftButton_->setIcon(leftIcon);

    panelLayout->addWidget(shiftLeftButton_);

    keyboardFrame_ = new QFrame(this);
    QSizePolicy fixedSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    keyboardFrame_->setGeometry(QRect(50, 5, 627, 201));
    keyboardFrame_->setSizePolicy(fixedSizePolicy);
    keyboardFrame_->setMinimumSize(QSize(627, 201));
    keyboardFrame_->setMaximumSize(QSize(627, 201));

    QLabel* pianoBorder = new QLabel(keyboardFrame_);
    pianoBorder->setSizePolicy(fixedSizePolicy);
    pianoBorder->setGeometry(QRect(0, 0, 627, 1));
    pianoBorder->setMinimumSize(QSize(627, 1));
    pianoBorder->setMaximumSize(QSize(627, 1));
    pianoBorder->setPixmap(QPixmap(":/keyboard/piano_border.jpg"));

    panelLayout->addWidget(keyboardFrame_);

    shiftRightButton_ = new QPushButton(this);
    shiftRightButton_->setSizePolicy(buttonSizePolicy);
    QIcon rightIcon;
    rightIcon.addFile(QStringLiteral(":/icons/arrow_right.png"), QSize(),
                      QIcon::Normal, QIcon::Off);
    shiftRightButton_->setIcon(rightIcon);

    panelLayout->addWidget(shiftRightButton_);

    shiftRightOctButton_ = new QPushButton(this);
    shiftRightOctButton_->setSizePolicy(buttonSizePolicy);
    QIcon rightOctIcon;
    rightOctIcon.addFile(QStringLiteral(":/icons/double_arrow_right.png"),
                         QSize(), QIcon::Normal, QIcon::Off);
    shiftRightOctButton_->setIcon(rightOctIcon);

    panelLayout->addWidget(shiftRightOctButton_);
    this->setLayout(panelLayout);
}

// Generate all keys C1 - B7 plus one octave above and one below that will
// be disabled
void Keyboard::generateKeys() {
    int position = 1;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 12; j++) {
            PianoKey* key;
            if(i == 0 || i == 8) {
                key = new PianoKey(keyboardFrame_, (Note)j, i, 0);
                key->disable();
            } else {
                key = new PianoKey(keyboardFrame_, (Note)j, i, position);
                position++;
            }
            keys_.append(key);
        }
    }  
}

// Update the keys that are in the current scale
void Keyboard::updateKeys() {
    lowestRoot_ = 84;
    currentKeys_.clear();
    foreach(PianoKey* key, keys_) {
        if(key->getState() == PianoKey::ACTIVE) {
            key->keyOff();
        }
        if(scale_->contains(key->getNote())) {
            currentKeys_.append(key);
        }
    }
}

// Add the labels to the piano
void Keyboard::addLabels() {
    QSizePolicy fixedSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    int count = 0;
    foreach(QString letter, shortcutLetters) {
        QLabel* label = new QLabel(keyboardFrame_);
        label->setText(letter);
        label->setGeometry(QRect(33*count + 10, 170, 20, 20));
        label->setSizePolicy(fixedSizePolicy);
        label->setMinimumSize(QSize(20, 20));
        label->setMaximumSize(QSize(20, 20));
        labels_.append(label);
        label->hide();

        QLabel* rootDot = new QLabel(keyboardFrame_);
        rootDot->setGeometry(QRect(33*count + 14, 50, 6, 6));
        rootDot->setSizePolicy(fixedSizePolicy);
        rootDot->setMinimumSize(QSize(6, 6));
        rootDot->setMaximumSize(QSize(6, 6));
        dots_.append(rootDot);
        rootDot->hide();

        count++;
    }
}

// Connect the shift buttons to keyboard shifts
void Keyboard::connectSlots() {
    connect(shiftLeftButton_, SIGNAL(clicked()), this, SLOT(shiftLeft()));

    connect(new QShortcut(Qt::Key_Left, this), SIGNAL(activated()),
            this, SLOT(shiftLeft()));

    connect(shiftLeftOctButton_, SIGNAL(clicked()),
            this, SLOT(shiftLeftOctave()));

    connect(new QShortcut(Qt::Key_PageDown, this), SIGNAL(activated()), this,
            SLOT(shiftLeftOctave()));

    connect(shiftRightButton_, SIGNAL(clicked()), this, SLOT(shiftRight()));

    connect(new QShortcut(Qt::Key_Right, this), SIGNAL(activated()), this,
            SLOT(shiftRight()));

    connect(shiftRightOctButton_, SIGNAL(clicked()), this,
            SLOT(shiftRightOctave()));

    connect(new QShortcut(Qt::Key_PageUp, this), SIGNAL(activated()), this,
            SLOT(shiftRightOctave()));
}

// Update the keys that are displayed in the GUI
void Keyboard::updateBoard() {
    foundLowestRoot_ = false;
    lowestRootChanged_ = false;

    foreach(PianoKey* key, keys_) {
        key->hide();
    }
    displayedKeys_.clear();

    int count = 0;
    for(int i = currentIndex_; i < currentKeys_.size() && count < 19;
            i++, count++) {

        PianoKey* key = currentKeys_.at(i);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        key->setGeometry(QRect(33*count, 1, 33, 200));
        key->setSizePolicy(sizePolicy);
        key->setMinimumSize(QSize(33, 200));
        key->setMaximumSize(QSize(33, 200));
        key->setShortcut(shortcutKeys.at(count));

        if(foundLowestRoot_ && configNotes_.size() < 8
                && key->getPosition() != 0) {
            configNotes_.append(key->getPosition());
        }

        if(key->isBlack()) {
            labels_.at(count)->setStyleSheet("QLabel { color: white; "
                                           "font: 12pt; font-weight: bold; }");
            dots_.at(count)->setPixmap(QPixmap(":/keyboard/white_root.png"));
        } else {
            labels_.at(count)->setStyleSheet("QLabel { color: #3f3f3f; "
                                           "font: 12pt; font-weight: bold; }");
            dots_.at(count)->setPixmap(QPixmap(":/keyboard/black_root.png"));
        }
        key->show();
        if (key->getState() != PianoKey::DISABLED) {
            labels_.at(count)->show();
        } else {
            labels_.at(count)->hide();
        }

        if(key->getNote() == scale_->getRoot()
                && key->getState() != PianoKey::DISABLED) {
            dots_.at(count)->show();
            if (!foundLowestRoot_) {
                if(key->getPosition() != lowestRoot_) {
                    lowestRootChanged_ = true;
                }
                lowestRoot_ = key->getPosition();
                configNotes_.clear();
                configNotes_.append(lowestRoot_);
                foundLowestRoot_ = true;
            }
        } else {
            dots_.at(count)->hide();
        }
        displayedKeys_.append(key);
    }
    if(lowestRootChanged_) {
        emit sendConfigInfo(configNotes_);
    }
}

// Return a list containing the currently displayed keys
QList<PianoKey*> Keyboard::getDisplayedKeys() {
    return displayedKeys_;
}

// Return a list containing all keys
QList<PianoKey*> Keyboard::getAllKeys() {
    return keys_;
}

// Activate the keyboard
void Keyboard::activate() {

    foreach(PianoKey* key, keys_) {
        if(key->getOctave() > 0 && key->getOctave() < 8) {
            key->enable();
        }
    }

    updateBoard();

    shiftLeftButton_->setEnabled(true);
    shiftLeftOctButton_->setEnabled(true);
    shiftRightButton_->setEnabled(true);
    shiftRightOctButton_->setEnabled(true);
}

// Deactivate the keyboard
void Keyboard::deactivate() {
    foreach(PianoKey* key, keys_) {
        key->disable();
    }

    foreach(QLabel* label, labels_) {
        label->hide();
    }

    foreach(QLabel* dot, dots_) {
        dot->hide();
    }

    shiftLeftButton_->setEnabled(false);
    shiftLeftOctButton_->setEnabled(false);
    shiftRightButton_->setEnabled(false);
    shiftRightOctButton_->setEnabled(false);
}

// Shift left by one
void Keyboard::shiftLeft() {
    if(currentIndex_ > scale_->size()) {
        currentIndex_--;
        updateBoard();
    }
}

// Shift right by one
void Keyboard::shiftRight() {
    if(currentIndex_ < currentKeys_.size() - scale_->size() - 19) {
        currentIndex_++;
        updateBoard();
    }
}

// Shift left by an octave
void Keyboard::shiftLeftOctave() {
    if(currentIndex_ > scale_->size()) {
        currentIndex_ -= scale_->size();
        updateBoard();
    }
}

// Shift right by an octave
void Keyboard::shiftRightOctave() {
    if(currentIndex_ < (currentKeys_.size() - scale_->size() - 19)) {
        currentIndex_ += scale_->size();
        updateBoard();
    }
}
