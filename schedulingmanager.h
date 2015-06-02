#ifndef SCHEDULINGSchedulingManager_H
#define SCHEDULINGSchedulingManager_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include "abstractmanager.h"
#include "programmation.h"


class SchedulingManager : public AbstractManager<Programmation>
{
private:
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_Single instance handling-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    SchedulingManager();
    ~SchedulingManager();
    SchedulingManager(const SchedulingManager& copy);
    SchedulingManager& operator=(const SchedulingManager& copy);

    struct Handler{
            SchedulingManager* m_instance;
            Handler():m_instance(0){}
            ~Handler(){ if (m_instance) delete m_instance; } // Destructor called at exit
        };
    static Handler m_handler;
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

public:

    static SchedulingManager &getInstance();
    static void freeInstance();
    list<const Programmation *> findTaskSchedulings(TacheUnitaire *element);
    void addElement(QDateTime date,QTime duree,QString titre);
    void addElement(QDateTime date,QTime duree,TacheUnitaire *tache);

};

Q_DECLARE_METATYPE(Programmation *)

#endif // SCHEDULINGSchedulingManager_H
