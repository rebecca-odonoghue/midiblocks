#include "metronome.h"

Metronome::Metronome(QWidget *parent) : QWidget(parent)
{
    drawMetronome();
    isMuted_ = true;
    timer_ = 0;

    highTick_.setSource(QUrl::fromLocalFile(":/metronome/High_tick.wav"));
    highTick_.setLoopCount(0);

    lowTick_.setSource(QUrl::fromLocalFile(":/metronome/Low_tick.wav"));
    lowTick_.setLoopCount(0);
}

void Metronome::start() {
    if(timer_ == 0) {
        timer_ = new QTimer(this);
        currentDotIndex_ = 0;
        timer_->start(500);
        connect(timer_, &QTimer::timeout, this, &Metronome::tick);
    }
}

void Metronome::stop() {
    if(timer_ == 0) return;
    timer_->stop();
    timer_ = 0;
    dots_.at(0)->setPixmap(QPixmap(":/metronome/metronome_special_inactive.png"));
    dots_.at(1)->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));
    dots_.at(2)->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));
    dots_.at(3)->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));
}

void Metronome::setMuted(bool muted) {
    this->isMuted_ = muted;
}

void Metronome::setTempo(int bpm) {
    double bps = bpm / 60.0;
    timer_->setInterval(1000 / bps);
}

void Metronome::tick() {
    switch(currentDotIndex_) {
        case 0:
            dots_.at(3)->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));
            dots_.at(0)->setPixmap(QPixmap(":/metronome/metronome_special_active.png"));
            if(!isMuted_) {
                //QSound::play(":/metronome/High_tick.wav");
                highTick_.play();
            }
            currentDotIndex_++;
            break;
        case 1:
            dots_.at(0)->setPixmap(QPixmap(":/metronome/metronome_special_inactive.png"));
            dots_.at(1)->setPixmap(QPixmap(":/metronome/metronome_active.png"));
            if(!isMuted_) {
                //QSound::play(":/metronome/Low_tick.wav");
                lowTick_.play();
            }
            currentDotIndex_++;
            break;
        case 2:
            dots_.at(1)->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));
            dots_.at(2)->setPixmap(QPixmap(":/metronome/metronome_active.png"));
            if(!isMuted_) {
                //QSound::play(":/metronome/Low_tick.wav");
                lowTick_.play();
            }
            currentDotIndex_++;
            break;
        case 3:
            dots_.at(2)->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));
            dots_.at(3)->setPixmap(QPixmap(":/metronome/metronome_active.png"));
            if(!isMuted_) {
                //QSound::play(":/metronome/Low_tick.wav");
                lowTick_.play();
            }
            currentDotIndex_ = 0;
            break;
    }
    emit onTick();
}

void Metronome::drawMetronome() {
    QLabel *dotOne, *dotTwo, *dotThree, *dotFour;
    QHBoxLayout* metronomeLayout = new QHBoxLayout(this);
    this->setGeometry(QRect(390, 60, 111, 38));
    metronomeLayout->setSpacing(5);
    metronomeLayout->setContentsMargins(2, 2, 6, 2);

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    dotOne = new QLabel(this);
    dotOne->setSizePolicy(sizePolicy);
    dotOne->setMinimumSize(QSize(20, 20));
    dotOne->setMaximumSize(QSize(20, 20));
    dotOne->setPixmap(QPixmap(":/metronome/metronome_special_inactive.png"));

    dots_.append(dotOne);
    metronomeLayout->addWidget(dotOne);

    dotTwo = new QLabel(this);
    dotTwo->setSizePolicy(sizePolicy);
    dotTwo->setMinimumSize(QSize(16, 16));
    dotTwo->setMaximumSize(QSize(16, 16));
    dotTwo->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));

    dots_.append(dotTwo);
    metronomeLayout->addWidget(dotTwo);

    dotThree = new QLabel(this);
    dotThree->setSizePolicy(sizePolicy);
    dotThree->setMinimumSize(QSize(16, 16));
    dotThree->setMaximumSize(QSize(16, 16));
    dotThree->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));

    dots_.append(dotThree);
    metronomeLayout->addWidget(dotThree);

    dotFour = new QLabel(this);
    dotFour->setSizePolicy(sizePolicy);
    dotFour->setMinimumSize(QSize(16, 16));
    dotFour->setMaximumSize(QSize(16, 16));
    dotFour->setPixmap(QPixmap(":/metronome/metronome_inactive.png"));

    dots_.append(dotFour);
    metronomeLayout->addWidget(dotFour);

}
