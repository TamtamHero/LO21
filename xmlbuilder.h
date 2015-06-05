#ifndef XMLBUILDER_H
#define XMLBUILDER_H
#include<QXmlStreamWriter>
#include<QFile>

#include"abstractbuilder.h"

class XmlBuilder : public AbstractBuilder
{
public:
    XmlBuilder(QString file_path):AbstractBuilder(file_path){}
    ~XmlBuilder();

    void writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list);
    void saveTask(QXmlStreamWriter& stream,Task * task,std::map<Task*,int>& pointer_to_id,int& id_incrementer);
    void readInput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list);
};

#endif // XMLBUILDER_H
