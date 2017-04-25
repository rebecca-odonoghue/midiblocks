#include "blockwidget.h"

BlockWidget::BlockWidget(QWidget *parent, BlockType type,
                         QStringList parameters) : QWidget(parent)
{
    type_ = type;

    setFixedSize(125, 125);
    setAutoFillBackground(true);
    selected_ = false;

    layout_ = new QVBoxLayout();
    layout_->setContentsMargins(10, 10, 10, 10);

    name_ = new QLabel();
    param1_ = new QLabel();
    param2_ = new QLabel();
    name_->setStyleSheet("QLabel {font-size: 12px; font-weight: bold; "
                         "color: 3f3f3f;}");
    param1_->setWordWrap(true);
    param2_->setWordWrap(true);
    param1_->setText("");
    param2_->setText("");
    param1Text_ = "";
    param2Text_ = "";

    switch(type) {
        case PITCH_SHIFT:
            name_->setText("Pitch Shift");
            param1Prefix_ = "Shift: ";
            param1Text_ = parameters.at(0);
            param1_->setText(param1Prefix_ + param1Text_);
            colour_ = "#ffffa3";
            break;
        case ARPEGGIATOR:
            name_->setText("Arpeggiator");
            param1Prefix_ = "Pattern: ";
            param1Text_ = parameters.at(0);
            param1_->setText(param1Prefix_ + param1Text_);
            colour_ = "#cc99ff";
            break;
        case MONOPHONIC:
            name_->setText("Monophonic");
            colour_ = "#ffb2b2";
            break;
        case CHORDIFY:
            name_->setText("Chordify");
            colour_ = "#b8ff70";
            break;
        case GATE:
            name_->setText("Gate");
            param1Prefix_ = "Notes per tick: ";
            param2Prefix_ = "Mode: ";
            param1Text_ = parameters.at(0);
            param2Text_ = parameters.at(1);
            param1_->setText(param1Prefix_ + param1Text_);
            param2_->setText(param2Prefix_ + param2Text_);
            colour_ = "#a3daff";
            break;
    }

    this->setStyleSheet("BlockWidget{background-color: " + colour_ + ";}");

    layout_->addWidget(name_);
    layout_->addWidget(param1_);
    layout_->addWidget(param2_);

    this->setLayout(layout_);
}

BlockType BlockWidget::getBlockType() const {
    return type_;
}

bool BlockWidget::isSelected() {
    return selected_;
}

int BlockWidget::getKey() {
    return key;
}

void BlockWidget::setKey(int key) {
    this->key = key;
}

void BlockWidget::mousePressEvent(QMouseEvent* /*ev*/) {
    emit clicked(key);
}

void BlockWidget::setSelected(bool selected) {
    if(selected) {
        select();
    } else {
        deselect();
    }
}

void BlockWidget::setParameter(int index, QString text) {
    switch(index) {
        case 1:
            param1Text_ = text;
            param1_->setText(param1Prefix_ + param1Text_);
            break;
        case 2:
            param2Text_ = text;
            param2_->setText(param2Prefix_ + param2Text_);
    }
}

QString BlockWidget::getParameter(int index) const {
    switch(index) {
        case 1:
            return param1Text_;
        case 2:
            return param2Text_;
    }
    return "";
}

void BlockWidget::select() {
    this->setStyleSheet("BlockWidget{background-color: " +
                        colour_ + "; border: 2px solid #737373;}");
    selected_ = true;
}

void BlockWidget::deselect() {
    this->setStyleSheet("BlockWidget{background-color: " + colour_ + ";}");
    selected_ = false;
}

void BlockWidget::paintEvent(QPaintEvent */*pe*/) {
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
