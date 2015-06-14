#ifndef UNIQUETASK_H
#define UNIQUETASK_H
#define PREEMPT_TASK_MAX_DURATION 12

#include "task.h"
#include "blendtask.h"
#include <QVariant>


class UniqueTask: public Task
{

protected:
    QTime m_duration;
    bool m_preemptable;

public:
    UniqueTask(QString title,QDateTime disponibility,QDateTime deadline,QTime duration,bool preemptable=false);
    QTime getDuree() const {return m_duration;}
    bool getPreemptability(){return m_preemptable;}
    void setDuree(QTime duration);
    void setPreemptability(bool choice);
    void display(QStandardItem * parent);
    list<Task *> getAllUniquePrerequisite();

    virtual ~UniqueTask();
};

Q_DECLARE_METATYPE(UniqueTask *)

#endif // UNIQUETASK_H
