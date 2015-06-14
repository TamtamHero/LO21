#ifndef UNIQUETASK_H
#define UNIQUETASK_H
#define PREEMPT_TASK_MAX_DURATION 12

//! \file uniquetask.h
//! \brief Classe Tache Unitaire
//! \author Passot J & Laviolette E
//! \version 1.0
//! \date Samedi 13 Juin 2015

#include "task.h"
#include "blendtask.h"
#include <QVariant>

//! \class UniqueTask
//! \brief Une UniqueTask est une tache unitaire, l'atome de base de notre conception. Tache unitaire héritant de la classe Task
//! \brief Une Tache unitaire est une spécialisation de tache

class UniqueTask: public Task
{

protected:
    QTime m_duration; //! La durée de la tache
    bool m_preemptable; //! Tache préemptable ou non

public:

    //! \brief Constructeur de la classe UniqueTask
    //! \param title : titre de la tache unitaire que l'on crée
    //! \param disponibility : date de début de la tache unitaire créée
    //! \param deadline : date de fin de la tache unitaire créee
    //! \param durée : durée de la tache unitaire que créee
    //!  \param preemptable : préemptabilité de la tache crée
    UniqueTask(QString title,QDateTime disponibility,QDateTime deadline,QTime duration,bool preemptable=false);

    //! \brief Accesseur en lecture, récupère la durée de la tache courante
    //! \param void
    //! \return Un QTime contenant la durée de la tache courante
    QTime getDuree() const {return m_duration;}

    //! \brief Accesseur en lecture, récupère le caractère préemptable de la tache courante
    //! \param void
    //! \return Un booléen contenant ce statut
    bool getPreemptability(){return m_preemptable;}

    //! \brief Accesseur en écriture, affecte une durée à la tache courante
    //! \param Un QTime contenant la durée
    //! \return void
    void setDuree(QTime duration);

    //! \brief Accesseur en écriture, affecte un booléen au caractère préemptable d'une tache
    //! \param Un booléen contenant le statut
    //! \return void
    void setPreemptability(bool choice);


    //! \brief Accesseur en lecture, récupère la liste des tache unitaire requise à la tache courante
    //! \param void
    //! \return Une liste contenant les taches requises à la réalisation del a tache unitaire courante
    list<Task *> getAllUniquePrerequisite();

    //! \brief Le destructeur de la classe UniqueTask en virtuel (pour éventuel evolution future)
    virtual ~UniqueTask();
};

Q_DECLARE_METATYPE(UniqueTask *)

#endif // UNIQUETASK_H
