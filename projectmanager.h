#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

//! \file projectmanager.h
//! \brief Classe ProjectManager
//! \author Passot J & Laviolette E
//! \version 1.1
//! \date Samedi 13 Juin 2015


#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include "abstractcontainer.h"
#include "project.h"

//! \class ProjectManager
//! \brief Classe qui gère les projet, implémentée avec le Design Pattern Singleton


class ProjectManager : public AbstractContainer<Project>
{
private:
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_Single instance handling-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    //! \brief Constructeur Privé de la classe ProjectManager
    ProjectManager();

    //! \brief Desctructeur Privé de la classe ProjectManager
    ~ProjectManager();

    //! \brief Constructeur de recopie Privé de la classe ProjectManager
    //! \param Une référence const sur le ProjectManager à copier
    ProjectManager(const ProjectManager& copy);

    //! \brief Surcharge de l'opérateur d'affectation placé en privé de la classe ProjectManager
    //! \param Une référence const sur le ProjectManager à copie
    ProjectManager& operator=(const ProjectManager& copy);

    //! \struct Handler qui sert à gérer le singleton sur la classe ProjectManager
    struct Handler{
            ProjectManager* m_instance; //! L'instance du ProjectManager
            Handler():m_instance(0){} //! Le constructeur par défaut avec l'instance à 0 du ProjectManager
            ~Handler(){ if (m_instance) delete m_instance; } //! Desctructeur appelé à la sortie
    };
    static Handler m_handler; //! Le Handler Static permettant de gérer le ProjectManager unique
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

public:

    //! \brief La méthode static permettant de renvoyer l'instance créée du ProjectManager
    //! \param void
    //! \return  Une référence sur le ProjectManager instancié de manière unique
    static ProjectManager& getInstance();

    //! \brief La méthode static permettant de libérer l'unique instance de type ProjectManager
    //! \param void
    //! \return  void
    static void freeInstance();

    //! \brief La méthode static permettant de libérer l'unique instance de type ProjectManager
    //! \param Le titre du projet à ajouter au Manager de projets
    //! \param La date potentielle de départ du projet à ajouter au manager de projets
    //! \param La deadline du projet à ajouter au manager de projets
    //! \return  void
    void addElement(QString title, QDateTime disponibility, QDateTime deadline);

    //! \brief Méthode d'affichage des projets contenus
    //! \param model : Pointeur vers un modèle de donnée de stockage
    //! \return  void
    void display(QStandardItemModel * model);

};

Q_DECLARE_METATYPE(Project *)

#endif // PROJECTMANAGER_H
