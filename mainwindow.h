#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "affichagegraphe.h"
#include "graphe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void homeWidget();
    void page2Widget();
    void page3Widget();

private slots:
    void on_btnSaisie_clicked();
    void on_btnRetour1_clicked();
    void on_checkBoxValue_stateChanged();
    void on_btnAjouter_clicked();
    void on_btnTerminer_clicked();

    void on_btnPageAccueil_clicked();

    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;
    affichagegraphe* affichagegraphe;
    graphe* graphe;
    QGraphicsView *view;
};
#endif // MAINWINDOW_H
