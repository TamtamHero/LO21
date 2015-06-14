#include "validationwindow.h"

validationWindow::validationWindow(QWidget *parent,QString info):
    QDialog(parent),
    m_validation(false)
{
    m_ok=new QPushButton("Ok");
    m_cancel=new QPushButton("Annuler");
    m_info=new QLabel(info);

    QVBoxLayout *vlayout=new QVBoxLayout;
    QHBoxLayout *hlayout=new QHBoxLayout;

    hlayout->addWidget(m_ok);
    hlayout->addWidget(m_cancel);
    vlayout->addWidget(m_info);
    vlayout->addLayout(hlayout);

    this->setLayout(vlayout);

    QObject::connect(m_ok,SIGNAL(clicked()),this,SLOT(setValidation()));
    QObject::connect(m_cancel,SIGNAL(clicked()),this,SLOT(setCancel()));
}

validationWindow::~validationWindow()
{

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void validationWindow::setValidation()
{
    m_validation=true;
    this->close();
}

void validationWindow::setCancel()
{
    m_validation=false;
    this->close();
}
