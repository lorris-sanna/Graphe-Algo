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

//------------------------------------------------------------------ DISTANCES

void MainWindow::on_btnDistances_clicked()
{
    if (grapheCourant != nullptr && !grapheCourant->estValue())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageDistances);

        affichagegraphe->matAdj2Aretes(grapheCourant->getMAT());

        QGraphicsScene* scene = new QGraphicsScene(this);

        affichagegraphe->setOriente(grapheCourant->estOriente());

        vector<arete> listeAretes = affichagegraphe->getAretes();
        std::cout << "Liste des aretes : " << std::endl;
        for (const auto& arete : affichagegraphe->getAretes()) {
            std::cout << arete.getDepart()->getNom().toInt() << " -> "
                      << arete.getArrivee()->getNom().toInt() << " (valeur : "
                      << arete.getValeur() << ")" << std::endl;
        }

        //Dessiner le graphe dans la scène
        affichagegraphe->dessinerGraphe(scene);

        //Configurer la vue avec la nouvelle scène
        ui->graphicsViewDistance->setScene(scene);

        //Ajuster la vue pour afficher toute la scène
        ui->graphicsViewDistance->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant non valué.");
    }
}

void MainWindow::on_btnRetourDistance_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageAlgos);
}

void MainWindow::on_btnExecDistance_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDistances2);

    vector<vector<int>> c = grapheCourant->getMAT();

    // --------------------------------------------- Affichage matrice avant

    QString matriceAvant = "Matrice avant exécution :\n\n";

    for (size_t i = 1; i < c.size(); ++i) {
        for (size_t j = 1; j < c[i].size(); ++j) {
            matriceAvant += QString::number(c[i][j]) + "   ";
        }
        matriceAvant += "\n"; // Retour à la ligne après chaque ligne de la matrice
    }

    // Assignation de la chaîne au QLabel
    ui->labelMatDistance1->setText(matriceAvant);

    c = grapheCourant->matriceDistance();

    // --------------------------------------------- Affichage matrice après

    QString matriceApres = "Matrice après exécution :\n\n";

    for (size_t i = 1; i < c.size(); ++i) {
        for (size_t j = 1; j < c[i].size(); ++j) {
            matriceApres += QString::number(c[i][j]) + "   ";
        }
        matriceApres += "\n"; // Retour à la ligne après chaque ligne de la matrice
    }

    // Assignation de la chaîne au QLabel
    ui->labelMatDistance2->setText(matriceApres);

    QGraphicsScene* scene = new QGraphicsScene(this);

    //Dessiner le graphe dans la scène
    affichagegraphe->dessinerGraphe(scene);

    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewDistance2->setScene(scene);

    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewDistance2->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_btnRetourDistance2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDistances);
}

//------------------------------------------------------------------ RANG

void MainWindow::on_btnRang_clicked()
{
    if (grapheCourant != nullptr && !grapheCourant->estValue() && grapheCourant->estOriente())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageRang);

        affichagegraphe->matAdj2Aretes(grapheCourant->getMAT());

        QGraphicsScene* scene = new QGraphicsScene(this);

        affichagegraphe->setOriente(grapheCourant->estOriente());

        vector<arete> listeAretes = affichagegraphe->getAretes();
        std::cout << "Liste des aretes : " << std::endl;
        for (const auto& arete : affichagegraphe->getAretes()) {
            std::cout << arete.getDepart()->getNom().toInt() << " -> "
                      << arete.getArrivee()->getNom().toInt() << " (valeur : "
                      << arete.getValeur() << ")" << std::endl;
        }

        //Dessiner le graphe dans la scène
        affichagegraphe->dessinerGraphe(scene);

        //Configurer la vue avec la nouvelle scène
        ui->graphicsViewRang->setScene(scene);

        //Ajuster la vue pour afficher toute la scène
        ui->graphicsViewRang->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant orienté non valué.");
    }
}

void MainWindow::on_btnRetourRang_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageAlgos);

    ui->labelRang->setText("");
}

void MainWindow::on_btnExecRang_clicked()
{
    grapheOnV* grapheOnVCourant = dynamic_cast<grapheOnV*>(grapheCourant);
    vector<int> rang = grapheOnVCourant->rang();

    QString rangString = "Rang : [";
    for (int i = 0; i < rang.size(); ++i) {
        rangString += QString::number(rang[i]);
        if (i != rang.size() - 1) {
            rangString += "] ["; // Ajout de crochets entre les éléments sauf pour le dernier
        }
    }
    rangString += "]";

    // Affichage de la chaîne de caractères dans le QLabel
    ui->labelRang->setText(rangString);
}

//------------------------------------------------------------------ TARJAN

void MainWindow::on_btnTarjan_clicked()
{
    if (grapheCourant != nullptr && !grapheCourant->estValue() && grapheCourant->estOriente())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageTarjan);

        affichagegraphe->matAdj2Aretes(grapheCourant->getMAT());

        QGraphicsScene* scene = new QGraphicsScene(this);

        affichagegraphe->setOriente(grapheCourant->estOriente());

        vector<arete> listeAretes = affichagegraphe->getAretes();
        std::cout << "Liste des aretes : " << std::endl;
        for (const auto& arete : affichagegraphe->getAretes()) {
            std::cout << arete.getDepart()->getNom().toInt() << " -> "
                      << arete.getArrivee()->getNom().toInt() << " (valeur : "
                      << arete.getValeur() << ")" << std::endl;
        }

        //Dessiner le graphe dans la scène
        affichagegraphe->dessinerGraphe(scene);

        //Configurer la vue avec la nouvelle scène
        ui->graphicsViewTarjan->setScene(scene);

        //Ajuster la vue pour afficher toute la scène
        ui->graphicsViewTarjan->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant orienté non valué.");
    }
}

void MainWindow::on_btnRetourTarjan_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageAlgos);
}

void MainWindow::on_btnExecTarjan_clicked()
{
    grapheOnV* grapheOnVCourant = dynamic_cast<grapheOnV*>(grapheCourant);
    vector<vector<int>> tarj = grapheOnVCourant->tarjan();

    for (size_t i = 0; i < tarj.size(); ++i) {
        std::cout << "Vecteur " << i << " : [";
        for (size_t j = 0; j < tarj[i].size(); ++j) {
            std::cout << tarj[i][j];
            if (j != tarj[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "] (taille = " << tarj[i].size() << ")" << std::endl;
    }
}

//------------------------------------------------------------------ DIJKSTRA

void MainWindow::on_btnDijkstra_clicked()
{
    if (grapheCourant != nullptr && grapheCourant->estValue() && grapheCourant->estOriente())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageDijkstra);

        affichagegraphe->setOriente(grapheCourant->estOriente());
        affichagegraphe->setValue(grapheCourant->estValue());

        affichagegraphe->matCout2Aretes(grapheCourant->getMAT());

        QGraphicsScene* scene = new QGraphicsScene(this);

        //Dessiner le graphe dans la scène
        affichagegraphe->dessinerGraphe(scene);

        //Configurer la vue avec la nouvelle scène
        ui->graphicsViewDijkstra->setScene(scene);

        //Ajuster la vue pour afficher toute la scène
        ui->graphicsViewDijkstra->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant orienté valué.");
    }
}

void MainWindow::on_btnRetourDijkstra_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageAlgos);
    ui->editTxtDijkstra->setText("");
    ui->labelDijkstraD->setText("");
    ui->labelDijkstraPred->setText("");
}

void MainWindow::on_btnExecDijkstra_clicked()
{
    grapheOV* grapheOVCourant = dynamic_cast<grapheOV*>(grapheCourant);

    if (ui->editTxtDijkstra->text() != "")
    {
        int s = ui->editTxtDijkstra->text().toInt();
        vector<int> pr, d;

        vector<vector<int>> p = grapheOVCourant->getMAT();
        vector<int> fs = grapheOVCourant->getFS();
        vector<int> aps = grapheOVCourant->getAPS();

        for (size_t i = 0; i < p.size(); ++i) {
            // Parcourir chaque élément dans le vecteur actuel
            for (size_t j = 0; j < p[i].size(); ++j) {
                // Afficher la valeur de l'élément actuel
                cout << p[i][j] << " ";
            }
            // Aller à la ligne après avoir affiché tous les éléments du vecteur actuel
            cout << endl;
        }

        grapheOVCourant->dijkstra(fs, aps, p, s, d, pr);

        for (int i = 1; i < d.size(); ++i) {
            std::cout << "Shortest distance to node " << i << " is " << d[i] << std::endl;
        }

        grapheOVCourant->afficherVecteur(d);
        grapheOVCourant->afficherVecteur(pr);

        QString dString = "d : [";
        for (int i = 1; i < d.size(); ++i) {
            if (d[i] == INT_MAX) {
                dString += QString::fromUtf8("\u221E");
            } else {
                dString += QString::number(d[i]);
            }
            if (i != d.size() - 1) {
                dString += "] ["; // Ajout de crochets entre les éléments sauf pour le dernier
            }
        }
        dString += "]";

        QString predString = "pred : [";
        for (int i = 1; i < pr.size(); ++i) {
            if (pr[i] == INT_MAX) {
                predString += QString::fromUtf8("\u221E");
            } else {
                predString += QString::number(pr[i]);
            }
            if (i != pr.size() - 1) {
                predString += "] ["; // Ajout de crochets entre les éléments sauf pour le dernier
            }
        }
        predString += "]";

        // Affichage de la chaîne de caractères dans le QLabel
        ui->labelDijkstraD->setText(dString);
        ui->labelDijkstraPred->setText(predString);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez entrer le sommet de départ.");
    }

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
    vector<vector<int>> c = grapheOVCourant->getMAT();

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

    grapheOVCourant->dantzig(c);

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

//------------------------------------------------------------------ PRUFER

void MainWindow::on_btnPrufer_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagePruferChoix);
}

void MainWindow::on_btnRetourDistance_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageAlgos);
}

//------------------------------------- CODAGE

void MainWindow::on_btnCodagePrufer_clicked()
{
    if (grapheCourant != nullptr && !grapheCourant->estValue() && !grapheCourant->estOriente())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageCodagePrufer);

        affichagegraphe->matAdj2Aretes(grapheCourant->getMAT());

        QGraphicsScene* scene = new QGraphicsScene(this);

        //Dessiner le graphe dans la scène
        affichagegraphe->dessinerGraphe(scene);

        //Configurer la vue avec la nouvelle scène
        ui->graphicsViewCodagePrufer->setScene(scene);

        //Ajuster la vue pour afficher toute la scène
        ui->graphicsViewCodagePrufer->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant non orienté non valué.");
    }
}

void MainWindow::on_btnRetourCodagePrufer_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagePruferChoix);
    ui->labelCodagePrufer->setText("");
}

void MainWindow::on_btnExecCodagePrufer_clicked()
{
    grapheNoNv* grapheNoNvCourant = dynamic_cast<grapheNoNv*>(grapheCourant);

    vector<vector<int>> matAdj = grapheNoNvCourant->getMAT();

    for (const auto& row : matAdj) {
        for (int cost : row) {
            cout << cost << "   ";
        }
        cout << endl; // Nouvelle ligne pour chaque ligne de la matrice
    }

    vector<int> codage = grapheNoNvCourant->codagePrufer(matAdj);

    QString CodageString = "Prufer : [";
    for (size_t i = 0; i < codage.size(); ++i) {
        CodageString += QString::number(codage[i]);
        if (i != codage.size() - 1) {
            CodageString += "] ["; // Ajout de crochets entre les éléments sauf pour le dernier
        }
    }
    CodageString += "]";

    // Affichage de la chaîne de caractères dans le QLabel
    ui->labelCodagePrufer->setText(CodageString);
}

//------------------------------------- DECODAGE

void MainWindow::on_btnDecodagePrufer_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDecodagePrufer);
}

void MainWindow::on_btnRetourCodagePrufer_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagePruferChoix);
}

void MainWindow::on_btnDecodageGrapheCourant_clicked()
{
    if (grapheCourant != nullptr && !grapheCourant->estValue() && !grapheCourant->estOriente())
    {
        ui->stackedWidget->setCurrentWidget(ui->pageDecodagePruferGrapheCourant);

        grapheNoNv* grapheNoNvCourant = dynamic_cast<grapheNoNv*>(grapheCourant);

        vector<vector<int>> matAdj = grapheNoNvCourant->getMAT();

        vector<int> codage = grapheNoNvCourant->codagePrufer(matAdj);

        QString CodageString = "Prufer : [";
        for (size_t i = 0; i < codage.size(); ++i) {
            CodageString += QString::number(codage[i]);
            if (i != codage.size() - 1) {
                CodageString += "] ["; // Ajout de crochets entre les éléments sauf pour le dernier
            }
        }
        CodageString += "]";

        // Affichage de la chaîne de caractères dans le QLabel
        ui->labelDecodagePruferGrapheCourant->setText(CodageString);
    } else {
    QMessageBox::warning(nullptr, "Erreur", "Veuillez charger un graphe courant non orienté non valué.");
    }
}

void MainWindow::on_btnRetourDecodagePruferGrapheCourant_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDecodagePrufer);

    affichagegraphe->reset();

    QGraphicsScene* scene = new QGraphicsScene(this);
    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewDecodagePruferGrapheCourant->setScene(scene);
    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewDecodagePruferGrapheCourant->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_btnExecDecodagePruferGrapheCourant_clicked()
{
    grapheNoNv* grapheNoNvCourant = dynamic_cast<grapheNoNv*>(grapheCourant);

    vector<vector<int>> matAdj = grapheNoNvCourant->getMAT();

    vector<int> codage = grapheNoNvCourant->codagePrufer(matAdj);
    vector<vector<int>> matAdjDecodage = grapheNoNvCourant->decodagePrufer(codage);

    affichagegraphe->matAdj2Aretes(matAdjDecodage);

    QGraphicsScene* scene = new QGraphicsScene(this);

    //Dessiner le graphe dans la scène
    affichagegraphe->dessinerGraphe(scene);

    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewDecodagePruferGrapheCourant->setScene(scene);

    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewDecodagePruferGrapheCourant->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_btnDecodageTableau_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDecodagePruferTableau);
}

void MainWindow::on_btnRetourDecodagePruferTableau_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDecodagePrufer);

    affichagegraphe->reset();

    QGraphicsScene* scene = new QGraphicsScene(this);
    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewDecodageTableau->setScene(scene);
    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewDecodageTableau->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_btnExecDecodagePruferTableau_clicked()
{
    grapheNoNv* grapheNoNvCourant = dynamic_cast<grapheNoNv*>(grapheCourant);

    // Supposons que 'lineEdit' est ton QLineEdit
    QString inputCodage = ui->editTxtDecodagePrufer->text(); // Récupérer le texte entré dans l'editText

    // Diviser la chaîne en une liste de nombres en séparant par des virgules
    QStringList num = inputCodage.split(',');

    vector<int> codage;

    // Convertir chaque élément de QStringList en int et l'ajouter à codage
    for(const QString &n : num) {
        codage.push_back(n.toInt());
    }

    codage.insert(codage.begin(), codage.size());

    for(const auto& c : codage) {
        cout << c;
    }

    vector<vector<int>> matAdjDecodage = grapheNoNvCourant->decodagePrufer(codage);

    for (const auto& row : matAdjDecodage) {
        for (int cost : row) {
            cout << cost << "   ";
        }
        cout << endl; // Nouvelle ligne pour chaque ligne de la matrice
    }

    affichagegraphe->matAdj2Aretes(matAdjDecodage);

    QGraphicsScene* scene = new QGraphicsScene(this);

    affichagegraphe->setOriente(false);
    affichagegraphe->setValue(false);

    //Dessiner le graphe dans la scène
    affichagegraphe->dessinerGraphe(scene);

    //Configurer la vue avec la nouvelle scène
    ui->graphicsViewDecodageTableau->setScene(scene);

    //Ajuster la vue pour afficher toute la scène
    ui->graphicsViewDecodageTableau->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

//------------------------------------------------------------------

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

            if (grapheCourant->estValue())
            {
                grapheCourant->couts2fs_aps(matCourant, FSCourant, APSCourant);
            } else
            {
                grapheCourant->adj2fs_aps(matCourant, FSCourant, APSCourant);
            }

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

        ui->labelFS->setText(graphe->fsToString());
        ui->labelAPS->setText(graphe->apsToString());
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
