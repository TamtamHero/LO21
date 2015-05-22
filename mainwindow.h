#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>

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
    QStandardItemModel *listModel_prerequisite;
    QStandardItemModel *listModel_attachedTo;
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
    void uniquePrerequisiteSelection();
    void blendPrerequisiteSelection();
    void uniqueAttachedToSelection();
    void blendAttachedToSelection();
    void edit();
    void creation(QString type);

};

#endif // MAINWINDOW_H
