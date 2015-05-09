#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include "tache.h"
#include "qtache.h"


class TacheUnitaire: public Tache
{

protected:
    QTime m_duree;
    bool m_preemptable;

public:
    TacheUnitaire(QString titre,QDateTime disponibilite,QDateTime echeance,QTime duree,bool preemptable=false);
    QTime getDuree() const {return m_duree;}
    void setDuree(QTime duree) {m_duree=duree;}
    void afficher(QStandardItem * parent);
    ~TacheUnitaire();
};

#endif // TACHEUNITAIRE_H
