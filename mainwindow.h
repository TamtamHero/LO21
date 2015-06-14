#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//! \file mainwindow.h
//! \brief Classe MainWindow dans le namespace UserInterface
//! \author Passot J & Laviolette E
//! \version 4.0
//! \date Samedi 13 Juin 2015

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QBrush>
#include <QDate>
#include <QKeyEvent>
#include <cmath>

#include "project.h"
#include "projectmanager.h"
#include "schedulingmanager.h"
#include "scheduling.h"
#include "taskselectionwindow.h"
#include "validationwindow.h"
#include "schedulingwindow.h"
#include "xmlbuilder.h"
#include "iomanager.h"

//! \namespace Ui
//! \brief namespace contenant la classe MainWindow qui s'occupe de toutes les IHM
namespace Ui {

class MainWindow;
}

//! \class MainWindow
//! \\brief Classe de la fenêtre graphique de l'application qui hérite de QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! \brief Constructeur de la classe
    //! \param un widget parent de type QWidget
    explicit MainWindow(QWidget *parent = 0);

     //! \brief Desctructeur de la classe MainWindow
    ~MainWindow();


    //! \brief Charge la tache en paramètre dans l'editeur
    //! \param task : un pointeur sur une tache à éditer
    //! \return  void
    void editorView(Task * task);


    //! \brief Charge le projet en paramètre dans l'editeur
    //! \param un pointeur sur un projet à éditer
    //! \return  void
    void editorView(Project * project);


    //! \brief Accesseur sur la tache actuelle
    //! \param void
    //! \return  un pointeur sur une tache
    Task * getCurrentTask(){return m_currentTask;}

private:
    Ui::MainWindow *ui; //! Contient toute l'interface graphique

    QStandardItemModel *m_treeModel; //! Modèle de donnée pour l'affichage des projets et taches
    QStandardItemModel *m_listModel_edit_prerequisite; //! Modèle de donnée pour l'affichage des pré-requis
    QStandardItemModel *m_listModel_edit_attachedTo; //! Modèle de donnée pour l'affichage de la composition
    QStandardItemModel *m_listModel_creation_prerequisite; //! Modèle de donnée pour l'affichage des pré-requis lors de la création d'une tache
    QStandardItemModel *m_listModel_creation_attachedTo;  //! Modèle de donnée pour l'affichage de la composition lors de la création d'une tache
    QMessageBox::StandardButton m_reply; //! Resultat de fenêtre de confirmation
    ProjectManager &projectManager; //! Une référence sur le ProjectManager
    SchedulingManager &scheduleManager; //! Une référence  sur le ProgrammationManager
    IOManager m_ioManager; //! Permet de gérer les import/export diverses grâce au pattern design Builder
    Project * m_currentProject; //! Pointeur sur le projet courant
    Task * m_currentTask; //! Pointeur sur la tâche courante
    UniqueTask * m_scheduleTask; //! Pointeur sur la programmation courante
    QDateTime m_firstDayOfWeek; //! Un attribut de type QDateTime, le premier jour de la semaine

    bool event(QEvent *event); //! Permet la gestion des évenements

    //! \brief  Rafraichi une arborescence de type TreeView
    //! \param model : Le modèle de donnée lié
    //! \param view : La vue à rafraichir
    //! \return  void
    void updateTreeView(QStandardItemModel *model, QTreeView *view);

    //! \brief  Rafraichi le calendrier
    //! \param void
    //! \return  void
    void updateScheduler();


private slots:

    //! \brief  Affiche la liste de tous les projets chargés en mémoire dans la vue editeur
    //! \param void
    //! \return  void
    void editing_selectionProject();

    //! \brief  Supprime l'objet sélectionné dans la vue editeur
    //! \param void
    //! \return  void
    void deleteSelection();

    //! \brief Lors d'un clic sur un objet de la vue editeur, affiche le contenu de l'objet dans l'interface d'édition
    //! \return  void
    void editing_clickTree(const QModelIndex&);

    //! \brief  Lors d'un double clic sur un projet, affiche le contenu du projet dans la vue editeur
    //! \return  void
    void editing_doubleclickTree(QModelIndex);

    //! \brief  Permet de sélectionner un pré-requis pour une tache existante
    //! \param void
    //! \return  void
    void editing_prerequisiteSelection();

    //! \brief  Permet de sélectionner une tache composite d'attache pour une tache existante
    //! \param void
    //! \return  void
    void editing_attachedToSelection();

    //! \brief  Permet de sélectionner un pré-requis pour une tache en cours de création
    //! \param void
    //! \return  void
    void creation_prerequisiteSelection();

    //! \brief  Permet de sélectionner une tache composite d'attache pour une tache en cours de création
    //! \param void
    //! \return  void
    void creation_attachedToSelection();

    //! \brief  Edite l'objet sélectionné et valide les changements
    //! \param void
    //! \return  void
    void edit();

    //! \brief  Change l'interface de création d'un objet selon son type
    //! \param type : Chaine de caractères contenant le type de l'objet à créer
    //! \return  void
    void creationView(QString type);

    //! \brief  Crée un objet avec les paramètres rentrés dans l'interface de création
    //! \param void
    //! \return  void
    void createElement();

    //! \brief  Permet de vider le pointeur de tache courante lors d'un changement d'onglet d'édition
    //! \param void
    //! \return  void
    void switchEditTab(){m_currentTask=NULL;}

    //! \brief  Permet de supprimer le dernier pré-requis de la tache en cours de création
    //! \param void
    //! \return  void
    void prerequisiteCreationUndo();

    //! \brief  Permet de supprimer le dernier pré-requis de la tache en cours d'édition
    //! \param void
    //! \return  void
    void prerequisiteEditUndo();

    //! \brief  Permet de sélectionner une tache parmis celles existantes pour la programmer
    //! \param void
    //! \return  void
    void scheduler_taskSelection();

    //! \brief  Lors de la sélection d'une tache à programmer, vérifie les contraintes de disponibilité en encadrant les possibilités offertes par l'interface
    //! \param t : durée envoyée à chaque mise à jour du widget TimeEdit
    //! \return  void
    void scheduler_checkTime(QTime t);

    //! \brief  Lors de la sélection d'une tache à programmer, vérifie les contraintes de disponibilité en encadrant les possibilités offertes par l'interface
    //! \param t : durée envoyée à chaque mise à jour du widget TimeEdit
    //! \return  void
    void scheduler_checkDeadline(QDateTime t);

    //! \brief  Remplis automatiquement le champs date et heure à chaque clic sur un endroit du calendrier
    //! \param numéro de la ligne selectionnée
    //! \param numéro de la colomne selectionnée
    //! \return  void
    void scheduler_setDate(int row,int column);

    //! \brief  Plannifie une tache ou une activité avec les données rentrées dans l'interface de programmation
    //! \param void
    //! \return  void
    void scheduler_save();

    //! \brief  Affiche la semaine précédente
    //! \param void
    //! \return  void
    void scheduler_previousWeek();

    //! \brief  Affiche la semaine suivante
    //! \param void
    //! \return  void
    void scheduler_nextWeek();

    //! \brief  Supprime les plannifications selectionnées (une seule, ou par lot)
    //! \param void
    //! \return  void
    void deleteScheduling();

    //! \brief  Exporte les données du calendrier et des projets sous la forme souhaitée
    //! \param void
    //! \return  void
    void scheduler_export();

    //! \brief  Exporte les données du calendrier et des projets depuis un fichier source
    //! \param void
    //! \return  void
    void scheduler_import();

};

bool checkCoherence(Task* parent, Task *prerequisite);  //! Vérifie la cohérence temporelle d'une tache et d'un pré-requis

#endif // MAINWINDOW_H
