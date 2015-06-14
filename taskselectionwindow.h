#ifndef TASKSELECTIONWINDOW_H
#define TASKSELECTIONWINDOW_H

//! \file taskselectionwindow.h
//! \brief Classe taskselectionwindow
//! \author Passot J & Laviolette E
//! \version 1.2
//! \date Samedi 13 Juin 2015

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "project.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

//! \enum Traite les cas selon si la fenêtre permet de sélectionner une attache ou un pré-requis
enum m_selectedTaskType{PREREQUISITE,ATTACHEDTO};

//! \class TaskSelectionWindow
//! \brief Implémentation de la classe TaskSelectionWindow, qui permet de sélectionner une attache ou un pré-requis
class TaskSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    //! \brief Constructeur de la classe TaskSelectionWindow
    //! \param parent : Pointeur vers le widget parent de la fenêtre
    //! \param project : Pointeur sur le projet dans lequel on veux faire la sélection
    //! \param type : indique le type de la sélection: attache ou pré-requis
    TaskSelectionWindow(QWidget *parent,Project *project,m_selectedTaskType type);

    //! \brief Desctructeur de la classe TaskSelectionWindow
    ~TaskSelectionWindow();

    //! \brief Accesseur en lecture de la tache selectionnée
    //! \param void
    //! \return Un pointeur vers la tache selectionnée
    Task * getSelectedTask(){return m_selectedTask;}

private:
    QStandardItemModel *m_treeModel; //! Modele de donnée pour l'affichage du projet
    QTreeView *treeView;  //! Vue pour l'affichage des données
    QPushButton *pushButton_TaskSelection_selection; //! Boutton de validation de la selection
    QPushButton *pushButton_TaskSelection_notAttached; //! Boutton d'annulation de la selection (permet de créer une tache sommet)
    Task *m_selectedTask; //! Un pointeur vers la tache selectionnée
    m_selectedTaskType m_type; //! Attribut indicateur de la nature de la tache que l'on veux sélectionner

private slots:

    //! \brief Stocke la tache sélectionnée et quitte la fenêtre
    //! \param void
    //! \return void
    void sendSelection();

    //! \brief Stocke NULL dans le pointeur de résultat et quitte la fenêtre
    //! \param void
    //! \return void
    void sendNotAttached();
};

#endif // TASKSELECTIONWINDOW_H
