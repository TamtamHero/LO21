#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tacheunitaire.h" //TEMPORAIRE POUR TEST, c'est un projetmanager qui doit balancer l'affichage
#include "tachecomposite.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    treeModel(new QStandardItemModel),
    listModel_edit_prerequisite(new QStandardItemModel),
    listModel_edit_attachedTo(new QStandardItemModel),
    listModel_creation_prerequisite(new QStandardItemModel),
    listModel_creation_attachedTo(new QStandardItemModel),
    reply(QMessageBox::No),
    projectManager(Manager<Projet>::getInstance()),
    scheduleManager(Manager<Programmation>::getInstance()),
    currentProject(NULL),
    currentTask(NULL),
    scheduleTask(NULL)
{
    ui->setupUi(this);

    ui->tableWidget_scheduler_view->setSpan(2,2,3,3);

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

    editing_selectionProjet();

    // Editing connections

    QObject::connect(ui->pushButton_editing_projectSelection, SIGNAL(clicked()), this, SLOT(editing_selectionProjet()));
    QObject::connect(ui->pushButton_edit_delete, SIGNAL(clicked()), this, SLOT(deleteSelection()));
    QObject::connect(ui->treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT( editing_clickArbre(const QModelIndex&)));
    QObject::connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editing_doubleclickArbre(QModelIndex)));
    QObject::connect(ui->toolButton_edit_attachedTo, SIGNAL(clicked()), this, SLOT(editing_attachedToSelection()));
    QObject::connect(ui->toolButton_edit_prerequisite, SIGNAL(clicked()), this, SLOT(editing_prerequisiteSelection()));
    QObject::connect(ui->toolButton_creation_attachedTo, SIGNAL(clicked()), this, SLOT(creation_attachedToSelection()));
    QObject::connect(ui->toolButton_creation_prerequisite, SIGNAL(clicked()), this, SLOT(creation_prerequisiteSelection()));
    QObject::connect(ui->pushButton_edit_edit, SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(ui->comboBox_creation, SIGNAL(currentTextChanged(QString)),this, SLOT(creationView(QString) ));
    QObject::connect(ui->pushButton_creation_create,SIGNAL(clicked()),this,SLOT(createElement()));
    QObject::connect(ui->tabWidget_editing_editor,SIGNAL(currentChanged(int)),this,SLOT(switchEditTab()));
    QObject::connect(ui->toolButton_edit_undo,SIGNAL(clicked()),this,SLOT(prerequisiteEditUndo()));
    QObject::connect(ui->toolButton_creation_undo,SIGNAL(clicked()),this,SLOT(prerequisiteCreationUndo()));

    // Scheduler connections

    QObject::connect(ui->toolButton_scheduler_taskSelection,SIGNAL(clicked()),this,SLOT(scheduler_taskSelection()));
    QObject::connect(ui->timeEdit_scheduler_duration,SIGNAL(timeChanged(QTime)),this,SLOT(scheduler_checkTime(QTime)));
    QObject::connect(ui->dateTimeEdit_scheduler_datetime,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(scheduler_checkDeadline(QDateTime)));
    QObject::connect(ui->tableWidget_scheduler_view,SIGNAL(cellClicked(int,int)),this,SLOT(scheduler_setDate(int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//_-_-_-_-_-_-_-_-_-_-_ SIGNALS -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void MainWindow::editing_selectionProjet()
{
    currentProject=NULL;
    treeModel->clear();
    projectManager.Afficher(treeModel);
    treeModel->setHorizontalHeaderLabels(QStringList("Sélectionnez un projet"));
    ui->treeView->setModel(treeModel);
}

void MainWindow::editing_clickArbre(const QModelIndex&)
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

void MainWindow::editing_doubleclickArbre(QModelIndex)
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

    listModel_edit_attachedTo->clear();
    if(task->getParent()!=NULL)
    {
        item=new QStandardItem(task->getParent()->getTitre());
        item->setData(QVariant::fromValue(task->getParent()),Qt::UserRole+2);
        listModel_edit_attachedTo->appendRow(item);
        ui->listView_edit_attachedTo->setModel(listModel_edit_attachedTo);
    }

    listModel_edit_prerequisite->clear();
    for(Tache *ptr=task;ptr!=NULL;ptr=ptr->getParent())
    {
        for(vector<Tache*>::iterator it=ptr->getPrerequisite().begin(); it!=ptr->getPrerequisite().end(); ++it)
        {
            item=new QStandardItem((*it)->getTitre());
            item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
            if(ptr!=task) item->setBackground(Qt::gray);
            else item->setBackground(QColor::fromRgb(175,229,250));
            listModel_edit_prerequisite->appendRow(item);
        }
    }
    ui->listView_edit_prerequisite->setModel(listModel_edit_prerequisite); //verif si c'est out de chaque boucle similaire


    ui->comboBox_edit_type->setCurrentIndex(1);
    ui->listView_edit_attachedTo->setEnabled(true);
    ui->toolButton_edit_attachedTo->setEnabled(true);
    ui->listView_edit_prerequisite->setEnabled(true);
    ui->toolButton_edit_prerequisite->setEnabled(true);
    ui->timeEdit_edit_length->setEnabled(false);
    ui->comboBox_edit_preemptability->setEnabled(false);


    if(dynamic_cast<TacheUnitaire*>(task)!=NULL) // If editing uniqueTask, more display
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

void MainWindow::editing_prerequisiteSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,PREREQUISITE);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            if(listModel_edit_attachedTo->item(0)!=0)
            {
                if(!checkCoherence(listModel_edit_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>(),selection->getSelectedTask()))
                {
                     return;
                }
            }
            QStandardItem *item;
            item=new QStandardItem(selection->getSelectedTask()->getTitre());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            listModel_edit_prerequisite->appendRow(item);
            ui->listView_edit_prerequisite->setModel(listModel_edit_prerequisite);
        }
    }
}


void MainWindow::editing_attachedToSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,ATTACHEDTO);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            if(!checkCoherence(selection->getSelectedTask(),currentTask))
            {
                 return;
            }
            QStandardItem * item=new QStandardItem(selection->getSelectedTask()->getTitre());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            listModel_edit_attachedTo->clear();
            listModel_edit_attachedTo->appendRow(item);
        }
        else
        {
            listModel_edit_attachedTo->clear();
        }
        ui->listView_edit_attachedTo->setModel(listModel_edit_attachedTo);

    }
}

void MainWindow::creation_prerequisiteSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,PREREQUISITE);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            if(listModel_creation_attachedTo->item(0)!=0)
            {
                if(!checkCoherence(listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>(),selection->getSelectedTask()))
                {
                     return;
                }
            }
            else if(reply==QMessageBox::No)
            {
                reply=QMessageBox::question(this,"Erreur","Êtes-vous sur de ne pas vouloir rattacher la nouvelle tache ?",QMessageBox::Yes|QMessageBox::No);
                if(reply==QMessageBox::No)
                {
                    return;
                }
            }
            QStandardItem *item;
            item=new QStandardItem(selection->getSelectedTask()->getTitre());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            listModel_creation_prerequisite->appendRow(item);
            ui->listView_creation_prerequisite->setModel(listModel_creation_prerequisite);
        }
    }
}


void MainWindow::creation_attachedToSelection()
{
    if(currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,currentProject,ATTACHEDTO);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            QStandardItem *item=new QStandardItem(selection->getSelectedTask()->getTitre());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            listModel_creation_attachedTo->clear();
            listModel_creation_attachedTo->appendRow(item);
        }
        else
        {
            listModel_creation_attachedTo->clear();
        }
        ui->listView_creation_attachedTo->setModel(listModel_creation_attachedTo);


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
   try
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
            if(listModel_edit_attachedTo->item(0)!=0 && listModel_edit_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>()!=currentTask->getParent()) // Linking new parent with son
            {
                TacheComposite * ptr_newParent=dynamic_cast<TacheComposite*>(listModel_edit_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache *>());
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
            else if(listModel_edit_attachedTo->item(0)==0 && currentTask->getParent()!=NULL) // Case where the task becomes an apex
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

            currentTask->getPrerequisite().clear();
            for(int i=0;listModel_edit_prerequisite->item(i)!=0;i++)
            {
                if(listModel_edit_prerequisite->item(i)->background().color()!=Qt::gray)
                {
                    currentTask->addPrerequisite(listModel_edit_prerequisite->item(i)->data(Qt::UserRole+2).value<Tache *>());
                }
            }
            if(dynamic_cast<TacheUnitaire*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache*>())!=NULL)
            {
                TacheUnitaire *ptr_task=dynamic_cast<TacheUnitaire*>(indexElementSelectionne.data(Qt::UserRole+2).value<Tache*>());
                ptr_task->setDuree(ui->timeEdit_edit_length->time());
                ptr_task->setPreemptability(ui->comboBox_edit_preemptability->currentText()=="Oui");
            }

            updateTreeView(treeModel,ui->treeView);
        }
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(this,"erreur",error.getInfo());
    }
}



void MainWindow::creationView(QString type)
{
    if(type=="Projet")
    {
        ui->listView_creation_prerequisite->setEnabled(false);
        ui->listView_creation_attachedTo->setEnabled(false);
        ui->toolButton_creation_attachedTo->setEnabled(false);
        ui->toolButton_creation_prerequisite->setEnabled(false);
        ui->toolButton_creation_undo->setEnabled(false);
        ui->timeEdit_creation_length->setEnabled(false);
        ui->comboBox_creation_preemptability->setEnabled(false);
    }
    else if(type=="Tache Composite")
    {
        ui->listView_creation_prerequisite->setEnabled(true);
        ui->listView_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_prerequisite->setEnabled(true);
        ui->toolButton_creation_undo->setEnabled(true);
        ui->timeEdit_creation_length->setEnabled(false);
        ui->comboBox_creation_preemptability->setEnabled(false);
    }
    else if(type=="Tache Unitaire")
    {
        ui->listView_creation_prerequisite->setEnabled(true);
        ui->listView_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_attachedTo->setEnabled(true);
        ui->toolButton_creation_prerequisite->setEnabled(true);
        ui->toolButton_creation_undo->setEnabled(true);
        ui->timeEdit_creation_length->setEnabled(true);
        ui->comboBox_creation_preemptability->setEnabled(true);
    }

    ui->dateTimeEdit_creation_disponibility->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_creation_deadline->setDateTime(QDateTime::currentDateTime().addDays(1));

    currentTask=NULL;
}

void MainWindow::createElement()
{
    try
    {
        if(ui->comboBox_creation->currentText()=="Projet")
        {
            if(ui->lineEdit_creation_title->text()=="")
            {
                QMessageBox::warning(this,"Attention","Veuillez donner un titre au nouveau projet");
                return;
            }
            else if(ui->dateTimeEdit_creation_deadline->dateTime()<=QDateTime::currentDateTime())
            {
                QMessageBox::warning(this,"Attention","L'échéance du projet doit être située dans le futur");
                return;
            }
            Projet *newProject=new Projet(ui->lineEdit_creation_title->text(),ui->dateTimeEdit_creation_disponibility->dateTime(),ui->dateTimeEdit_creation_deadline->dateTime());
            projectManager.addElement(newProject);
            editing_selectionProjet();
            return;
        }

        if(currentProject!=NULL)
        {
            if(ui->lineEdit_creation_title->text()=="")
            {
                QMessageBox::warning(this,"Attention","Veuillez donner un titre à la nouvelle tache");
                return;
            }
            else if(ui->dateTimeEdit_creation_deadline->dateTime()<=QDateTime::currentDateTime())
            {
                QMessageBox::warning(this,"Attention","L'échéance de la tache doit être située dans le futur");
                return;
            }

            if(ui->comboBox_creation->currentText()=="Tache Composite")
            {
                TacheComposite *newTask=new TacheComposite(ui->lineEdit_creation_title->text(),ui->dateTimeEdit_creation_disponibility->dateTime(),ui->dateTimeEdit_creation_deadline->dateTime());
                for(int i=0;listModel_creation_prerequisite->item(i)!=0;newTask->addPrerequisite(listModel_creation_prerequisite->item(i++)->data(Qt::UserRole+2).value<Tache *>()));

                if(listModel_creation_attachedTo->item(0)!=0 && dynamic_cast<TacheComposite*>(listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>())!=NULL) //Attaching
                {
                    newTask->setParent(listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>());
                    dynamic_cast<TacheComposite*>(listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>())->addElement(newTask);
                }
                else if(listModel_creation_attachedTo->item(0)==0)
                {
                    currentProject->addElement(newTask);
                }
            }
            else // UniqueTask
            {
                TacheUnitaire *newTask=new TacheUnitaire(ui->lineEdit_creation_title->text(),ui->dateTimeEdit_creation_disponibility->dateTime(),ui->dateTimeEdit_creation_deadline->dateTime(),ui->timeEdit_creation_length->time(),ui->comboBox_creation_preemptability->currentText()=="Oui");
                for(int i=0;listModel_creation_prerequisite->item(i)!=0;newTask->addPrerequisite(listModel_creation_prerequisite->item(i++)->data(Qt::UserRole+2).value<Tache *>()));

                if(listModel_creation_attachedTo->item(0)!=0 && dynamic_cast<TacheComposite*>(listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>())!=NULL)
                {
                    newTask->setParent(listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>());
                    dynamic_cast<TacheComposite*>(listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Tache*>())->addElement(newTask);
                }
                else if(listModel_creation_attachedTo->item(0)==0)
                {
                    currentProject->addElement(newTask);
                }
            }


        }
        else
        {
            QMessageBox::warning(this,"Attention","Attention, veillez à être à l'interieur d'un projet pour créer une nouvelle tache !");
            return;
        }

        updateTreeView(treeModel,ui->treeView);
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(this, "Erreur", error.getInfo());
    }

}

void MainWindow::prerequisiteCreationUndo()
{
    int i;
    for(i=0;listModel_creation_prerequisite->item(i)!=0;i++);
    if(i--!=0)
    {
        listModel_creation_prerequisite->removeRow(i);
    }
}

void MainWindow::prerequisiteEditUndo()
{
    int i;
    for(i=0;listModel_edit_prerequisite->item(i)!=0;i++);
    if(i--!=0)
    {
        listModel_edit_prerequisite->removeRow(i);
    }
}

void MainWindow::scheduler_taskSelection()
{
    SchedulingWindow * selection=new SchedulingWindow(this,projectManager);
    selection->exec();

    if(selection->getSelectedTask()!=NULL)
    {
        scheduleTask=static_cast<TacheUnitaire*>(selection->getSelectedTask());
        ui->lineEdit_scheduler_title->setText(scheduleTask->getTitre());
        ui->timeEdit_scheduler_duration->setTime(scheduleTask->getDuree());
        ui->dateTimeEdit_scheduler_datetime->setDateTime(scheduleTask->getDisponibility());
    }
}

void MainWindow::scheduler_checkTime(QTime t)
{
    if(scheduleTask!=NULL && scheduleTask->getDuree()<t)
    {
        ui->timeEdit_scheduler_duration->setTime(scheduleTask->getDuree());
    }
}

void MainWindow::scheduler_checkDeadline(QDateTime t)
{
    if(scheduleTask!=NULL && scheduleTask->getDeadline()<t)
    {
        ui->dateTimeEdit_scheduler_datetime->setDateTime(scheduleTask->getDeadline());
    }
    else if(scheduleTask!=NULL && scheduleTask->getDisponibility()>t)
    {
        ui->dateTimeEdit_scheduler_datetime->setDateTime(scheduleTask->getDisponibility());
    }
}

void MainWindow::scheduler_setDate(int row,int column)
{
    QTime time=QTime::fromString("08:00:00");
    time=time.addSecs(1800*row);
    ui->dateTimeEdit_scheduler_datetime->setTime(time);

    QDate date=QDate::currentDate();
    int day=date.dayOfWeek()-1;
    date=date.addDays(column-day);
    ui->dateTimeEdit_scheduler_datetime->setDate(date);
}

//_-_-_-_-_-_-_-_-_-_-_-_-_ METHODS -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void MainWindow::updateTreeView(QStandardItemModel *model,QTreeView *view)
{
    if(model->item(0)==0)
    {
        model->clear();
        currentProject->afficher(model);
        return; //If no item in the view, then no expand list needed;
    }

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


//_-_-_-_-_-_-_-_-_-_-_-_-_ FUNCTIONS -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool checkCoherence(Tache* parent, Tache* prerequisite)
{
    try
    {
        if(parent==NULL)
        {
            return true;
        }
        else if(parent==prerequisite)
        {
            throw CalendarException("La tache est déjà rattachée à la tache \""+prerequisite->getTitre()+"\"");
        }

        for(vector<Tache*>::iterator it=parent->getPrerequisite().begin();it!=parent->getPrerequisite().end();++it)
        {
            if((*it)==prerequisite)
            {
                throw CalendarException("La tache "+ prerequisite->getTitre()+" est déjà un pérequis d'une tache parente\nVeuillez enlever le prérequis ou changer l'attache.");
            }
        }

        return checkCoherence(parent->getParent(),prerequisite);
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(NULL,"erreur",error.getInfo());
        return false;
    }
}

