#ifndef PROJET_H
#define PROJET_H

#include <vector>
#include <QString>
#include <QDateTime>
#include <QStandardItem>
#include <QStandardItemModel>
#include "tache.h"


class Projet
{
protected:
    QString m_titre;
    QDateTime m_disponibilite;
    QDateTime m_echeance;
    vector<Tache *> m_decomposition;

    Projet(const Projet& source);
    Projet& operator=(const Projet& source);

public:
    Projet(QString titre, QDateTime disponibilite, QDateTime echeance);
    void addSousTache(Tache * sousTache);
    ~Projet();

    void afficher(QStandardItemModel * treeModel);
    QString getTitre(){return m_titre;}
    QDateTime getDisponibility(){return m_disponibilite;}
    QDateTime getDeadline(){return m_echeance;}
};

// A faire: ProjetManager

#endif // PROJET_H
