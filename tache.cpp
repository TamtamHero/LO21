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


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

bool Tache::checkPrerequisite(Tache* task,Tache * previousTask)
{
    if(task==previousTask)
    {
        throw CalendarException("Une tache ne peut pas se composer d'elle même ou se précéder");
    }
    else if(task->getDisponibility()>=previousTask->getDeadline())
    {
        throw CalendarException("La date de disponibilité de la tache est postérieure à la tache qu'elle compose");
    }
    //Cas d'une tache mère
    return true;

}
