#include "uniquetask.h"
#include <iostream>

UniqueTask::UniqueTask(QString title,QDateTime disponibility,QDateTime deadline,QTime duration,bool preemptable):
    Task(title,disponibility,deadline),m_duration(duration),m_preemptable(preemptable)
{
    if(!preemptable && QTime(0, 0, 0).secsTo(duration)>=PREEMPT_TASK_MAX_DURATION*3600)
    {
        throw CalendarException("Une tache préemptable ne peux pas avoir une durée qui excède "+QString::number(PREEMPT_TASK_MAX_DURATION)+"h");
    }
}

UniqueTask::~UniqueTask()
{

}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void UniqueTask::setPreemptability(bool choice)
{
    if(QTime(0, 0, 0).secsTo(m_duration)>=PREEMPT_TASK_MAX_DURATION*3600 && !choice)        
        throw CalendarException("Une tache préemptable ne peux pas avoir une durée qui excède "+QString::number(PREEMPT_TASK_MAX_DURATION)+"h");
    else
        m_preemptable=choice;
}

void UniqueTask::setDuree(QTime duration)
{
    if(!m_preemptable && QTime(0, 0, 0).secsTo(duration)>=PREEMPT_TASK_MAX_DURATION*3600)
        throw CalendarException("Une tache préemptable ne peux pas avoir une durée qui excède "+QString::number(PREEMPT_TASK_MAX_DURATION)+"h");
    else
        m_duration=duration;
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
