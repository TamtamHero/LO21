#include "blendtask.h"

BlendTask::BlendTask(QString title,QDateTime disponibility,QDateTime deadline):
    Task(title,disponibility,deadline)
{

}

BlendTask::~BlendTask()
{
    for(unsigned long i=0;i<m_element.size();i++)
    {
        delete(m_element[i]);
        m_element[i]=0;
    }
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void BlendTask::addElement(Task * element)
{
    if(element==this)
    {
        throw CalendarException("Tentative avortée d'auto-inclusion de la tache "+element->getTitle());
    }
    m_element.push_back(element);
    std::sort(m_element.begin(),m_element.end(),taskCompare());
    element->setParent(this);
}

void BlendTask::display(QStandardItem * parent)
{
    QStandardItem *item;

    for(vector<Task *>::iterator it=this->m_element.begin();it!=this->m_element.end();++it)
    {
        item=new QStandardItem((*it)->getTitle());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
        parent->appendRow(item);
        if(dynamic_cast<BlendTask*>((*it))!=NULL)
        {
            dynamic_cast<BlendTask*>((*it))->display(item);
        }
    }
}


list<Task *> BlendTask::getAllUniquePrerequisite()
{
    list<Task*> result,part;
    for(vector<Task *>::iterator it=this->m_prerequisite.begin();it!=this->m_prerequisite.end();++it)
    {
        if(dynamic_cast<UniqueTask*>((*it))!=NULL)
        {
            result.push_back((*it));
        }
        else
        {
            part=dynamic_cast<BlendTask*>((*it))->getAllUniqueSons();
            result.merge(part);
        }
    }

    if(getParent()!=NULL)
    {
        part=dynamic_cast<BlendTask*>(getParent())->getAllUniquePrerequisite();
        result.merge(part);
    }

    return result;
}

 list<Task *> BlendTask::getAllUniqueSons()
 {
     list<Task*> result,part;
     foreach(Task* ptr,this->m_element)
     {
         if(dynamic_cast<UniqueTask*>(ptr)!=NULL)
         {
             result.push_back(ptr);
         }
         else
         {
             part=dynamic_cast<BlendTask*>(ptr)->getAllUniqueSons();
             result.merge(part);
         }
     }
     return result;
 }
