#ifndef DEMO_CW_H
#define DEMO_CW_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_toggled(bool checked);
    void toggle_action(bool state);
    void writeData(const QByteArray &data);
    void readData();

private:
    Ui::Widget *ui;
    QSerialPort *stm32f4;
    QByteArray serialData;
    quint8 *serialBuffer;
    bool send;
};

#endif // DEMO_CW_H
