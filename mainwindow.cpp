#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_7->setVisible(false);
    ui->txtValeurArete->setVisible(false);

    g = new affichagegraphe;

    if (g->isEmpty()) {
        ui->btnTerminer->setEnabled(false);
    }

    view = new QGraphicsView(this);
    view->setScene(new QGraphicsScene(this));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
    delete g;
}

void MainWindow::homeWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->home);
}

void MainWindow::page2Widget()
{
    ui->stackedWidget->setCurrentWidget(ui->page2);
}

void MainWindow::page3Widget()
{
    ui->stackedWidget->setCurrentWidget(ui->page3);
}

//Callback bouton vers saisie graphe
void MainWindow::on_btnSaisie_clicked()
{
    page2Widget();
}

//Callback bouton retour
void MainWindow::on_btnRetour1_clicked()
{

    if (!g->isEmpty()) {
        QMessageBox messageBox(QMessageBox::Question,
                               tr("Confirmation"),
                               tr("Voulez-vous annuler la saisie du graphe ?"));
        messageBox.addButton(tr("Oui"), QMessageBox::YesRole);
        messageBox.addButton(tr("Non"), QMessageBox::NoRole);

        messageBox.exec();

        if (messageBox.buttonRole(messageBox.clickedButton()) == QMessageBox::YesRole) {
            homeWidget();
            g->reset();

            ui->checkBoxOriente->setEnabled(true);
            ui->checkBoxValue->setEnabled(true);
            ui->btnTerminer->setEnabled(false);
            ui->label_5->setEnabled(true);
            ui->label_6->setEnabled(true);
        }
    } else {
        homeWidget();
        g->reset();

        ui->checkBoxOriente->setEnabled(true);
        ui->checkBoxValue->setEnabled(true);
        ui->checkBoxOriente->setChecked(false);
        ui->checkBoxValue->setChecked(false);
        ui->btnTerminer->setEnabled(false);
        ui->label_5->setEnabled(true);
        ui->label_6->setEnabled(true);
    }

}


void MainWindow::on_checkBoxValue_stateChanged()
{
    bool checked = ui->checkBoxValue->isChecked();

    ui->label_7->setVisible(checked);
    ui->txtValeurArete->setVisible(checked);
}

void MainWindow::on_btnAjouter_clicked()
{
    QString sommetDepartNom = ui->txtSommet1->text();
    QString sommetArriveeNom = ui->txtSommet2->text();
    QString valeurAreteTexte = ui->txtValeurArete->text();
    int valeurArete = valeurAreteTexte.toInt();

    sommet* sommetDepart = new sommet(sommetDepartNom);
    sommet* sommetArrivee = new sommet(sommetArriveeNom);

    bool oriente = ui->checkBoxOriente->isChecked();
    bool value = ui->checkBoxValue->isChecked();

    g->setOriente(oriente);
    g->setValue(value);

    g->ajouterArete(sommetDepart, sommetArrivee, valeurArete);

    g->afficher();

    ui->txtSommet1->clear();
    ui->txtSommet2->clear();

    if (!g->isEmpty()) {
        ui->checkBoxOriente->setEnabled(false);
        ui->label_5->setEnabled(false);
        ui->checkBoxValue->setEnabled(false);
        ui->label_6->setEnabled(false);
        ui->btnTerminer->setEnabled(true);
    }
}



void MainWindow::on_btnTerminer_clicked()
{
    ui->btnTerminer->setEnabled(false);
    QMessageBox messageBox(QMessageBox::Question,
                           tr("Confirmation"),
                           tr("Avez-vous fini de saisir les arêtes de votre graphe ?"));
    messageBox.addButton(tr("Oui"), QMessageBox::YesRole);
    messageBox.addButton(tr("Non"), QMessageBox::NoRole);

    messageBox.exec();

    if (messageBox.buttonRole(messageBox.clickedButton()) == QMessageBox::YesRole) {
        page3Widget();

        QGraphicsScene* scene = new QGraphicsScene(this);

        // Dessinez le graphe dans la scène
        g->dessinerGraphe(scene);

        // Configurez la vue avec la nouvelle scène
        ui->graphicsView->setScene(scene);

        // Ajustez la vue pour afficher toute la scène
        ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

        // Affichez la vue
        ui->graphicsView->setVisible(true);

        qDebug() << "Dimensions de la scène :" << scene->sceneRect();
        qDebug() << "Dimensions de la vue :" << view->viewport()->rect();

        // Réinitialiser le graphe après l'affichage
        //g->reset();

        ui->checkBoxOriente->setEnabled(true);
        ui->checkBoxValue->setEnabled(true);
        ui->checkBoxOriente->setChecked(false);
        ui->checkBoxValue->setChecked(false);
        ui->label_5->setEnabled(true);
        ui->label_6->setEnabled(true);
    }
}


void MainWindow::on_btnPageAccueil_clicked()
{
    homeWidget();
    g->reset();
}


void MainWindow::on_btnSave_clicked()
{
    g->creerGraphe();
}
