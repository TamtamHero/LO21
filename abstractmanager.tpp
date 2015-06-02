#include "abstractmanager.h"

template<typename Type>
AbstractManager<Type>::AbstractManager()
{

}

template<typename Type>
AbstractManager<Type>::~AbstractManager()
{

}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-



template<typename Type>
void AbstractManager<Type>::addElement(Type * element)
{
    m_liste.push_back(element);
    sort();
}

template<typename Type>
void AbstractManager<Type>::removeElement(Type * element)
{
    m_liste.erase(std::remove(m_liste.begin(),m_liste.end(),element),m_liste.end());
}

template<typename Type>
void AbstractManager<Type>::sort()
{
    m_liste.sort(typeIsInferior());
}
