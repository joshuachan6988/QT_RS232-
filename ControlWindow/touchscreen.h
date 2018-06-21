#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <QMainWindow>
#include <windows.h>
#include <stdint.h>

namespace Ui {
class TouchScreen;
}

class TouchScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit TouchScreen(QWidget *parent = 0);
    ~TouchScreen();

private slots:
    void on_pushButton_toggled(bool checked);

private:
    Ui::TouchScreen *ui;
    HANDLE hComm;                  // Handle to the Serial port
    char   *ComPortName;          // Name of the Serial port(May Change) to be opened
    DCB dcbSerialParams;           // Initializing DCB structure
    COMMTIMEOUTS timeouts;
    uint8_t   *lpBuffer;		   // lpBuffer should be  char or byte array, otherwise write wil fail
    DWORD  dNoOFBytestoWrite;      // No of bytes to write into the port
    DWORD  dNoOfBytesWritten;      // No of bytes written to the port
};

#endif // TOUCHSCREEN_H
