#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QDir>
#include <QStringList>

#include "affichagegraphe.h"
#include "graphe.h"
#include "graphenonv.h"
#include "grapheonv.h"
#include "grapheov.h"
#include "graphevno.h"

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
    void pageSaisieWidget();
    void pageVisuGrapheWidget();
    void pageAlgosWidget();
    void pageKruskalWidget();
    void pageChargerGrapheWidget();

private slots:
    void on_btnSaisie_clicked();
    void on_checkBoxValue_stateChanged();
    void on_btnAjouter_clicked();
    void on_btnTerminer_clicked();
    void on_btnPageAccueil_clicked();
    void on_btnSave_clicked();
    void on_btnKruskal_clicked();
    void on_btnAlgo_clicked();
    void on_btnRetourSaisie_clicked();
    void on_btnRetourAlgos_clicked();
    void on_btnRetourKruskal_clicked();
    void on_btnCharger_clicked();
    void on_btnRetourChargerGraphe_clicked();

    void on_btnChoisirGrapheCourant_clicked();

    void on_btnExecKruskal_clicked();

    void on_btnRetourKruskal2_clicked();

    void on_btnDantzig_clicked();

    void on_btnRetourDantzig_clicked();

    void on_btnExecDantzig_clicked();

    void on_btnRetourDantzig_2_clicked();

private:
    Ui::MainWindow *ui;
    class affichagegraphe* affichagegraphe;
    class graphe* graphe = nullptr;
    class graphe* grapheCourant = nullptr;
    QGraphicsView *view;
};
#endif // MAINWINDOW_H
