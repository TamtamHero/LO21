#include "manager.h"

template<typename Type>
Manager<Type>::Manager()
{

}

template<typename Type>
Manager<Type>::~Manager()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

template<typename Type>
typename Manager<Type>::Handler Manager<Type>::m_handler=Manager<Type>::Handler(); //Initialization of handler

template<typename Type>
Manager<Type>& Manager<Type>::getInstance()
{
    if(m_handler.m_instance == 0)
    {
        m_handler.m_instance= new Manager;
    }
    return *(m_handler.m_instance);
}

template<typename Type>
void Manager<Type>::freeInstance()
{
    if(m_handler.m_instance != 0)
    {
        delete m_handler.m_instance;
    }
}

template<typename Type>
void Manager<Type>::addElement(Type * element)
{
    m_liste.push_back(element);
    sort();
}

template<typename Type>
void Manager<Type>::removeElement(Type * element)
{
    m_liste.erase(std::remove(m_liste.begin(),m_liste.end(),element),m_liste.end());
}

template<typename Type>
Type* Manager<Type>::findElement(Type *element)
{
    comparator a;
    a.toFind=element;
    typename list<Type*>::iterator it=std::find_if(m_liste.begin(),m_liste.end(),a);
    if(it!=m_liste.end())
    {
        return (*it);
    }
    return NULL;
}

template<typename Type>
void Manager<Type>::sort()
{
    m_liste.sort(typeIsInferior());
}

template<typename Type>
void Manager<Type>::Afficher(QStandardItemModel * model)
{
    QStandardItem *item;

    for(typename list<Type *>::iterator it=this->m_liste.begin();it!=this->m_liste.end();++it)
    {
        item=new QStandardItem((*it)->getTitre());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+1);
        model->appendRow(item);
    }
}
