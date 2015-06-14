#ifndef ABSTRACTCONTAINER_H
#define ABSTRACTCONTAINER_H

//! \file abstractcontainer.h
//! \brief Classe AbstractContainer
//! \author Passot J & Laviolette E
//! \version 3.0
//! \date Samedi 13 Juin 2015

#include <iostream>
#include <vector>

#include <QStandardItemModel>
#include <QVariant>
#include <QFile>
#include <QXmlStreamWriter>
#include "project.h"
#include "scheduling.h"


//! \class AbstractContainer
//! \\brief Classe template pour gérer les classes container

template<typename Type> class AbstractContainer
{
protected:


    //! \brief Constructeur de la classe AbstractContainer
    //! \param void
    AbstractContainer();


    //! \brief Constructeur de recopie classe AbstractContainer
    //! \param une référence constante sur un AbstractContainer
    AbstractContainer(const AbstractContainer& copy);


    //! \brief Surcharge opérateur d'affectation
    //! \param une référence constante sur un AbstractContainer
    AbstractContainer& operator=(const AbstractContainer& copy);

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    list<Type *> m_liste; //! liste de pointeurs d'élements contenus
public:

    //! \brief Desctructeur virtuel de la classe AbstractContainer
    virtual ~AbstractContainer()=0;

    //! \brief Retourne une référence sur la liste d'éléments contenus
    //! \param void
    //! \return  liste
    list<Type *>& getList(){return m_liste;}

    //! \brief Ajoute un élement à la liste et réordonne la liste
    //! \param un pointeur sur un élément à indexer
    //! \return  void
    void addElement(Type * element);

    //! \brief Désindexe une élement de la liste
    //! \param un pointeur sur un élément à désindexer
    //! \return void
    void removeElement(Type * element);

    //! \brief Trie la liste d'élements avec l'opérateur <
    //! \param void
    //! \return void
    void  sort();

    //! \struct typeIsInferior
    //! \brief Permet de d'utiliser l'opérateur de comparaison < dans la classe template
    struct typeIsInferior
    {

          //! \brief surcharge l'opérateur () avec la comparaison <
          //! \return booléen
          template<typename T>
          bool operator()(const T* l, const T* r)
          {
            return *l < *r;
          }
    };

};

#include "abstractcontainer.tpp"
#endif // ABSTRACTCONTAINER_H
