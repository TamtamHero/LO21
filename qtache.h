#ifndef QTACHE_H
#define QTACHE_H

#include <QStandardItem>
#include "tache.h"

class QTache : public QStandardItem
{
private:
    Tache * m_cible;
public:
    QTache(QString nom,Tache * cible=NULL);
    virtual QStandardItem * clone() const{return new QTache(text(),m_cible);}
    Tache* getTache() {return m_cible;}
    ~QTache();
};

#endif // QTACHE_H
