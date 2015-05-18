#ifndef TACHE_H
#define TACHE_H

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QVariant>

#include "calendarexception.h"

enum tabValue{PROJECT,BLEND_TASK,UNIQUE_TASK};

using namespace std;

class Tache
{

protected:
    QString m_titre;
    QDateTime m_disponibilite;
    QDateTime m_echeance;
    int m_status;
    Tache* m_parent;
    vector<Tache*> m_prerequisite;
    Tache(QString titre,QDateTime disponibilite,QDateTime echeance);

    Tache(const Tache& source);
    Tache& operator=(const Tache& source);

public:
    void setParent(Tache * parent){m_parent=parent;}
    Tache* getParent() { return m_parent;}
    QString getTitre(){return m_titre;}
    void setTitle(QString title){m_titre=title;}
    QDateTime getDisponibility(){return m_disponibilite;}
    void setDisponibility(QDateTime disponibility){m_disponibilite=disponibility;}
    QDateTime getDeadline(){return m_echeance;}
    void setDeadline(QDateTime deadline){m_echeance=deadline;}
    vector<Tache*>& getPrerequisite(){return m_prerequisite;}
    void addPrerequisite(Tache * prerequisite);
    virtual void afficher(QStandardItem * parent)=0;

    static bool checkPrerequisite(Tache* task,Tache * prerequisiteTask);
    static bool checkAttachedTo(Tache* task,Tache * motherTask);
    virtual ~Tache()=0;

};

Q_DECLARE_METATYPE(Tache *)

#endif // TACHE_H
