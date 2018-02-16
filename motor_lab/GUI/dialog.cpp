#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QTime>
#include<string>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    arduino_is_available = false;
//    arduino_port_name = "/dev/cu.usbmodem1451";
    arduino_port_name = "";
    arduino = new QSerialPort;

    serialBuffer = "";
    pot_value = 0;
    ultrasound_value = 0;
    forceSensor_value = 0;

//    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
//    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
//            qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
//            if(serialPortInfo.hasVendorIdentifier()){
//                qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
//            }
//            qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
//            if(serialPortInfo.hasProductIdentifier()){
//                qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
//            }
//        }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
                if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                    if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                        arduino_port_name = serialPortInfo.portName();
                        arduino_is_available = true;
                    }
                }
            }
        }

    if(arduino_is_available){
            // open and configure the serialport
            arduino->setPortName(arduino_port_name);
            arduino->open(QSerialPort::ReadWrite);
            arduino->setBaudRate(QSerialPort::Baud9600);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            arduino->setFlowControl(QSerialPort::NoFlowControl);
            QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
        }else{
            // give error message if not available
            QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
        }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
            arduino->close();
        }
    delete ui;
}

void Dialog::updatePos(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}



void Dialog::on_setRCPos_clicked()
{
    QString input = ui->RCText->text();
    int value = input.toInt();
    Dialog::updatePos(QString("r%1").arg(value));
}

void Dialog::on_setDC_clicked()
{
    QString input = ui->DCText->text();
    int value = input.toInt();
    Dialog::updatePos(QString("d%1").arg(value));
}

void Dialog::on_setDCPos_clicked()
{
    QString input = ui->DCPosText->text();
    int value = input.toInt();
    Dialog::updatePos(QString("p%1").arg(value));
}

void Dialog::on_setStepper_clicked()
{
    QString input = ui->StepperText->text();
    int value = input.toInt();
    Dialog::updatePos(QString("s%1").arg(value));
}


//Read
void Dialog::readSerial()
{
//    qDebug() << "Read Work!";
    QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

    if(buffer_split.length() < 3){
        serialData = arduino->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }else{
        serialBuffer = "";
        qDebug() << buffer_split << "\n";
        pot_value = buffer_split[0].toInt();
        ultrasound_value = buffer_split[1].toInt();
        forceSensor_value = buffer_split[2].toInt();

        Dialog::updatePot(pot_value);
        Dialog::updateUltraSound(ultrasound_value);
        Dialog::updateForceSensor(forceSensor_value);
    }

}

void Dialog::updatePot(int value)
{
    ui->PotLabel->setText(QString("<span style=\" font-size:12pt; font-weight:100;\">%1</span>").arg(value));
}

void Dialog::updateUltraSound(int value)
{
    ui->UltraSoundLabel->setText(QString("<span style=\" font-size:12pt; font-weight:100;\">%1</span>").arg(value));
}

void Dialog::updateForceSensor(int value)
{
    ui->ForceSensorLabel->setText(QString("<span style=\" font-size:12pt; font-weight:100;\">%1</span>").arg(value));
}




