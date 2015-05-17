#include <iostream>
#include <tache.h>
#include <mainwindow.h>
#include <QTextStream>
#include <QApplication>
#include <QMetaType>



int main(int argc, char * argv[])
{
    QApplication app(argc,argv);
/*
    QDateTime t1=QDateTime::currentDateTime();
    QDateTime t2=QDateTime::currentDateTime().addDays(1);
    TacheUnitaire *t=new TacheUnitaire("tache 1",t1,t2,QTime::fromString("11:00:00"),true);
    TacheUnitaire t5("tache 1",t1,t2,QTime::fromString("11:00:00"),true);

    QTextStream out(stdout);


    TacheComposite *tc=new TacheComposite("tache compo",t1,t2);


    tc->addElement(t);
    tc->addElement(&t5);


    out << t->getDuree().toString() ;

*/


    MainWindow fenetre;
    fenetre.show();

    return app.exec();
}
