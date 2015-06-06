#ifndef XMLBUILDER_H
#define XMLBUILDER_H
#include<QXmlStreamWriter>
#include<QFile>
#include <QDomDocument>


#include"abstractbuilder.h"


class XmlBuilder : public AbstractBuilder
{
public:
    XmlBuilder(QString file_path):AbstractBuilder(file_path){}
    ~XmlBuilder();

    void writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list);
    void saveTask(QXmlStreamWriter& stream, Task * task);
    void readInput(ProjectManager &projectManager, SchedulingManager &schedulingManager);
    void readTask(QDomNode task_node,BlendTask* task_ptr);
};

#endif // XMLBUILDER_H
