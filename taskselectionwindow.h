#ifndef TASKSELECTIONWINDOW_H
#define TASKSELECTIONWINDOW_H

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "projet.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

class TaskSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    TaskSelectionWindow(QWidget *parent,Projet *project);
    ~TaskSelectionWindow();

    Tache * getSelectedTask(){return selectedTask;}

private:
    QStandardItemModel *treeModel;
    QTreeView *treeView;
    QPushButton *pushButton_TaskSelection_selection;
    Tache *selectedTask;

private slots:
    void sendSelection();
};

#endif // TASKSELECTIONWINDOW_H
