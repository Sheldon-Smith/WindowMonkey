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
    value = value*100/360;
    Dialog::updatePos(QString("s%1").arg(value));
}


//Read
void Dialog::readSerial()
{
//    qDebug() << "Read Work!";
//    /*
//     * readyRead() doesn't guarantee that the entire message will be received all at once.
//     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
//     *
//     */
//    QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

//    //  Check to see if there less than 3 tokens in buffer_split.
//    //  If there are at least 3 then this means there were 2 commas,
//    //  means there is a parsed temperature value as the second token (between 2 commas)
//    if(buffer_split.length() < 3){
//        // no parsed value yet so continue accumulating bytes from serial in the buffer.
//        serialData = arduino->readAll();
//        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
//        serialData.clear();
//    }else{
//        // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
//        serialBuffer = "";
//        qDebug() << buffer_split << "\n";
//        parsed_data = buffer_split[1];
//        temperature_value = (9/5.0) * (parsed_data.toDouble()) + 32; // convert to fahrenheit
//        qDebug() << "Temperature: " << temperature_value << "\n";
//        parsed_data = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
//        Dialog::updateTemperature(parsed_data);
//    }

}



