#ifndef TASKSELECTIONWINDOW_H
#define TASKSELECTIONWINDOW_H

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "projet.h"
#include "QVBoxLayout"

class TaskSelectionWindow : public QDialog
{

public:
    TaskSelectionWindow(QWidget *parent,Projet *project);
    ~TaskSelectionWindow();

private:
    QStandardItemModel *modele;
    QTreeView *treeView;
    QPushButton *pushButton_TaskSelection_selection;

private slots:
    void sendSelection();
};

#endif // TASKSELECTIONWINDOW_H
