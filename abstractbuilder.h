#ifndef ABSTRACTBUILDER_H
#define ABSTRACTBUILDER_H

#include<QString>
#include"scheduling.h"
#include"project.h"


class AbstractBuilder
{
protected:
    QString m_file_path;
public:
    AbstractBuilder(QString path):m_file_path(path){}
    ~AbstractBuilder();

    virtual void writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list)=0;
    virtual void readInput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list)=0;
};

#endif // ABSTRACTBUILDER_H
