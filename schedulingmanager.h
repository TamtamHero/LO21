#ifndef SCHEDULINGSchedulingManager_H
#define SCHEDULINGSchedulingManager_H

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include <QMessageBox>
#include "abstractcontainer.h"
#include "scheduling.h"


class SchedulingManager : public AbstractContainer<Scheduling>
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
    list<const Scheduling *> findTaskSchedulings(UniqueTask *element);
    void addElement(QDateTime date,QTime duration,QString title);
    void addElement(QDateTime date,QTime duration,UniqueTask *task);
    void removeElement(Scheduling *element);


};

Q_DECLARE_METATYPE(Scheduling *)

#endif // SCHEDULINGSchedulingManager_H
