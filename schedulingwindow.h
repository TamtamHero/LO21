#ifndef SCHEDULINGWINDOW_H
#define SCHEDULINGWINDOW_H

//! \file schedulingwindow.h
//! \brief Classe SchedulingWindow
//! \version 2.1
//! \date Samedi 13 Juin 2015

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "project.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>


//! \class SchedulingWindow
//! \brief Classe qui gère la sélection de la tache à programmer
class SchedulingWindow : public QDialog
{
    Q_OBJECT

public:

    //! \brief Constructeur de la classe SchedulingWindow
    SchedulingWindow(QWidget *parent, ProjectManager &manager);

     //! \brief Desctructeur Privé de la classe SchedulingWindow
    ~SchedulingWindow();

     //! \brief Accesseur renvoyant une pointeur vers la Task selectionnée
     //! \param void
     //! \return Un pointeur vers la Task
    Task * getSelectedTask(){return m_selectedTask;}

private:
    QStandardItemModel *Model; //! Modele de donnée pour l'affichage du projet
    QTreeView *treeView; //! Vue pour l'affichage des données
    QPushButton *pushButton_TaskSelection_selection; //! Boutton de validation de la selection
    QPushButton *pushButton_TaskSelection_projectSelection; //! Boutton de retour à la selection d'un projet
    ProjectManager& projectManager; //! Référence vers le gestionnaire de projet de l'application
    Project *selectedProject; //! Pointeur vers le projet sélectionné
    Task *m_selectedTask; //! Pointeur vers la tache selectionnée

private slots:

    //! \brief Retourne à la selection d'un projet
    //! \param void
    //! \return void
    void scheduler_selectionProject();

    //! \brief Stocke la tache sélectionnée et quitte la fenêtre
    //! \param void
    //! \return void
    void sendSelection();

    //! \brief S'active lors d'un clic de souris sur l'arbre, et récupère l'objet selectionné
    //! \return void
    void scheduler_clickTree(const QModelIndex&);

    //! \brief S'active lors d'un double clic, permet de pénetrer l'arbre
    //! \return void
    void scheduler_doubleclickTree(QModelIndex);
};

#endif // SCHEDULINGWINDOW_H
