#ifndef SCHEDULINGSchedulingManager_H
#define SCHEDULINGSchedulingManager_H

//! \file schedulingmanager.h
//! \brief Classe SchedulingManager
//! \author Passot J & Laviolette E
//! \version 1.1
//! \date Samedi 13 Juin 2015

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include <QMessageBox>
#include "abstractcontainer.h"
#include "scheduling.h"

//! \class SchedulingManager
//! \brief Classe qui gère les programmations, implémentée avec le Design Pattern Singleton
class SchedulingManager : public AbstractContainer<Scheduling>
{
private:
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_Single instance handling-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    //! \brief Constructeur Privé de la classe SchedulingManager
    SchedulingManager();

    //! \brief Desctructeur Privé de la classe SchedulingManager
    ~SchedulingManager();

    //! \brief Constructeur de recopie Privé de la classe SchedulingManager
    //! \param Une référence const sur le SchedulingManager à copier
    SchedulingManager(const SchedulingManager& copy);

    //! \brief Surcharge de l'opérateur d'affectation placé en privé de la classe SchedulingManager
    //! \param Une référence const sur le SchedulingManager à copie
    SchedulingManager& operator=(const SchedulingManager& copy);

     //! \struct Handler qui sert à gérer le singleton sur la classe SchedulingManager
    struct Handler{
            SchedulingManager* m_instance;  //! L'instance du SchedulingManager
            Handler():m_instance(0){} //! Le constructeur par défaut avec l'instance à 0 du SchedulingManager
            ~Handler(){ if (m_instance) delete m_instance; } //! Destructeur appelé à la sortie
        };
    static Handler m_handler; //! Le Handler Static permettant de gérer le SchedulingManager unique
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

public:

    //! \brief La méthode static permettant de renvoyer l'instance créée du SchedulingManager
    //! \param void
    //! \return  Une référence sur le SchedulingManager instancié de manière unique
    static SchedulingManager &getInstance();


    //! \brief La méthode static permettant de libérer l'unique instance de type SchedulingManager
    //! \param void
    //! \return  void
    static void freeInstance();


    list<const Scheduling *> findTaskSchedulings(UniqueTask *element);

    //! \brief Ajoute une activité à la programmation
    //! \param La date se l'activité
    //! \param la durée de l'activité
    //! \param le titre de l'activité
    //! \return  void
    void addElement(QDateTime date, QTime duration, QString title, bool import);

    //! \brief Planifie une tache déjà existante
    //! \param Une date
    //! \param Une durée
    //! \param Un pointeur vers une tache
    //! \return  void
    void addElement(QDateTime date,QTime duration,UniqueTask *task, bool import);

    //! \brief Retire un élément de la programmation
    //! \param Un pointeur vers l'élément à retirer
    //! \return  void
    void removeElement(Scheduling *element);


};

Q_DECLARE_METATYPE(Scheduling *)

#endif // SCHEDULINGSchedulingManager_H
