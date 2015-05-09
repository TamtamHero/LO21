#include "tacheunitaire.h"

TacheUnitaire::TacheUnitaire(QString titre,QDateTime disponibilite,QDateTime echeance,QTime duree,bool preemptable):
    Tache(titre,disponibilite,echeance),m_duree(duree),m_preemptable(preemptable)
{
    if(m_preemptable && m_duree>QTime::fromString("12:00:00"))
    {
        throw CalendarException("Tache unitaire trop longue ! (12H max.) ");
    }
}

TacheUnitaire::~TacheUnitaire()
{
    this->setDuree(QTime::fromString("15:00:00"));
}

void TacheUnitaire::afficher(QStandardItem * parent)
{

}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
