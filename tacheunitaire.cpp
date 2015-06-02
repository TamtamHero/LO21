#include "tacheunitaire.h"
#include <iostream>

TacheUnitaire::TacheUnitaire(QString titre,QDateTime disponibilite,QDateTime echeance,QTime duree,bool preemptable):
    Tache(titre,disponibilite,echeance),m_duree(duree),m_preemptable(preemptable)
{
    if(m_preemptable && m_duree>QTime::fromString("12:00:00"))
    {
        throw CalendarException("Tache unitaire trop longue ! (12H max.) ");
    }
}

TacheUnitaire::~TacheUnitaire()
{
    this->setDuree(QTime::fromString("15:00:00"));
}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void TacheUnitaire::afficher(QStandardItem * parent)
{

}

list<Tache*> TacheUnitaire::getAllUniquePrerequisite()
{
    list<Tache*> result,part;
    for(vector<Tache *>::iterator it=this->m_prerequisite.begin();it!=this->m_prerequisite.end();++it)
    {
        if(dynamic_cast<TacheUnitaire*>((*it))!=NULL)
        {
            result.push_back((*it));
        }
        else
        {
            part=dynamic_cast<TacheComposite*>((*it))->getAllUniqueSons();
            result.merge(part);
        }
    }

    if(getParent()!=NULL)
    {
        part=dynamic_cast<TacheComposite*>(getParent())->getAllUniquePrerequisite();
        result.merge(part);
    }

    return result;
}
