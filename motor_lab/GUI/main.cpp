#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedSize(500,500);
    w.setWindowTitle("Motor Controller");
    w.show();

    return a.exec();
}

