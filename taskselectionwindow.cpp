#include "taskselectionwindow.h"
#include <iostream>

TaskSelectionWindow::TaskSelectionWindow(QWidget *parent,Projet * project,selectedTaskType type):
    QDialog(parent),
    treeModel(new QStandardItemModel()),
    treeView(new QTreeView(this)),
    pushButton_TaskSelection_selection(new QPushButton("select")),
    selectedTask(NULL),
    m_type(type)
{
    project->afficher(treeModel);
    treeModel->setHorizontalHeaderLabels(QStringList(project->getTitre()));
    treeView->setModel(treeModel);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(treeView);
    layout->addWidget(pushButton_TaskSelection_selection);
    this->setLayout(layout);

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
    selectedTask=indexElementSelectionne.data(Qt::UserRole+1).value<Tache *>();
    try
    {
        switch (m_type)
        {
            case PREREQUISITE:
            if(Tache::checkPrerequisite(dynamic_cast<MainWindow*>(parent())->getCurrentTask(),selectedTask)) //check if the selected task can be a prerequisite of current task
            {
                this->close();
            }
                break;

            case ATTACHEDTO:
            if(Tache::checkAttachedTo(dynamic_cast<MainWindow*>(parent())->getCurrentTask(),selectedTask)) //check if the selected task can be a prerequisite of current task
            {
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
