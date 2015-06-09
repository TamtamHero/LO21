#include "schedulingwindow.h"

SchedulingWindow::SchedulingWindow(QWidget *parent, ProjectManager &manager):
    QDialog(parent),
    Model(new QStandardItemModel()),
    treeView(new QTreeView(this)),
    pushButton_TaskSelection_selection(new QPushButton("select")),
    pushButton_TaskSelection_projectSelection(new QPushButton("Autre projet")),
    projectManager(manager),
    m_selectedTask(NULL)
{
    projectManager.display(Model);
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



    QObject::connect(pushButton_TaskSelection_projectSelection, SIGNAL(clicked()), this, SLOT(scheduler_selectionProject()));
    QObject::connect(pushButton_TaskSelection_selection,SIGNAL(clicked()),this,SLOT(sendSelection()));
    QObject::connect(treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(scheduler_clickTree(const QModelIndex&)));
    QObject::connect(treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(scheduler_doubleclickTree(QModelIndex)));
}


SchedulingWindow::~SchedulingWindow()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void SchedulingWindow::scheduler_selectionProject()
{
    selectedProject=NULL;
    Model->clear();
    projectManager.display(Model);
    Model->setHorizontalHeaderLabels(QStringList("Sélectionnez un projet"));
    treeView->setModel(Model);
}

void SchedulingWindow::sendSelection()
{
    try
    {
        if(m_selectedTask==NULL)
        {
            throw CalendarException("Vous n'avez pas sélectionné de task");
        }
        else if(dynamic_cast<UniqueTask*>(m_selectedTask)==NULL)
        {
            throw CalendarException("Vous ne pouvez pas programmer une task composite");
        }
        this->close();
    }
    catch(CalendarException error)
    {
        m_selectedTask=NULL;
        QMessageBox::warning(this, "Erreur", error.getInfo());
    }
}

void SchedulingWindow::scheduler_clickTree(const QModelIndex&)
{
    QItemSelectionModel *selection = treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Project*>(indexElementSelectionne.data(Qt::UserRole+1).value<Project *>())!=NULL) // Check if selected element is a Project
    {
        selectedProject=indexElementSelectionne.data(Qt::UserRole+1).value<Project *>();
    }
    else if(dynamic_cast<Task*>(indexElementSelectionne.data(Qt::UserRole+2).value<Task *>())!=NULL) // Else, Task* case
    {
        m_selectedTask=indexElementSelectionne.data(Qt::UserRole+2).value<Task *>();
    }
}

void SchedulingWindow::scheduler_doubleclickTree(QModelIndex)
{
    QItemSelectionModel *selection = treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Project*>(indexElementSelectionne.data(Qt::UserRole+1).value<Project *>())!=NULL) // Check if selected element is a Project
    {
        Model->clear();
        selectedProject->display(Model);
        Model->setHorizontalHeaderLabels(QStringList(selectedProject->getTitle()));
        treeView->setModel(Model);
    }
}

