#include "projet.h"
#include "qtache.h"
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

}

void Projet::addSousTache(Tache * sousTache)
{
    m_decomposition.push_back(sousTache);
}

void Projet::afficher(QStandardItemModel * modele)
{
    QTache *item;

    for(vector<Tache *>::iterator it=this->m_decomposition.begin();it!=this->m_decomposition.end();++it)
    {
        item=new QTache((*it)->getTitre(),*it);
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+1);
        modele->appendRow(item);
        item->getTache()->afficher(item);

    }
}


