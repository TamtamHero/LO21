#ifndef TASK_H
#define TASK_H

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QVariant>

#include "calendarexception.h"

enum tabValue{EDIT,CREATION};

using namespace std;

class Task
{

protected:
    QString m_title;
    QDateTime m_disponibility;
    QDateTime m_echeance;
    bool m_status; // false if not done, true if done
    Task* m_parent;
    vector<Task*> m_prerequisite;
    Task(QString title,QDateTime disponibility,QDateTime echeance);

    Task(const Task& source);
    Task& operator=(const Task& source);

public:
    void setParent(Task * parent){m_parent=parent;}
    Task* getParent()const{ return m_parent;}
    QString getTitre()const{return m_title;}
    void setTitle(QString title){m_title=title;}
    QDateTime getDisponibility()const{return m_disponibility;}
    void setDisponibility(QDateTime disponibility){m_disponibility=disponibility;}
    QDateTime getDeadline() const{return m_echeance;}
    void setDeadline(QDateTime deadline){m_echeance=deadline;}
    vector<Task*>& getPrerequisite(){return m_prerequisite;}
    void setStatus(bool status){m_status=status;}
    bool getStatus(){return m_status;}
    void addPrerequisite(Task * prerequisite);
    virtual void afficher(QStandardItem * parent)=0;
    bool arePrerequisiteScheduled();

    static bool checkPrerequisite(Task* task,Task * prerequisiteTask);
    static bool checkAttaskdTo(Task* task,Task * motherTask);
    bool operator < (const Task& b) const;

    struct taskCompare
    {
          bool operator()(const Task* l, const Task* r)
          {
            return *l < *r;
          }
    };

    virtual ~Task()=0;

};


Q_DECLARE_METATYPE(Task *)

#endif // TASK_H
