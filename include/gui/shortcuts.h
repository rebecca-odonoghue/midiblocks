#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <QKeySequence>
#include <QString>
#include <QList>

// The keys corresponding to each PianoKey on the virtual piano
const static QList<Qt::Key> shortcutKeys = {Qt::Key_Q, Qt::Key_A, Qt::Key_W,
                                            Qt::Key_S, Qt::Key_E, Qt::Key_D,
                                            Qt::Key_R, Qt::Key_F, Qt::Key_T,
                                            Qt::Key_G, Qt::Key_Y, Qt::Key_H,
                                            Qt::Key_U, Qt::Key_J, Qt::Key_I,
                                            Qt::Key_K, Qt::Key_O, Qt::Key_L,
                                            Qt::Key_P};

// The letters that appear on each PianoKey representing it's shortcut
const static QList<QString> shortcutLetters = {"Q", "A", "W", "S", "E", "D",
                                               "R", "F", "T", "G", "Y", "H",
                                               "U", "J", "I", "K", "O", "L",
                                               "P"};

#endif // SHORTCUT_H
