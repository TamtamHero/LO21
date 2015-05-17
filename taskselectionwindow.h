#ifndef TASKSELECTIONWINDOW_H
#define TASKSELECTIONWINDOW_H

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "projet.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

enum selectedTaskType{PREREQUISITE,ATTACHEDTO};

class TaskSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    TaskSelectionWindow(QWidget *parent,Projet *project,selectedTaskType type);
    ~TaskSelectionWindow();

    Tache * getSelectedTask(){return selectedTask;}

private:
    QStandardItemModel *treeModel;
    QTreeView *treeView;
    QPushButton *pushButton_TaskSelection_selection;
    Tache *selectedTask;
    selectedTaskType m_type;

private slots:
    void sendSelection();
};

#endif // TASKSELECTIONWINDOW_H
