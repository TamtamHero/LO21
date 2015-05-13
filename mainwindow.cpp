#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tacheunitaire.h" //TEMPORAIRE POUR TEST, c'est un projetmanager qui doit balancer l'affichage
#include "tachecomposite.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    modele(new QStandardItemModel),
    projectManager(Manager<Projet>::getInstance()),
    programManager(Manager<Programmation>::getInstance())
{
    ui->setupUi(this);



    QDateTime t1=QDateTime::currentDateTime();
    QDateTime t2=QDateTime::currentDateTime().addDays(1);
    TacheUnitaire *t=new TacheUnitaire("tache 1",t1,t2,QTime::fromString("11:00:00"),true);
    TacheUnitaire *t5=new TacheUnitaire("tache 5",t1,t2,QTime::fromString("11:00:00"),false);

    TacheComposite *tc=new TacheComposite("tache compo",t1,t2);
    TacheComposite *tc2=new TacheComposite("tache compo 2",t1,t2);


    tc->addSousTache(t);
    tc->addSousTache(t5);


    tc2->addSousTache(t);
    tc2->addSousTache(t5);

    Projet *projet=new Projet("projet 1",t1,t2);
    Projet *projet2=new Projet("projet 2",t1,t2);
    projet->addSousTache(tc);
    projet->addSousTache(tc2);
  /*  projet->Afficher(modele);
    // nécessité d'avoir ici un pointeur vers l'instance unique du projetManager: il appelle sa méthode affichage avec *modele ici.
     */

    projectManager.addElement(projet);
    projectManager.addElement(projet2);
    selectionProjet();

    QObject::connect(ui->pushButon_Editing_projectSelection, SIGNAL(clicked()), this, SLOT(selectionProjet()));
    QObject::connect(ui->treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT( clickArbre(const QModelIndex&)));
    QObject::connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleclickArbre(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-


void MainWindow::selectionProjet()
{
    modele->clear();
    projectManager.Afficher(modele);
    ui->treeView->setModel(modele);
}

void MainWindow::clickArbre(const QModelIndex&)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        Projet* projet=indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>();
        editing(projet);
    }
    else // Else, Task case
    {
        Tache* tache=indexElementSelectionne.data(Qt::UserRole+1).value<Tache *>();
        editing(tache);
    }
}

void MainWindow::doubleclickArbre(QModelIndex)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(dynamic_cast<Projet*>(indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>())!=NULL) // Check if selected element is a Project
    {
        Projet* projet=indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>();
        modele->clear();
        projet->afficher(modele);
        ui->treeView->setModel(modele);
    }

}

void MainWindow::editing(Tache * task)
{
    if(dynamic_cast<TacheUnitaire*>(task)!=NULL) // Check if argument is a uniqueTask
    {
        ui->tabWidget_editor->setCurrentIndex(UNIQUE_TASK);
        ui->comboBox_uniqueTask_type->setCurrentIndex(0);
        ui->lineEdit_uniqueTask_title->setText(task->getTitre());
        ui->dateTimeEdit_uniqueTask_disponibility->setDateTime(task->getDisponibility());
        ui->dateTimeEdit_uniqueTask_deadline->setDateTime(task->getDeadline());
        ui->timeEdit_uniqueTask_length->setTime(dynamic_cast<TacheUnitaire*>(task)->getDuree());
        ui->comboBox_uniqueTask_preemptability->setCurrentIndex(dynamic_cast<TacheUnitaire*>(task)->getPreemptability());

    }
    else
    {
        ui->tabWidget_editor->setCurrentIndex(BLEND_TASK);
        ui->comboBox_blendTask_type->setCurrentIndex(0);
        ui->lineEdit_blendTask_title->setText(task->getTitre());
        ui->dateTimeEdit_blendTask_disponibility->setDateTime(task->getDisponibility());
        ui->dateTimeEdit_blendTask_deadline->setDateTime(task->getDeadline());

    }
}

void MainWindow::editing(Projet * project)
{
    ui->tabWidget_editor->setCurrentIndex(PROJECT);
    ui->comboBox_project_type->setCurrentIndex(0);
    ui->lineEdit_project_title->setText(project->getTitre());
    ui->dateTimeEdit_project_disponibility->setDateTime(project->getDisponibility());
    ui->dateTimeEdit_project_deadline->setDateTime(project->getDeadline());
}
