/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *setRCPos;
    QLineEdit *RCText;
    QLineEdit *DCText;
    QPushButton *setDC;
    QLineEdit *StepperText;
    QPushButton *setStepper;
    QLabel *label_4;
    QLabel *Pot;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *UltraSound;
    QLabel *FSensor;
    QLineEdit *DCPosText;
    QPushButton *setDCPos;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(610, 487);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 270, 60, 16));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 320, 60, 16));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 410, 101, 16));
        setRCPos = new QPushButton(Dialog);
        setRCPos->setObjectName(QStringLiteral("setRCPos"));
        setRCPos->setGeometry(QRect(260, 260, 113, 32));
        RCText = new QLineEdit(Dialog);
        RCText->setObjectName(QStringLiteral("RCText"));
        RCText->setGeometry(QRect(120, 260, 113, 31));
        DCText = new QLineEdit(Dialog);
        DCText->setObjectName(QStringLiteral("DCText"));
        DCText->setGeometry(QRect(120, 310, 113, 31));
        setDC = new QPushButton(Dialog);
        setDC->setObjectName(QStringLiteral("setDC"));
        setDC->setGeometry(QRect(260, 310, 113, 32));
        StepperText = new QLineEdit(Dialog);
        StepperText->setObjectName(QStringLiteral("StepperText"));
        StepperText->setGeometry(QRect(130, 400, 113, 31));
        setStepper = new QPushButton(Dialog);
        setStepper->setObjectName(QStringLiteral("setStepper"));
        setStepper->setGeometry(QRect(270, 400, 113, 32));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 40, 60, 16));
        Pot = new QLabel(Dialog);
        Pot->setObjectName(QStringLiteral("Pot"));
        Pot->setGeometry(QRect(80, 40, 60, 16));
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 80, 81, 16));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 120, 151, 16));
        UltraSound = new QLabel(Dialog);
        UltraSound->setObjectName(QStringLiteral("UltraSound"));
        UltraSound->setGeometry(QRect(130, 80, 60, 16));
        FSensor = new QLabel(Dialog);
        FSensor->setObjectName(QStringLiteral("FSensor"));
        FSensor->setGeometry(QRect(200, 120, 81, 20));
        DCPosText = new QLineEdit(Dialog);
        DCPosText->setObjectName(QStringLiteral("DCPosText"));
        DCPosText->setGeometry(QRect(120, 360, 113, 31));
        setDCPos = new QPushButton(Dialog);
        setDCPos->setObjectName(QStringLiteral("setDCPos"));
        setDCPos->setGeometry(QRect(260, 360, 113, 32));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog", "RC Servo", nullptr));
        label_2->setText(QApplication::translate("Dialog", "DC Motor", nullptr));
        label_3->setText(QApplication::translate("Dialog", "Stepper Motor", nullptr));
        setRCPos->setText(QApplication::translate("Dialog", "setRCPos", nullptr));
        RCText->setText(QApplication::translate("Dialog", "0", nullptr));
        DCText->setText(QApplication::translate("Dialog", "0", nullptr));
        setDC->setText(QApplication::translate("Dialog", "setDCSpeed", nullptr));
        StepperText->setText(QApplication::translate("Dialog", "0", nullptr));
        setStepper->setText(QApplication::translate("Dialog", "setStepperPos", nullptr));
        label_4->setText(QApplication::translate("Dialog", "Pot:", nullptr));
        Pot->setText(QApplication::translate("Dialog", "0", nullptr));
        label_6->setText(QApplication::translate("Dialog", "Ultrasonic:", nullptr));
        label_7->setText(QApplication::translate("Dialog", "Force Sensitive Sensor:", nullptr));
        UltraSound->setText(QApplication::translate("Dialog", "0", nullptr));
        FSensor->setText(QApplication::translate("Dialog", "0", nullptr));
        DCPosText->setText(QApplication::translate("Dialog", "0", nullptr));
        setDCPos->setText(QApplication::translate("Dialog", "setDCPos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
