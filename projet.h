#ifndef PROJET_H
#define PROJET_H

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QStandardItemModel>
#include "tache.h"
#include "tachecomposite.h"


class Projet
{
protected:
    QString m_titre;
    QDateTime m_disponibilite;
    QDateTime m_echeance;
    vector<Tache *> m_decomposition;
    vector<Tache *> m_deadList; //Used to clean interconnection between Task when destructor is called.

    Projet(const Projet& source);
    Projet& operator=(const Projet& source);

public:
    Projet(QString titre, QDateTime disponibilite, QDateTime echeance);
    ~Projet();

    void addElement(Tache * element);
    void deleteElement(Tache * element);
    void fillDeadList(Tache * element);
    void cleanPrerequisite(Tache * element);
    void afficher(QStandardItemModel * treeModel);
    QString getTitre(){return m_titre;}
    QDateTime getDisponibility(){return m_disponibilite;}
    QDateTime getDeadline(){return m_echeance;}
};

// A faire: ProjetManager

#endif // PROJET_H
