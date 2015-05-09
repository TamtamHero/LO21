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


void ProjectManager::addProject(Projet * projet)
{
    m_liste.push_back(projet);
}

void ProjectManager::Afficher(QStandardItemModel * modele)
{
    QStandardItem *item;

    for(vector<Projet *>::iterator it=this->m_liste.begin();it!=this->m_liste.end();++it)
    {
        item=new QStandardItem((*it)->getTitre());
        modele->appendRow(item);
    }
}