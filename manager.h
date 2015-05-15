#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include "projet.h"

Q_DECLARE_METATYPE(Projet *)

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

    vector<Type *> m_liste;
public:

    static Manager<Type> &getInstance();
    static void freeInstance();
    void addElement(Type * element);
    void Afficher(QStandardItemModel * treeModel);

};

#include "manager.tpp"
#endif // MANAGER_H
