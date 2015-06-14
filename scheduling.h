#ifndef SCHEDULING_H
#define SCHEDULING_H

//! \file scheduling.h
//! \brief Classe Project
//! \author Passot J & Laviolette E
//! \version 1.0
//! \date Samedi 13 Juin 2015

#include <QString>
#include <QDateTime>
#include "uniquetask.h"

//! \class Scheduling
//! \brief Implémentation de la classe Scheduling(Programmation) qui fait le lien entre nos deux modules de programmation
//! \brief Ici sont contenus les informations relatives à une activités.
//! \brief Ainsi qu'un pointeur vers une tâche
//! Si le pointeur est NULL.. Alors la programmation est une planification d'activité
//! Sinon il s'agit d'une planification de tâche
class Scheduling
{
protected:
    QDateTime m_date; //! La date de l'activité
    QTime m_duration; //! La durée de l'activité
    QString m_title; //! Le titre de l'activité
    UniqueTask *m_task; //! Pointeur vers une tache


    //! \brief Constructeur de la classe Scheduling pour construire une activité (pointeur task NULL)
    Scheduling(QDateTime date,QTime duration,QString title);
    //! \brief Constructeur de la classe Scheduling pour construire une planification de task (utilisation du m_task)
    Scheduling(QDateTime date,QTime duration,UniqueTask *task);

    //! DESCRIPTION
    friend class SchedulingManager;

public:

    //! \brief Destructeur de la classe Scheduling
    ~Scheduling();

    //! \brief Accesseur en lecture de la date
    //! \param void
    //! \return La date de type QDateTime
    QDateTime getDateTime()const {return m_date;}

    //! \brief Accesseur en lecture du titre
    //! \param void
    //! \return Le titre du Project dans une QString
    QString getTitle()const{return m_title;}

    //! \brief Accesseur en lecture de la durée
    //! \param void
    //! \return La durée du Project dans un QTime
    QTime getDuration(){return m_duration;}

    //! \brief Accesseur en lecture de la Task (unitaire) à programmer
    //! \param void
    //! \return Un pointeur vers une UniqueTask
    UniqueTask* getTask(){return m_task;}

    //! \brief Surcharge de l'opérateur de comparaison "<"
    //! \param Une référence sur une programmation pour comparer celle grâce à laquelle
    //! \return Le titre du Project dans une QString
    bool operator < (const Scheduling& b) const;

};

#endif // SCHEDULING_Hd
