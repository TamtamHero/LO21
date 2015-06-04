#ifndef ABSTRACTAbstractManager_H
#define ABSTRACTAbstractManager_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include "project.h"
#include "scheduling.h"


template<typename Type> class AbstractManager
{
protected:
    AbstractManager();
    AbstractManager(const AbstractManager& copy);
    AbstractManager& operator=(const AbstractManager& copy);

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    list<Type *> m_liste;
public:
    virtual ~AbstractManager()=0;

    list<Type *>& getList(){return m_liste;}
    void addElement(Type * element);
    void removeElement(Type * element);
    void sort();

    struct typeIsInferior
    {
          template<typename T>
          bool operator()(const T* l, const T* r)
          {
            return *l < *r;
          }
    };

};

#include "AbstractManager.tpp"
#endif // ABSTRACTAbstractManager_H
