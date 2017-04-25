#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStringList>
#include <QStyleOption>
#include <QPainter>
#include <QDataStream>

#include "blocktypes.h"

// A GUI component that represents a block in the applications processing chain
class BlockWidget : public QWidget
{
    Q_OBJECT

public:
    BlockWidget(QWidget *parent, BlockType type, QStringList parameters);
    ~BlockWidget() {}
    BlockType getBlockType() const;
    void setSelected(bool);
    bool isSelected();
    int getKey();
    void setKey(int);
    void setParameter(int, QString);
    QString getParameter(int) const;



private:
    BlockType type_;
    QString param1Text_, param2Text_;
    QString param1Prefix_, param2Prefix_;
    QVBoxLayout* layout_;
    QLabel* name_;
    QLabel* param1_;
    QLabel* param2_;
    QPalette palette_;
    QString colour_;
    bool selected_;
    void select();
    void deselect();
    void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    int key;
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

signals:
    void clicked(int);

public slots:

};

#endif // BLOCKWIDGET_H
