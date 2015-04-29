#ifndef TACHE_H
#define TACHE_H

#include <vector>
#include <QString>
#include <QDateTime>

using namespace std;

class CalendarException{
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


class Tache
{

protected:
    QString m_titre;
    QDateTime m_disponibilite;
    QDateTime m_echeance;
    int m_status;
    vector<Tache*> m_precedent;
    Tache(QString titre,QDateTime disponibilite,QDateTime echeance);

    virtual ~Tache()=0;

public:


};

class TacheUnitaire: public Tache
{

protected:
    QTime m_duree;
    bool m_preemptable;

public:
    TacheUnitaire(QString titre,QDateTime disponibilite,QDateTime echeance,QTime duree,bool preemptable=false);
    QTime getDuree() {return m_duree;}
    ~TacheUnitaire();
};

class TacheMultiple: public Tache
{

protected:
    vector<Tache *> m_sousTache;

public:
    TacheMultiple(QString titre,QDateTime disponibilite,QDateTime echeance);
    ~TacheMultiple();
};

#endif // TACHE_H
