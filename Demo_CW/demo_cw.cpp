#include "demo_cw.h"
#include "ui_demo_cw.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <string>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    send = true;

    serialBuffer = '\0';
    serialData = '\0';

    stm32f4 = new QSerialPort(this);

    stm32f4->setPortName("COM5");
    stm32f4->open(QIODevice::ReadWrite );
    stm32f4->setBaudRate(QSerialPort::Baud9600);
    stm32f4->setDataBits(QSerialPort::Data8);
    stm32f4->setFlowControl(QSerialPort::NoFlowControl);
    stm32f4->setParity(QSerialPort::OddParity);
    stm32f4->setStopBits(QSerialPort::OneStop);
    QObject::connect(stm32f4, SIGNAL(readyRead()), this, SLOT(readData()));
    //QObject::connect(stm32f4, SIGNAL(QIODevice::readyRead()), this, SLOT(readData()));
}

Widget::~Widget()
{
    if(stm32f4->isOpen())
    {
            stm32f4->close(); //    Close the serial port if it's open.
    }
    delete ui;
}

void Widget::on_pushButton_toggled(bool checked)
{
    toggle_action(checked);
}

void Widget::toggle_action(bool state)
{
    if(send)
    {
        writeData((const QByteArray) "T");
    }

    if(state)
    {
        this->setStyleSheet("background-color:red;");
        ui->label->setStyleSheet("color: rgb(255, 0, 0); background-color: rgb(255, 255, 255);");
        ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255);");
    }
    else
    {
        this->setStyleSheet("background-color:white;");
        ui->label->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(255, 0, 0);");
        ui->pushButton->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    send = true;
}

void Widget::writeData(const QByteArray &data)
{
    stm32f4->write(data);
}

void Widget::readData()
{
    serialData = stm32f4->readAll();
    serialBuffer = (quint8 *) serialData.data();

    if(serialBuffer[0] == (quint8) 'T')
    {
        //writeData((const QByteArray) "G");
        bool current_state;
        send = false;
        current_state = !(ui->pushButton->isChecked());
        ui->pushButton->setChecked(current_state);
        //toggle_action(!current_state);
    }
}
