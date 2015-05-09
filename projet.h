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

    void Afficher(QStandardItemModel * modele);
    QString getTitre(){return m_titre;}
};

// A faire: ProjetManager

#endif // PROJET_H
