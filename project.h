#ifndef PROJECT_H
#define PROJECT_H

//! \file project.h
//! \brief Classe Project
//! \author Passot J & Laviolette E
//! \version 2.0
//! \date Samedi 13 Juin 2015

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QStandardItemModel>
#include "task.h"
#include "blendtask.h"

//! \class ProjectManager
//! \brief Implémentation de la classe Project qui contient des taches et sera gérée par le ProjectManager
class Project
{
protected:
    QString m_title; //! Titre du projet
    QDateTime m_disponibility; //! Disponibilité du projet
    QDateTime m_deadline; //! Echéance du projet
    vector<Task *> m_list; //! Liste des taches composant le projet
    vector<Task *> m_deadList; //! Utilisé pour faire la liste des sous taches à supprimer lors de la supression d'une tache composite



    //! \brief Constructeur de recopie classe Project
    //! \param Une référence constante sur un Project
    //! \return  Un projet nouvellement crée
    Project(const Project& source);


    //! \brief Surcharge de l'opérateur d'affectation
    //! \param Une référence constante sur un Project à cloner
    //! \return Une référence sur un projet
    Project& operator=(const Project& source);



    //! \brief Rempli la liste des sous taches à supprimer lors de la supression d'une tache composite
    //! \param Une référence sur une Task à supprimer
    //! \return void
    void fillDeadList(Task * element);


    //! \brief Nettoie la tache passée en argument de tout les pré-requis contenus dans m_deadList
    //! \param Une référence sur une Task à nettoyer
    //! \return void
    void cleanPrerequisite(Task * element);

    //! Permet l'accès aux données contenues dans le projet au classes qui gèrent les entrées/sorties
    friend class AbstractBuilder;

public:

    //! \brief Constructeur de la classe Project
    //! \param Le titre du projet de type QString
    //! \param La deadline du projet de type QDateTime
    //! \param Quand peut on démarrer le projet de type QSDateTime
    //! \return  Un projet nouvellement crée
    Project(QString title, QDateTime disponibility, QDateTime deadline);

     //! \brief Desctructeur de la classe Project
    ~Project();

    //! \brief Accesseur en écriture, ajoute une Task au Project
    //! \param Un pointeur sur une Task
    //! \return void
    void addElement(Task * element);


    //! \brief Accesseur en écriture, désindexe une tache du projet, ne la supprime pas
    //! \param Un pointeur sur une Task
    //! \return void
    void removeElement(Task * element);


    //! \brief Supprime une tache de la mémoire et tous les pointeurs qui pointe vers elle
    //! \param Un pointeur sur une Task
    //! \return void
    void deleteElement(Task * element);

    //! \brief Affiche l'arborescende des taches stockées dans le projet
    //! \param Modele de donnée pour l'affichage de l'arborescence
    //! \return void
    void display(QStandardItemModel * m_treeModel);

    //! \brief Accesseur en lecture du titre du Project
    //! \param void
    //! \return Le titre du Project dans une QString
    QString getTitle(){return m_title;}

    //! \brief Accesseur en écriture, modifie le titre du Project
    //! \param Le titre du projet de type QString
    //! \return void
    void setTitle(QString title){m_title=title;}

    //! \brief Accesseur en lecture, de la date à laquelle le Project peut démarrer
    //! \param void
    //! \return La date en question de type QDateTime
    QDateTime getDisponibility(){return m_disponibility;}

    //! \brief Accesseur en écriture, modifie la date de départ potentielle du projet
    //! \param La date en question de type QDateTime
    //! \return void
    void setDisponibility(QDateTime disponibility){m_disponibility=disponibility;}

    //! \brief Accesseur en lecture, de la deadline du Project
    //! \param void
    //! \return La date en question de type QDateTime
    QDateTime getDeadline()const {return m_deadline;}

    //! \brief Accesseur en écriture, modifie la deadline du Project
    //! \param La date en question de type QDateTime
    //! \return void
    void setDeadline(QDateTime deadline){m_deadline=deadline;}

    //! \brief Accesseur en lecture, récupère la liste des Task du Project
    //! \param void
    //! \return La liste constante des Task du Project
    const vector<Task *>& getList(){return m_list;}

    //! \brief Surcharge de l'opérateur de comparaison < sur des Project.
    //! \brief Renvoie true si la deadline du Project sur lequel on appelle la méthode est antérieure à celle de celui passé en paramètre, permet de trier les Project
    //! \param Une référence constante sur une project
    //! \return Un booléen
    bool operator < (const Project& b) const;



};


#endif // PROJECT_H
