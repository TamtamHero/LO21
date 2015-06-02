#ifndef TACHE_H
#define TACHE_H

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QVariant>

#include "calendarexception.h"

enum tabValue{EDIT,CREATION};

using namespace std;

class Tache
{

protected:
    QString m_titre;
    QDateTime m_disponibilite;
    QDateTime m_echeance;
    bool m_status; // false if not done, true if done
    Tache* m_parent;
    vector<Tache*> m_prerequisite;
    Tache(QString titre,QDateTime disponibilite,QDateTime echeance);

    Tache(const Tache& source);
    Tache& operator=(const Tache& source);

public:
    void setParent(Tache * parent){m_parent=parent;}
    Tache* getParent()const{ return m_parent;}
    QString getTitre()const{return m_titre;}
    void setTitle(QString title){m_titre=title;}
    QDateTime getDisponibility()const{return m_disponibilite;}
    void setDisponibility(QDateTime disponibility){m_disponibilite=disponibility;}
    QDateTime getDeadline() const{return m_echeance;}
    void setDeadline(QDateTime deadline){m_echeance=deadline;}
    vector<Tache*>& getPrerequisite(){return m_prerequisite;}
    void setStatus(bool status){m_status=status;}
    bool getStatus(){return m_status;}
    void addPrerequisite(Tache * prerequisite);
    virtual void afficher(QStandardItem * parent)=0;
    bool arePrerequisiteScheduled();

    static bool checkPrerequisite(Tache* task,Tache * prerequisiteTask);
    static bool checkAttachedTo(Tache* task,Tache * motherTask);
    bool operator < (const Tache& b) const;

    struct taskCompare
    {
          bool operator()(const Tache* l, const Tache* r)
          {
            return *l < *r;
          }
    };

    virtual ~Tache()=0;

};


Q_DECLARE_METATYPE(Tache *)

#endif // TACHE_H
