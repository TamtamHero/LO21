#ifndef BLENDTASK_H
#define BLENDTASK_H

//! \file blendtask.h
//! \brief Classe Tache Composite
//! \author Passot J & Laviolette E
//! \version 1.0
//! \date Samedi 13 Juin 2015

#include "task.h"
#include "uniquetask.h"
#include <QVariant>

//! \class BlendTask
//! \\brief Une BlendTask est une Task qui est composée d'un ensemble de Task (Agrégation). Cette classe hérite de la classe Task
//! \brief C'est une spécialisation d'une tache

class BlendTask: public Task
{

protected:
    vector<Task *> m_element; //! Vecteur de taches représentant les taches composants cette tache composite

public:
    //! \brief Constructeur de la classe BlendTask
    //! \param title : titre de la tache composite que l'on crée
    //! \param disponibility : date potentiel de début de la tache composite que l'on crée
    //! \param deadline : date de fin de la tache composite que l'on crée
    BlendTask(QString title,QDateTime disponibility,QDateTime deadline);

    //! \brief Ajout d'une tache dans la tache composite
    //! \param : pointeur sur l'élément à ajouter
    //! \return void
    void addElement(Task * element);

    //! \brief Accesseur en lecture, récupération d'un élément
    //! \param void
    //! \return  vector<Task *>&
    vector<Task *>& getElement(){return m_element;}

    //! \brief Enregistre l'arborescende la tache dans des items d'affichage
    //! \param un pointeur sur l'item parent
    //! \return  void
    void display(QStandardItem * parent);

    //! \brief Accesseur en lecture qui récupére toutes les taches (sous forme de liste) qui
    //! \param un pointeur sur le pare
    //! \return  liste de taches
    list<Task*> getAllUniquePrerequisite();

    //! \brief Récupérer toutes les taches composants la tache composite et qui sont des taches unitaires
    //! \param void
    //! \return  liste de taches
    list<Task*> getAllUniqueSons();

    //! \brief Destructeur de la classe BlendTask
    virtual ~BlendTask();
};

Q_DECLARE_METATYPE(BlendTask *)

#endif // BLENDTASK_H
