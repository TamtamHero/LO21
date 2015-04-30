#ifndef PROJET_H
#define PROJET_H

#include <vector>
#include <QString>
#include <QDateTime>
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
    ~Projet();
};

// A faire: ProjetManager

#endif // PROJET_H
