#ifndef SCHEDULINGWINDOW_H
#define SCHEDULINGWINDOW_H


#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "projet.h"
#include "manager.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

class SchedulingWindow : public QDialog
{
    Q_OBJECT

public:
    SchedulingWindow(QWidget *parent, Manager<Projet>& manager);
    ~SchedulingWindow();

    Tache * getSelectedTask(){return selectedTask;}

private:
    QStandardItemModel *Model;
    QTreeView *treeView;
    QPushButton *pushButton_TaskSelection_selection;
    QPushButton *pushButton_TaskSelection_projectSelection;
    Manager<Projet>& projectManager;
    Projet *selectedProject;
    Tache *selectedTask;

    virtual void closeEvent(QCloseEvent *event);


private slots:
    void scheduler_selectionProjet();
    void sendSelection();
    void scheduler_clickArbre(const QModelIndex&);
    void scheduler_doubleclickArbre(QModelIndex);
};

#endif // SCHEDULINGWINDOW_H
