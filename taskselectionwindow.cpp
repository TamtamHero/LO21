#include "taskselectionwindow.h"
#include <iostream>

TaskSelectionWindow::TaskSelectionWindow(QWidget *parent,Projet * project):
    QDialog(parent),
    treeModel(new QStandardItemModel()),
    treeView(new QTreeView(this)),
    pushButton_TaskSelection_selection(new QPushButton("select")),
    selectedTask(NULL)
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

void TaskSelectionWindow::sendSelection()
{
    QItemSelectionModel *selection = treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    selectedTask=indexElementSelectionne.data(Qt::UserRole+1).value<Tache *>();
    this->close();
}
