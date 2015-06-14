#ifndef ABSTRACTBUILDER_H
#define ABSTRACTBUILDER_H



//! \file abstractbuilder.h
//! \brief Classe (abstraite) AbstractBuilder
//! \author Passot J & Laviolette E
//! \version 2.1
//! \date Samedi 13 Juin 2015

#include<QString>
#include "schedulingmanager.h"
#include "projectmanager.h"


//! \class AbstractBuilder
//! \brief Utilisation du design pattern Builder pour gérer plusieurs types d'import et d'export de données.

class AbstractBuilder
{
protected:
    QString m_file_path; //! Chemin du fichier utilisé pour l'import ou l'export
    std::map<Task*,int> m_pointer_to_id; //! Map qui fait le lien entre une adresse de Task et un identifiant numérique
    std::map<int,Task*> m_id_to_pointer; //! Map qui fait le lien entre un identifiant numérique et une adresse de Task
    int m_id_incrementer; //! Entier qui s'incrémente lors de l'enregistrement des Task

public:

    //! \brief Constructeur de la classe AbstractBuilder
    //! \param path : Chemin du fichier utilisé pour l'import ou l'export
    AbstractBuilder(QString path):m_file_path(path),m_id_incrementer(0){}

    //! \brief Destructeur de la classe AbstractBuilder
    ~AbstractBuilder();

    //! \brief Enregistre le chemin du fichier
    //! \param path : Une chaine de caractère contenant le chemin du fichier
    //! \return  void
    void setFilePath(QString path){m_file_path=path;}

    //! \brief Sauvegarde les données chargées dans le programme
    //! \param project_list : référence sur la liste des projets à sauvegarder
    //! \param scheduling_list : référence sur la liste des planifications à sauvegarder
    //! \return  void
    virtual void writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list)=0;

    //! \brief Importe les données depuis une source
    //! \param projectManager : référence sur l'instance du ProjectManager
    //! \param schedulingManager : référence sur l'instance du SchedulingManager
    //! \return  void
    virtual void readInput(ProjectManager &projectManager, SchedulingManager &schedulingManager)=0;
};

#endif // ABSTRACTBUILDER_H
