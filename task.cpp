#include "task.h"
#include <iostream>

Task::Task(QString titre,QDateTime disponibility,QDateTime echeance):
    m_titre(titre), m_disponibility(disponibility), m_echeance(echeance), m_status(false), m_parent(NULL)
{
    if(echeance < QDateTime::currentDateTime())
    {
        throw CalendarException("Echéance de la task déjà passée !");
    }
    else if(echeance < disponibility)
    {
        throw CalendarException("La disponibilité entrée pour la task est ultérieure à l'échéance !");
    }
}

Task::~Task()
{

}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void Task::addPrerequisite(Task *prerequisite)
{
    checkPrerequisite(this,prerequisite);
    m_prerequisite.push_back(prerequisite);
    std::sort(m_prerequisite.begin(),m_prerequisite.end(),taskCompare());
}

bool Task::arePrerequisiteScheduled()
{
    for(vector<Task *>::iterator it=this->m_prerequisite.begin();it!=this->m_prerequisite.end();++it)
    {
        if((*it)->getStatus()!=true)
        {
            return false;
        }
    }
    if(getParent()==NULL)
    {
        return true;
    }
    if(getParent()->arePrerequisiteScheduled()==false)
    {
        return false;
    }
    return true;
}

//_-_-_-_-_-_-_-_-_-STATIC_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Task::checkPrerequisite(Task* task, Task * prerequisiteTask)
{
    if(task==NULL)
    {
        return true; //Creation case
    }
    if(task==prerequisiteTask)
    {
        throw CalendarException("Une task ne peut être son propre prérequis");
    }
    else if(task->getDisponibility()<=prerequisiteTask->getDisponibility())
    {
        throw CalendarException("La date de disponibilité de la nouvelle task doit être postérieure aux disponibilités des tasks qui la précède");
    }

    Task* ptr_task=task->getParent();
    while(ptr_task!=NULL)
    {
        if(ptr_task==prerequisiteTask)
        {
            throw CalendarException("Une task ne peut pas avoir une task parente en prérequis");
        }
        ptr_task=ptr_task->getParent();
    }
    return true;

}


bool Task::checkAttaskdTo(Task* task, Task * motherTask)
{
    if(task==NULL)
    {
        return true; //Creation case
    }
    if(task==motherTask)
    {
        throw CalendarException("Une task ne peut pas être rattachée à elle même");
    }
    else if(task->getDisponibility()>=motherTask->getDeadline())
    {
        throw CalendarException("La date de disponibilité de la task est postérieure ou égale à la task qu'elle compose");
    }
    //A FAIRE: nom déjà utilisé ?
    return true;

}


//_-_-_-_-_-_-_-_OPERATOR OVERLOADS-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Task::operator<(const Task &b) const
{
    if(this->getDeadline()<=b.getDeadline())
    {
        return true;
    }
    return false;
}
