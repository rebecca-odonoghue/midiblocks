#ifndef BLOCKPANEL_H
#define BLOCKPANEL_H

#include <QWidget>
#include <QList>
#include <QFrame>

#include "blocktypes.h"
#include "blockwidget.h"

// A GUI component that contains and displays the visual representations of
// all processing blocks
class BlockFrame : public QWidget
{
    Q_OBJECT

public:
    explicit BlockFrame(QWidget *parent = 0);
    int addBlock(BlockType, QStringList);
    void insertBlock(int, BlockWidget*);
    void deselectBlocks();
    BlockWidget* getBlock(int);
    int blockCount();
    void clearBlocks();

private:
    QList<BlockWidget*> blocks_;
    QFrame* blockContainer_;
    void clearBlockContainer();
    void updateBlockContainer();

public slots:
    void deleteBlock(int);
    void shiftBlockLeft(int);
    void shiftBlockRight(int);
    void selectBlock(int);

signals:
    void blockSelected(int, BlockType);
    void blockDeselected();
};

#endif // BLOCKCONTAINER_H
