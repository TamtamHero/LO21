#ifndef CALENDAREXCEPTION
#define CALENDAREXCEPTION

//! \file calendarException.h
//! \brief Classe CalendarException
//! \author Passot J & Laviolette E
//! \version 1.0
//! \date Samedi 13 Juin 2015

#include <QString>


//! \class CalendarException
//! \\brief Permet de traiter les exceptions issues des blocs try/catch

class CalendarException{
public:

    //! \brief Constructeur de la classe BlendTask
    //! \param référence sur un message de type QString constant
    CalendarException(const QString& message):info(message){}

    //! \brief Accesseur de l'information de l'exception
    //! \param : void
    //! \return QString
    QString getInfo() const { return info; }

private:
    QString info; //! Attribut stockant la chaine de caractère (QString) caractérisant l'exception
};

#endif // CALENDAREXCEPTION

