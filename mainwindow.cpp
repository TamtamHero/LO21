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
    TacheUnitaire *t5=new TacheUnitaire("tache 5",t1,t2,QTime::fromString("11:00:00"),true);

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

    QObject::connect(ui->bouton_selection_projet, SIGNAL(clicked()), this, SLOT(selectionProjet()));
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

void MainWindow::doubleclickArbre(QModelIndex)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    Projet* projet=indexElementSelectionne.data(Qt::UserRole+1).value<Projet *>();
    modele->clear();
    projet->Afficher(modele);
    ui->treeView->setModel(modele);
}

