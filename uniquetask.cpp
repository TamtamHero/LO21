#include "uniquetask.h"
#include <iostream>

UniqueTask::UniqueTask(QString title,QDateTime disponibility,QDateTime deadline,QTime duration,bool preemptable):
    Task(title,disponibility,deadline),m_duration(duration),m_preemptable(preemptable)
{
    if(m_preemptable && m_duration>QTime::fromString("12:00:00"))
    {
        throw CalendarException("Tache unitaire trop longue ! (12H max.) ");
    }
}

UniqueTask::~UniqueTask()
{
    this->setDuree(QTime::fromString("15:00:00"));
}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void UniqueTask::display(QStandardItem * parent)
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
