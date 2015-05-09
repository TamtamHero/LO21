#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

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

    vector<Projet *> m_liste;
public:

    static ProjectManager& getInstance();
    static void freeInstance();
    void addProject(Projet * projet);
    void Afficher(QStandardItemModel * modele);

};

#endif // PROJECTMANAGER_H
