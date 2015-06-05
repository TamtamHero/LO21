#ifndef ABSTRACTCONTAINER_H
#define ABSTRACTCONTAINER_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include <QFile>
#include <QXmlStreamWriter>
#include "project.h"
#include "scheduling.h"


template<typename Type> class AbstractContainer
{
protected:
    AbstractContainer();
    AbstractContainer(const AbstractContainer& copy);
    AbstractContainer& operator=(const AbstractContainer& copy);

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    list<Type *> m_liste;
public:
    virtual ~AbstractContainer()=0;

    list<Type *>& getList(){return m_liste;}
    void addElement(Type * element);
    void removeElement(Type * element);
    void sort();
    void save(const QString& f);

    struct typeIsInferior
    {
          template<typename T>
          bool operator()(const T* l, const T* r)
          {
            return *l < *r;
          }
    };

};

#include "abstractcontainer.tpp"
#endif // ABSTRACTCONTAINER_H
