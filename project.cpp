#include "project.h"
#include "mainwindow.h"


Project::Project(QString title, QDateTime disponibility, QDateTime deadline):
    m_title(title),m_disponibility(disponibility),m_deadline(deadline)
{
    if(deadline < disponibility)
    {
        throw CalendarException("La disponibilité entrée pour le projet est ultérieure à l'échéance !");
    }
}

Project::~Project()
{
    for(vector<Task*>::iterator it=m_list.begin(); it!=m_list.end(); ++it)
    {
        delete(*it);
    }
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void Project::addElement(Task * element)
{
    m_list.push_back(element);
    std::sort(m_list.begin(),m_list.end(),Task::taskCompare());
}

void Project::removeElement(Task * element)
{
    m_list.erase(std::remove(m_list.begin(),m_list.end(),element),m_list.end());
    std::sort(m_list.begin(),m_list.end());
}

void Project::fillDeadList(Task * element)
{
    m_deadList.push_back(element);

    if(dynamic_cast<BlendTask*>(element)!=NULL)
    {
        BlendTask* composite=dynamic_cast<BlendTask*>(element);
        for(vector<Task*>::iterator it=composite->getElement().begin(); it!=composite->getElement().end(); ++it)
        {
            fillDeadList(*it);
        }
    }

}

void Project::cleanPrerequisite(Task * element)
{
    for(vector<Task*>::iterator it=element->getPrerequisite().begin(); it!=element->getPrerequisite().end(); ++it)
    {
        for(vector<Task*>::iterator it2=m_deadList.begin(); it2!=m_deadList.end(); ++it2)
        {
            if(*it==*it2)
            {
                element->getPrerequisite().erase(it);
                it--;
            }
        }
    }

    if(dynamic_cast<BlendTask*>(element)!=NULL)
    {
        BlendTask* composite=dynamic_cast<BlendTask*>(element);
        for(vector<Task*>::iterator it=composite->getElement().begin(); it!=composite->getElement().end(); ++it)
        {
            cleanPrerequisite(*it);
        }
    }
}

void Project::deleteElement(Task * element)
{
    /*
    1) faire la liste des tasks et sous tasks à nettoyer -> filldeadlist
    2)chercher si UNE task contient la task sommet dans sa décomposition, supprimer ce pointeur
    3)chercher dans tout les élements du projets si des liste de prérequis contiennent des élements de la dead list
    4)détruire la task sommet (qui va détruire les sous tasks)
    */


    if(dynamic_cast<BlendTask*>(element->getParent())!=NULL) //remove element from blendTask
    {
        vector<Task*>& p_parent=dynamic_cast<BlendTask*>(element->getParent())->getElement();
        p_parent.erase(std::remove(p_parent.begin(),p_parent.end(),element),p_parent.end());
    }
    else //remove element from project's root
    {
        m_list.erase(std::remove(m_list.begin(),m_list.end(),element),m_list.end());
    }

    fillDeadList(element); //Make a list of tasks to be cleaned out

    for(vector<Task*>::iterator it=m_list.begin(); it!=m_list.end(); ++it)
    {
        cleanPrerequisite(*it);
    }

    delete element; //Delete the head task and its subtasks
}



void Project::display(QStandardItemModel * m_treeModel)
{
    QStandardItem *item;

    for(vector<Task *>::iterator it=this->m_list.begin();it!=this->m_list.end();++it)
    {
        item=new QStandardItem((*it)->getTitle());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
        m_treeModel->appendRow(item);
        if(dynamic_cast<BlendTask*>((*it))!=NULL)
        {
            dynamic_cast<BlendTask*>((*it))->display(item);
        }

    }
}

//_-_-_-_-_-_-_-_OPERATOR OVERLOADS-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Project::operator<(const Project &b) const
{
    if(this->getDeadline()<=b.getDeadline())
    {
        return true;
    }
    return false;
}
