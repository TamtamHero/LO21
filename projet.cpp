#include "projet.h"
#include "mainwindow.h"


Projet::Projet(QString titre, QDateTime disponibilite, QDateTime echeance):
    m_titre(titre),m_disponibilite(disponibilite),m_echeance(echeance)
{
    if(echeance < QDateTime::currentDateTime())
    {
        throw CalendarException("Echéance du projet déjà passée !");
    }
    else if(echeance < disponibilite)
    {
        throw CalendarException("La disponibilité entrée pour le projet est ultérieure à l'échéance !");
    }
}

Projet::~Projet()
{
    for(vector<Tache*>::iterator it=m_decomposition.begin(); it!=m_decomposition.end(); ++it)
    {
        delete(*it);
    }
}

void Projet::addElement(Tache * element)
{
    m_decomposition.push_back(element);
}

void Projet::fillDeadList(Tache * element)
{
    m_deadList.push_back(element);

    if(dynamic_cast<TacheComposite*>(element)!=NULL)
    {
        TacheComposite* composite=dynamic_cast<TacheComposite*>(element);
        for(vector<Tache*>::iterator it=composite->getElement().begin(); it!=composite->getElement().end(); ++it)
        {
            fillDeadList(*it);
        }
    }

}

void Projet::cleanPrerequisite(Tache * element)
{
    for(vector<Tache*>::iterator it=element->getPrerequisite().begin(); it!=element->getPrerequisite().end(); ++it)
    {
        for(vector<Tache*>::iterator it2=m_deadList.begin(); it2!=m_deadList.end(); ++it2)
        {
            if(*it==*it2)
            {
                element->getPrerequisite().erase(it);
                it--;
            }
        }
    }

    if(dynamic_cast<TacheComposite*>(element)!=NULL)
    {
        TacheComposite* composite=dynamic_cast<TacheComposite*>(element);
        for(vector<Tache*>::iterator it=composite->getElement().begin(); it!=composite->getElement().end(); ++it)
        {
            cleanPrerequisite(*it);
        }
    }
}

void Projet::deleteElement(Tache * element)
{
    /*
    1) faire la liste des taches et sous taches à nettoyer -> filldeadlist
    2)chercher si UNE tache contient la tache sommet dans sa décomposition, supprimer ce pointeur
    3)chercher dans tout les élements du projets si des liste de prérequis contiennent des élements de la dead list
    4)détruire la tache sommet (qui va détruire les sous taches)
    */


    if(dynamic_cast<TacheComposite*>(element->getParent())!=NULL) //remove element from blendTask
    {
        vector<Tache*>& p_parent=dynamic_cast<TacheComposite*>(element->getParent())->getElement();
        p_parent.erase(std::remove(p_parent.begin(),p_parent.end(),element),p_parent.end());
    }
    else //remove element from project's root
    {
        m_decomposition.erase(std::remove(m_decomposition.begin(),m_decomposition.end(),element),m_decomposition.end());
    }

    fillDeadList(element); //Make a list of tasks to be cleaned out

    for(vector<Tache*>::iterator it=m_decomposition.begin(); it!=m_decomposition.end(); ++it)
    {
        cleanPrerequisite(*it);
    }

    delete element; //Delete the head task and its subtasks
}



void Projet::afficher(QStandardItemModel * treeModel)
{
    QStandardItem *item;

    for(vector<Tache *>::iterator it=this->m_decomposition.begin();it!=this->m_decomposition.end();++it)
    {
        item=new QStandardItem((*it)->getTitre());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+1);
        treeModel->appendRow(item);
        (*it)->afficher(item);

    }
}


