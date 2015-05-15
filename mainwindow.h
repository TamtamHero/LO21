#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>

#include "projet.h"
#include "manager.h"
#include "programmation.h"
#include "taskselectionwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void editing(Tache * task);
    void editing(Projet * project);

private:
    Ui::MainWindow *ui;

    QStandardItemModel *treeModel;
    QStandardItemModel *listModel;
    Manager<Projet> &projectManager;
    Manager<Programmation> &programManager;
    Projet * currentProject;
    Tache * currentTask;


private slots:
    void selectionProjet();
    void clickArbre(const QModelIndex&);
    void doubleclickArbre(QModelIndex);
    void uniquePrerequisiteSelection();
    void blendPrerequisiteSelection();
    void uniqueAttachedToSelection();
    void blendAttchedToSelection();
};

#endif // MAINWINDOW_H
