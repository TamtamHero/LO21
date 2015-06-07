#ifndef TASKSELECTIONWINDOW_H
#define TASKSELECTIONWINDOW_H

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include "project.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

enum m_selectedTaskType{PREREQUISITE,ATTACHEDTO};

class TaskSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    TaskSelectionWindow(QWidget *parent,Project *project,m_selectedTaskType type);
    ~TaskSelectionWindow();

    Task * getSelectedTask(){return m_selectedTask;}

private:
    QStandardItemModel *m_treeModel;
    QTreeView *treeView;
    QPushButton *pushButton_TaskSelection_selection;
    QPushButton *pushButton_TaskSelection_notAttaskd;
    Task *m_selectedTask;
    m_selectedTaskType m_type;

private slots:
    void sendSelection();
    void sendNotAttaskd();
};

#endif // TASKSELECTIONWINDOW_H
