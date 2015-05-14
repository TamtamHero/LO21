#include "taskselectionwindow.h"

TaskSelectionWindow::TaskSelectionWindow(QWidget *parent,Projet * project):
    QDialog(parent),
    modele(new QStandardItemModel()),
    treeView(new QTreeView(this)),
    pushButton_TaskSelection_selection(new QPushButton("select"))
{
    project->afficher(modele);
    modele->setHorizontalHeaderLabels(QStringList(project->getTitre()));
    treeView->setModel(modele);
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
    Tache* task=indexElementSelectionne.data(Qt::UserRole+1).value<Tache *>();
    //Send task to *parent for treatment
}
