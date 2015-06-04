#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <QString>
#include <QDateTime>
#include "uniquetask.h"

class Scheduling
{
protected:
    QDateTime m_date;
    QTime m_duree;
    QString m_titre;
    UniqueTask *m_task;

public:
    Scheduling(QDateTime date,QTime duree,QString titre);
    Scheduling(QDateTime date,QTime duree,UniqueTask *task);
    ~Scheduling();

    QDateTime getDateTime()const {return m_date;}
    QString getTitle()const{return m_titre;}
    QTime getDuration(){return m_duree;}
    UniqueTask* getTask(){return m_task;}
    bool operator < (const Scheduling& b) const;

};

#endif // SCHEDULING_H
