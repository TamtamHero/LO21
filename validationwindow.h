#ifndef VALIDATIONWINDOW_H
#define VALIDATIONWINDOW_H

//! \file validationwindow.h
//! \brief Classe validationWindow
//! \author Passot J & Laviolette E
//! \version 1.0
//! \date Samedi 13 Juin 2015

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

//! \class validationWindow
//! \brief Fenetre de confirmation de choix
class validationWindow : public QDialog
{
    Q_OBJECT

public:
    //! \brief Constructeur de la classe validationWindow
    //! \param parent : Pointeur vers le widget parent de la fenêtre
    //! \param info : Texte à afficher dans la fenêtre
    validationWindow(QWidget * parent, QString info);

    //! \brief Destructeur de la classe validationWindow
    ~validationWindow();


    //! \brief Accesseur de la validation du choix
    //! \param void
    //! \return Un booléen contenant le statut (validé si true, false sinon)
    bool getValidation(){return m_validation;}

private:
    bool m_validation; //! Booléen contenant le statut (validé si true, false sinon)
    QPushButton *m_ok; //! Boutton de validation
    QPushButton *m_cancel; //! Boutton d'annulation
    QLabel *m_info; //! Texte affiché dans la fenêtre

private slots:
    //! \brief Ecris "vrai" dans l'attribut m_validation
    //! \param void
    //! \return void
    void setValidation();

    //! \brief Ecris "faux" dans l'attribut m_validation
    //! \param void
    //! \return void
    void setCancel();
};

#endif // VALIDATIONWINDOW_H
