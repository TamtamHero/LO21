#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QBrush>
#include <QDate>
#include <QKeyEvent>
#include <cmath>

#include "project.h"
#include "projectmanager.h"
#include "schedulingmanager.h"
#include "scheduling.h"
#include "taskselectionwindow.h"
#include "validationwindow.h"
#include "schedulingwindow.h"
#include "xmlbuilder.h"
#include "iomanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void editorView(Task * task);
    void editorView(Project * project);
    Task * getCurrentTask(){return currentTask;}

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
    IOManager ioManager;
    Project * currentProject;
    Task * currentTask;
    Scheduling * currentScheduling;
    UniqueTask * scheduleTask;
    QDateTime weekDisplayed;

    bool event(QEvent *event);
    void updateTreeView(QStandardItemModel *model, QTreeView *view);
    void updateScheduler();


private slots:
    void editing_selectionProject();
    void deleteSelection();
    void editing_clickTree(const QModelIndex&);
    void editing_doubleclickTree(QModelIndex);
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
    void scheduler_export();
    void scheduler_import();

};

bool checkCoherence(Task* parent, Task *prerequisite);

#endif // MAINWINDOW_H
