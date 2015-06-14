#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "uniquetask.h"
#include "blendtask.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_treeModel(new QStandardItemModel),
    m_listModel_edit_prerequisite(new QStandardItemModel),
    m_listModel_edit_attachedTo(new QStandardItemModel),
    m_listModel_creation_prerequisite(new QStandardItemModel),
    m_listModel_creation_attachedTo(new QStandardItemModel),
    m_reply(QMessageBox::No),
    projectManager(ProjectManager::getInstance()),
    scheduleManager(SchedulingManager::getInstance()),
    m_currentProject(NULL),
    m_currentTask(NULL),
    m_scheduleTask(NULL),
    m_firstDayOfWeek(QDateTime::currentDateTime().addDays(-QDate::currentDate().dayOfWeek()+1)) //store monday date
{
    ui->setupUi(this);
    updateScheduler();
    ui->label_scheduler_week->setText("Semaine du "+m_firstDayOfWeek.toString("dd/MM"));

    // Editing connections

    QObject::connect(ui->pushButton_editing_projectSelection, SIGNAL(clicked()), this, SLOT(editing_selectionProject()));
    QObject::connect(ui->pushButton_edit_delete, SIGNAL(clicked()), this, SLOT(deleteSelection()));
    QObject::connect(ui->treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT( editing_clickTree(const QModelIndex&)));
    QObject::connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editing_doubleclickTree(QModelIndex)));
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
    QObject::connect(ui->pushButton_scheduler_validateTask,SIGNAL(clicked()),this,SLOT(scheduler_save()));
    QObject::connect(ui->pushButton_scheduler_validateActivity,SIGNAL(clicked()),this,SLOT(scheduler_save()));
    QObject::connect(ui->pushButton_scheduler_previous,SIGNAL(clicked()),this,SLOT(scheduler_previousWeek()));
    QObject::connect(ui->pushButton_scheduler_next,SIGNAL(clicked()),this,SLOT(scheduler_nextWeek()));
    QObject::connect(ui->pushButton_scheduler_export,SIGNAL(clicked()),this,SLOT(scheduler_export()));
    QObject::connect(ui->pushButton_scheduler_import,SIGNAL(clicked()),this,SLOT(scheduler_import()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//_-_-_-_-_-_-_-_-_-_-_ SLOTS -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void MainWindow::editing_selectionProject()
{
    m_currentProject=NULL;
    m_treeModel->clear();
    projectManager.display(m_treeModel);
    m_treeModel->setHorizontalHeaderLabels(QStringList("Sélectionnez un projet"));
    ui->treeView->setModel(m_treeModel);
}

void MainWindow::editing_clickTree(const QModelIndex&)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Project*>(indexElementSelectionne.data(Qt::UserRole+1).value<Project *>())!=NULL) // Check if selected element is a Project
    {
        m_currentProject=indexElementSelectionne.data(Qt::UserRole+1).value<Project *>();
        editorView(m_currentProject);
    }
    else if(dynamic_cast<Task*>(indexElementSelectionne.data(Qt::UserRole+2).value<Task *>())!=NULL) // Else, Task* case
    {
        m_currentTask=indexElementSelectionne.data(Qt::UserRole+2).value<Task *>();
        editorView(m_currentTask);
    }
}

void MainWindow::editing_doubleclickTree(QModelIndex)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Project*>(indexElementSelectionne.data(Qt::UserRole+1).value<Project *>())!=NULL) // Check if selected element is a Project
    {
        m_currentProject=indexElementSelectionne.data(Qt::UserRole+1).value<Project *>();
        m_treeModel->clear();
        m_currentProject->display(m_treeModel);
        m_treeModel->setHorizontalHeaderLabels(QStringList(m_currentProject->getTitle()));
        ui->treeView->setModel(m_treeModel);
    }
}

void MainWindow::editorView(Task * task)
{
    ui->tabWidget_editing_editor->setCurrentIndex(EDIT);
    ui->lineEdit_edit_title->setText(task->getTitle());
    ui->dateTimeEdit_edit_disponibility->setDateTime(task->getDisponibility());
    ui->dateTimeEdit_edit_deadline->setDateTime(task->getDeadline());

    QStandardItem *item;

    m_listModel_edit_attachedTo->clear();
    if(task->getParent()!=NULL)
    {
        item=new QStandardItem(task->getParent()->getTitle());
        item->setData(QVariant::fromValue(task->getParent()),Qt::UserRole+2);
        m_listModel_edit_attachedTo->appendRow(item);
        ui->listView_edit_attachedTo->setModel(m_listModel_edit_attachedTo);
    }

    m_listModel_edit_prerequisite->clear();
    for(Task *ptr=task;ptr!=NULL;ptr=ptr->getParent())
    {
        for(vector<Task*>::iterator it=ptr->getPrerequisite().begin(); it!=ptr->getPrerequisite().end(); ++it)
        {
            item=new QStandardItem((*it)->getTitle());
            item->setData(QVariant::fromValue((*it)),Qt::UserRole+2);
            if(ptr!=task) item->setBackground(Qt::gray);
            else item->setBackground(QColor::fromRgb(175,229,250));
            m_listModel_edit_prerequisite->appendRow(item);
        }
    }
    ui->listView_edit_prerequisite->setModel(m_listModel_edit_prerequisite);


    ui->comboBox_edit_type->setCurrentIndex(1);
    ui->listView_edit_attachedTo->setEnabled(true);
    ui->toolButton_edit_attachedTo->setEnabled(true);
    ui->listView_edit_prerequisite->setEnabled(true);
    ui->toolButton_edit_prerequisite->setEnabled(true);
    ui->timeEdit_edit_length->setEnabled(false);
    ui->comboBox_edit_preemptability->setEnabled(false);


    if(dynamic_cast<UniqueTask*>(task)!=NULL) // If editing uniqueTask, more display
    {
        ui->comboBox_edit_type->setCurrentIndex(2);

        ui->timeEdit_edit_length->setTime(dynamic_cast<UniqueTask*>(task)->getDuree());
        ui->comboBox_edit_preemptability->setCurrentIndex(dynamic_cast<UniqueTask*>(task)->getPreemptability());

        ui->timeEdit_edit_length->setEnabled(true);
        ui->comboBox_edit_preemptability->setEnabled(true);
    }
}

void MainWindow::editorView(Project * project)
{
    ui->comboBox_edit_type->setCurrentIndex(0);
    ui->tabWidget_editing_editor->setCurrentIndex(EDIT);
    ui->lineEdit_edit_title->setText(project->getTitle());
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
    if(m_currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,m_currentProject,PREREQUISITE);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            if(m_listModel_edit_attachedTo->item(0)!=0)
            {
                if(!checkCoherence(m_listModel_edit_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>(),selection->getSelectedTask()))
                {
                     return;
                }
            }
            QStandardItem *item;
            item=new QStandardItem(selection->getSelectedTask()->getTitle());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            m_listModel_edit_prerequisite->appendRow(item);
            ui->listView_edit_prerequisite->setModel(m_listModel_edit_prerequisite);
        }
    }
}


void MainWindow::editing_attachedToSelection()
{
    if(m_currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,m_currentProject,ATTACHEDTO);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            if(!checkCoherence(selection->getSelectedTask(),m_currentTask))
            {
                 return;
            }
            QStandardItem * item=new QStandardItem(selection->getSelectedTask()->getTitle());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            m_listModel_edit_attachedTo->clear();
            m_listModel_edit_attachedTo->appendRow(item);
        }
        else
        {
            m_listModel_edit_attachedTo->clear();
        }
        ui->listView_edit_attachedTo->setModel(m_listModel_edit_attachedTo);

    }
}

void MainWindow::creation_prerequisiteSelection()
{
    if(m_currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,m_currentProject,PREREQUISITE);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            if(m_listModel_creation_attachedTo->item(0)!=0)
            {
                if(!checkCoherence(m_listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>(),selection->getSelectedTask()))
                {
                     return;
                }
            }
            else if(m_reply==QMessageBox::No)
            {
                m_reply=QMessageBox::question(this,"Erreur","Êtes-vous sur de ne pas vouloir rattacher la nouvelle tache ?",QMessageBox::Yes|QMessageBox::No);
                if(m_reply==QMessageBox::No)
                {
                    return;
                }
            }
            QStandardItem *item;
            item=new QStandardItem(selection->getSelectedTask()->getTitle());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            m_listModel_creation_prerequisite->appendRow(item);
            ui->listView_creation_prerequisite->setModel(m_listModel_creation_prerequisite);
        }
    }
}


void MainWindow::creation_attachedToSelection()
{
    if(m_currentProject!=NULL)
    {
        TaskSelectionWindow *selection=new TaskSelectionWindow(this,m_currentProject,ATTACHEDTO);
        selection->exec();

        if(selection->getSelectedTask()!=NULL)
        {
            QStandardItem *item=new QStandardItem(selection->getSelectedTask()->getTitle());
            item->setData(QVariant::fromValue((selection->getSelectedTask())),Qt::UserRole+2);
            m_listModel_creation_attachedTo->clear();
            m_listModel_creation_attachedTo->appendRow(item);
        }
        else
        {
            m_listModel_creation_attachedTo->clear();
        }
        ui->listView_creation_attachedTo->setModel(m_listModel_creation_attachedTo);


    }
}

void MainWindow::deleteSelection()
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Project*>(indexElementSelectionne.data(Qt::UserRole+1).value<Project *>())!=NULL && m_currentProject!=NULL) // Check if selected element is a Project
    {
        validationWindow result(this,"Êtes-vous sur de vouloir supprimer le projet\"" + m_currentProject->getTitle() +"\" et les tasks qui le composent?");
        result.exec();
        if(result.getValidation())
        {
            projectManager.removeElement(m_currentProject);
            m_currentProject=NULL;
            m_treeModel->removeRow(indexElementSelectionne.row(),indexElementSelectionne.parent());
        }
    }
    else if(dynamic_cast<Task*>(indexElementSelectionne.data(Qt::UserRole+2).value<Task*>())!=NULL && m_currentTask!=NULL)
    {
        validationWindow result(this,"Êtes-vous sur de vouloir supprimer la Task \"" + m_currentTask->getTitle() +"\" ?");
        result.exec();
        if(result.getValidation())
        {
            m_currentProject->deleteElement(m_currentTask);
            m_currentTask=NULL;
            m_treeModel->removeRow(indexElementSelectionne.row(),indexElementSelectionne.parent());
        }
    }
}

void MainWindow::edit()
{
   try
    {
        QItemSelectionModel *selection = ui->treeView->selectionModel();
        QModelIndex indexElementSelectionne = selection->currentIndex();

        if(dynamic_cast<Project*>(indexElementSelectionne.data(Qt::UserRole+1).value<Project *>())!=NULL && m_currentProject!=NULL) // Check if selected element is a Project
        {
            m_currentProject->setTitle(ui->lineEdit_edit_title->text());
            m_currentProject->setDisponibility(ui->dateTimeEdit_edit_disponibility->dateTime());
            m_currentProject->setDeadline(ui->dateTimeEdit_edit_deadline->dateTime());
            projectManager.sort();
            editing_selectionProject(); // update view
        }
        else if(m_currentTask!=NULL) // If it's not a Project, it's a Task
        {
            if(m_listModel_edit_attachedTo->item(0)!=0 && m_listModel_edit_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>()!=m_currentTask->getParent()) // Linking new parent with son
            {
                BlendTask * ptr_newParent=dynamic_cast<BlendTask*>(m_listModel_edit_attachedTo->item(0)->data(Qt::UserRole+2).value<Task *>());
                if(m_currentTask->getParent()!=NULL)
                {
                    vector<Task*>& list=static_cast<BlendTask*>(m_currentTask->getParent())->getElement(); // Erasing son from parent
                    list.erase(std::remove(list.begin(),list.end(),m_currentTask),list.end());
                }
                else
                {
                    m_currentProject->removeElement(m_currentTask); // Erasing son from Project
                }
                m_currentTask->setParent(ptr_newParent);
                ptr_newParent->addElement(m_currentTask);
            }
            else if(m_listModel_edit_attachedTo->item(0)==0 && m_currentTask->getParent()!=NULL) // Case where the task becomes an apex
            {
                 vector<Task*>& list=static_cast<BlendTask*>(m_currentTask->getParent())->getElement(); // Erasing son from parent
                 list.erase(std::remove(list.begin(),list.end(),m_currentTask),list.end());
                 m_currentTask->setParent(NULL);
                 m_currentProject->addElement(m_currentTask);
            }

            //_-_-_-_-_-_-_-_-_-_-_-END OF ATTACHING TREATMENT-_-_-_-_-_-_-_-_--_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

            m_currentTask->setTitle(ui->lineEdit_edit_title->text());
            m_currentTask->setDisponibility(ui->dateTimeEdit_edit_disponibility->dateTime());
            m_currentTask->setDeadline(ui->dateTimeEdit_edit_deadline->dateTime());

            m_currentTask->getPrerequisite().clear();
            for(int i=0;m_listModel_edit_prerequisite->item(i)!=0;i++)
            {
                if(m_listModel_edit_prerequisite->item(i)->background().color()!=Qt::gray)
                {
                    m_currentTask->addPrerequisite(m_listModel_edit_prerequisite->item(i)->data(Qt::UserRole+2).value<Task *>());
                }
            }
            if(dynamic_cast<UniqueTask*>(indexElementSelectionne.data(Qt::UserRole+2).value<Task*>())!=NULL)
            {
                UniqueTask *ptr_task=dynamic_cast<UniqueTask*>(indexElementSelectionne.data(Qt::UserRole+2).value<Task*>());
                ptr_task->setDuree(ui->timeEdit_edit_length->time());
                ptr_task->setPreemptability(ui->comboBox_edit_preemptability->currentText()=="Oui");
            }

            updateTreeView(m_treeModel,ui->treeView);
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

    m_currentTask=NULL;
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
            projectManager.addElement(ui->lineEdit_creation_title->text(),ui->dateTimeEdit_creation_disponibility->dateTime(),ui->dateTimeEdit_creation_deadline->dateTime());
            editing_selectionProject();
            return;
        }

        if(m_currentProject!=NULL)
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
                BlendTask *newTask=new BlendTask(ui->lineEdit_creation_title->text(),ui->dateTimeEdit_creation_disponibility->dateTime(),ui->dateTimeEdit_creation_deadline->dateTime());
                for(int i=0;m_listModel_creation_prerequisite->item(i)!=0;newTask->addPrerequisite(m_listModel_creation_prerequisite->item(i++)->data(Qt::UserRole+2).value<Task *>()));

                if(m_listModel_creation_attachedTo->item(0)!=0 && dynamic_cast<BlendTask*>(m_listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>())!=NULL) //Attaching
                {
                    newTask->setParent(m_listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>());
                    dynamic_cast<BlendTask*>(m_listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>())->addElement(newTask);
                }
                else if(m_listModel_creation_attachedTo->item(0)==0)
                {
                    m_currentProject->addElement(newTask);
                }
            }
            else // UniqueTask
            {
                UniqueTask *newTask=new UniqueTask(ui->lineEdit_creation_title->text(),ui->dateTimeEdit_creation_disponibility->dateTime(),ui->dateTimeEdit_creation_deadline->dateTime(),ui->timeEdit_creation_length->time(),ui->comboBox_creation_preemptability->currentText()=="Oui");
                for(int i=0;m_listModel_creation_prerequisite->item(i)!=0;newTask->addPrerequisite(m_listModel_creation_prerequisite->item(i++)->data(Qt::UserRole+2).value<Task *>()));

                if(m_listModel_creation_attachedTo->item(0)!=0 && dynamic_cast<BlendTask*>(m_listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>())!=NULL)
                {
                    newTask->setParent(m_listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>());
                    dynamic_cast<BlendTask*>(m_listModel_creation_attachedTo->item(0)->data(Qt::UserRole+2).value<Task*>())->addElement(newTask);
                }
                else if(m_listModel_creation_attachedTo->item(0)==0)
                {
                    m_currentProject->addElement(newTask);
                }
            }

        }
        else
        {
            QMessageBox::warning(this,"Attention","Attention, veillez à être à l'interieur d'un projet pour créer une nouvelle tache !");
            return;
        }

        updateTreeView(m_treeModel,ui->treeView);
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(this, "Erreur", error.getInfo());
    }

}

void MainWindow::prerequisiteCreationUndo()
{
    int i;
    for(i=0;m_listModel_creation_prerequisite->item(i)!=0;i++);
    if(i--!=0)
    {
        m_listModel_creation_prerequisite->removeRow(i);
    }
}

void MainWindow::prerequisiteEditUndo()
{
    int i;
    for(i=0;m_listModel_edit_prerequisite->item(i)!=0;i++);
    if(i--!=0)
    {
        m_listModel_edit_prerequisite->removeRow(i);
    }
}

void MainWindow::scheduler_taskSelection()
{
    SchedulingWindow * selection=new SchedulingWindow(this,projectManager);
    selection->exec();

    if(selection->getSelectedTask()!=NULL)
    {
        m_scheduleTask=static_cast<UniqueTask*>(selection->getSelectedTask());
        ui->lineEdit_scheduler_title->setText(m_scheduleTask->getTitle());
        ui->timeEdit_scheduler_duration->setTime(m_scheduleTask->getDuree());
        ui->dateTimeEdit_scheduler_datetime->setDateTime(m_scheduleTask->getDisponibility());
    }
}

void MainWindow::scheduler_checkTime(QTime t)
{
    if(m_scheduleTask!=NULL && m_scheduleTask->getDuree()<t)
    {
        ui->timeEdit_scheduler_duration->setTime(m_scheduleTask->getDuree());
    }
}

void MainWindow::scheduler_checkDeadline(QDateTime t)
{
    if(m_scheduleTask!=NULL && m_scheduleTask->getDeadline()<t)
    {
        ui->dateTimeEdit_scheduler_datetime->setDateTime(m_scheduleTask->getDeadline().addSecs(-QTime(0, 0, 0).secsTo(m_scheduleTask->getDuree())));
    }
    else if(m_scheduleTask!=NULL && m_scheduleTask->getDisponibility()>t)
    {
        ui->dateTimeEdit_scheduler_datetime->setDateTime(m_scheduleTask->getDisponibility());
    }
}

void MainWindow::scheduler_setDate(int row,int column) //Auto completion of DateTime when clicking on TableView boxes
{
    QTime time=QTime::fromString("00:00:00");
    time=time.addSecs(1800*row);
    ui->dateTimeEdit_scheduler_datetime->setTime(time);

    QDateTime date=m_firstDayOfWeek;
    date=date.addDays(column);
    ui->dateTimeEdit_scheduler_datetime->setDate(date.date());
}

void MainWindow::scheduler_save()
{
    try
    {
        bool isTask=static_cast<QPushButton*>(QObject::sender())==ui->pushButton_scheduler_validateTask;

        if(isTask)
        {
            scheduleManager.addElement(ui->dateTimeEdit_scheduler_datetime->dateTime(),ui->timeEdit_scheduler_duration->time(),m_scheduleTask);
        }
        else
        {
            scheduleManager.addElement(ui->dateTimeEdit_scheduler_datetime->dateTime(),ui->timeEdit_scheduler_duration->time(),ui->lineEdit_scheduler_title->text());
        }

        m_scheduleTask=NULL;
        updateScheduler();
        XmlBuilder *test=new XmlBuilder("xmltest.xml");
        test->writeOutput(projectManager.getList(),scheduleManager.getList());

    }
    catch(CalendarException error)
    {
        QMessageBox::warning(this, "Erreur", error.getInfo());
    }
}

void MainWindow::scheduler_previousWeek()
{
    m_firstDayOfWeek=m_firstDayOfWeek.addDays(-7);
    ui->label_scheduler_week->setText("Semaine du "+m_firstDayOfWeek.toString("dd/MM"));
    updateScheduler();
}

void MainWindow::scheduler_nextWeek()
{
    m_firstDayOfWeek=m_firstDayOfWeek.addDays(7);
    ui->label_scheduler_week->setText("Semaine du "+m_firstDayOfWeek.toString("dd/MM"));
    updateScheduler();
}

void MainWindow::deleteScheduling()
{
    if(!ui->tableWidget_scheduler_view->selectedItems().empty())
    {
        validationWindow confirm(this,"Êtes-vous sûr de vouloir enlever les programmations sélectionnées?");
        confirm.exec();
        if(!confirm.getValidation())
        {
            return;
        }
        Scheduling * ptr;

        foreach (QTableWidgetItem *item, ui->tableWidget_scheduler_view->selectedItems())
        {
            ptr=item->data(Qt::UserRole+2).value<Scheduling*>();
            scheduleManager.removeElement(ptr);
        }
        updateScheduler();
    }
    else
    {
        return;
    }
}

void MainWindow::scheduler_export()
{
    try
    {
        QString path;
        if(ui->comboBox_scheduler_export->currentText()=="XML")
        {
            path = QFileDialog::getOpenFileName(this, "Choisissez un fichier d'export", QString(), "XML (*.xml *.XML)");
            if(path=="")
                return;
            XmlBuilder *builder= new XmlBuilder(path);
            m_ioManager.setBuilder(builder);
        }
        else if(ui->comboBox_scheduler_export->currentText()==".txt")
        {
            path = QFileDialog::getOpenFileName(this, "Choisissez un fichier d'export", QString(), "texte (*.txt *.TXT)");
            if(path=="")
                return;
            XmlBuilder *builder= new XmlBuilder(path);
            m_ioManager.setBuilder(builder);
        }
        m_ioManager.exportTo(projectManager,scheduleManager);
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(this,"erreur",error.getInfo());
    }
}

void MainWindow::scheduler_import()
{
    try
    {
        QString path;
        if(ui->comboBox_scheduler_export->currentText()=="XML")
        {
            path = QFileDialog::getOpenFileName(this, "Choisissez un fichier d'import", QString(), "XML (*.xml *.XML)");
            if(path=="")
                return;
            XmlBuilder *builder= new XmlBuilder(path);
            m_ioManager.setBuilder(builder);
        }
        else if(ui->comboBox_scheduler_export->currentText()==".txt")
        {
            path = QFileDialog::getOpenFileName(this, "Choisissez un fichier d'import", QString(), "texte (*.txt *.TXT)");
            if(path=="")
                return;
            XmlBuilder *builder= new XmlBuilder(path);
            m_ioManager.setBuilder(builder);
        }
        m_ioManager.importFrom(projectManager,scheduleManager);
        updateScheduler();
        editing_selectionProject();
    }
    catch(CalendarException error)
    {
        QMessageBox::warning(this,"erreur",error.getInfo());
    }
}

//_-_-_-_-_-_-_-_-_-_-_-_-_ METHODS -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void MainWindow::updateTreeView(QStandardItemModel *model,QTreeView *view)
{
    if(model->item(0)==0)
    {
        model->clear();
        m_currentProject->display(model);
        return; //If no item in the view, then no expand list needed;
    }

    QList<Task*> expandedList;
    QModelIndexList indexList=model->match(model->index(0,0),Qt::FontRole,model->item(0)->data(Qt::FontRole));
    foreach(QModelIndex index,indexList)
    {
        if(view->isExpanded(index))
        {
            expandedList.append(index.data(Qt::UserRole+2).value<Task*>());
        }
    }

    model->clear();
    m_currentProject->display(model);

    foreach (Task* expandedTask,expandedList)
    {
        QModelIndexList item=model->match(model->index(0,0),Qt::UserRole+2,QVariant::fromValue(expandedTask));
        if(!item.isEmpty())
        {
            view->setExpanded(item.first(),true);
        }
    }
}

void MainWindow::updateScheduler()
{
    ui->tableWidget_scheduler_view->clearContents();
    ui->tableWidget_scheduler_view->clearSpans();

    int row,column;
    QDateTime endOfWeek=m_firstDayOfWeek.addDays(7);
    endOfWeek=endOfWeek.addSecs(24*3600);
    QTableWidgetItem *item;
    for(list<Scheduling *>::iterator it=scheduleManager.getList().begin();it!=scheduleManager.getList().end();++it)
    {
        if((*it)->getDateTime() >= m_firstDayOfWeek && (*it)->getDateTime() < endOfWeek)
        {
            row=(QTime(0, 0, 0).secsTo((*it)->getDateTime().time()))/1800;
            column=(*it)->getDateTime().date().dayOfWeek()-1;

            item=new QTableWidgetItem((*it)->getTitle());
            item->setData(Qt::UserRole+2,QVariant::fromValue((*it)));
            item->setBackgroundColor(Qt::gray);
            ui->tableWidget_scheduler_view->setSpan(row,column,ceil(QTime(0, 0, 0).secsTo((*it)->getDuration())/1800.0),1);
            ui->tableWidget_scheduler_view->setItem(row,column,item);
        }
    }

    QDateTime day_iterator=m_firstDayOfWeek;

    for(unsigned int i = 0; i < 7; i++)
    {
       ui->tableWidget_scheduler_view->setHorizontalHeaderItem(i, new QTableWidgetItem(day_iterator.toString("ddd d MMMM")));
       day_iterator = day_iterator.addDays(1);
    }
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == 16777219 ) //Why the hell can't I use Qt::Key_Delete instead ? it's worth 16777223...
        {
            deleteScheduling();
            return true;
        }
    }
    return QWidget::event(event);
}

//_-_-_-_-_-_-_-_-_-_-_-_-_ FUNCTIONS -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


bool checkCoherence(Task* parent, Task* prerequisite)
{
    try
    {
        if(parent==NULL)
        {
            return true;
        }
        else if(parent==prerequisite)
        {
            throw CalendarException("La task est déjà rattachée à la tache \""+prerequisite->getTitle()+"\"");
        }

        for(vector<Task*>::iterator it=parent->getPrerequisite().begin();it!=parent->getPrerequisite().end();++it)
        {
            if((*it)==prerequisite)
            {
                throw CalendarException("La task "+ prerequisite->getTitle()+" est déjà un pérequis d'une tache parente\nVeuillez enlever le prérequis ou changer l'attache.");
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

