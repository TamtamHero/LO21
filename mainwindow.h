#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QBrush>
#include <QDate>
#include <QKeyEvent>
#include <cmath>

#include "projet.h"
#include "projectmanager.h"
#include "schedulingmanager.h"
#include "programmation.h"
#include "taskselectionwindow.h"
#include "validationwindow.h"
#include "schedulingwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void editorView(Tache * task);
    void editorView(Projet * project);
    Tache * getCurrentTask(){return currentTask;}

private:
    Ui::MainWindow *ui;

    QStandardItemModel *treeModel;
    QStandardItemModel *schedulerModel;
    QStandardItemModel *listModel_edit_prerequisite;
    QStandardItemModel *listModel_edit_attachedTo;
    QStandardItemModel *listModel_creation_prerequisite;
    QStandardItemModel *listModel_creation_attachedTo;
    QMessageBox::StandardButton reply;
    ProjectManager &projectManager;
    SchedulingManager &scheduleManager;
    Projet * currentProject;
    Tache * currentTask;
    Programmation * currentScheduling;
    TacheUnitaire * scheduleTask;
    QDateTime weekDisplayed;

    bool event(QEvent *event);
    void updateTreeView(QStandardItemModel *model, QTreeView *view);
    void updateScheduler();


private slots:
    void editing_selectionProjet();
    void deleteSelection();
    void editing_clickArbre(const QModelIndex&);
    void editing_doubleclickArbre(QModelIndex);
    void editing_prerequisiteSelection();
    void editing_attachedToSelection();
    void creation_prerequisiteSelection();
    void creation_attachedToSelection();
    void edit();
    void creationView(QString type);
    void createElement();
    void switchEditTab(){currentTask=NULL;}
    void prerequisiteCreationUndo();
    void prerequisiteEditUndo();

    void scheduler_taskSelection();
    void scheduler_checkTime(QTime t);
    void scheduler_checkDeadline(QDateTime t);
    void scheduler_setDate(int row,int column);
    void scheduler_save();
    void scheduler_previousWeek();
    void scheduler_nextWeek();
    void deleteScheduling();

};

bool checkCoherence(Tache* parent, Tache *prerequisite);

#endif // MAINWINDOW_H
