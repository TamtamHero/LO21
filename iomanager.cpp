#include "iomanager.h"

IOManager::IOManager()
{

}

IOManager::~IOManager()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void IOManager::importFrom(ProjectManager &projectManager, SchedulingManager &schedulingManager)
{
    m_builder->readInput(projectManager,schedulingManager);
}

void IOManager::exportTo(ProjectManager &projectManager, SchedulingManager &schedulingManager)
{
    m_builder->writeOutput(projectManager.getList(),schedulingManager.getList());
}
