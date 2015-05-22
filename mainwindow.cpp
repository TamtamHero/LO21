#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tacheunitaire.h" //TEMPORAIRE POUR TEST, c'est un projetmanager qui doit balancer l'affichage
#include "tachecomposite.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    treeModel(new QStandardItemModel),
    listModel_prerequisite(new QStandardItemModel),
    listModel_attachedTo(new QStandardItemModel),
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
    QDateTime temps5=QDateTime::currentDateTime().addDays(4);
    QDateTime temps6=QDateTime::currentDateTime().addDays(6);
    QDateTime temps7=QDateTime::currentDateTime().addDays(5);
    QDateTime temps8=QDateTime::currentDateTime().addDays(7);
    TacheUnitaire *t=new TacheUnitaire("tache 1",t1,t2,QTime::fromString("11:00:00"),true);
    TacheUnitaire *t5=new TacheUnitaire("tache 5",t3,t4,QTime::fromString("5:00:00"),false);
    TacheUnitaire *t7=new TacheUnitaire("tache 7",temps5,temps6,QTime::fromString("5:00:00"),false);
    TacheUnitaire *t9=new TacheUnitaire("tache 9",temps7,temps8,QTime::fromString("5:00:00"),false);
    TacheUnitaire *t66=new TacheUnitaire("tache 66",t1,t2,QTime::fromString("11:00:00"),true);
    TacheUnitaire *t77=new TacheUnitaire("tache 77",t3,t4,QTime::fromString("5:00:00"),false);

    TacheComposite *tc=new TacheComposite("tache compo",t3,t4);
    TacheComposite *tc2=new TacheComposite("tache compo 2",t1,t2);


    tc->addElement(t);
    tc->addElement(t5);
    tc->addElement(t7);
    tc->addElement(t9);


    tc2->addElement(t66);
    tc2->addElement(t77);

    Projet *projet=new Projet("projet 1",t1,t2);
    Projet *projet2=new Projet("projet 2",t1,t2);
    projet->addElement(tc);
    projet->addElement(tc2);


    projectManager.addElement(projet);
    projectManager.addElement(projet2);

    selectionProjet();

    QObject::connect(ui->pushButton_editing_projectSelection, SIGNAL(clicked()), this, SLOT(selectionProjet()));
    QObject::connect(ui->pushButton_edit_delete, SIGNAL(clicked()), this, SLOT(deleteSelection()));
    QObject::connect(ui->treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT( clickArbre(const QModelIndex&)));
    QObject::connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleclickArbre(QModelIndex)));
    QObject::connect(ui->toolButton_edit_attachedTo, SIGNAL(clicked()), this, SLOT(attachedToSelection()));
    QObject::connect(ui->toolButton_edit_prerequisite, SIGNAL(clicked()), this, SLOT(prerequisiteSelection()));
    QObject::connect(ui->pushButton_edit_edit, SIGNAL(clicked()), this, SLOT(edit()));

    QObject::connect(ui->comboBox_creation, SIGNAL(currentTextChanged(QString)),this, SLOT(creation(QString) ));
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
    else if(dynamic_cast<Tache*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache *>())!=NULL) // Else, Task* case
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
    ui->tabWidget_editing_editor->setCurrentIndex(EDIT);
    ui->lineEdit_edit_title->setText(task->getTitre());
    ui->dateTimeEdit_edit_disponibility->setDateTime(task->getDisponibility());
    ui->dateTimeEdit_edit_deadline->setDateTime(task->getDeadline());

    QStandardItem *item;

    listModel_attachedTo->clear();
    if(task->getParent()!=NULL)
    {
        item=new QStandardItem(task->getParent()->getTitre());
        item->setData(QVariant::fromValue(task->getParent()),Qt::UserRole+2);
        listModel_attachedTo->appendRow(item);
        ui->listView_edit_attachedTo->setModel(listModel_attachedTo);
    }

    listModel_prerequisite->clear();
    for(vector<Tache*>::iterator it=task->getPrerequisite().begin(); it!=task->getPrerequisite().end(); ++it)
    {
        item=new QStandardItem((*it)->getTitre());
        item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
        listModel_prerequisite->appendRow(item);
        ui->listView_edit_prerequisite->setModel(listModel_prerequisite);
    }

    ui->comboBox_edit_type->setCurrentIndex(1);
    ui->listView_edit_attachedTo->setEnabled(true);
    ui->toolButton_edit_attachedTo->setEnabled(true);
    ui->listView_edit_prerequisite->setEnabled(true);
    ui->toolButton_edit_prerequisite->setEnabled(true);
    ui->timeEdit_edit_length->setEnabled(false);
    ui->comboBox_edit_preemptability->setEnabled(false);


    if(dynamic_cast<TacheUnitaire*>(task)!=NULL) // If uniqueTask, more display
    {
        ui->comboBox_edit_type->setCurrentIndex(2);

        ui->timeEdit_edit_length->setTime(dynamic_cast<TacheUnitaire*>(task)->getDuree());
        ui->comboBox_edit_preemptability->setCurrentIndex(dynamic_cast<TacheUnitaire*>(task)->getPreemptability());

        ui->timeEdit_edit_length->setEnabled(true);
        ui->comboBox_edit_preemptability->setEnabled(true);
    }
}

void MainWindow::editorView(Projet * project)
{
    ui->comboBox_edit_type->setCurrentIndex(0);
    ui->tabWidget_editing_editor->setCurrentIndex(EDIT);
    ui->lineEdit_edit_title->setText(project->getTitre());
    ui->dateTimeEdit_edit_disponibility->setDateTime(project->getDisponibility());
    ui->dateTimeEdit_edit_deadline->setDateTime(project->getDeadline());

    ui->listView_edit_attachedTo->setEnabled(false);
    ui->toolButton_edit_attachedTo->setEnabled(false);
    ui->listView_edit_prerequisite->setEnabled(false);
    ui->toolButton_edit_prerequisite->setEnabled(false);
    ui->timeEdit_edit_length->setEnabled(false);
    ui->comboBox_edit_preemptability->setEnabled(false);
}

void MainWindow::prerequisiteSelection()
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
            listModel_prerequisite->appendRow(item);
            ui->listView_edit_prerequisite->setModel(listModel_prerequisite);
        }
    }
}


void MainWindow::attachedToSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,ATTACHEDTO);
        selection->exec();

        QStandardItem *item=new QStandardItem("");
        if(selection->getSelectedTask()!=NULL)
        {
            delete item;
            item=new QStandardItem(selection->getSelectedTask()->getTitre());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            listModel_attachedTo->clear();
            listModel_attachedTo->appendRow(item);
        }
        else
        {
            listModel_attachedTo->clear();
        }
        ui->listView_edit_attachedTo->setModel(listModel_attachedTo);

    }
}

void MainWindow::deleteSelection()
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL && currentProject!=NULL) // Check if selected element is a Project
    {
        validationWindow result(this,"Êtes-vous sur de vouloir supprimer le projet\"" + currentProject->getTitre() +"\" et les taches qui le composent?");
        result.exec();
        if(result.getValidation())
        {
            vector<Projet*>& projectList=projectManager.getList();
            projectList.erase(std::remove(projectList.begin(),projectList.end(),currentProject),projectList.end());
            delete currentProject;
            currentProject=NULL;
            treeModel->removeRow(indexElementSelectionne.row(),indexElementSelectionne.parent());
        }
    }
    else if(dynamic_cast<Tache*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache*>())!=NULL && currentTask!=NULL)
    {
        validationWindow result(this,"Êtes-vous sur de vouloir supprimer la Tache \"" + currentTask->getTitre() +"\" ?");
        result.exec();
        if(result.getValidation())
        {
            currentProject->deleteElement(currentTask);
            currentTask=NULL;
            treeModel->removeRow(indexElementSelectionne.row(),indexElementSelectionne.parent());
        }
    }
}

void MainWindow::edit()
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL && currentProject!=NULL) // Check if selected element is a Project
    {
        currentProject->setTitle(ui->lineEdit_edit_title->text());
        currentProject->setDisponibility(ui->dateTimeEdit_edit_disponibility->dateTime());
        currentProject->setDeadline(ui->dateTimeEdit_edit_deadline->dateTime());
        treeModel->itemFromIndex(indexElementSelectionne)->setText(currentProject->getTitre()); //Update the view
    }
    else if(currentTask!=NULL) // If it's not a Project, it's a Task
    {
        if(listModel_attachedTo->item(0)!=0 && listModel_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>()!=currentTask->getParent()) // Linking new parent with son
        {
            TacheComposite * ptr_newParent=dynamic_cast<TacheComposite*>(listModel_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache *>());
            if(currentTask->getParent()!=NULL)
            {
                vector<Tache*>& list=static_cast<TacheComposite*>(currentTask->getParent())->getElement(); // Erasing son from parent
                list.erase(std::remove(list.begin(),list.end(),currentTask),list.end());
            }
            else
            {
                currentProject->removeElement(currentTask); // Erasing son from Project
            }
            currentTask->setParent(ptr_newParent);
            ptr_newParent->addElement(currentTask);
        }
        else if(listModel_attachedTo->item(0)==0 && currentTask->getParent()!=NULL) // Case where the task becomes an apex
        {
             vector<Tache*>& list=static_cast<TacheComposite*>(currentTask->getParent())->getElement(); // Erasing son from parent
             list.erase(std::remove(list.begin(),list.end(),currentTask),list.end());
             currentTask->setParent(NULL);
             currentProject->addElement(currentTask);
        }

        //_-_-_-_-_-_-_-_-_-_-_-END OF ATTACHING TREATMENT-_-_-_-_-_-_-_-_--_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

        currentTask->setTitle(ui->lineEdit_edit_title->text());
        currentTask->setDisponibility(ui->dateTimeEdit_edit_disponibility->dateTime());
        currentTask->setDeadline(ui->dateTimeEdit_edit_deadline->dateTime());
        for(int i=0;listModel_prerequisite->item(i)!=0;currentTask->addPrerequisite(listModel_prerequisite->item(i++)->data(Qt::UserRole+2).value<Tache *>()));
        std::sort(currentTask->getPrerequisite().begin(),currentTask->getPrerequisite().end());

        if(dynamic_cast<TacheUnitaire*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache*>())!=NULL)
        {
            TacheUnitaire *ptr_task=dynamic_cast<TacheUnitaire*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache*>());
            ptr_task->setDuree(ui->timeEdit_edit_length->time());
            ptr_task->setPreemptability(ui->comboBox_edit_preemptability->currentText()=="Oui");
        }

        updateTreeView(treeModel,ui->treeView);
    }
}


void MainWindow::updateTreeView(QStandardItemModel *model,QTreeView *view)
{
    QList<Tache*> expandedList;
    QModelIndexList indexList=model->match(model->index(0,0),Qt::FontRole,model->item(0)->data(Qt::FontRole));
    foreach(QModelIndex index,indexList)
    {
        if(view->isExpanded(index))
        {
            expandedList.append(index.data(Qt::UserRole+2).value<Tache*>());
        }
    }

    model->clear();
    currentProject->afficher(model);

    foreach (Tache* expandedTask,expandedList)
    {
        QModelIndexList item=model->match(model->index(0,0),Qt::UserRole+2,QVariant::fromValue(expandedTask));
        if(!item.isEmpty())
        {
            view->setExpanded(item.first(),true);
        }
    }
}

void MainWindow::creation(QString type)
{
    if(type=="Projet")
    {
        ui->listView_creationprerequisite->setEnabled(false);
        ui->listView_creation_attachedTo->setEnabled(false);
        ui->toolButton_creation_attachedTo->setEnabled(false);
        ui->toolButton_creation_prerequisite->setEnabled(false);
        ui->timeEdit_creation_length->setEnabled(false);
        ui->comboBox_creation_preemptability->setEnabled(false);
    }
    else if(type=="Tache Composite")
    {
        ui->listView_creationprerequisite->setEnabled(true);
        ui->listView_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_prerequisite->setEnabled(true);
        ui->timeEdit_creation_length->setEnabled(false);
        ui->comboBox_creation_preemptability->setEnabled(false);
    }
    else if(type=="Tache Unitaire")
    {
        ui->listView_creationprerequisite->setEnabled(true);
        ui->listView_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_prerequisite->setEnabled(true);
        ui->timeEdit_creation_length->setEnabled(true);
        ui->comboBox_creation_preemptability->setEnabled(true);
    }
}






