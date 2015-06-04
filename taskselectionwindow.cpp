#include "taskselectionwindow.h"
#include <iostream>

TaskSelectionWindow::TaskSelectionWindow(QWidget *parent,Project * project,selectedTaskType type):
    QDialog(parent),
    treeModel(new QStandardItemModel()),
    treeView(new QTreeView(this)),
    pushButton_TaskSelection_selection(new QPushButton("select")),
    pushButton_TaskSelection_notAttaskd(NULL),
    selectedTask(NULL),
    m_type(type)
{
    project->afficher(treeModel);
    treeModel->setHorizontalHeaderLabels(QStringList(project->getTitre()));
    treeView->setModel(treeModel);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *vLayout=new QVBoxLayout;
    QHBoxLayout *hLayout=new QHBoxLayout;
    hLayout->addWidget(pushButton_TaskSelection_selection);
    if(m_type==ATTACHEDTO)
    {
        pushButton_TaskSelection_notAttaskd=new QPushButton("Not attaskd");
        hLayout->addWidget(pushButton_TaskSelection_notAttaskd);
        QObject::connect(pushButton_TaskSelection_notAttaskd,SIGNAL(clicked()),this,SLOT(sendNotAttaskd()));
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
    selectedTask=indexElementSelectionne.data(Qt::UserRole+2).value<Task *>();
    try
    {
        switch (m_type)
        {
            case PREREQUISITE:
            if(Task::checkPrerequisite(dynamic_cast<MainWindow*>(parent())->getCurrentTask(),selectedTask)) //check if the selected task can be a prerequisite of current task
            {
                this->close();
            }
                break;

            case ATTACHEDTO:
            if(Task::checkAttaskdTo(dynamic_cast<MainWindow*>(parent())->getCurrentTask(),selectedTask)) //check if the selected task can be composed of current task
            {
                if(dynamic_cast<UniqueTask*>(selectedTask)!=NULL)
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
        selectedTask=NULL;
        QMessageBox::warning(this, "Erreur", error.getInfo());
    }
}

void TaskSelectionWindow::sendNotAttaskd()
{
    selectedTask=NULL;
    this->close();
}
