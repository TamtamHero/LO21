#ifndef VALIDATIONWINDOW_H
#define VALIDATIONWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class validationWindow : public QDialog
{
    Q_OBJECT

public:
    validationWindow(QWidget * parent, QString info);
    ~validationWindow();

    bool getValidation(){return validation;}

private:
    bool validation;
    QPushButton *m_ok;
    QPushButton *m_cancel;
    QLabel *m_info;

private slots:
    void setValidation();
    void setCancel();
};

#endif // VALIDATIONWINDOW_H
