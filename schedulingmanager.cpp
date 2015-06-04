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


list<const Programmation *> SchedulingManager::findTaskSchedulings(TacheUnitaire *element)
{
    list<const Programmation *> results;
    for(list<Programmation*>::iterator it=m_liste.begin();it!=m_liste.end();++it)
    {
        if((*it)->getTask()==element)
        {
            results.push_back((*it));
        }
    }
    return results;
}


void SchedulingManager::addElement(QDateTime date,QTime duree,QString titre) // Add an activity
{
    if(duree<QTime::fromString("00:30:00"))
    {
        throw CalendarException("Vous ne pouvez pas créer une programmation de moins de 30 minutes");
    }

    QDateTime firstLimit,secondLimit;
    firstLimit=date.addSecs(QTime(0, 0, 0).secsTo(duree));

    for(list<Programmation *>::iterator it=getList().begin();it!=getList().end();++it)
    {
        secondLimit=(*it)->getDateTime().addSecs(QTime(0, 0, 0).secsTo((*it)->getDuration()));
        if((*it)->getDateTime()<firstLimit && secondLimit>date)
        {
            throw CalendarException("Une tache est déjà programmée sur cet intervalle");
        }
    }
    if(date.time().addSecs(QTime(0, 0, 0).secsTo(duree))<QTime::fromString("08:00:00"))
    {
        throw CalendarException("Vous ne pouvez pas programmer une tache après minuit");
    }
    Programmation *new_prog=new Programmation(date,duree,titre);
    AbstractManager::addElement(new_prog);
}


void SchedulingManager::addElement(QDateTime date,QTime duree,TacheUnitaire* tache) // Add a task
{
    if(duree<QTime::fromString("00:30:00"))
    {
        throw CalendarException("Vous ne pouvez pas créer une programmation de moins de 30 minutes");
    }
    else if(tache==NULL)
    {
        throw CalendarException("Veuillez d'abord sélectionner une tache");
    }
    else if(!tache->arePrerequisiteScheduled())
    {
        throw CalendarException("Certains prérequis ne sont pas encore programmés, impossible de programmer cette tache");
    }
    else
    {
        list<Tache*> prerequisiteList=tache->getAllUniquePrerequisite(); // Get list of all the UniqueTask that are a prerequisite of the task
        if(!prerequisiteList.empty())
        {
            list<const Programmation*> prerequisiteSchedulings;
            foreach(Tache* ptr,prerequisiteList)
            {

                prerequisiteSchedulings=findTaskSchedulings(dynamic_cast<TacheUnitaire*>(ptr)); //for each prerequisite, get a list of all its scheduling

                if(!prerequisiteSchedulings.empty())
                {
                    foreach(const Programmation* prog_ptr,prerequisiteSchedulings) // for each scheduling, check
                    {
                        if(prog_ptr->getDateTime()>date)
                        {
                            throw CalendarException("La tache "+prog_ptr->getTitle()+" est prérequise, mais est actuellement programmée antérieurement");
                        }
                    }
                }
            }
        }
    }

    if(!tache->getPreemptability() && duree!=tache->getDuree())
    {
        throw CalendarException("La tache n'est pas préemptable, vous devez la programmer entièrement");
    }

    QDateTime firstLimit,secondLimit;
    firstLimit=date.addSecs(QTime(0, 0, 0).secsTo(duree));

    for(list<Programmation *>::iterator it=getList().begin();it!=getList().end();++it)
    {
        secondLimit=(*it)->getDateTime().addSecs(QTime(0, 0, 0).secsTo((*it)->getDuration()));
        if((*it)->getDateTime()<firstLimit && secondLimit>date)
        {
            throw CalendarException("Une tache est déjà programmée sur cet intervalle");
        }
    }
    if(date.time().addSecs(QTime(0, 0, 0).secsTo(duree))<QTime::fromString("08:00:00"))
    {
        throw CalendarException("Vous ne pouvez pas programmer une tache après minuit");
    }
    Programmation *new_prog=new Programmation(date,duree,tache);

    tache->setDuree(tache->getDuree().addSecs(-QTime(0, 0, 0).secsTo(new_prog->getDuration())));
    if(tache->getDuree()==QTime::fromString("00:00:00"))     // Status management
    {
        tache->setStatus(true);
        tache->getParent()->setStatus(true);
        foreach(Tache* ptr,static_cast<TacheComposite*>(tache->getParent())->getElement()) // after completion of a task, check if parent task has to be set completed too
        {
            if(!ptr->getStatus())
            {
                tache->getParent()->setStatus(false); //only one task not complete, and the parent is set as not complete
            }
        }
    }

    AbstractManager::addElement(new_prog);

}


void SchedulingManager::removeElement(Programmation * element)
{
    try
    {
        list<Programmation*>::iterator it2;
        for(list<Programmation*>::iterator it=m_liste.begin();it!=m_liste.end();++it)
        {
            if((*it)==element)
            {
                it2=it;
                break;
            }
        }
        TacheUnitaire* ptr=element->getTask();
        while(it2!=m_liste.end())
        {
            foreach(Tache* prerequisite,(*it2)->getTask()->getPrerequisite())
            {
                if(prerequisite==ptr)
                {
                    throw CalendarException("Vous ne pouvez pas supprimer cette programmation, la tache "+prerequisite->getTitre()+" la recquiert et est déjà programmée");
                }
            }
            it2++;
        }

        if(element!=NULL) //restore duration of task if unscheduled, and remove status of parent task
        {
            ptr->setDuree(ptr->getDuree().addSecs(QTime(0, 0, 0).secsTo(element->getDuration())));
            ptr->getParent()->setStatus(false);
        }
        m_liste.erase(std::remove(m_liste.begin(),m_liste.end(),element),m_liste.end());
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(NULL, "Erreur", error.getInfo());
    }
}
