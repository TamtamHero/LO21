#include "task.h"
#include <iostream>

Task::Task(QString title,QDateTime disponibility,QDateTime deadline):
    m_title(title), m_disponibility(disponibility), m_deadline(deadline), m_status(false), m_parent(NULL)
{
    if(deadline < disponibility)
    {
        throw CalendarException("La disponibilité entrée pour la tache est ultérieure à l'échéance !");
    }
}

Task::~Task()
{

}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void Task::setParent(Task * parent)
{
    if(this!=parent)
    {
       m_parent=parent;
    }
    else
    {
        throw CalendarException("Tentative avortée d'auto-inclusion de la tache "+getTitle());
    }
}

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
        throw CalendarException("Une tache ne peut être son propre prérequis");
    }
    else if(task->getDisponibility()<=prerequisiteTask->getDisponibility())
    {
        throw CalendarException("La date de disponibilité de la nouvelle tache doit être postérieure aux disponibilités des taches qui la précèdent");
    }

    Task* ptr_task=task->getParent();
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


bool Task::checkAttaskdTo(Task* task, Task * motherTask)
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
