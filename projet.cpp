#include "projet.h"

Projet::Projet(QString titre, QDateTime disponibilite, QDateTime echeance):
    m_titre(titre),m_disponibilite(disponibilite),m_echeance(echeance)
{
    if(echeance < QDateTime::currentDateTime())
    {
        throw CalendarException("Echéance du projet déjà passée !");
    }
    else if(echeance < disponibilite)
    {
        throw CalendarException("La disponibilité entrée pour le projet est ultérieure à l'échéance !");
    }
}

Projet::~Projet()
{

}

