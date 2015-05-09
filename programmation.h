#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QString>
#include <QDateTime>
#include "tacheunitaire.h"

class Programmation
{
protected:
    QDateTime m_date;
    QTime m_duree;
    QString m_titre;
    TacheUnitaire *m_tache;

public:
    Programmation(QDateTime date,QTime duree,QString titre);
    Programmation(QDateTime date,QTime duree,TacheUnitaire *tache);
    ~Programmation();
};

#endif // PROGRAMMATION_H
