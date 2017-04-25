#include "blockframe.h"

#include <QDebug>

BlockFrame::BlockFrame(QWidget *parent) : QWidget(parent)
{
    // Set up GUI components
    blocks_ = {};
    setAutoFillBackground(true);
    setPalette(QPalette(QPalette::Background, Qt::white));
    QHBoxLayout* containerLayout = new QHBoxLayout();

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    blockContainer_ = new QFrame(this);
    QHBoxLayout* blockLayout = new QHBoxLayout();
    blockContainer_->setLayout(blockLayout);

    containerLayout->addWidget(blockContainer_);
    containerLayout->addWidget(spacer);
    this->setLayout(containerLayout);
}

// Return the block widget at index
BlockWidget* BlockFrame::getBlock(int index) {
    return blocks_.at(index);
}

// Return the current number of blocks in the frame
int BlockFrame::blockCount() {
    return blocks_.size();
}

// Insert the provided block at the provided index
void BlockFrame::insertBlock(int index, BlockWidget* block) {
    blockContainer_->layout()->addWidget(block);
    block->setVisible(true);
    blocks_.insert(index, block);
    clearBlockContainer();
    updateBlockContainer();
}

// Add a block to the end of the chain
int BlockFrame::addBlock(BlockType type, QStringList args) {
    BlockWidget* block = new BlockWidget(blockContainer_, type, args);
    block->setKey(blocks_.size());
    connect(block, &BlockWidget::clicked, this, &BlockFrame::selectBlock);

    insertBlock(blocks_.size(), block);

    return blocks_.size() - 1;
}

// Select the block that has the provided key
void BlockFrame::selectBlock(int key) {
    bool isDeselect = false;
    int index = 0;
    volatile BlockType type;
    foreach(BlockWidget* block, blocks_) {
        if (block->getKey() == key ) {
            if(!block->isSelected()) {
                index = blocks_.indexOf(block);
                type = block->getBlockType();
                block->setSelected(true);
            } else {
                isDeselect = true;
                block->setSelected(false);
            }
        } else {
            block->setSelected(false);
        }
    }
    if(isDeselect) {
        emit blockDeselected();
    } else {
        emit blockSelected(index, type);
    }
}

// Deselect all blocks
void BlockFrame::deselectBlocks() {
    foreach(BlockWidget* block, blocks_) {
        block->setSelected(false);
    }
    emit blockDeselected();
}

// Remove all blocks
void BlockFrame::clearBlocks() {
    clearBlockContainer();
    foreach(BlockWidget* block, blocks_) {
      block->setVisible(false);
    }
    blocks_.clear();
}

// Delete the block at index
void BlockFrame::deleteBlock(int index) {
    BlockWidget* block = blocks_.at(index);
    clearBlockContainer();
    blocks_.removeAll(block);
    block->setVisible(false);
    updateBlockContainer();
    emit blockDeselected();
}

// Shift the block at index left
void BlockFrame::shiftBlockLeft(int index) {
    BlockWidget* block = blocks_.at(index);
    int newPos = index - 1;
    blocks_.removeAll(block);
    blocks_.insert(newPos, block);
    clearBlockContainer();
    updateBlockContainer();
}

// Shift the block at index right
void BlockFrame::shiftBlockRight(int index) {
    BlockWidget* block = blocks_.at(index);
    int newPos = index + 1;
    blocks_.removeAll(block);
    blocks_.insert(newPos, block);
    clearBlockContainer();
    updateBlockContainer();
}

// Remove all blocks from blockContainer_
void BlockFrame::clearBlockContainer() {
    foreach(BlockWidget* block, blocks_) {
        blockContainer_->layout()->removeWidget(block);
    }
}

// Add all blocks in blocks_ to blockContainer_
void BlockFrame::updateBlockContainer() {
    foreach(BlockWidget* block, blocks_) {
        blockContainer_->layout()->addWidget(block);
    }
}
