#include "scheduling.h"

Scheduling::Scheduling(QDateTime date,QTime duration,QString title):
    m_date(date),m_duration(duration),m_title(title),m_task(NULL)
{
    if(date < QDateTime::currentDateTime())
    {
        throw CalendarException("La date de la programmation est déjà passée !");
    }
}

Scheduling::Scheduling(QDateTime date,QTime duration,UniqueTask *task):
    m_date(date),m_duration(duration)
{
    if(date < QDateTime::currentDateTime())
    {
        throw CalendarException("La date de la programmation est déjà passée !");
    }

    m_task=task;
    m_title=m_task->getTitle();

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

