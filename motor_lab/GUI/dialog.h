#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>

#include <QTime>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void updatePos(QString);

    void on_setRCPos_clicked();

    void on_setDC_clicked();

    void on_setStepper_clicked();

    //Reading
    void readSerial();
//    void updateRC(QString);

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 10755;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // DIALOG_H
