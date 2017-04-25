#-------------------------------------------------
#
# Project created by QtCreator 2015-08-23T14:37:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia serialport

QMAKE_CXXFLAGS += -std=c++0x

TARGET = MIDIBlocks
DESTDIR = bin/
TEMPLATE = app

DEFINES += __WINDOWS_MM__

LIBS += -lwinmm

SOURCES += \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/gui/pianokey.cpp \
    src/gui/keyboard.cpp \
    src/gui/metronome.cpp \
    src/scale.cpp \
    src/gui/blockframe.cpp \
    src/io/inputhandler.cpp \
    src/io/outputhandler.cpp \
    Midifile/src-library/Binasc.cpp \
    Midifile/src-library/MidiEvent.cpp \
    Midifile/src-library/MidiEventList.cpp \
    Midifile/src-library/MidiFile.cpp \
    Midifile/src-library/MidiMessage.cpp \
    Midifile/src-library/Options.cpp \
    src/blocks/arpeggiator.cpp \
    src/blocks/chordify.cpp \
    src/blocks/gate.cpp \
    src/blocks/monophonic.cpp \
    src/blocks/pitchshift.cpp \
    src/inputprocessor.cpp \
    src/gui/selectoutput.cpp \
    src/io/mididriverinput.cpp \
    src/io/midifileinput.cpp \
    src/io/midifileoutput.cpp \
    src/io/pianoinput.cpp \
    rtmidi/RtMidi.cpp \
    src/gui/selectinput.cpp \
    src/io/serialoutput.cpp \
    src/gui/blockwidget.cpp \
    src/io/mididriveroutput.cpp \
    src/gui/commands/addblockcommand.cpp \
    src/gui/commands/deleteblockcommand.cpp \
    src/gui/commands/applychangescommand.cpp \
    src/gui/commands/changeinputcommand.cpp \
    src/gui/commands/shiftblockcommand.cpp \
    src/gui/losechanges.cpp \
    src/blocks/blockdata.cpp \
    src/io/inputdata.cpp

HEADERS  += include/scale.h \
    include/gui/blockframe.h \
    include/gui/keyboard.h \
    include/gui/mainwindow.h \
    include/gui/metronome.h \
    include/gui/pianokey.h \
    include/gui/shortcuts.h \
    include/io/inputhandler.h \
    include/io/iotypes.h \
    include/io/outputhandler.h \
    include/note.h \
    Midifile/include/Binasc.h \
    Midifile/include/MidiEvent.h \
    Midifile/include/MidiEventList.h \
    Midifile/include/MidiFile.h \
    Midifile/include/MidiMessage.h \
    Midifile/include/Options.h \
    include/blocks/arpeggiator.h \
    include/blocks/chordify.h \
    include/blocks/gate.h \
    include/blocks/monophonic.h \
    include/blocks/pitchshift.h \
    include/inputprocessor.h \
    include/gui/selectoutput.h \
    include/io/abstractinput.h \
    include/io/abstractoutput.h \
    include/io/midifileinput.h \
    include/io/midifileoutput.h \
    include/io/serialoutput.h \
    include/io/pianoinput.h \
    include/io/mididriverinput.h \
    rtmidi/RtMidi.h \
    include/gui/selectinput.h \
    include/gui/blockwidget.h \
    include/blocktypes.h \
    include/block.h \
    include/io/mididriveroutput.h \
    include/gui/commands/addblockcommand.h \
    include/gui/commands/deleteblockcommand.h \
    include/gui/commands/shiftblockcommand.h \
    include/gui/commands/applychangescommand.h \
    include/gui/commands/changeinputcommand.h \
    include/gui/losechanges.h \
    include/blocks/blockdata.h \
    include/io/inputdata.h

FORMS    += \
    forms/mainwindow.ui \
    forms/about.ui \
    forms/selectoutput.ui \
    forms/selectinput.ui \
    forms/losechanges.ui

RESOURCES += \
    resources/images.qrc \
    resources/sounds.qrc

INCLUDEPATH += Midifile/include \
    rtmidi \
    include \
    include/io \
    include/gui \
    include/blocks \
    include/gui/commands


CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/qrc
UI_DIR = $$DESTDIR/ui
