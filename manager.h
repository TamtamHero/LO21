#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include "projet.h"
#include "programmation.h"

Q_DECLARE_METATYPE(Projet *)
Q_DECLARE_METATYPE(Programmation *)


template<typename Type> class Manager
{
private:
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_Single instance handling-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    Manager();
    ~Manager();
    Manager(const Manager& copy);
    Manager& operator=(const Manager& copy);

    struct Handler{
            Manager* m_instance;
            Handler():m_instance(0){}
            ~Handler(){ if (m_instance) delete m_instance; } // Destructor called at exit
        };
    static Handler m_handler;
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    list<Type *> m_liste;
public:

    static Manager<Type> &getInstance();
    static void freeInstance();
    list<Type *>& getList(){return m_liste;}
    void addElement(Type * element);
    void removeElement(Type * element);
    Type* findElement(Type *element);
    void Afficher(QStandardItemModel * model);
    void sort();

    struct typeIsInferior
    {
          template<typename T>
          bool operator()(const T* l, const T* r)
          {
            return *l < *r;
          }
    };

    struct comparator
    {
          Type *toFind;
          bool operator()(Type const* item)
          {
            return *toFind == *item;
          }
    };

};

#include "manager.tpp"
#endif // MANAGER_H
