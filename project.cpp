#include "project.h"
#include "mainwindow.h"


Project::Project(QString titre, QDateTime disponibility, QDateTime echeance):
    m_titre(titre),m_disponibility(disponibility),m_echeance(echeance)
{
    if(echeance < QDateTime::currentDateTime())
    {
        throw CalendarException("Echéance du projet déjà passée !");
    }
    else if(echeance < disponibility)
    {
        throw CalendarException("La disponibilité entrée pour le projet est ultérieure à l'échéance !");
    }
}

Project::~Project()
{
    for(vector<Task*>::iterator it=m_decomposition.begin(); it!=m_decomposition.end(); ++it)
    {
        delete(*it);
    }
}

void Project::addElement(Task * element)
{
    m_decomposition.push_back(element);
    std::sort(m_decomposition.begin(),m_decomposition.end(),Task::taskCompare());
}

void Project::removeElement(Task * element)
{
    m_decomposition.erase(std::remove(m_decomposition.begin(),m_decomposition.end(),element),m_decomposition.end());
    std::sort(m_decomposition.begin(),m_decomposition.end());
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
        m_decomposition.erase(std::remove(m_decomposition.begin(),m_decomposition.end(),element),m_decomposition.end());
    }

    fillDeadList(element); //Make a list of tasks to be cleaned out

    for(vector<Task*>::iterator it=m_decomposition.begin(); it!=m_decomposition.end(); ++it)
    {
        cleanPrerequisite(*it);
    }

    delete element; //Delete the head task and its subtasks
}



void Project::afficher(QStandardItemModel * treeModel)
{
    QStandardItem *item;

    for(vector<Task *>::iterator it=this->m_decomposition.begin();it!=this->m_decomposition.end();++it)
    {
        item=new QStandardItem((*it)->getTitre());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
        treeModel->appendRow(item);
        (*it)->afficher(item);

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
