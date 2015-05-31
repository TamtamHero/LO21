#include "programmation.h"

Programmation::Programmation(QDateTime date,QTime duree,QString titre):
    m_date(date),m_duree(duree),m_titre(titre)
{
    if(date < QDateTime::currentDateTime())
    {
        throw CalendarException("La date de la programmation est déjà passée !");
    }
}

Programmation::Programmation(QDateTime date,QTime duree,TacheUnitaire *tache):
    m_date(date),m_duree(duree)
{
    if(date < QDateTime::currentDateTime())
    {
        throw CalendarException("La date de la programmation est déjà passée !");
    }

    m_tache=tache;
    m_titre=m_tache->getTitre();

    // Il faudra voir si on réduit la durée de tache ici ou si on le fait ailleurs, dans l'agenda
}


Programmation::~Programmation()
{

}

//_-_-_-_-_-_-_-_OPERATOR OVERLOADS-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Programmation::operator<(const Programmation &b) const
{
    if(this->getDateTime()<=b.getDateTime())
    {
        return true;
    }
    return false;
}
