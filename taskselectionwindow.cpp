#include "taskselectionwindow.h"
#include <iostream>

TaskSelectionWindow::TaskSelectionWindow(QWidget *parent,Project * project,m_selectedTaskType type):
    QDialog(parent),
    m_treeModel(new QStandardItemModel()),
    treeView(new QTreeView(this)),
    pushButton_TaskSelection_selection(new QPushButton("select")),
    pushButton_TaskSelection_notAttached(NULL),
    m_selectedTask(NULL),
    m_type(type)
{
    project->display(m_treeModel);
    m_treeModel->setHorizontalHeaderLabels(QStringList(project->getTitle()));
    treeView->setModel(m_treeModel);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *vLayout=new QVBoxLayout;
    QHBoxLayout *hLayout=new QHBoxLayout;
    hLayout->addWidget(pushButton_TaskSelection_selection);
    if(m_type==ATTACHEDTO)
    {
        pushButton_TaskSelection_notAttached=new QPushButton("Sans attache");
        hLayout->addWidget(pushButton_TaskSelection_notAttached);
        QObject::connect(pushButton_TaskSelection_notAttached,SIGNAL(clicked()),this,SLOT(sendNotAttaskd()));
    }
    vLayout->addWidget(treeView);
    vLayout->addLayout(hLayout);
    this->setLayout(vLayout);

    QObject::connect(pushButton_TaskSelection_selection,SIGNAL(clicked()),this,SLOT(sendSelection()));
}

TaskSelectionWindow::~TaskSelectionWindow()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void TaskSelectionWindow::sendSelection()
{
    QItemSelectionModel *selection = treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    m_selectedTask=indexElementSelectionne.data(Qt::UserRole+2).value<Task *>();
    try
    {
        switch (m_type)
        {
            case PREREQUISITE:
            if(Task::checkPrerequisite(dynamic_cast<MainWindow*>(parent())->getCurrentTask(),m_selectedTask)) //check if the selected task can be a prerequisite of current task
            {
                this->close();
            }
                break;

            case ATTACHEDTO:
            if(Task::checkAttaskdTo(dynamic_cast<MainWindow*>(parent())->getCurrentTask(),m_selectedTask)) //check if the selected task can be composed of current task
            {
                if(dynamic_cast<UniqueTask*>(m_selectedTask)!=NULL)
                {
                    throw CalendarException("La task sélectionnée n'est pas une task composite");
                }
                this->close();
            }
                break;

            default:
                break;
        }

    }
    catch(CalendarException error)
    {
        m_selectedTask=NULL;
        QMessageBox::warning(this, "Erreur", error.getInfo());
    }
}

void TaskSelectionWindow::sendNotAttached()
{
    m_selectedTask=NULL;
    this->close();
}
