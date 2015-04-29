#include "tache.h"

Tache::Tache(QString titre,QDateTime disponibilite,QDateTime echeance):
    m_titre(titre), m_disponibilite(disponibilite), m_echeance(echeance), m_status(0)
{
    if(echeance < QDateTime::currentDateTime())
    {
        throw CalendarException("Echéance de la tache déjà passée !");
    }
    else if(echeance < disponibilite)
    {
        throw CalendarException("La disponibilité entrée est ultérieure à l'échéance !");
    }
}

Tache::~Tache()
{

}

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

}

TacheMultiple::TacheMultiple(QString titre,QDateTime disponibilite,QDateTime echeance):
    Tache(titre,disponibilite,echeance)
{
    // Useless pour l'instant, le constructeur de la classe mère Tache fait tout le travail.
}

TacheMultiple::~TacheMultiple()
{

}

