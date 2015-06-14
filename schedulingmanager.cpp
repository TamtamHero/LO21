#include "schedulingmanager.h"

SchedulingManager::SchedulingManager()
{

}

SchedulingManager::~SchedulingManager()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


SchedulingManager::Handler SchedulingManager::m_handler=SchedulingManager::Handler(); //Initialization of handler


SchedulingManager& SchedulingManager::getInstance()
{
    if(m_handler.m_instance == 0)
    {
        m_handler.m_instance= new SchedulingManager;
    }
    return *(m_handler.m_instance);
}


void SchedulingManager::freeInstance()
{
    if(m_handler.m_instance != 0)
    {
        delete m_handler.m_instance;
    }
}


list<const Scheduling *> SchedulingManager::findTaskSchedulings(UniqueTask *element)
{
    list<const Scheduling *> results;
    for(list<Scheduling*>::iterator it=m_liste.begin();it!=m_liste.end();++it)
    {
        if((*it)->getTask()==element)
        {
            results.push_back((*it));
        }
    }
    return results;
}


void SchedulingManager::addElement(QDateTime date,QTime duration,QString title, bool import) // Add an activity
{
    if(duration<QTime::fromString("00:30:00"))
    {
        throw CalendarException("Vous ne pouvez pas créer une programmation de moins de 30 minutes");
    }

    QDateTime firstLimit,secondLimit;
    firstLimit=date.addSecs(QTime(0, 0, 0).secsTo(duration));

    for(list<Scheduling *>::iterator it=getList().begin();it!=getList().end();++it)
    {
        secondLimit=(*it)->getDateTime().addSecs(QTime(0, 0, 0).secsTo((*it)->getDuration()));
        if((*it)->getDateTime()<firstLimit && secondLimit>date)
        {
            throw CalendarException("Une task est déjà programmée sur cet intervalle");
        }
    }
    if(date.time().addSecs(QTime(0, 0, 0).secsTo(duration))<date.time())
    {
        throw CalendarException("Vous ne pouvez pas programmer une tache sur plusieurs jours consécutifs");
    }
    Scheduling *new_prog=new Scheduling(date,duration,title);
    AbstractContainer::addElement(new_prog);
}


void SchedulingManager::addElement(QDateTime date,QTime duration,UniqueTask* task,bool import) // Add a task
{
    if(duration<QTime::fromString("00:30:00"))
    {
        throw CalendarException("Vous ne pouvez pas créer une programmation de moins de 30 minutes");
    }
    else if(task==NULL)
    {
        throw CalendarException("Veuillez d'abord sélectionner une task");
    }
    else if(!task->arePrerequisiteScheduled() && !import)
    {
        throw CalendarException("Certains prérequis ne sont pas encore programmés, impossible de programmer cette task");
    }
    else
    {
        list<Task*> prerequisiteList=task->getAllUniquePrerequisite(); // Get list of all the UniqueTask that are a prerequisite of the task
        if(!prerequisiteList.empty())
        {
            list<const Scheduling*> prerequisiteSchedulings;
            foreach(Task* ptr,prerequisiteList)
            {

                prerequisiteSchedulings=findTaskSchedulings(dynamic_cast<UniqueTask*>(ptr)); //for each prerequisite, get a list of all its scheduling

                if(!prerequisiteSchedulings.empty())
                {
                    foreach(const Scheduling* prog_ptr,prerequisiteSchedulings) // for each scheduling, check
                    {
                        if(prog_ptr->getDateTime()>date)
                        {
                            throw CalendarException("La task "+prog_ptr->getTitle()+" est prérequise, mais est actuellement programmée antérieurement");
                        }
                    }
                }
            }
        }
    }

    if(!task->getPreemptability() && duration!=task->getDuree() && !import)
    {
        throw CalendarException("La task n'est pas préemptable, vous devez la programmer entièrement");
    }

    QDateTime firstLimit,secondLimit;
    firstLimit=date.addSecs(QTime(0, 0, 0).secsTo(duration));

    for(list<Scheduling *>::iterator it=getList().begin();it!=getList().end();++it)
    {
        secondLimit=(*it)->getDateTime().addSecs(QTime(0, 0, 0).secsTo((*it)->getDuration()));
        if((*it)->getDateTime()<firstLimit && secondLimit>date)
        {
            throw CalendarException("Une task est déjà programmée sur cet intervalle");
        }
    }
    if(date.time().addSecs(QTime(0, 0, 0).secsTo(duration))<date.time())
    {
        throw CalendarException("Vous ne pouvez pas programmer une tache sur plusieurs jours consécutifs");
    }
    Scheduling *new_prog=new Scheduling(date,duration,task);

    if(!import)
        task->setDuree(task->getDuree().addSecs(-QTime(0, 0, 0).secsTo(new_prog->getDuration())));
    else
        task->setDuree(task->getDuree().addSecs(QTime(0, 0, 0).secsTo(new_prog->getDuration())));

    if(task->getDuree()==QTime::fromString("00:00:00"))     // Status management
    {
        task->setStatus(true);

        if(task->getParent()!=NULL)
        {
            task->getParent()->setStatus(true);
            foreach(Task* ptr,static_cast<BlendTask*>(task->getParent())->getElement()) // after completion of a task, check if parent task has to be set completed too
            {
                if(!ptr->getStatus())
                {
                    task->getParent()->setStatus(false); //only one task not complete, and the parent is set as not complete
                }
            }
        }
    }

    AbstractContainer::addElement(new_prog);

}


void SchedulingManager::removeElement(Scheduling * element)
{
    try
    {
        list<Scheduling*>::iterator it2;
        for(list<Scheduling*>::iterator it=m_liste.begin();it!=m_liste.end();++it)
        {
            if((*it)==element)
            {
                it2=it;
                break;
            }
        }
        UniqueTask* ptr=element->getTask();
        if(ptr!=NULL)
        {
            while(it2!=m_liste.end())
            {
                foreach(Task* prerequisite,(*it2)->getTask()->getPrerequisite())
                {
                    if(prerequisite==ptr)
                    {
                        throw CalendarException("Vous ne pouvez pas supprimer cette programmation, la task "+prerequisite->getTitle()+" la recquiert et est déjà programmée");
                    }
                }
                it2++;
            }

            if(element!=NULL) //restore duration of task if unscheduled, and remove status of parent task
            {
                ptr->setDuree(ptr->getDuree().addSecs(QTime(0, 0, 0).secsTo(element->getDuration())));
                if(ptr->getParent()!=NULL)
                    ptr->getParent()->setStatus(false);
            }
        }
        m_liste.erase(std::remove(m_liste.begin(),m_liste.end(),element),m_liste.end());
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(NULL, "Erreur", error.getInfo());
    }
}

