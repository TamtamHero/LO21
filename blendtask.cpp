#include "blendtask.h"

BlendTask::BlendTask(QString titre,QDateTime disponibility,QDateTime echeance):
    Task(titre,disponibility,echeance)
{
    // Useless pour l'instant, le constructeur de la classe mère Task fait tout le travail.
}

BlendTask::~BlendTask()
{
    for(unsigned long i=0;i<m_element.size();i++)
    {
        delete(m_element[i]);   // Est-ce la meilleure manière de détruire une task composite ?``
        m_element[i]=0;
    }
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void BlendTask::addElement(Task * element)
{
    if(element==this)
    {
        throw CalendarException("Tentative avortée d'auto-inclusion"); // A verifier: est-ce utile ?
    }
    m_element.push_back(element);
    std::sort(m_element.begin(),m_element.end(),taskCompare());
    element->setParent(this);
}

void BlendTask::afficher(QStandardItem * parent)
{
    QStandardItem *item;

    for(vector<Task *>::iterator it=this->m_element.begin();it!=this->m_element.end();++it)
    {
        item=new QStandardItem((*it)->getTitre());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
        parent->appendRow(item);
        (*it)->afficher(item);

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
