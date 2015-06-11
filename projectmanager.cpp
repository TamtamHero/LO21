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

void ProjectManager::addElement(QString title, QDateTime disponibility, QDateTime deadline)
{
    Project * element=new Project(title,disponibility,deadline);
    m_liste.push_back(element);
    sort();
}

void ProjectManager::display(QStandardItemModel * model)
{
    QStandardItem *item;

    for(list<Project *>::iterator it=this->m_liste.begin();it!=this->m_liste.end();++it)
    {
        item=new QStandardItem((*it)->getTitle());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+1);
        model->appendRow(item);
    }
}
