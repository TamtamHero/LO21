#ifndef ABSTRACTBUILDER_H
#define ABSTRACTBUILDER_H

#include<QString>
#include "schedulingmanager.h"
#include "projectmanager.h"


class AbstractBuilder
{
protected:
    QString m_file_path;
    std::map<Task*,int> m_pointer_to_id;
    std::map<int,Task*> m_id_to_pointer;
    int m_id_incrementer;

public:
    AbstractBuilder(QString path):m_file_path(path),m_id_incrementer(0){}
    ~AbstractBuilder();

    virtual void writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list)=0;
    virtual void readInput(ProjectManager &projectManager, SchedulingManager &schedulingManager)=0;
};

#endif // ABSTRACTBUILDER_H
