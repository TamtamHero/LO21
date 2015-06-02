#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include "tache.h"
#include "tacheunitaire.h"
#include <QVariant>


class TacheComposite: public Tache
{

protected:
    vector<Tache *> m_element;

public:
    TacheComposite(QString titre,QDateTime disponibilite,QDateTime echeance);
    void addElement(Tache * element);
    vector<Tache *>& getElement(){return m_element;}
    void afficher(QStandardItem * parent);
    list<Tache*> getAllUniquePrerequisite();
    list<Tache*> getAllUniqueSons();
    virtual ~TacheComposite();
};

Q_DECLARE_METATYPE(TacheComposite *)

#endif // TACHECOMPOSITE_H
