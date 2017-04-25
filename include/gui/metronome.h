#ifndef METRONOME_H
#define METRONOME_H

#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QSound>
#include <QSoundEffect>

// A GUI component that keeps track of and displays each beat defined by the
// global tempo
class Metronome : public QWidget
{
    Q_OBJECT

public:
    explicit Metronome(QWidget *parent = 0);
    void setMuted(bool);

private:
    QList<QLabel*> dots_;
    int currentDotIndex_;
    bool isMuted_;
    QSoundEffect highTick_, lowTick_;
    QTimer* timer_;
    void drawMetronome();

signals:
    void onTick();

public slots:
    void tick();
    void start();
    void stop();
    void setTempo(int);
};

#endif // METRONOME_H
