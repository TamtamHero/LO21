#include "schedulingwindow.h"

SchedulingWindow::SchedulingWindow(QWidget *parent, Manager<Projet> &manager):
    QDialog(parent),
    Model(new QStandardItemModel()),
    treeView(new QTreeView(this)),
    pushButton_TaskSelection_selection(new QPushButton("select")),
    pushButton_TaskSelection_projectSelection(new QPushButton("Autre projet")),
    projectManager(manager),
    selectedTask(NULL)
{
    projectManager.Afficher(Model);
    Model->setHorizontalHeaderLabels(QStringList("Sélectionnez un projet"));
    treeView->setModel(Model);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *vLayout=new QVBoxLayout;
    QHBoxLayout *hLayout=new QHBoxLayout;
    hLayout->addWidget(pushButton_TaskSelection_projectSelection);
    hLayout->addWidget(pushButton_TaskSelection_selection);
    vLayout->addWidget(treeView);
    vLayout->addLayout(hLayout);
    this->setLayout(vLayout);

    QObject::connect(pushButton_TaskSelection_projectSelection, SIGNAL(clicked()), this, SLOT(scheduler_selectionProjet()));
    QObject::connect(treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(scheduler_clickArbre(const QModelIndex&)));
    QObject::connect(treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(scheduler_doubleclickArbre(QModelIndex)));
    //QObject::connect(pushButton_TaskSelection_selection,SIGNAL(clicked()),this,SLOT(sendSelection()));
}


SchedulingWindow::~SchedulingWindow()
{

}

void SchedulingWindow::scheduler_selectionProjet()
{
    selectedProject=NULL;
    Model->clear();
    projectManager.Afficher(Model);
    Model->setHorizontalHeaderLabels(QStringList("Sélectionnez un projet"));
    treeView->setModel(Model);
}

void SchedulingWindow::scheduler_clickArbre(const QModelIndex&)
{
    QItemSelectionModel *selection = treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        selectedProject=indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>();
    }
    else if(dynamic_cast<Tache*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache *>())!=NULL) // Else, Task* case
    {
        selectedTask=indexElementSelectionne.data(Qt::UserRole+2).value<Tache *>();
    }
}

void SchedulingWindow::scheduler_doubleclickArbre(QModelIndex)
{
    QItemSelectionModel *selection = treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        Model->clear();
        selectedProject->afficher(Model);
        Model->setHorizontalHeaderLabels(QStringList(selectedProject->getTitre()));
        treeView->setModel(Model);
    }
}
