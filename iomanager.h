#ifndef IOMANAGER_H
#define IOMANAGER_H


//! \file iomanager.h
//! \brief Classe IOManager
//! \author Passot J & Laviolette E
//! \version 2.0
//! \date Samedi 13 Juin 2015

#include "abstractbuilder.h"

//! \class IOManager
//! \\brief Joue le role du directeur dans le design pattern Builder
class IOManager
{
private:
    AbstractBuilder *m_builder; //! Pointeur vers un Builder à utiliser
public:

    //! \brief Constructeur de la classe BlendTask
    //! \param void
    IOManager();

    //! \brief Destructeur de la classe BlendTask
    ~IOManager();

    //! \brief Accesseur en écriture du pointeur de Builder
    //! \param pointeur vers un Builder
    //! \return  void
    void setBuilder(AbstractBuilder * builder){m_builder=builder;}

    //! \brief Importe les données de la source dans les gestionnaires
    //! \param projectManager : référence sur le gestionnaire de projet
    //! \param schedulingManager : référence sur le gestionnaire de planification
    //! \return  void
    void importFrom(ProjectManager &projectManager, SchedulingManager &schedulingManager);

    //! \brief exporte les données de estionnaires dans un destinataire
    //! \param projectManager : référence sur le gestionnaire de projet
    //! \param schedulingManager : référence sur le gestionnaire de planification
    //! \return  void
    void exportTo(ProjectManager &projectManager, SchedulingManager &schedulingManager);
};

#endif // IOMANAGER_H
