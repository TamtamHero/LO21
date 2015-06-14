#include "xmlbuilder.h"

XmlBuilder::~XmlBuilder()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void XmlBuilder::writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list)
{
    QFile output(m_file_path);
    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    }
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("xml_data");
    stream.writeStartElement("projects");
    foreach(Project* project,project_list)
    {
        stream.writeStartElement("project");
        stream.writeTextElement("title",project->getTitle());
        stream.writeTextElement("disponibility",project->getDisponibility().toString(Qt::ISODate));
        stream.writeTextElement("deadline",project->getDeadline().toString(Qt::ISODate));

        stream.writeStartElement("tasks");
        foreach(Task* task,project->getList())
        {
            saveTask(stream,task);
        }
        stream.writeEndElement();
        stream.writeEndElement();
    }
    stream.writeEndElement();

    stream.writeStartElement("schedulings");
    foreach(Scheduling* scheduling,scheduling_list)
    {
        stream.writeStartElement("scheduling");
        stream.writeTextElement("title",scheduling->getTitle());
        stream.writeTextElement("date",scheduling->getDateTime().toString(Qt::ISODate));
        stream.writeTextElement("duration",scheduling->getDuration().toString(Qt::ISODate));
        stream.writeTextElement("task_id",QString::number(m_pointer_to_id[scheduling->getTask()]));

        stream.writeEndElement();
    }
    stream.writeEndElement();


    stream.writeEndElement();
    stream.writeEndDocument();
    output.close();
    m_pointer_to_id.clear();
    m_id_incrementer=0;
}

void XmlBuilder::saveTask(QXmlStreamWriter& stream,Task * task)
{
    if(m_pointer_to_id[task]==0)
    {
        m_pointer_to_id[task]=++m_id_incrementer;
    }
    if(m_pointer_to_id[task->getParent()]==0)
    {
        m_pointer_to_id[task->getParent()]=++m_id_incrementer;
    }
    stream.writeStartElement("task");
    stream.writeTextElement("title",task->getTitle());
    stream.writeTextElement("id",QString::number(m_pointer_to_id[task]));
    stream.writeTextElement("parent_id",QString::number(m_pointer_to_id[task->getParent()]));
    stream.writeTextElement("disponibility",task->getDisponibility().toString(Qt::ISODate));
    stream.writeTextElement("deadline",task->getDeadline().toString(Qt::ISODate));

    stream.writeStartElement("prerequisites");
    foreach(Task* prerequisite,task->getPrerequisite())
    {
        stream.writeStartElement("prerequisite");
        if(m_pointer_to_id[prerequisite]!=0)
        {
            stream.writeTextElement("prerequisite_id",QString::number(m_pointer_to_id[prerequisite]));
        }
        else
        {
            m_pointer_to_id[prerequisite]=++m_id_incrementer;
            stream.writeTextElement("prerequisite_id",QString::number(m_pointer_to_id[prerequisite]));
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();

    if(dynamic_cast<UniqueTask*>(task)!=NULL)
    {
        if(dynamic_cast<UniqueTask*>(task)->getPreemptability())
        {
            stream.writeTextElement("preemptability","true");
        }
        else
        {
            stream.writeTextElement("preemptability","false");
        }
        stream.writeTextElement("task_duration",dynamic_cast<UniqueTask*>(task)->getDuree().toString(Qt::ISODate));
    }
    else
    {
        stream.writeStartElement("sub_tasks");
        foreach(Task * sub_task,dynamic_cast<BlendTask*>(task)->getElement())
        {
            saveTask(stream,sub_task);
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();
}


void XmlBuilder::readInput(ProjectManager& projectManager,SchedulingManager& schedulingManager)
{
    Project *new_project;
    UniqueTask * new_uniqueTask;
    BlendTask* new_blendTask;
    bool preemptability;
    int id,parent_id,prereq_id;

    QDomDocument doc;
    QFile file(m_file_path);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return;

    QDomNodeList projects = doc.elementsByTagName("project");
    for (int i = 0; i < projects.size(); i++)
    {
        QDomNode project_node = projects.item(i);
        QDomElement title = project_node.firstChildElement("title");
        QDomElement disponibility = project_node.firstChildElement("disponibility");
        QDomElement deadline = project_node.firstChildElement("deadline");
        if (title.isNull() || disponibility.isNull() || deadline.isNull())
            continue;
        new_project = new Project(title.text(),QDateTime::fromString(disponibility.text(),Qt::ISODate),QDateTime::fromString(deadline.text(),Qt::ISODate));
        projectManager.AbstractContainer::addElement(new_project);

        QDomElement tasks= project_node.firstChildElement("tasks");
        QDomNodeList sub_tasks= tasks.elementsByTagName("task");
        for(int j = 0;j<sub_tasks.size();j++)
        {
            QDomNode task_node= sub_tasks.item(j);
            QDomElement task_title=task_node.firstChildElement("title");
            QDomElement task_disponibility = task_node.firstChildElement("disponibility");
            QDomElement task_deadline = task_node.firstChildElement("deadline");
            QDomElement task_id = task_node.firstChildElement("id");
            QDomElement task_parent_id = task_node.firstChildElement("parent_id");
            id=task_id.text().toInt();
            parent_id=task_parent_id.text().toInt();

            if(task_node.firstChildElement("sub_tasks")!=QDomElement())
            {
                new_blendTask = new BlendTask(task_title.text(),QDateTime::fromString(task_disponibility.text(),Qt::ISODate),QDateTime::fromString(task_deadline.text(),Qt::ISODate));
                m_id_to_pointer[id]=new_blendTask;
                new_blendTask->setParent(m_id_to_pointer[parent_id]);

                if(m_id_to_pointer[parent_id]==NULL)
                    new_project->addElement(new_blendTask);
                else
                    dynamic_cast<BlendTask*>(m_id_to_pointer[parent_id])->addElement(new_blendTask);
            }
            else
            {
                QDomElement task_preemptability= task_node.firstChildElement("preemptability");
                if(task_preemptability.text()=="true")
                    preemptability=true;
                else
                    preemptability=false;
                QDomElement task_duration=task_node.firstChildElement("task_duration");
                new_uniqueTask = new UniqueTask(task_title.text(),QDateTime::fromString(task_disponibility.text(),Qt::ISODate),QDateTime::fromString(task_deadline.text(),Qt::ISODate),QTime::fromString(task_duration.text(),Qt::ISODate),preemptability);
                m_id_to_pointer[id]=new_uniqueTask;
                new_uniqueTask->setParent(m_id_to_pointer[parent_id]);
                if(m_id_to_pointer[parent_id]==NULL)
                    new_project->addElement(new_uniqueTask);
                else
                    dynamic_cast<BlendTask*>(m_id_to_pointer[parent_id])->addElement(new_uniqueTask);
            }

        }

        tasks= project_node.firstChildElement("tasks");
        sub_tasks= tasks.elementsByTagName("task");
        for(int j = 0;j<sub_tasks.size();j++)
        {
            QDomNode task_node= sub_tasks.item(j);
            QDomElement task_id = task_node.firstChildElement("id");
            id=task_id.text().toInt();

            QDomElement prerequisites= task_node.firstChildElement("prerequisites");
            QDomNodeList prerequisiteList= prerequisites.elementsByTagName("prerequisite");
            for(int k = 0;k<prerequisiteList.size();k++)
            {
                QDomNode prerequisite_node=prerequisiteList.item(k);
                QDomElement prerequisite_id=prerequisite_node.firstChildElement("prerequisite_id");
                prereq_id=prerequisite_id.text().toInt();
                m_id_to_pointer[id]->addPrerequisite(m_id_to_pointer[prereq_id]);
            }
        }

    }

    QDomNodeList schedulings = doc.elementsByTagName("scheduling");
    for (int i = 0; i < schedulings.size(); i++)
    {
        QDomNode scheduling_node = schedulings.item(i);
        QDomElement title = scheduling_node.firstChildElement("title");
        QDomElement date = scheduling_node.firstChildElement("date");
        QDomElement duration = scheduling_node.firstChildElement("duration");
        QDomElement task_id= scheduling_node.firstChildElement("task_id");
        id=task_id.text().toInt();

        if(m_id_to_pointer[id]==NULL)
            schedulingManager.addElement(QDateTime::fromString(date.text(),Qt::ISODate),QTime::fromString(duration.text(),Qt::ISODate),title.text(), true);
        else
            schedulingManager.addElement(QDateTime::fromString(date.text(),Qt::ISODate),QTime::fromString(duration.text(),Qt::ISODate),static_cast<UniqueTask*>(m_id_to_pointer[id]), true);

    }
}
