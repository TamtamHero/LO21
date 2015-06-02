#include "projectmanager.h"

ProjectManager::ProjectManager()
{

}

ProjectManager::~ProjectManager()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

ProjectManager::Handler ProjectManager::m_handler=ProjectManager::Handler(); //Initialization of handler

ProjectManager& ProjectManager::getInstance()
{
    if(m_handler.m_instance == 0)
    {
        m_handler.m_instance= new ProjectManager;
    }
    return *(m_handler.m_instance);
}

void ProjectManager::freeInstance()
{
    if(m_handler.m_instance != 0)
    {
        delete m_handler.m_instance;
    }
}

void ProjectManager::addElement(Projet * element)
{
    m_liste.push_back(element);
    sort();
}

void ProjectManager::removeElement(Projet * element)
{
    m_liste.erase(std::remove(m_liste.begin(),m_liste.end(),element),m_liste.end());
}

void ProjectManager::sort()
{
    m_liste.sort(ProjectIsSooner());
}

void ProjectManager::Afficher(QStandardItemModel * model)
{
    QStandardItem *item;

    for(list<Projet *>::iterator it=this->m_liste.begin();it!=this->m_liste.end();++it)
    {
        item=new QStandardItem((*it)->getTitre());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+1);
        model->appendRow(item);
    }
}
