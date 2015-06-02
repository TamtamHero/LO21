#include "tache.h"
#include <iostream>

Tache::Tache(QString titre,QDateTime disponibilite,QDateTime echeance):
    m_titre(titre), m_disponibilite(disponibilite), m_echeance(echeance), m_status(false), m_parent(NULL)
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
    std::sort(m_prerequisite.begin(),m_prerequisite.end(),taskCompare());
}

bool Tache::arePrerequisiteDone()
{
    for(vector<Tache *>::iterator it=this->m_prerequisite.begin();it!=this->m_prerequisite.end();++it)
    {
        if((*it)->getStatus()!=true)
        {
            return false;
        }
        if((*it)->arePrerequisiteDone()==false)
        {
            return false;
        }
    }
    return true;
}

//_-_-_-_-_-_-_-_-_-STATIC_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Tache::checkPrerequisite(Tache* task, Tache * prerequisiteTask)
{
    if(task==NULL)
    {
        return true; //Creation case
    }
    if(task==prerequisiteTask)
    {
        throw CalendarException("Une tache ne peut être son propre prérequis");
    }
    else if(task->getDisponibility()<=prerequisiteTask->getDisponibility())
    {
        throw CalendarException("La date de disponibilité de la nouvelle tache doit être postérieure aux disponibilités des taches qui la précède");
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
    if(task==NULL)
    {
        return true; //Creation case
    }
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
