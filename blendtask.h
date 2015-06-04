#ifndef BLENDTASK_H
#define BLENDTASK_H

#include "task.h"
#include "uniquetask.h"
#include <QVariant>


class BlendTask: public Task
{

protected:
    vector<Task *> m_element;

public:
    BlendTask(QString titre,QDateTime disponibility,QDateTime echeance);
    void addElement(Task * element);
    vector<Task *>& getElement(){return m_element;}
    void afficher(QStandardItem * parent);
    list<Task*> getAllUniquePrerequisite();
    list<Task*> getAllUniqueSons();
    virtual ~BlendTask();
};

Q_DECLARE_METATYPE(BlendTask *)

#endif // BLENDTASK_H
