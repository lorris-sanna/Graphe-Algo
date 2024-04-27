#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_7->setVisible(false);
    ui->txtValeurArete->setVisible(false);

    affichagegraphe = new class affichagegraphe;

    if (affichagegraphe->isEmpty()) {
        ui->btnTerminer->setEnabled(false);
    }

    view = new QGraphicsView(this);
    view->setScene(new QGraphicsScene(this));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
}

// -------------------------------------------------------- Widgets

void MainWindow::homeWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->home);
    affichagegraphe->reset();
}

void MainWindow::pageAlgosWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->pageAlgos);
}

//------------------------------------------------------------------ DANTZIG

void MainWindow::on_btnDantzig_clicked()
{
    if (grapheCourant != nullptr && grapheCourant->estValue() && grapheCourant->estOriente())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageDantzig);

        affichagegraphe->setOriente(grapheCourant->estOriente());
        affichagegraphe->setValue(grapheCourant->estValue());

        affichagegraphe->matCout2Aretes(grapheCourant->getMAT());

        QGraphicsScene* scene = new QGraphicsScene(this);

        //Dessiner le graphe dans la scène
        affichagegraphe->dessinerGraphe(scene);

        //Configurer la vue avec la nouvelle scène
        ui->graphicsViewDantzig->setScene(scene);

        //Ajuster la vue pour afficher toute la scène
        ui->graphicsViewDantzig->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant orienté valué.");
    }
}

void MainWindow::on_btnRetourDantzig_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageAlgos);
}

void MainWindow::on_btnRetourDantzig_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDantzig);
}

void MainWindow::on_btnExecDantzig_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDantzig2);

    grapheOV* grapheOVCourant = dynamic_cast<grapheOV*>(grapheCourant);
    vector<arete> a = affichagegraphe->getAretes();
    vector<vector<int>> c = grapheCourant->getMAT();

    // --------------------------------------------- Affichage matrice avant

    const int seuil_infini = 2000000000; // seuil pour représenter l'infini

    QString matriceAvant = "Matrice avant exécution :\n\n";

    // Parcours de la matrice et construction de la chaîne
    for (const auto& row : c) {
        for (int cost : row) {
            if (cost >= seuil_infini) {
                matriceAvant += "∞   ";
            } else {
                matriceAvant += QString::number(cost) + "   ";
            }
        }
        matriceAvant += "\n";
    }

    // Assignation de la chaîne au QLabel
    ui->labelMatDantzig1->setText(matriceAvant);

    grapheOVCourant->dantzig(c, a);

    // --------------------------------------------- Affichage matrice après

    QString matriceApres = "Matrice après exécution :\n\n";

    // Parcours de la matrice et construction de la chaîne
    for (const auto& row : c) {
        for (int cost : row) {
            if (cost >= seuil_infini) {
                matriceApres += "∞   ";
            } else if (cost <= -seuil_infini) {
                matriceApres += "-∞   ";
            } else {
                matriceApres += QString::number(cost) + "   ";
            }
        }
        matriceApres += "\n"; // Nouvelle ligne pour chaque ligne de la matrice
    }

    // Assignation de la chaîne au QLabel
    ui->labelMatDantzig2->setText(matriceApres);

    QGraphicsScene* scene = new QGraphicsScene(this);

    //Dessiner le graphe dans la scène
    affichagegraphe->dessinerGraphe(scene);

    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewDantzig_2->setScene(scene);

    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewDantzig_2->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

//------------------------------------------------------------------ KRUSKAL

void MainWindow::pageKruskalWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->pageKruskal);

    affichagegraphe->setOriente(grapheCourant->estOriente());
    affichagegraphe->setValue(grapheCourant->estValue());

    affichagegraphe->matCout2Aretes(grapheCourant->getMAT());

    QGraphicsScene* scene = new QGraphicsScene(this);

    //Dessiner le graphe dans la scène
    affichagegraphe->dessinerGraphe(scene);

    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewKruskal->setScene(scene);

    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewKruskal->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_btnExecKruskal_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageKruskal2);

    affichagegraphe->matCout2Aretes(grapheCourant->getMAT());

    std::cout << "Liste des aretes : " << std::endl;
    for (const auto& arete : affichagegraphe->getAretes()) {
        std::cout << arete.getDepart()->getNom().toInt() << " -> "
                  << arete.getArrivee()->getNom().toInt() << " (valeur : "
                  << arete.getValeur() << ")" << std::endl;
    }

    vector<arete> a = affichagegraphe->getAretes();
    grapheVnO* grapheVnOCourant = dynamic_cast<grapheVnO*>(grapheCourant);
    grapheVnO* T = nullptr;
    vector<arete> aretesT = grapheVnOCourant->kruskal(*T, a);

    affichagegraphe->reset();

    QString text;
    for (const auto& arete : aretesT) {
        sommet* sommetDepart = arete.getDepart();
        sommet* sommetArrivee = arete.getArrivee();
        int valeur = arete.getValeur();

        cout << "Ajout de l'arete (" << sommetDepart->getNom().toInt() << ", " << sommetArrivee->getNom().toInt() << ") (valeur  = " << valeur << ")" << "au graphe T." << endl;

        text += "Ajout de l'arête (" + QString::number(sommetDepart->getNom().toInt()) + ", " + QString::number(sommetArrivee->getNom().toInt()) + ") (valeur = " + QString::number(valeur) + ") au graphe T.\n";

        // Ajouter l'arête à affichagegraphe
        affichagegraphe->ajouterArete(sommetDepart, sommetArrivee, valeur);
    }

    ui->labelAretesKruskal->setText(text);

    QGraphicsScene* scene = new QGraphicsScene(this);

    //Dessiner le graphe dans la scène
    affichagegraphe->dessinerGraphe(scene);

    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewKruskal2->setScene(scene);

    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewKruskal2->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::pageChargerGrapheWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->pageChargerGraphe);
}

void MainWindow::pageSaisieWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSaisie);
}

void MainWindow::pageVisuGrapheWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->pageGraphe);
}

// -------------------------------------------------------- Callbacks

void MainWindow::on_btnAlgo_clicked()
{
    pageAlgosWidget();
}

void MainWindow::on_btnCharger_clicked()
{
    pageChargerGrapheWidget();

    QDir repertoire("graphes/");

    // Vérification si le répertoire existe
    if (!repertoire.exists()) {
        std::cerr << "Le repertoire 'graphes' n'existe pas.";
        return;
    }

    // Filtrer les fichiers du répertoire
    QStringList fichiers = repertoire.entryList(QDir::Files);

    // Boucle pour parcourir chaque fichier et les ajouter à labelFichiers
    QString nomsFichiers;
    for (const QString& fichier : fichiers) {
        nomsFichiers += "- " + fichier + "\n"; // Ajouter le nom du fichier à la liste
    }

    // Mettre à jour le texte de labelFichiers avec les noms des fichiers
    ui->labelFichiers->setText(nomsFichiers);
}

void MainWindow::on_btnSaisie_clicked()
{
    pageSaisieWidget();
}

void MainWindow::on_btnRetourAlgos_clicked()
{
    homeWidget();
}

void MainWindow::on_btnKruskal_clicked()
{
    if (grapheCourant != nullptr && grapheCourant->estValue() && !grapheCourant->estOriente())
    {
        pageKruskalWidget();
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant valué non orienté.");
    }
}

void MainWindow::on_btnRetourKruskal_clicked()
{
    pageAlgosWidget();
}

void MainWindow::on_btnRetourKruskal2_clicked()
{
    pageKruskalWidget();
}

void MainWindow::on_btnRetourChargerGraphe_clicked()
{
    homeWidget();
}

void MainWindow::on_btnChoisirGrapheCourant_clicked()
{
    if (ui->editTxtFichier2->text() != "")
    {
        QDir repertoire("graphes/");
        QStringList fichiers = repertoire.entryList(QDir::Files);
        bool fichierExiste = false;
        for (const QString& fichier : fichiers)
        {
            if(ui->editTxtFichier2->text() == fichier)
            {
                fichierExiste = true;
            }
        }
        if (fichierExiste)
        {
            QMessageBox::warning(nullptr, "Succès", "Le graphe du fichier '" + ui->editTxtFichier2->text() + "' est désormais courant.");
            fichierExiste = false;

            vector<int> APSCourant;
            vector<int> FSCourant;
            vector<vector<int>> matCourant;

            QString cheminFichier = repertoire.absoluteFilePath(ui->editTxtFichier2->text());
            std::ifstream fichier(cheminFichier.toStdString());

            std::vector<std::string> dernieresLignes;

            if (fichier.is_open()) {
                std::string ligne;
                while (std::getline(fichier, ligne)) {
                    dernieresLignes.push_back(ligne);
                    if (dernieresLignes.size() > 2) {
                        dernieresLignes.erase(dernieresLignes.begin());
                    }
                }
            }

            // Analyser la dernière ligne pour déterminer la nature du graphe
            bool oriente = (dernieresLignes[0] == "1");
            bool value = (dernieresLignes[1] == "1");

            cout << oriente;
            cout << value;

            // Créer un nouveau graphe selon le type déterminé
            if (oriente) {
                if (value) {
                    grapheCourant = new grapheOV();
                } else {
                    grapheCourant = new grapheOnV();
                }
                grapheCourant->setValue(value);
                grapheCourant->setOriente(true);
            } else {
                if (value) {
                    grapheCourant = new grapheVnO();
                } else {
                    grapheCourant = new grapheNoNv();
                }
                grapheCourant->setValue(value);
                grapheCourant->setOriente(false);
            }
            matCourant = grapheCourant->lireMatDepuisFichier(ui->editTxtFichier2->text().toStdString());

            grapheCourant->adj2fs_aps(matCourant, FSCourant, APSCourant);

            grapheCourant->setFS(FSCourant);
            grapheCourant->setAPS(APSCourant);
            grapheCourant->setMAT(matCourant);

            cout << grapheCourant->fsToString().toStdString();
            cout << grapheCourant->apsToString().toStdString();

            ui->editTxtFichier2->clear();
        } else {
            QMessageBox::warning(nullptr, "Erreur", "Le fichier entré n'existe pas.");
        }
    } else
    {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez entrer un nom de fichier.");
    }
}

void MainWindow::on_btnRetourSaisie_clicked()
{
    if (!affichagegraphe->isEmpty()) {
        QMessageBox messageBox(QMessageBox::Question,
                               tr("Confirmation"),
                               tr("Voulez-vous annuler la saisie du graphe ?"));
        messageBox.addButton(tr("Oui"), QMessageBox::YesRole);
        messageBox.addButton(tr("Non"), QMessageBox::NoRole);

        messageBox.exec();

        if (messageBox.buttonRole(messageBox.clickedButton()) == QMessageBox::YesRole) {
            homeWidget();
            affichagegraphe->reset();

            ui->checkBoxOriente->setEnabled(true);
            ui->checkBoxValue->setEnabled(true);
            ui->btnTerminer->setEnabled(false);
            ui->label_5->setEnabled(true);
            ui->label_6->setEnabled(true);
        }
    } else {
        homeWidget();
        affichagegraphe->reset();

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

    affichagegraphe->setOriente(oriente);
    affichagegraphe->setValue(value);

    affichagegraphe->ajouterArete(sommetDepart, sommetArrivee, valeurArete);

    affichagegraphe->afficher();

    ui->txtSommet1->clear();
    ui->txtSommet2->clear();
    ui->txtValeurArete->clear();

    if (!affichagegraphe->isEmpty()) {
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
        pageVisuGrapheWidget();

        QGraphicsScene* scene = new QGraphicsScene(this);

        //Dessiner le graphe dans la scène
        affichagegraphe->dessinerGraphe(scene);

        //Configurer la vue avec la nouvelle scène
        ui->graphicsView->setScene(scene);

        //Ajuster la vue pour afficher toute la scène
        ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

        //Afficher la vue
        ui->graphicsView->setVisible(true);

        ui->checkBoxOriente->setEnabled(true);
        ui->checkBoxValue->setEnabled(true);
        ui->checkBoxOriente->setChecked(false);
        ui->checkBoxValue->setChecked(false);
        ui->label_5->setEnabled(true);
        ui->label_6->setEnabled(true);

        //------------------------------------- Création graphe (fs et aps) et affichage

        if (!affichagegraphe->estOriente() && !affichagegraphe->estValue())
        {
            graphe = new class grapheNoNv(affichagegraphe->creerGraphe());
            graphe->setOriente(false);
            graphe->setValue(false);
        }
        else if (affichagegraphe->estOriente() && !affichagegraphe->estValue())
        {
            graphe = new class grapheOnV(affichagegraphe->creerGraphe());
            graphe->setOriente(true);
            graphe->setValue(false);
        }
        else if (!affichagegraphe->estOriente() && affichagegraphe->estValue())
        {
            graphe = new class grapheVnO(affichagegraphe->creerGraphe());
            graphe->setOriente(false);
            graphe->setValue(true);
        }
        else
        {
            graphe = new class grapheOV(affichagegraphe->creerGraphe());
            graphe->setOriente(true);
            graphe->setValue(true);
        }

        /*cout << (graphe->estOriente() ? "true" : "false") << endl;
        cout << (graphe->estValue() ? "true" : "false") << endl;

        ui->labelFS->setText(graphe->fsToString());
        ui->labelAPS->setText(graphe->apsToString());*/
    }
}

void MainWindow::on_btnPageAccueil_clicked()
{
    homeWidget();
    affichagegraphe->reset();
}

void MainWindow::on_btnSave_clicked()
{
    if (ui->editTxtFichier1->text() != "")
    {
        vector<vector<int>> mat;
        if(!graphe->estValue())
        {
            graphe->fs_aps2adj(graphe->getAPS(), graphe->getFS(), mat);
        } else if (graphe->estValue())
        {
            vector<arete> listeAretes = affichagegraphe->getAretes();
            /*std::cout << "Liste des aretes : " << std::endl;
            for (const auto& arete : affichagegraphe->getAretes()) {
                std::cout << arete.getDepart()->getNom().toInt() << " -> "
                          << arete.getArrivee()->getNom().toInt() << " (valeur : "
                          << arete.getValeur() << ")" << std::endl;
            }*/
            mat = graphe->matriceCouts(*graphe, listeAretes);
        }
        graphe->ecrireMatDansUnFichier(mat, ui->editTxtFichier1->text().toStdString());
        QMessageBox::warning(nullptr, "Succès", "Le fichier '" + ui->editTxtFichier1->text() + ".txt' a été sauvegardé dans le répertoire 'graphes'.");
        ui->editTxtFichier1->clear();
    } else
    {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez entrer un nom de fichier.");
    }

}
