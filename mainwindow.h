#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QDir>
#include <QStringList>
#include <unordered_set>
#include <QTimer>

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

    void on_btnDistances_clicked();

    void on_btnRetourDistance_clicked();

    void on_btnExecDistance_clicked();

    void on_btnRetourDistance2_clicked();

    void on_btnRang_clicked();

    void on_btnRetourRang_clicked();

    void on_btnExecRang_clicked();

    void on_btnTarjan_clicked();

    void on_btnRetourTarjan_clicked();

    void on_btnExecTarjan_clicked();

    void on_btnPrufer_clicked();

    void on_btnRetourDistance_2_clicked();

    void on_btnCodagePrufer_clicked();

    void on_btnRetourCodagePrufer_clicked();

    void on_btnExecCodagePrufer_clicked();

    void on_btnDecodagePrufer_clicked();

    void on_btnRetourCodagePrufer_2_clicked();

    void on_btnDecodageGrapheCourant_clicked();

    void on_btnDecodageTableau_clicked();

    void on_btnRetourDecodagePruferGrapheCourant_clicked();

    void on_btnExecDecodagePruferGrapheCourant_clicked();

    void on_btnRetourDecodagePruferTableau_clicked();

    void on_btnExecDecodagePruferTableau_clicked();

    void on_btnDijkstra_clicked();

    void on_btnRetourDijkstra_clicked();

    void on_btnExecDijkstra_clicked();

    void on_btnOrdonnancement_clicked();

    void on_btnRetourOrdonnancement_clicked();

    void on_btnExecOrdonnancement_clicked();

    void on_btnGrapheReduit_clicked();

    void on_btnRetourTarjan2_clicked();

private:
    Ui::MainWindow *ui;
    class affichagegraphe* affichagegraphe;
    class graphe* graphe = nullptr;
    class graphe* grapheCourant = nullptr;
    QGraphicsView *view;
};
#endif // MAINWINDOW_H
