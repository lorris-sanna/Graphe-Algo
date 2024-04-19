#include "affichagegraphe.h"

affichagegraphe::affichagegraphe()
{}

void affichagegraphe::setOriente(bool oriente) {
    this->oriente = oriente;
}

void affichagegraphe::setValue(bool value) {
    this->value = value;
}

std::map<QString, std::vector<QString>> affichagegraphe::getSuccesseurs(const QString& nomSommet) const {
    std::map<QString, std::vector<QString>> successeursLocaux; // Variable locale pour stocker les successeurs

    // Recherche des successeurs pour le sommet spécifié
    for (const auto& arete : aretes) {
        if (arete.getDepart()->getNom() == nomSommet) {
            successeursLocaux[arete.getDepart()->getNom()].push_back(arete.getArrivee()->getNom());
        }
    }

    return successeursLocaux;
}


void affichagegraphe::ajouterSommets(QString nomSommetDepart, QString nomSommetArrivee) {
    if (nomSommetDepart != nomSommetArrivee && !nomSommetDepart.isEmpty() && !nomSommetArrivee.isEmpty()) {
        if (trouverSommet(nomSommetDepart) == nullptr) {
            sommets.push_back(new sommet(nomSommetDepart));
        }
        if (trouverSommet(nomSommetArrivee) == nullptr) {
            sommets.push_back(new sommet(nomSommetArrivee));
        }
    }
}

void affichagegraphe::ajouterArete(sommet* nomSommetDepart, sommet* nomSommetArrivee, int valeur) {
    if (nomSommetDepart->getNom() != "" && nomSommetArrivee->getNom() != "") {
        if (nomSommetDepart->getNom() != nomSommetArrivee->getNom()) {

            bool areteExiste = false;

            for (const auto& arete : aretes) {
                if (arete.getDepart()->getNom() == nomSommetDepart->getNom() && arete.getArrivee()->getNom() == nomSommetArrivee->getNom()) {
                    areteExiste = true;
                    break;
                }
            }

            if (!areteExiste) {
                ajouterSommets(nomSommetDepart->getNom(), nomSommetArrivee->getNom());
                aretes.push_back(arete(nomSommetDepart, nomSommetArrivee, valeur));
            } else {
                QMessageBox::warning(nullptr, "Erreur", "Une arête reliant ces deux sommets existe déjà.");
            }
        } else {
            QMessageBox::warning(nullptr, "Erreur", "Les sommets renseignés sont identiques.");
        }

    } else {
        QMessageBox::warning(nullptr, "Erreur", "Les sommets renseignés ne doivent pas être nuls.");
    }
}

// Méthode pour trouver un sommet par son nom
sommet* affichagegraphe::trouverSommet(QString nom) {
    for (sommet* sommet : sommets) {
        if (sommet->getNom() == nom) {
            return sommet;
        }
    }
    return nullptr;
}

void affichagegraphe::dessinerGraphe(QGraphicsScene* scene) {
    // Si le graphe est vide, il n'y a rien à dessiner
    if (sommets.empty() || aretes.empty()) return;

    // Rayon du cercle
    const int rayon = 100;

    // Centre du cercle
    QPointF centre(scene->width() / 2, scene->height() / 2);

    // Dessiner les sommets
    int i = 0; // Pour garder une trace de l'indice du sommet
    for (const auto& s : sommets) {
        qreal x = centre.x() + rayon * cos(2 * M_PI * i / sommets.size());
        qreal y = centre.y() + rayon * sin(2 * M_PI * i / sommets.size());
        QGraphicsEllipseItem* sommetItem = scene->addEllipse(x - 10, y - 10, 20, 20,
                                                             QPen(Qt::black), QBrush(Qt::transparent));
        QString nomSommet = s->getNom();
        QGraphicsTextItem* nomSommetItem = scene->addText(nomSommet);
        nomSommetItem->setPos(x + 2, y + 2);
        scene->addItem(sommetItem);
        scene->addItem(nomSommetItem);
        i++;
    }

    // Parcourir les arêtes pour dessiner les liaisons entre les sommets concernés
    for (const auto& arete : aretes) {
        sommet* depart = nullptr;
        sommet* arrivee = nullptr;

        // Trouver les sommets de départ et d'arrivée associés à l'arête
        for (const auto& s : sommets) {
            if (s->getNom() == arete.getDepart()->getNom()) depart = s;
            if (s->getNom() == arete.getArrivee()->getNom()) arrivee = s;
            if (depart && arrivee) break;
        }

        // Si les sommets de départ ou d'arrivée ne sont pas valides, passer à l'itération suivante
        if (!depart || !arrivee) continue;

        // Calculer les coordonnées des sommets de départ et d'arrivée
        qreal xDepart = centre.x() + rayon * cos(2 * M_PI * std::distance(sommets.begin(), std::find(sommets.begin(), sommets.end(), depart)) / sommets.size());
        qreal yDepart = centre.y() + rayon * sin(2 * M_PI * std::distance(sommets.begin(), std::find(sommets.begin(), sommets.end(), depart)) / sommets.size());
        qreal xArrivee = centre.x() + rayon * cos(2 * M_PI * std::distance(sommets.begin(), std::find(sommets.begin(), sommets.end(), arrivee)) / sommets.size());
        qreal yArrivee = centre.y() + rayon * sin(2 * M_PI * std::distance(sommets.begin(), std::find(sommets.begin(), sommets.end(), arrivee)) / sommets.size());

        // Créer un chemin
        QPainterPath chemin;
        chemin.moveTo(xDepart, yDepart); // Déplacer le point de départ du chemin

        // Ajouter une ligne au chemin
        chemin.lineTo(xArrivee, yArrivee);

        // Dessiner le chemin
        QPen pen(Qt::black);
        pen.setWidth(1);
        QGraphicsPathItem* areteItem = scene->addPath(chemin, pen);
        scene->addItem(areteItem);

        // Calculer l'angle de la droite entre les sommets de départ et d'arrivée
        qreal angle = atan2(yArrivee - yDepart, xArrivee - xDepart) * 180 / M_PI;

        // Calculer les coordonnées du point avant l'extrémité de la droite
        qreal xArrow = xArrivee - 25 * cos(angle * M_PI / 180);
        qreal yArrow = yArrivee - 25 * sin(angle * M_PI / 180);

        if (oriente) {
            // Créer un élément de flèche
            QGraphicsPolygonItem* arrowItem = new QGraphicsPolygonItem(QPolygonF() << QPointF(0, -2.5) << QPointF(10, 0) << QPointF(0, 2.5), nullptr);
            arrowItem->setRotation(angle); // Faire pivoter la flèche
            arrowItem->setPos(xArrow, yArrow); // Positionner la flèche juste avant l'extrémité de la droite

            arrowItem->setBrush(Qt::black);

            // Dessiner la flèche
            scene->addItem(arrowItem);
        }

        if (value) {
            qreal xMilieu = (xDepart + xArrivee) / 2;
            qreal yMilieu = (yDepart + yArrivee) / 2;

            QGraphicsTextItem* poidsItem = scene->addText(QString::number(arete.getValeur()));
            poidsItem->setPos(xMilieu, yMilieu);

            scene->addItem(poidsItem);
        }

    }
}

void affichagegraphe::reset() {
    sommets.clear();
    aretes.clear();
    oriente = false;
    value = false;
}

bool affichagegraphe::isEmpty() const {
    return (sommets.empty() || aretes.empty());
}

// Méthode pour afficher le graphe
void affichagegraphe::afficher() {
    if (sommets.empty() || aretes.empty()) {
        std::cout << "Le graphe est vide." << std::endl;
        return;
    }

    std::cout << "Graphe oriente : " << (oriente ? "oui" : "non") << std::endl;
    std::cout << "Graphe value : " << (value ? "oui" : "non") << std::endl;

    // Afficher les sommets
    std::cout << "Sommet(s) du graphe :" << std::endl;
    for (const auto& sommet : sommets) {
        std::cout << " - " << sommet->getNom().toStdString() << std::endl;
    }

    // Afficher les arêtes avec leurs valeurs si le graphe est valué
    std::cout << "Arete(s) du graphe :" << std::endl;
    for (const auto& arete : aretes) {
        std::cout << arete.getDepart()->getNom().toStdString() << " -> "
                  << arete.getArrivee()->getNom().toStdString();

        if (value) {
            std::cout << " (valeur : " << arete.getValeur() << ")";
        }
        std::cout << std::endl;
    }
}

void affichagegraphe::creerGraphe() {
    // Initialiser les vecteurs fs et aps
    std::vector<int> fs;
    std::vector<int> aps;

    aps.push_back(sommets.size());
    aps.push_back(1);

    // Créer une fonction lambda pour comparer les noms des sommets
    auto compareSommets = [](const sommet* a, const sommet* b) {
        return a->getNom().toInt() < b->getNom().toInt();
    };

    // Trier les sommets par ordre croissant
    std::sort(sommets.begin(), sommets.end(), compareSommets);

    // Parcourir tous les sommets
    for (const auto& sommet : sommets) {
        // Obtenir les successeurs du sommet
        std::map<QString, std::vector<QString>> successeurs = getSuccesseurs(sommet->getNom());

        // Mettre à jour fs avec les indices des successeurs
        if (successeurs.empty()) {
            // Si le sommet n'a pas de successeurs, ajouter directement un 0 à fs
            fs.push_back(0);
        } else {
            for (const auto& pair : successeurs) {
                const std::vector<QString>& successeursSommet = pair.second;

                for (const auto& successeur : successeursSommet) {
                    fs.push_back(successeur.toInt());
                }
                fs.push_back(0);
            }
        }
    }

    for (int i = 1; i < fs.size(); ++i) {
        if (fs[i] == 0) {
            // Ajouter l'indice de début du successeur au prochain sommet
            aps.push_back(i + 2);
        }
    }

    if (fs.back() == 0) {
        aps.pop_back();
    }

    fs.insert(fs.begin(), fs.size());

    // Créez le graphe avec les vecteurs fs et aps
    graphe nouveauGraphe(fs, aps);

    nouveauGraphe.afficher();
}