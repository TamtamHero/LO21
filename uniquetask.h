#ifndef UNIQUETASK_H
#define UNIQUETASK_H

#include "task.h"
#include "blendtask.h"
#include <QVariant>


class UniqueTask: public Task
{

protected:
    QTime m_duration;
    bool m_preemptable;

public:
    UniqueTask(QString title,QDateTime disponibility,QDateTime echeance,QTime duration,bool preemptable=false);
    QTime getDuree() const {return m_duration;}
    bool getPreemptability(){return m_preemptable;}
    void setDuree(QTime duration) {m_duration=duration;}
    void setPreemptability(bool choice){m_preemptable=choice;}
    void afficher(QStandardItem * parent);
    list<Task *> getAllUniquePrerequisite();

    virtual ~UniqueTask();
};

Q_DECLARE_METATYPE(UniqueTask *)

#endif // UNIQUETASK_H
