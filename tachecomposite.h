#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include "tache.h"
#include "qtache.h"


class TacheComposite: public Tache
{

protected:
    vector<Tache *> m_sousTache;

public:
    TacheComposite(QString titre,QDateTime disponibilite,QDateTime echeance);
    void addSousTache(Tache * sousTache);
    void afficher(QStandardItem * parent);
    ~TacheComposite();
};

#endif // TACHECOMPOSITE_H
