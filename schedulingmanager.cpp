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


void SchedulingManager::addElement(Programmation * element)
{
    m_liste.push_back(element);
    sort();
}


void SchedulingManager::removeElement(Programmation * element)
{
    m_liste.erase(std::remove(m_liste.begin(),m_liste.end(),element),m_liste.end());
}


Programmation* SchedulingManager::findElement(Programmation *element)
{
    comparator a;
    a.toFind=element;
    list<Programmation*>::iterator it=std::find_if(m_liste.begin(),m_liste.end(),a);
    if(it!=m_liste.end())
    {
        return (*it);
    }
    return NULL;
}


void SchedulingManager::sort()
{
    m_liste.sort(ProgrammationIsInferior());
}
