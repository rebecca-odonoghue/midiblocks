#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include <mmsystem.h>

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QStandardPaths>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QKeyEvent>
#include <QComboBox>
#include <QUndoStack>
#include <QDataStream>
#include <QPushButton>
#include <QSpinBox>
#include <QSplitter>

#include "keyboard.h"
#include "metronome.h"
#include "shortcuts.h"
#include "blockframe.h"
#include "inputprocessor.h"
#include "iotypes.h"
#include "inputhandler.h"
#include "outputhandler.h"
#include "selectoutput.h"
#include "selectinput.h"
#include "losechanges.h"
#include "addblockcommand.h"
#include "deleteblockcommand.h"
#include "shiftblockcommand.h"
#include "applychangescommand.h"
#include "changeinputcommand.h"
#include "ui_mainwindow.h"
#include "ui_about.h"
#include "blockdata.h"
#include "inputdata.h"

// The main window of the application, instantiates all other classes and
// manages connections between the GUI and processing threads
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newProj();
    void loadProj();
    void saveProj();
    void saveProjAs();
    void enableSave(bool);
    void about();
    void addBlock();
    void deleteBlock();
    void shiftBlockLeft();
    void shiftBlockRight();
    void changeScale();
    void importScales();
    void selectOutput();
    void selectInput();
    void changeInput(InputType, QString);
    void changeOutput(OutputType);
    void inputChanged(InputType);
    void play();
    void stop();
    void record();
    void toggleMute();
    void catchIllegalWrite();
    void selectBlockType(int);
    void blockDeselected();
    void blockSelected(int, BlockType);
    void applyChanges();

private:
    Ui::MainWindow* ui_;
    QString saveFileName_;
    Metronome* metronome_;
    Keyboard* keyboard_;
    BlockFrame* blockFrame_;
    QList<Scale> scales_ = {};
    int currentScaleIndex_;
    QComboBox* scaleRootSelect_;
    QComboBox* scaleModeSelect_;
    QSpinBox* tempoSelect_;
    InputType inputType_;
    QString inputArg_;
    OutputType outputType_;
    QComboBox* addBlockSelect_;
    InputProcessor* inputProcessor_;
    QUndoStack* undoStack_;
    QAction* actionMute_;
    QAction* actionUndo_;
    QAction* actionRedo_;
    QLabel* inputLabel_;
    QLabel* outputLabel_;
    QAction* editShiftAction_, *editPatternAction_, *editGateAction_;
    QAction* editBlockAction_;
    QSpinBox* shiftSelect_;
    QComboBox* patternSelect_, *modeSelect_;
    QDoubleSpinBox* nptSelect_;
    int selectedBlockIndex_;
    double tempo_;
    bool isMuted_;
    void keyPressEvent(QKeyEvent*) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent*) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;
    int loseChanges();
    void cleanProject();
    void writeProjectFile(QString);
    void readProjectFile(QString);
    void loadScales(QString);
    int currentScale();
    void generateMainToolbar();
    void generateIoToolbar();
    void activateButtons();
    void addMetronome();
    void generateBlockToolbar();
    void showBlockParameters(bool, BlockType);
    void hideBlockParameters();
    void checkShiftButtons();
};

#endif // MAINWINDOW_H
