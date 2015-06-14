#ifndef XMLBUILDER_H
#define XMLBUILDER_H
#include<QXmlStreamWriter>
#include<QFile>
#include <QDomDocument>


//! \file xmlbuilder.h
//! \brief Classe xmlBuilder
//! \author Passot J & Laviolette E
//! \version 1.0
//! \date Samedi 13 Juin 2015

#include"abstractbuilder.h"

//! \class XmlBuilder
//! \brief Classe XmlBuilder héritant de la classe AbstractBuilder publiquement, servant à l'import/export XML
class XmlBuilder : public AbstractBuilder
{
public:

    //! \brief Constructeur de la classe XmlBuilder
    //! \param Le chemin de du fichier XML
    XmlBuilder(QString file_path):AbstractBuilder(file_path){}

    //! \brief Destructeur de la classe XmlBuilder
    ~XmlBuilder();

    //! \brief Export (écriture) dans le fichier XML
    //! \param project_list : La liste des projets à écrire dans le fichier XML
    //! \param scheduling_list : La liste des planifications à écrire dans le fichier XML
    //! \return void
    void writeOutput(std::list<Project*>& project_list,std::list<Scheduling*>& scheduling_list);

    //! \brief Import(lecteur) dans le fichier XML
    //! \param projectManager : référence sur l'instance du ProjectManager
    //! \param schedulingManager : référence sur l'instance du SchedulingManager
    //! \return void
    void readInput(ProjectManager &projectManager, SchedulingManager &schedulingManager);

private:

    //! \brief Enregistrement récursif de l'arbre des taches
    //! \param stream : référence vers le flux XML
    //! \param task : pointeur sur la tache à parcourir
    //! \return void
    void saveTask(QXmlStreamWriter& stream, Task * task);

};

#endif // XMLBUILDER_H
