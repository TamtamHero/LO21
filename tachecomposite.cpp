#include "tachecomposite.h"

TacheComposite::TacheComposite(QString titre,QDateTime disponibilite,QDateTime echeance):
    Tache(titre,disponibilite,echeance)
{
    // Useless pour l'instant, le constructeur de la classe mère Tache fait tout le travail.
}

TacheComposite::~TacheComposite()
{
    for(unsigned long i=0;i<m_element.size();i++)
    {
        delete(m_element[i]);   // Est-ce la meilleure manière de détruire une tache composite ?``
        m_element[i]=0;
    }
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void TacheComposite::addElement(Tache * element)
{
    if(element==this)
    {
        throw CalendarException("Tentative avortée d'auto-inclusion"); // A verifier: est-ce utile ?
    }
    m_element.push_back(element);
    std::sort(m_element.begin(),m_element.end(),taskCompare());
    element->setParent(this);
}

void TacheComposite::afficher(QStandardItem * parent)
{
    QStandardItem *item;

    for(vector<Tache *>::iterator it=this->m_element.begin();it!=this->m_element.end();++it)
    {
        item=new QStandardItem((*it)->getTitre());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
        parent->appendRow(item);
        (*it)->afficher(item);

    }
}


