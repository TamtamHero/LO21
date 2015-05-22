#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include "tache.h"
#include <QVariant>


class TacheUnitaire: public Tache
{

protected:
    QTime m_duree;
    bool m_preemptable;

public:
    TacheUnitaire(QString titre,QDateTime disponibilite,QDateTime echeance,QTime duree,bool preemptable=false);
    QTime getDuree() const {return m_duree;}
    bool getPreemptability(){return m_preemptable;}
    void setDuree(QTime duree) {m_duree=duree;}
    void setPreemptability(bool choice){m_preemptable=choice;}
    void afficher(QStandardItem * parent);

    virtual ~TacheUnitaire();
};

Q_DECLARE_METATYPE(TacheUnitaire *)

#endif // TACHEUNITAIRE_H
