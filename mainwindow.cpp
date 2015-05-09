#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projet.h"
#include "tacheunitaire.h" //TEMPORAIRE POUR TEST, c'est un projetmanager qui doit balancer l'affichage
#include "tachecomposite.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    modele = new QStandardItemModel;

    QDateTime t1=QDateTime::currentDateTime();
    QDateTime t2=QDateTime::currentDateTime().addDays(1);
    TacheUnitaire *t=new TacheUnitaire("tache 1",t1,t2,QTime::fromString("11:00:00"),true);
    TacheUnitaire t5("tache 5",t1,t2,QTime::fromString("11:00:00"),true);

    TacheComposite *tc=new TacheComposite("tache compo",t1,t2);
    TacheComposite *tc2=new TacheComposite("tache compo 2",t1,t2);


    tc->addSousTache(t);
    tc->addSousTache(&t5);
    tc->addSousTache(tc2);


    tc2->addSousTache(t);
    tc2->addSousTache(&t5);

    Projet *projet=new Projet("projet 1",t1,t2);
    projet->addSousTache(tc);
    projet->addSousTache(tc2);
    projet->Afficher(modele);
    // nécessité d'avoir ici un pointeur vers l'instance unique du projetManager: il appelle sa méthode affichage avec *modele ici.
    ui->treeView->setModel(modele);
}

MainWindow::~MainWindow()
{
    delete ui;
}
