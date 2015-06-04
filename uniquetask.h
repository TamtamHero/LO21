#ifndef UNIQUETASK_H
#define UNIQUETASK_H

#include "task.h"
#include "blendtask.h"
#include <QVariant>


class UniqueTask: public Task
{

protected:
    QTime m_duree;
    bool m_preemptable;

public:
    UniqueTask(QString titre,QDateTime disponibility,QDateTime echeance,QTime duree,bool preemptable=false);
    QTime getDuree() const {return m_duree;}
    bool getPreemptability(){return m_preemptable;}
    void setDuree(QTime duree) {m_duree=duree;}
    void setPreemptability(bool choice){m_preemptable=choice;}
    void afficher(QStandardItem * parent);
    list<Task *> getAllUniquePrerequisite();

    virtual ~UniqueTask();
};

Q_DECLARE_METATYPE(UniqueTask *)

#endif // UNIQUETASK_H
