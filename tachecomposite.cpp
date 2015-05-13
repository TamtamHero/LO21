#include "tachecomposite.h"

TacheComposite::TacheComposite(QString titre,QDateTime disponibilite,QDateTime echeance):
    Tache(titre,disponibilite,echeance)
{
    // Useless pour l'instant, le constructeur de la classe mère Tache fait tout le travail.
}

TacheComposite::~TacheComposite()
{
    for(int i=0;i<m_sousTache.size();i++)
    {
        delete(m_sousTache[i]);   // Est-ce la meilleure manière de détruire une tache composite ?
        m_sousTache[i]=0;
    }
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void TacheComposite::addSousTache(Tache * sousTache)
{
    if(sousTache==this)
    {
        throw CalendarException("Tentative avortée d'auto-inclusion"); // A verifier: est-ce utile ?
    }
    m_sousTache.push_back(sousTache);
}

void TacheComposite::afficher(QStandardItem * parent)
{
    QTache *item;

    for(vector<Tache *>::iterator it=this->m_sousTache.begin();it!=this->m_sousTache.end();++it)
    {
        //item=new QTache(*it);
        item=new QTache((*it)->getTitre(),*it);
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+1);
        parent->appendRow(item);
        item->getTache()->afficher(item);

    }
}


