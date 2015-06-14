#ifndef TASK_H
#define TASK_H

//! \file task.h
//! \brief Classe Task
//! \author Passot J & Laviolette E
//! \version 1.2
//! \date Samedi 13 Juin 2015

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QVariant>

#include "calendarexception.h"

//! \enum Enumération entre l'édition d'une tache ou sa création
enum tabValue{EDIT,CREATION};

//! \namespace Std utilisé dans tout ce fichier d'en-tête
using namespace std;


//! \class Task
//! \brief Implémentation de la classe abstraite Task, classe de base de notre projet avec ses attibuts et ses méthodes
class Task
{

protected:
    QString m_title; //! Titre de la tache
    QDateTime m_disponibility; //! Date à partir de quand on peut potentiellement la commencer
    QDateTime m_deadline; //! Deadline de la tache
    bool m_status; //! Statut de la tache : true si déjà complétée, false sinon
    Task* m_parent; //! Pointeur vers la tâche parente
    vector<Task*> m_prerequisite; //! Liste des tache requise pour effectuer la tache courante

     //! \brief Constructeur de la classe Task
     //! \param Le titre de la tache
     //!  \param La date potentielle de début de la tache
     //! \param La deadline de la tache
    Task(QString title,QDateTime disponibility,QDateTime deadline);


    //! \brief Constructeur de recopie la classe Task
    //! \param Une référence constante vers la tache à recopier
    //! \return La tache créée par recopie
    Task(const Task& source);

    //! \brief Surcharge de l'opérateur d'affectation "="
    //! \param Une référence constante vers la tache à recopier
    //! \return Une référence vers la tache créée par recopie
    Task& operator=(const Task& source);

public:

    //! \brief Accesseur en écriture, lie la tache actuelle à une tache parente
    //! \param Un pointeur vers la tache parente à lier
     //! \return void
    void setParent(Task * parent);

    //! \brief Accesseur en lecture, récupère le parent lié à la tache courante
    //! \param void
     //! \return Un pointeur vers la tache parente
    Task* getParent()const{ return m_parent;}

    //! \brief Accesseur en lecture, récupère le titre de la tache courante
    //! \param void
     //! \return Un QString contenant le titre
    QString getTitle()const{return m_title;}

    //! \brief Accesseur en écriture, affecte un titre à la tache courante
    //! \param un QString contenant le titre
     //! \return void
    void setTitle(QString title){m_title=title;}

    //! \brief Accesseur en lecture, récupère la date potentielle de début de la tache
    //! \param void
     //! \return Un QDateTime contenant la date
    QDateTime getDisponibility()const{return m_disponibility;}

    //! \brief Accesseur en écriture, affecte un début potentiel de tache à la tache courante
    //! \param un QDateTime contenant la date
     //! \return void
    void setDisponibility(QDateTime disponibility){m_disponibility=disponibility;}

    //! \brief Accesseur en lecture, récupère la deadline de la tache
    //! \param void
     //! \return Un QDateTime contenant la deadline
    QDateTime getDeadline() const{return m_deadline;}

    //! \brief Accesseur en écriture, affecte une deadline à la tache courante
    //! \param un QDateTime contenant la deadline
     //! \return void
    void setDeadline(QDateTime deadline){m_deadline=deadline;}

    //! \brief Accesseur en lecture, récupère le tableau des Task requise à l'accomplissement de la tache courante
    //! \param void
    //! \return Un tableau Vector de tache
    vector<Task*>& getPrerequisite(){return m_prerequisite;}

    //! \brief Accesseur en écriture, affecte à la tache le statut "effectué" ou non
    //! \param Un booléen contenant la valeur de la réalisation de la tache
     //! \return void
    void setStatus(bool status){m_status=status;}

    //! \brief Accesseur en lecture, récupère le statut de réalisation de la tache courante
    //! \param void
    //! \return Un booléen contenant ce statut
    bool getStatus(){return m_status;}

    //! \brief Accesseur en écriture, aajoute une tache requise à la réalisation de la tache actuelle
    //! \param Une pointeur vers la Task à ajouter
     //! \return void
    void addPrerequisite(Task * prerequisite);

    //! \brief Détermine si les tache requise pour la tache courant sont toutes programmées
    //! \param void
     //! \return Booléen (true si oui, false sinon)
    bool arePrerequisiteScheduled();

    //! \brief Méthode statit vérifiant si les taches requises sont des dates de début potentiel avant la tache courant
    //! \param Un pointeur sur une tache et un pointeur sur la tache requise à comparer
     //! \return Booléen (true si oui, false sinon)
    static bool checkPrerequisite(Task* task,Task * prerequisiteTask);

    //! \brief Méthode statit vérifiant si la date de disponibilité d'une tache parente d'une tache est bien antérieure à celle de la tache courante
    //! \param Un pointeur sur une tache et un pointeur sur la tache mère à comparer
     //! \return Booléen (true si oui, false sinon)
    static bool checkAttaskdTo(Task* task,Task * motherTask);

    //! \brief Surcharge de l'opérateur de comparaison "<", nécessaire à la comparaison de deux taches
    //! \param Une référence constante vers la tache à comparer avec la tache courante
     //! \return Booléen (true si oui, false sinon)
    bool operator < (const Task& b) const;

   //! \struct taskCompare

    struct taskCompare
    {
          bool operator()(const Task* l, const Task* r) //! Surcharge des () pour comparer deux taches
          {
            return *l < *r;
          }
    };

    //! \brief Destructeur virtuelle de la classe Task
    virtual ~Task()=0;

};


Q_DECLARE_METATYPE(Task *)

#endif // TASK_H
