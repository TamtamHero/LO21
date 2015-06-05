#include "xmlbuilder.h"

XmlBuilder::~XmlBuilder()
{

}


void XmlBuilder::writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list)
{
    int id_incrementer=1;
    std::map<Task*,int> pointer_to_id;
    QFile newfile(m_file_path);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    }
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    foreach(Project* project,project_list)
    {
        stream.writeStartElement("project");
        stream.writeTextElement("title",project->getTitle());
        stream.writeTextElement("disponibility",project->getDisponibility().toString(Qt::ISODate));
        stream.writeTextElement("deadline",project->getDeadline().toString(Qt::ISODate));
        foreach(Task* task,project->getList())
        {
            saveTask(stream,task,pointer_to_id,id_incrementer);
        }

        stream.writeEndElement();
    }

    foreach(Scheduling* scheduling,scheduling_list)
    {
        stream.writeStartElement("scheduling");
        stream.writeTextElement("title",scheduling->getTitle());
        stream.writeTextElement("date",scheduling->getDateTime().toString(Qt::ISODate));
        stream.writeTextElement("duration",scheduling->getDuration().toString(Qt::ISODate));
        stream.writeTextElement("task_id",QString::number(pointer_to_id[scheduling->getTask()]));

        stream.writeEndElement();
    }


    stream.writeEndDocument();
    newfile.close();
}

void XmlBuilder::saveTask(QXmlStreamWriter& stream,Task * task,std::map<Task*,int>& pointer_to_id,int& id_incrementer)
{
    if(pointer_to_id[task]==0)
    {
        pointer_to_id[task]=++id_incrementer;
    }
    stream.writeStartElement("task");
    stream.writeTextElement("title",task->getTitle());
    stream.writeTextElement("id",QString::number(id_incrementer));
    stream.writeTextElement("disponibility",task->getDisponibility().toString(Qt::ISODate));
    stream.writeTextElement("deadline",task->getDeadline().toString(Qt::ISODate));
    foreach(Task* prerequisite,task->getPrerequisite())
    {
        if(pointer_to_id[prerequisite]!=0)
        {
            stream.writeTextElement("prerequisite_id",QString::number(pointer_to_id[prerequisite]));
        }
        else
        {
            pointer_to_id[prerequisite]=++id_incrementer;
            stream.writeTextElement("prerequisite_id",QString::number(pointer_to_id[prerequisite]));
        }
    }
    if(dynamic_cast<BlendTask*>(task)!=NULL)
    {
        foreach(Task * sub_task,dynamic_cast<BlendTask*>(task)->getElement())
        {
            saveTask(stream,sub_task,pointer_to_id,id_incrementer);
        }
    }
    stream.writeEndElement();
}


void XmlBuilder::readInput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list)
{

}
