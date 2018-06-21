#include "touchscreen.h"
#include "ui_touchscreen.h"
#include <windows.h>
#include <stdint.h>

TouchScreen::TouchScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TouchScreen)
{
    ui->setupUi(this);

    ComPortName = (char *) "\\\\.\\COM5";

    /*----------------------------------- Opening the Serial Port --------------------------------------------*/

    hComm = CreateFileA( ComPortName,                       // Name of the Port to be Opened
                         GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
                         0,                                 // No Sharing, ports cant be shared
                         NULL,                              // No Security
                         OPEN_EXISTING,                     // Open existing port only
                         0,                                 // Non Overlapped I/O
                         NULL);                             // Null for Comm Devices

    /*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    GetCommState(hComm, &dcbSerialParams);     //retreives  the current settings

    dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
    dcbSerialParams.Parity   = ODDPARITY;      // Setting Parity = Odd

    SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB

    /*------------------------------------ Setting Timeouts --------------------------------------------------*/

    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    /*----------------------------- Writing a Character to Serial Port----------------------------------------*/
    lpBuffer = (uint8_t *) "T";

}

TouchScreen::~TouchScreen()
{
    delete ui;
}

void TouchScreen::on_pushButton_toggled(bool checked)
{
    dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

    WriteFile(hComm,                      // Handle to the Serialport
              lpBuffer,                   // Data to be written to the port
              dNoOFBytestoWrite,          // No of bytes to write into the port
              &dNoOfBytesWritten,         // No of bytes written to the port
              NULL);

    if(checked)
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
}
