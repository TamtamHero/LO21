#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QBrush>

#include "projet.h"
#include "manager.h"
#include "programmation.h"
#include "taskselectionwindow.h"
#include "validationwindow.h"

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
    QStandardItemModel *listModel_edit_prerequisite;
    QStandardItemModel *listModel_edit_attachedTo;
    QStandardItemModel *listModel_creation_prerequisite;
    QStandardItemModel *listModel_creation_attachedTo;
    Manager<Projet> &projectManager;
    Manager<Programmation> &programManager;
    Projet * currentProject;
    Tache * currentTask;

    void updateTreeView(QStandardItemModel *model, QTreeView *view);


private slots:
    void selectionProjet();
    void deleteSelection();
    void clickArbre(const QModelIndex&);
    void doubleclickArbre(QModelIndex);
    void editPrerequisiteSelection();
    void editAttachedToSelection();
    void creationPrerequisiteSelection();
    void creationAttachedToSelection();
    void edit();
    void creationView(QString type);
    void createElement();
    void switchEditTab(){currentTask=NULL;}
    void prerequisiteCreationUndo();
    void prerequisiteEditUndo();

};

#endif // MAINWINDOW_H
