#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tacheunitaire.h" //TEMPORAIRE POUR TEST, c'est un projetmanager qui doit balancer l'affichage
#include "tachecomposite.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    treeModel(new QStandardItemModel),
    listModel(new QStandardItemModel),
    projectManager(Manager<Projet>::getInstance()),
    programManager(Manager<Programmation>::getInstance()),
    currentProject(NULL),
    currentTask(NULL)
{
    ui->setupUi(this);



    QDateTime t1=QDateTime::currentDateTime();
    QDateTime t2=QDateTime::currentDateTime().addDays(1);
    QDateTime t3=QDateTime::currentDateTime().addDays(3);
    QDateTime t4=QDateTime::currentDateTime().addDays(5);
    TacheUnitaire *t=new TacheUnitaire("tache 1",t1,t2,QTime::fromString("11:00:00"),true);
    TacheUnitaire *t5=new TacheUnitaire("tache 5",t3,t4,QTime::fromString("5:00:00"),false);
    TacheUnitaire *t66=new TacheUnitaire("tache 66",t1,t2,QTime::fromString("11:00:00"),true);
    TacheUnitaire *t77=new TacheUnitaire("tache 77",t3,t4,QTime::fromString("5:00:00"),false);

    TacheComposite *tc=new TacheComposite("tache compo",t1,t2);
    TacheComposite *tc2=new TacheComposite("tache compo 2",t1,t2);


    tc->addElement(t);
    tc->addElement(t5);


    tc2->addElement(t66);
    t66->addPrerequisite(t77);
    tc2->addElement(t77);
    tc2->addPrerequisite(tc);

    Projet *projet=new Projet("projet 1",t1,t2);
    Projet *projet2=new Projet("projet 2",t1,t2);
    projet->addElement(tc);
    projet->addElement(tc2);
  /*  projet->Afficher(treeModel);
    // nécessité d'avoir ici un pointeur vers l'instance unique du projetManager: il appelle sa méthode affichage avec *treeModel ici.
     */

    projectManager.addElement(projet);
    projectManager.addElement(projet2);

    selectionProjet();

    QObject::connect(ui->pushButton_editing_projectSelection, SIGNAL(clicked()), this, SLOT(selectionProjet()));
    QObject::connect(ui->pushButton_editing_delete, SIGNAL(clicked()), this, SLOT(deleteSelection()));
    QObject::connect(ui->treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT( clickArbre(const QModelIndex&)));
    QObject::connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleclickArbre(QModelIndex)));
    QObject::connect(ui->toolButton_uniqueTask_attachedTo, SIGNAL(clicked()), this, SLOT(uniqueAttachedToSelection()));
    QObject::connect(ui->toolButton_blendTask_attachedTo, SIGNAL(clicked()), this, SLOT(blendAttachedToSelection()));
    QObject::connect(ui->toolButton_uniqueTask_prerequisite, SIGNAL(clicked()), this, SLOT(uniquePrerequisiteSelection()));
    QObject::connect(ui->toolButton_blendTask_prerequisite, SIGNAL(clicked()), this, SLOT(blendPrerequisiteSelection()));
    QObject::connect(ui->pushButton_editing_edit, SIGNAL(clicked()), this, SLOT(edit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void MainWindow::selectionProjet()
{
    treeModel->clear();
    projectManager.Afficher(treeModel);
    treeModel->setHorizontalHeaderLabels(QStringList("Sélectionnez un projet"));
    ui->treeView->setModel(treeModel);
}

void MainWindow::clickArbre(const QModelIndex&)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        currentProject=indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>();
        editorView(currentProject);
    }
    else  // Else, Task* case
    {
        currentTask=indexElementSelectionne.data(Qt::UserRole+2).value<Tache *>();
        editorView(currentTask);
    }
}

void MainWindow::doubleclickArbre(QModelIndex)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        currentProject=indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>();
        treeModel->clear();
        currentProject->afficher(treeModel);
        treeModel->setHorizontalHeaderLabels(QStringList(currentProject->getTitre()));
        ui->treeView->setModel(treeModel);
    }

}

void MainWindow::editorView(Tache * task)
{
    QStandardItem *item;

    if(dynamic_cast<TacheUnitaire*>(task)!=NULL) // Check if argument is a uniqueTask
    {
        ui->tabWidget_editing_editor->setCurrentIndex(UNIQUE_TASK);
        ui->comboBox_uniqueTask_type->setCurrentIndex(0);
        ui->lineEdit_uniqueTask_title->setText(task->getTitre());
        ui->dateTimeEdit_uniqueTask_disponibility->setDateTime(task->getDisponibility());
        ui->dateTimeEdit_uniqueTask_deadline->setDateTime(task->getDeadline());
        ui->timeEdit_uniqueTask_length->setTime(dynamic_cast<TacheUnitaire*>(task)->getDuree());
        ui->comboBox_uniqueTask_preemptability->setCurrentIndex(dynamic_cast<TacheUnitaire*>(task)->getPreemptability());
        if(task->getParent()!=NULL)
        {
            ui->lineEdit_uniqueTask_attachedTo->setText(task->getParent()->getTitre());
        }

        listModel->clear();
        for(vector<Tache*>::iterator it=task->getPrerequisite().begin(); it!=task->getPrerequisite().end(); ++it)
        {
            item=new QStandardItem((*it)->getTitre());
            listModel->appendRow(item);
            ui->listView_uniqueTask_prerequisite->setModel(listModel);
        }

    }
    else if(dynamic_cast<TacheComposite*>(task)!=NULL)
    {
        ui->tabWidget_editing_editor->setCurrentIndex(BLEND_TASK);
        ui->comboBox_blendTask_type->setCurrentIndex(0);
        ui->lineEdit_blendTask_title->setText(task->getTitre());
        ui->dateTimeEdit_blendTask_disponibility->setDateTime(task->getDisponibility());
        ui->dateTimeEdit_blendTask_deadline->setDateTime(task->getDeadline());
        if(task->getParent()!=NULL)
        {
            ui->lineEdit_blendTask_attachedTo->setText(task->getParent()->getTitre());
        }

        listModel->clear();
        for(vector<Tache*>::iterator it=task->getPrerequisite().begin(); it!=task->getPrerequisite().end(); ++it)
        {
            item=new QStandardItem((*it)->getTitre());
            item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
            listModel->appendRow(item);
            ui->listView_blendTask_prerequisite->setModel(listModel);
        }
    }
    else
    {
        cout << "you're fucked";
    }
}

void MainWindow::editorView(Projet * project)
{
    ui->tabWidget_editing_editor->setCurrentIndex(PROJECT);
    ui->comboBox_project_type->setCurrentIndex(0);
    ui->lineEdit_project_title->setText(project->getTitre());
    ui->dateTimeEdit_project_disponibility->setDateTime(project->getDisponibility());
    ui->dateTimeEdit_project_deadline->setDateTime(project->getDeadline());
}


void MainWindow::uniquePrerequisiteSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,PREREQUISITE);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            QStandardItem *item;
            item=new QStandardItem(selection->getSelectedTask()->getTitre());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            listModel->appendRow(item);
            ui->listView_uniqueTask_prerequisite->setModel(listModel);
        }
    }
}

void MainWindow::blendPrerequisiteSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,PREREQUISITE);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            QStandardItem *item;
            item=new QStandardItem(selection->getSelectedTask()->getTitre());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            listModel->appendRow(item);
            ui->listView_blendTask_prerequisite->setModel(listModel);
        }
    }
}


void MainWindow::uniqueAttachedToSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,ATTACHEDTO);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            ui->lineEdit_uniqueTask_attachedTo->setText(selection->getSelectedTask()->getTitre());
        }
    }
}

void MainWindow::blendAttachedToSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,ATTACHEDTO);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
        ui->lineEdit_blendTask_attachedTo->setText(selection->getSelectedTask()->getTitre());
        }
    }
}

void MainWindow::deleteSelection()
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        validationWindow result(this,"Êtes-vous sur de vouloir supprimer le projet\"" + currentProject->getTitre() +"\" et les taches qui le composent?");
        result.exec();
        if(result.getValidation())
        {
            vector<Projet*>& projectList=projectManager.getList();
            projectList.erase(std::remove(projectList.begin(),projectList.end(),currentProject),projectList.end());
            delete currentProject;
            currentProject=NULL;
        }
        treeModel->removeRow(indexElementSelectionne.row(),indexElementSelectionne.parent());
    }
    else if(dynamic_cast<Tache*>(indexElementSelectionne.data(Qt::UserRole+1).value<Tache*>())!=NULL)
    {
        validationWindow result(this,"Êtes-vous sur de vouloir supprimer la Tache \"" + currentTask->getTitre() +"\" ?");
        result.exec();
        if(result.getValidation())
        {
            currentProject->deleteElement(currentTask);
            currentTask=NULL;
        }
        treeModel->removeRow(indexElementSelectionne.row(),indexElementSelectionne.parent());
    }
}

void MainWindow::edit()
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        currentProject->setTitle(ui->lineEdit_project_title->text());
        currentProject->setDisponibility(ui->dateTimeEdit_project_disponibility->dateTime());
        currentProject->setDeadline(ui->dateTimeEdit_project_deadline->dateTime());
        treeModel->itemFromIndex(indexElementSelectionne)->setText(currentProject->getTitre());
    }
    else if(dynamic_cast<TacheUnitaire*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache*>())!=NULL)
    {
        currentTask->setTitle(ui->lineEdit_uniqueTask_title->text());
        currentTask->setDisponibility(ui->dateTimeEdit_uniqueTask_disponibility->dateTime());
        currentTask->setDeadline(ui->dateTimeEdit_uniqueTask_deadline->dateTime());
        treeModel->itemFromIndex(indexElementSelectionne)->setText(currentTask->getTitre());
    }
    else if(dynamic_cast<TacheComposite*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache*>())!=NULL)
    {
        currentTask->setTitle(ui->lineEdit_blendTask_title->text());
        currentTask->setDisponibility(ui->dateTimeEdit_blendTask_disponibility->dateTime());
        currentTask->setDeadline(ui->dateTimeEdit_blendTask_deadline->dateTime());
        treeModel->itemFromIndex(indexElementSelectionne)->setText(currentTask->getTitre());
    }
    else
    {
        cout << "coucou";
    }

}
