#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include "projet.h"

class ProjectManager
{
private:
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_Single instance handling-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    ProjectManager();
    ~ProjectManager();
    ProjectManager(const ProjectManager& copy);
    ProjectManager& operator=(const ProjectManager& copy);

    struct Handler{
            ProjectManager* m_instance;
            Handler():m_instance(0){}
            ~Handler(){ if (m_instance) delete m_instance; } // Destructor called at exit
        };
    static Handler m_handler;
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    list<Projet *> m_liste;
public:

    static ProjectManager& getInstance();
    static void freeInstance();
    list<Projet *>& getList(){return m_liste;}
    void addElement(Projet * element);
    void removeElement(Projet * element);
    void Afficher(QStandardItemModel * model);
    void sort();

    struct ProjectIsSooner
    {
          bool operator()(const Projet* l, const Projet* r)
          {
            return *l < *r;
          }
    };

};

Q_DECLARE_METATYPE(Projet *)

#endif // PROJECTMANAGER_H
