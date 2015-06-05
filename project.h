#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QStandardItemModel>
#include "task.h"
#include "blendtask.h"


class Project
{
protected:
    QString m_title;
    QDateTime m_disponibility;
    QDateTime m_deadline;
    vector<Task *> m_list;
    vector<Task *> m_deadList; //Used to clean interconnection between Task when destructor is called.

    Project(const Project& source);
    Project& operator=(const Project& source);

    void fillDeadList(Task * element);
    void cleanPrerequisite(Task * element);

    friend class AbstractBuilder;

public:
    Project(QString title, QDateTime disponibility, QDateTime deadline);
    ~Project();

    void addElement(Task * element);
    void removeElement(Task * element);
    void deleteElement(Task * element);
    void display(QStandardItemModel * treeModel);
    QString getTitle(){return m_title;}
    void setTitle(QString title){m_title=title;}
    QDateTime getDisponibility(){return m_disponibility;}
    void setDisponibility(QDateTime disponibility){m_disponibility=disponibility;}
    QDateTime getDeadline()const {return m_deadline;}
    void setDeadline(QDateTime deadline){m_deadline=deadline;}
    const vector<Task *>& getList(){return m_list;}


    bool operator < (const Project& b) const;
    bool operator == (const Project& b) const;


};


#endif // PROJECT_H
