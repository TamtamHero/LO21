#include "scheduling.h"

Scheduling::Scheduling(QDateTime date,QTime duree,QString titre):
    m_date(date),m_duree(duree),m_titre(titre),m_task(NULL)
{
    if(date < QDateTime::currentDateTime())
    {
        throw CalendarException("La date de la programmation est déjà passée !");
    }
}

Scheduling::Scheduling(QDateTime date,QTime duree,UniqueTask *task):
    m_date(date),m_duree(duree)
{
    if(date < QDateTime::currentDateTime())
    {
        throw CalendarException("La date de la programmation est déjà passée !");
    }

    m_task=task;
    m_titre=m_task->getTitre();

    // Il faudra voir si on réduit la durée de task ici ou si on le fait ailleurs, dans l'agenda
}


Scheduling::~Scheduling()
{

}

//_-_-_-_-_-_-_-_OPERATOR OVERLOADS-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool Scheduling::operator<(const Scheduling &b) const
{
    if(this->getDateTime()<=b.getDateTime())
    {
        return true;
    }
    return false;
}

