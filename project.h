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
    QDateTime m_echeance;
    vector<Task *> m_decomposition;
    vector<Task *> m_deadList; //Used to clean interconnection between Task when destructor is called.

    Project(const Project& source);
    Project& operator=(const Project& source);

    void fillDeadList(Task * element);
    void cleanPrerequisite(Task * element);

public:
    Project(QString title, QDateTime disponibility, QDateTime echeance);
    ~Project();

    void addElement(Task * element);
    void removeElement(Task * element);
    void deleteElement(Task * element);
    void afficher(QStandardItemModel * treeModel);
    QString getTitre(){return m_title;}
    void setTitle(QString title){m_title=title;}
    QDateTime getDisponibility(){return m_disponibility;}
    void setDisponibility(QDateTime disponibility){m_disponibility=disponibility;}
    QDateTime getDeadline()const {return m_echeance;}
    void setDeadline(QDateTime deadline){m_echeance=deadline;}

    bool operator < (const Project& b) const;
    bool operator == (const Project& b) const;


};


#endif // PROJECT_H
