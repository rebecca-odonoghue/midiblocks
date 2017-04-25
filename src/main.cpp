#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication midiBlocks(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("MIDIBlocks Studio");
    mainWindow.show();
    return midiBlocks.exec();
}
