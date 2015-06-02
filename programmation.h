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

    QDateTime getDateTime()const {return m_date;}
    QString getTitle()const{return m_titre;}
    QTime getDuration(){return m_duree;}
    TacheUnitaire* getTask(){return m_tache;}
    bool operator < (const Programmation& b) const;
    bool operator == (const Programmation& b) const;

};

#endif // PROGRAMMATION_H
