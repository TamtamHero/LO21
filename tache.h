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
    vector<Tache*> m_precedent;
    Tache(QString titre,QDateTime disponibilite,QDateTime echeance);

    Tache(const Tache& source);
    Tache& operator=(const Tache& source);

public:
    QString getTitre() { return m_titre;}
    QDateTime getDisponibility(){return m_disponibilite;}
    QDateTime getDeadline(){return m_echeance;}
    virtual void afficher(QStandardItem * parent)=0;

    virtual ~Tache()=0;

};

Q_DECLARE_METATYPE(Tache *)

#endif // TACHE_H
