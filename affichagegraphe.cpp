#include "affichagegraphe.h"

affichagegraphe::affichagegraphe()
{}

void affichagegraphe::setOriente(bool oriente) {
    this->oriente = oriente;
}

void affichagegraphe::setValue(bool value) {
    this->value = value;
}

bool affichagegraphe::estOriente() const {
    return oriente;
}

bool affichagegraphe::estValue() const {
    return value;
}

const std::vector<arete>& affichagegraphe::getAretes() const {
    return aretes;
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

void affichagegraphe::setAretes(vector<arete> aretes)
{
    this->aretes = aretes;
}

void affichagegraphe::matAdj2Aretes(vector<vector<int>> matAdj) {
    // Parcourir la matrice d'adjacence
    for (size_t i = 0; i < matAdj.size(); ++i) {
        for (size_t j = 0; j < matAdj[i].size(); ++j) {
            if (matAdj[i][j] == 1) // Si l'élément de la matrice est 1, cela signifie qu'il y a une arête entre les sommets i et j
            {
                // Obtenir le nom des sommets de départ et d'arrivée
                QString nomSommetDepart = QString::number(i);
                QString nomSommetArrivee = QString::number(j);

                // Ajouter les sommets si nécessaire
                ajouterSommets(nomSommetDepart, nomSommetArrivee);

                // Obtenir les pointeurs vers les sommets de départ et d'arrivée
                sommet* sommetDepart = trouverSommet(nomSommetDepart);
                sommet* sommetArrivee = trouverSommet(nomSommetArrivee);

                // Ajouter l'arête si les sommets sont valides
                if (sommetDepart && sommetArrivee) {
                    // Vérifier si une arête identique existe déjà
                    bool arreteExistante = false;
                    for (const auto& existingArete : aretes) {
                        if (existingArete.getDepart()->getNom() == sommetDepart->getNom() && existingArete.getArrivee()->getNom() == sommetArrivee->getNom()) {
                            arreteExistante = true;
                            break;
                        }
                    }

                    // Si aucune arête identique n'existe, ajouter la nouvelle arête
                    if (!arreteExistante) {
                        // Vérifier si les sommets existent déjà dans la liste de sommets
                        sommet* sommetDepartExistant = nullptr;
                        sommet* sommetArriveeExistant = nullptr;

                        for (auto& s : sommets) {
                            if (s->getNom() == sommetDepart->getNom()) {
                                sommetDepartExistant = s;
                            }
                            if (s->getNom() == sommetArrivee->getNom()) {
                                sommetArriveeExistant = s;
                            }
                        }

                        // Si les sommets n'existent pas, les créer
                        if (!sommetDepartExistant) {
                            sommetDepartExistant = new sommet(sommetDepart->getNom());
                            // Ajouter le sommet à la liste de sommets
                            sommets.push_back(sommetDepartExistant);
                        }

                        if (!sommetArriveeExistant) {
                            sommetArriveeExistant = new sommet(sommetArrivee->getNom());
                            // Ajouter le sommet à la liste de sommets
                            sommets.push_back(sommetArriveeExistant);
                        }

                        // Créer la nouvelle arête et l'ajouter à la liste d'arêtes
                        arete nouvelleArete(sommetDepartExistant, sommetArriveeExistant, 1); // Par défaut, on peut mettre un poids de 1 pour une arête sans coût
                        aretes.push_back(nouvelleArete);
                    }
                }
            }
        }
        cout << endl; // Ajoutez un retour à la ligne après chaque ligne de la matrice d'adjacence
    }
}

void affichagegraphe::matCout2Aretes(vector<vector<int>> matCout) {
    // Parcourir la matrice de coûts
    for (size_t i = 0; i < matCout.size(); ++i) {
        for (size_t j = 0; j < matCout[i].size(); ++j) {
            if (matCout[i][j] != std::numeric_limits<int>::max() && matCout[i][j] != 0)
            {
                // Obtenir la valeur du coût
                int valeur = matCout[i][j];

                // Obtenir le nom des sommets de départ et d'arrivée
                QString nomSommetDepart = QString::number(i+1);
                QString nomSommetArrivee = QString::number(j+1);

                // Ajouter les sommets si nécessaire
                ajouterSommets(nomSommetDepart, nomSommetArrivee);

                // Obtenir les pointeurs vers les sommets de départ et d'arrivée
                sommet* sommetDepart = trouverSommet(nomSommetDepart);
                sommet* sommetArrivee = trouverSommet(nomSommetArrivee);

                // Ajouter l'arête si les sommets sont valides
                if (sommetDepart && sommetArrivee) {
                    // Vérifier si une arête identique existe déjà
                    bool arreteExistante = false;
                    for (const auto& existingArete : aretes) {
                        if (existingArete.getDepart()->getNom() == sommetDepart->getNom() && existingArete.getArrivee()->getNom() == sommetArrivee->getNom()) {
                            arreteExistante = true;
                            break;
                        }
                    }

                    // Si aucune arête identique n'existe, ajouter la nouvelle arête
                    if (!arreteExistante) {
                        // Vérifier si les sommets existent déjà dans la liste de sommets
                        sommet* sommetDepartExistant = nullptr;
                        sommet* sommetArriveeExistant = nullptr;

                        for (auto& s : sommets) {
                            if (s->getNom() == sommetDepart->getNom()) {
                                sommetDepartExistant = s;
                            }
                            if (s->getNom() == sommetArrivee->getNom()) {
                                sommetArriveeExistant = s;
                            }
                        }

                        // Si les sommets n'existent pas, les créer
                        if (!sommetDepartExistant) {
                            sommetDepartExistant = new sommet(sommetDepart->getNom());
                            // Ajouter le sommet à la liste de sommets
                            sommets.push_back(sommetDepartExistant);
                        }

                        if (!sommetArriveeExistant) {
                            sommetArriveeExistant = new sommet(sommetArrivee->getNom());
                            // Ajouter le sommet à la liste de sommets
                            sommets.push_back(sommetArriveeExistant);
                        }

                        // Créer la nouvelle arête et l'ajouter à la liste d'arêtes
                        arete nouvelleArete(sommetDepartExistant, sommetArriveeExistant, valeur);
                        aretes.push_back(nouvelleArete);
                    }
                }
            }
        }
        cout << endl; // Ajoutez un retour à la ligne après chaque ligne de la matrice de coûts
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

        // Si l'arête a son opposé, ajouter un décalage à l'angle
        bool arreteInverse = false;
        for (const auto& reverseArete : aretes) {
            if (reverseArete.getDepart()->getNom() == arrivee->getNom() && reverseArete.getArrivee()->getNom() == depart->getNom()) {
                arreteInverse = true;
                break;
            }
        }
        if (arreteInverse) {
            qreal angle = atan2(yDepart - yArrivee, xDepart - xArrivee) * 180 / M_PI;
            xArrivee += 20 * cos(angle * M_PI / 180);
            yArrivee += 20 * sin(angle * M_PI / 180);
        }

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
            QGraphicsPolygonItem* arrowItem = new QGraphicsPolygonItem(QPolygonF() << QPointF(0, -2.5) << QPointF(10, 0) << QPointF(0, 2.5), nullptr);
            arrowItem->setRotation(angle); // Faire pivoter la flèche
            arrowItem->setPos(xArrow, yArrow); // Positionner la flèche juste avant l'extrémité de la droite

            arrowItem->setBrush(Qt::black);

            // Dessiner la flèche
            scene->addItem(arrowItem);

            if (value)
            {
                // Placer le texte près de la flèche
                qreal dx = xArrivee - xDepart;
                qreal dy = yArrivee - yDepart;
                qreal distance = sqrt(dx * dx + dy * dy);

                // Ajuster la position du texte en fonction de la direction de la flèche
                qreal offset = 20; // Décalage par rapport à la flèche
                qreal xText = xArrivee - offset * cos(angle * M_PI / 180);
                qreal yText = yArrivee - offset * sin(angle * M_PI / 180);

                QGraphicsTextItem* poidsItem = scene->addText(QString::number(arete.getValeur()));
                poidsItem->setPos(xText, yText);
                scene->addItem(poidsItem);
            }
        } else {
            if (value)
            {
                // Si non orienté, placer le texte au milieu de l'arête
                qreal dx = xArrivee - xDepart;
                qreal dy = yArrivee - yDepart;
                qreal distance = sqrt(dx * dx + dy * dy);
                qreal segmentLength = distance / 10; // Diviser l'arête en 10 segments

                qreal xPlacement = xDepart + 0.5 * dx;
                qreal yPlacement = yDepart + 0.5 * dy;

                // Ajouter le texte de l'arête
                QGraphicsTextItem* poidsItem = scene->addText(QString::number(arete.getValeur()));
                poidsItem->setPos(xPlacement, yPlacement);
                scene->addItem(poidsItem);
            }
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

const graphe& affichagegraphe::creerGraphe() {
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

    // Créer une instance de la classe de graphe appropriée en fonction des cases à cocher
    graphe* nouveauGraphe = nullptr;

    if (!oriente && !value) {
        nouveauGraphe = new grapheNoNv(fs, aps);
    } else if (oriente && !value) {
        nouveauGraphe = new grapheOnV(fs, aps);
    } else if (!oriente && value) {
        nouveauGraphe = new grapheVnO(fs, aps);
    } else if (oriente && value) {
        nouveauGraphe = new grapheOV(fs, aps);
    }

    // Retourner la référence à l'instance de graphe créée
    return *nouveauGraphe;
}
