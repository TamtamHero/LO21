#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <QString>
#include <QDateTime>
#include "uniquetask.h"

class Scheduling
{
protected:
    QDateTime m_date;
    QTime m_duration;
    QString m_title;
    UniqueTask *m_task;

public:
    Scheduling(QDateTime date,QTime duration,QString title);
    Scheduling(QDateTime date,QTime duration,UniqueTask *task);
    ~Scheduling();

    QDateTime getDateTime()const {return m_date;}
    QString getTitle()const{return m_title;}
    QTime getDuration(){return m_duration;}
    UniqueTask* getTask(){return m_task;}
    bool operator < (const Scheduling& b) const;

};

#endif // SCHEDULING_Hd
