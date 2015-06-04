#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include "abstractmanager.h"
#include "project.h"

class ProjectManager : public AbstractManager<Project>
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

public:

    static ProjectManager& getInstance();
    static void freeInstance();
    void Afficher(QStandardItemModel * model);

};

Q_DECLARE_METATYPE(Project *)

#endif // PROJECTMANAGER_H
