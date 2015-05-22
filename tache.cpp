#include "tache.h"
#include <iostream>

Tache::Tache(QString titre,QDateTime disponibilite,QDateTime echeance):
    m_titre(titre), m_disponibilite(disponibilite), m_echeance(echeance), m_status(0), m_parent(NULL)
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
void Tache::addPrerequisite(Tache *prerequisite)
{
    checkPrerequisite(this,prerequisite);
    m_prerequisite.push_back(prerequisite);
}

//_-_-_-_-_-_-_-_-_-STATIC_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Tache::checkPrerequisite(Tache* task, Tache * prerequisiteTask)
{
    if(task==prerequisiteTask)
    {
        throw CalendarException("Une tache ne peut être son propre prérequis");
    }
    else if(task->getDisponibility()<=prerequisiteTask->getDisponibility())
    {
        throw CalendarException("La date de disponibilité de la tache est antérieure ou égale à celle de la tache qu'elle est censé précéder");
    }

    Tache* ptr_task=task->getParent();
    while(ptr_task!=NULL)
    {
        if(ptr_task==prerequisiteTask)
        {
            throw CalendarException("Une tache ne peut pas avoir une tache parente en prérequis");
        }
        ptr_task=ptr_task->getParent();
    }
    return true;

}


bool Tache::checkAttachedTo(Tache* task, Tache * motherTask)
{
    if(task==motherTask)
    {
        throw CalendarException("Une tache ne peut pas être rattachée à elle même");
    }
    else if(task->getDisponibility()>=motherTask->getDeadline())
    {
        throw CalendarException("La date de disponibilité de la tache est postérieure ou égale à la tache qu'elle compose");
    }
    //A FAIRE: nom déjà utilisé ?
    return true;

}


//_-_-_-_-_-_-_-_OPERATOR OVERLOADS-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Tache::operator<(const Tache &b) const
{
    if(this->getDeadline()<=b.getDeadline())
    {
        return true;
    }
    return false;
}
