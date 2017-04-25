#include "serialoutput.h"

SerialOutput::SerialOutput(QString portName) : AbstractOutput()
{  
    // Set up the serial connection settings
    port_ = new QSerialPort();
    port_->setPortName(portName);
    port_->setBaudRate(QSerialPort::Baud19200);
    port_->setDataBits(QSerialPort::Data8);
    port_->setParity(QSerialPort::NoParity);
    port_->setStopBits(QSerialPort::OneStop);
}

// Returns the port_ variable
QSerialPort* SerialOutput::getPort() {
    return port_;
}

// Attempt to open the serial port
void SerialOutput::start() {
    bool success = port_->open(QIODevice::ReadWrite);
    if (!success) {
        qDebug() << port_->errorString();
    }
}

// Closes the port
void SerialOutput::stop() {
    if(port_->isOpen())
        port_->close();
}

// Sends a note on message one byte at a time, waiting for a byte to be
// returned before moving on
void SerialOutput::sendNoteOn(int note) {
    if(port_->isOpen()) {
        char* msg = new char[2];
        char* inp = new char[2];
        msg[1] = '\0';
        msg[0] = (char)NOTE_ON;

        port_->write(msg);
        port_->flush();
        port_->waitForBytesWritten(30);
        port_->waitForReadyRead(30);
        port_->read(inp, 1);

        msg[0] = (char)note;

        port_->write(msg);
        port_->flush();
        port_->waitForBytesWritten(30);
        port_->waitForReadyRead(30);
        port_->read(inp, 1);
    }
}

// Sends a note off message one byte at a time, waiting for a byte to be
// returned before moving on
void SerialOutput::sendNoteOff(int note) {
    if(port_->isOpen()) {
        char* msg = new char[2];
        char* inp = new char[2];
        msg[1] = '\0';
        msg[0] = (char)NOTE_OFF;

        port_->write(msg);
        port_->flush();
        port_->waitForBytesWritten(30);
        port_->waitForReadyRead(30);
        port_->read(inp, 1);

        msg[0] = (char)note;

        port_->write(msg);
        port_->flush();
        port_->waitForBytesWritten(30);
        port_->waitForReadyRead(30);
        port_->read(inp, 1);
    }
}

// Sends a configuration message one byte at a time, waiting for a byte to be
// returned before moving on
void SerialOutput::sendConfigInfo(QList<int> notes) {
    if(port_->isOpen()) {
        char* msg = new char[2];
        char* inp = new char[2];
        msg[1] = '\0';
        msg[0] = (char)CONFIG;

        port_->write(msg);
        port_->flush();
        port_->waitForBytesWritten(30);
        port_->waitForReadyRead(30);
        port_->read(inp, 1);

        for (int i = 0; i < 8; i++) {
            if(i < notes.size()) {
                msg[0] = (char)(notes.at(i));
            } else {
                msg[0] = (char)85;
            }

            port_->write(msg);
            port_->flush();
            port_->waitForBytesWritten(30);
            port_->waitForReadyRead(30);
            port_->read(inp, 1);
        }
    }
}
