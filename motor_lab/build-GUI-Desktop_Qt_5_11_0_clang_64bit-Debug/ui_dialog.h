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
    QLabel *PotLabel;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *UltraSoundLabel;
    QLabel *ForceSensorLabel;
    QLineEdit *DCPosText;
    QPushButton *setDCPos;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(610, 487);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 260, 60, 16));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 310, 60, 16));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 420, 101, 16));
        setRCPos = new QPushButton(Dialog);
        setRCPos->setObjectName(QStringLiteral("setRCPos"));
        setRCPos->setGeometry(QRect(330, 250, 171, 41));
        setRCPos->setStyleSheet(QStringLiteral("color:rgb(0, 0, 0);"));
        RCText = new QLineEdit(Dialog);
        RCText->setObjectName(QStringLiteral("RCText"));
        RCText->setGeometry(QRect(180, 250, 113, 31));
        DCText = new QLineEdit(Dialog);
        DCText->setObjectName(QStringLiteral("DCText"));
        DCText->setGeometry(QRect(180, 310, 113, 31));
        setDC = new QPushButton(Dialog);
        setDC->setObjectName(QStringLiteral("setDC"));
        setDC->setGeometry(QRect(330, 310, 171, 41));
        StepperText = new QLineEdit(Dialog);
        StepperText->setObjectName(QStringLiteral("StepperText"));
        StepperText->setGeometry(QRect(180, 410, 113, 31));
        setStepper = new QPushButton(Dialog);
        setStepper->setObjectName(QStringLiteral("setStepper"));
        setStepper->setGeometry(QRect(330, 410, 171, 41));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 40, 60, 16));
        PotLabel = new QLabel(Dialog);
        PotLabel->setObjectName(QStringLiteral("PotLabel"));
        PotLabel->setGeometry(QRect(120, 40, 60, 16));
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(80, 80, 81, 16));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(80, 120, 151, 16));
        UltraSoundLabel = new QLabel(Dialog);
        UltraSoundLabel->setObjectName(QStringLiteral("UltraSoundLabel"));
        UltraSoundLabel->setGeometry(QRect(170, 80, 60, 16));
        ForceSensorLabel = new QLabel(Dialog);
        ForceSensorLabel->setObjectName(QStringLiteral("ForceSensorLabel"));
        ForceSensorLabel->setGeometry(QRect(240, 120, 81, 20));
        DCPosText = new QLineEdit(Dialog);
        DCPosText->setObjectName(QStringLiteral("DCPosText"));
        DCPosText->setGeometry(QRect(180, 350, 113, 31));
        setDCPos = new QPushButton(Dialog);
        setDCPos->setObjectName(QStringLiteral("setDCPos"));
        setDCPos->setGeometry(QRect(330, 350, 171, 41));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(150, 40, 60, 16));
        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(190, 80, 60, 16));
        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(270, 120, 60, 21));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog", "RC Servo", nullptr));
        label_2->setText(QApplication::translate("Dialog", "DC Motor", nullptr));
        label_3->setText(QApplication::translate("Dialog", "Stepper Motor", nullptr));
        setRCPos->setText(QApplication::translate("Dialog", "setRCPos(degree)", nullptr));
        RCText->setText(QApplication::translate("Dialog", "0", nullptr));
        DCText->setText(QApplication::translate("Dialog", "0", nullptr));
        setDC->setText(QApplication::translate("Dialog", "setDCSpeed", nullptr));
        StepperText->setText(QApplication::translate("Dialog", "0", nullptr));
        setStepper->setText(QApplication::translate("Dialog", "setStepperPos(degree)", nullptr));
        label_4->setText(QApplication::translate("Dialog", "Pot:", nullptr));
        PotLabel->setText(QApplication::translate("Dialog", "0", nullptr));
        label_6->setText(QApplication::translate("Dialog", "Ultrasonic:", nullptr));
        label_7->setText(QApplication::translate("Dialog", "Force Sensitive Sensor:", nullptr));
        UltraSoundLabel->setText(QApplication::translate("Dialog", "0", nullptr));
        ForceSensorLabel->setText(QApplication::translate("Dialog", "0", nullptr));
        DCPosText->setText(QApplication::translate("Dialog", "0", nullptr));
        setDCPos->setText(QApplication::translate("Dialog", "setDCPos(degree)", nullptr));
        label_5->setText(QApplication::translate("Dialog", "degree", nullptr));
        label_8->setText(QApplication::translate("Dialog", "cm", nullptr));
        label_9->setText(QApplication::translate("Dialog", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
