#include "uniquetask.h"
#include <iostream>

UniqueTask::UniqueTask(QString titre,QDateTime disponibility,QDateTime echeance,QTime duree,bool preemptable):
    Task(titre,disponibility,echeance),m_duree(duree),m_preemptable(preemptable)
{
    if(m_preemptable && m_duree>QTime::fromString("12:00:00"))
    {
        throw CalendarException("Task unitaire trop longue ! (12H max.) ");
    }
}

UniqueTask::~UniqueTask()
{
    this->setDuree(QTime::fromString("15:00:00"));
}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void UniqueTask::afficher(QStandardItem * parent)
{

}

list<Task*> UniqueTask::getAllUniquePrerequisite()
{
    list<Task*> result,part;
    for(vector<Task *>::iterator it=this->m_prerequisite.begin();it!=this->m_prerequisite.end();++it)
    {
        if(dynamic_cast<UniqueTask*>((*it))!=NULL)
        {
            result.push_back((*it));
        }
        else
        {
            part=dynamic_cast<BlendTask*>((*it))->getAllUniqueSons();
            result.merge(part);
        }
    }

    if(getParent()!=NULL)
    {
        part=dynamic_cast<BlendTask*>(getParent())->getAllUniquePrerequisite();
        result.merge(part);
    }

    return result;
}
