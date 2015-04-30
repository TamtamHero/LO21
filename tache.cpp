#include "tache.h"
#include <iostream>

Tache::Tache(QString titre,QDateTime disponibilite,QDateTime echeance):
    m_titre(titre), m_disponibilite(disponibilite), m_echeance(echeance), m_status(0)
{
    if(echeance < QDateTime::currentDateTime())
    {
        throw CalendarException("Echéance de la tache déjà passée !");
    }
    else if(echeance < disponibilite)
    {
        throw CalendarException("La disponibilité entrée pour la tache est ultérieure à l'échéance !");
    }
}

Tache::~Tache()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

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

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

TacheComposite::TacheComposite(QString titre,QDateTime disponibilite,QDateTime echeance):
    Tache(titre,disponibilite,echeance)
{
    // Useless pour l'instant, le constructeur de la classe mère Tache fait tout le travail.
}

void TacheComposite::addSousTache(Tache * sousTache)
{
    m_sousTache.push_back(sousTache);
}

TacheComposite::~TacheComposite()
{
    for(int i=0;i<m_sousTache.size();i++)
    {
        delete(m_sousTache[i]);
        m_sousTache[i]=0;
    }
    cout << m_sousTache.size() << "lol";
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
