#include "abstractcontainer.h"

template<typename Type>
AbstractContainer<Type>::AbstractContainer()
{

}

template<typename Type>
AbstractContainer<Type>::~AbstractContainer()
{

}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-



template<typename Type>
void AbstractContainer<Type>::addElement(Type * element)
{
    m_liste.push_back(element);
    sort();
}

template<typename Type>
void AbstractContainer<Type>::removeElement(Type * element)
{
    m_liste.erase(std::remove(m_liste.begin(),m_liste.end(),element),m_liste.end());
    delete element;
}

template<typename Type>
void AbstractContainer<Type>::sort()
{
    m_liste.sort(typeIsInferior());
}
