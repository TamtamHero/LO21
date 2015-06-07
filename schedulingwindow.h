#ifndef SCHEDULINGWINDOW_H
#define SCHEDULINGWINDOW_H


#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "project.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

class SchedulingWindow : public QDialog
{
    Q_OBJECT

public:
    SchedulingWindow(QWidget *parent, ProjectManager &manager);
    ~SchedulingWindow();

    Task * getSelectedTask(){return m_selectedTask;}

private:
    QStandardItemModel *Model;
    QTreeView *treeView;
    QPushButton *pushButton_TaskSelection_selection;
    QPushButton *pushButton_TaskSelection_projectSelection;
    ProjectManager& projectManager;
    Project *selectedProject;
    Task *m_selectedTask;

private slots:
    void scheduler_selectionProject();
    void sendSelection();
    void scheduler_clickTree(const QModelIndex&);
    void scheduler_doubleclickTree(QModelIndex);
};

#endif // SCHEDULINGWINDOW_H
