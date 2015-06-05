#include <iostream>
#include <task.h>
#include <mainwindow.h>
#include <QTextStream>
#include <QApplication>
#include <QMetaType>



int main(int argc, char * argv[])
{
    QApplication app(argc,argv);


    MainWindow fenetre;
    fenetre.show();

    return app.exec();
}
