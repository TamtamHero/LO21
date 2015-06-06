#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "abstractbuilder.h"

class IOManager
{
private:
    AbstractBuilder *m_builder;
public:
    IOManager();
    ~IOManager();

    void setBuilder(AbstractBuilder * builder){m_builder=builder;}
    void importFrom(ProjectManager &projectManager, SchedulingManager &schedulingManager);
    void exportTo(ProjectManager &projectManager, SchedulingManager &schedulingManager);
};

#endif // IOMANAGER_H
