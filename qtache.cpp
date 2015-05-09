#include "qtache.h"

 QTache::QTache(QString nom,Tache * cible): QStandardItem(nom), m_cible(cible)
 {

 }

QTache::~QTache()
{

}

