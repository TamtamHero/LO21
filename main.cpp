#include <iostream>
#include <tache.h>
#include <QTextStream>


int main(int argc, const char * argv[])
{
    QDateTime t1=QDateTime::currentDateTime();
    QDateTime t2=QDateTime::currentDateTime().addDays(1);
    TacheUnitaire *t=new TacheUnitaire("tache 1",t1,t2,QTime::fromString("11:00:00"),true);

    QTextStream out(stdout);

    out << t->getDuree().toString() << "lol";

    return 0;
}
