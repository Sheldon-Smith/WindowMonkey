#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>

#include <QTime>

////////////
#include <QByteArray>
///

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

    void on_setDCPos_clicked();

    //Reading
    void readSerial();
    void updatePot(int);
    void updateUltraSound(int);
    void updateForceSensor(int);

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 10755;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;

    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    int pot_value;
    int ultrasound_value;
    int forceSensor_value;
};

#endif // DIALOG_H
