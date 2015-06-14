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
    QMessageBox::StandardButton m_reply; //! DESCRIPTION
    ProjectManager &projectManager; //! Une référence sur le ProjectManager
    SchedulingManager &scheduleManager; //! Unne référence  sur le ProgrammationManager
    IOManager m_ioManager; //! DESCRIPTION
    Project * m_currentProject; //! Un pointeur sur un projet
    Task * m_currentTask; //! Un pointeur sur une tâche
    UniqueTask * m_scheduleTask; //! DESCRIPTION
    QDateTime m_firstDayOfWeek; //! Un attribut de type QDateTime, le premier jour de la semaine

    bool event(QEvent *event); //! DESCRIPTION

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void updateTreeView(QStandardItemModel *model, QTreeView *view);

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void updateScheduler();


private slots:

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void editing_selectionProject();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void deleteSelection();

    //! \brief  DESCRIPTION
    //! \param DESCRIPTION
    //! \return  void
    void editing_clickTree(const QModelIndex&);

    //! \brief  DESCRIPTION
    //! \param DESCRIPTION
    //! \return  void
    void editing_doubleclickTree(QModelIndex);

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void editing_prerequisiteSelection();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void editing_attachedToSelection();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void creation_prerequisiteSelection();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void creation_attachedToSelection();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void edit();

    //! \brief  DESCRIPTION
    //! \param DESCRIPTION
    //! \return  void
    void creationView(QString type);

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void createElement();

    //! \brief  DESCRIPTION
    //! \param DESCRIPTION
    //! \return  void
    void switchEditTab(){m_currentTask=NULL;}

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void prerequisiteCreationUndo();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void prerequisiteEditUndo();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void scheduler_taskSelection();

    //! \brief  DESCRIPTION
    //! \param DESCRIPTION
    //! \return  void
    void scheduler_checkTime(QTime t);

    //! \brief  DESCRIPTION
    //! \param DESCRIPTION
    //! \return  void
    void scheduler_checkDeadline(QDateTime t);

    //! \brief  DESCRIPTION
    //! \param DESCRIPTION
    //! \param DESCRIPTION
    //! \return  void
    void scheduler_setDate(int row,int column);

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void scheduler_save();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void scheduler_previousWeek();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void scheduler_nextWeek();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void deleteScheduling();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void scheduler_export();

    //! \brief  DESCRIPTION
    //! \param void
    //! \return  void
    void scheduler_import();

};

bool checkCoherence(Task* parent, Task *prerequisite);  //! DESCRIPTION

#endif // MAINWINDOW_H
