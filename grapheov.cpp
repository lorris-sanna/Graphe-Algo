#include "grapheov.h"

grapheOV::grapheOV(const graphe& g): graphe(g)
{}

grapheOV::grapheOV(vector<int>& fs, vector<int>& aps): graphe(fs,aps)
{}

grapheOV::grapheOV()
{}

void grapheOV::dijkstra(const vector<int>& fs, const vector<int>& aps, const vector<vector<int>>& p, int s, vector<int>& d, vector<int>& pr) {
    int n = aps[0]; // nombre de sommets
    int m = fs[0];  // taille de fs
    const int MAXPOIDS = INT_MAX; // poids maximum inatteignable

    d.resize(n + 1, MAXPOIDS);
    pr.resize(n + 1, -1);
    vector<int> inS(n + 1, 1); //pour les sommets qui restent à traiter
    // Initialisation des tableaux d, pr, et inS
    for (int i = 1; i <= n; i++) {
        d[i] = p[s][i];
        pr[i] = s;
    }
    d[s] = 0;
    pr[s] = s;
    inS[s] = 0; //on connait déjà le sommet s

    int ind = n - 1; //le sommet s est déjà traité

    while (ind > 0) {
        // recherche du sommet le plus proche de s
        int m = MAXPOIDS;
        int j = -1;
        for (int i = 1; i <= n; i++) {
            if (inS[i] && d[i] < m) {
                m = d[i];
                j = i;
            }
        }

        if (m == MAXPOIDS) break; // aucun noeud accessible depuis s

        inS[j] = 0;
        ind--;

        // traitement des successeurs de j
        for (int k = aps[j]; fs[k] != 0; k++) {
            int v = d[j] + p[j][fs[k]];
            if (inS[fs[k]] && v < d[fs[k]]) {
                d[fs[k]] = v;
                pr[fs[k]] = j;
            }
        }
    }
}

void grapheOV::dantzig(vector<vector<int>>& c)
{
    int x;

    // Récupérer le nombre de sommets dans le graphe
    int n = c[0][0];

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (c[i][k] != INT_MAX && c[k][j] != INT_MAX) {
                    c[i][j] = std::min(c[i][j], c[i][k] + c[k][j]);
                }
            }
        }
    }
}

void grapheOV::afficherVecteur(const std::vector<int>& vecteur) {
    std::cout << "Contenu du vecteur : ";
    for (int element : vecteur) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void grapheOV::ordonnancement(const vector<int>& fp, const vector<int>& app, const vector<int>& d, vector<int>& fpc, vector<int>& appc, vector<int>& lc)
{
    int n = app[0]; // Nombre total de tâches
    fpc.resize(n + 1); // Initialisation du vecteur des dates au plus tôt
    appc.resize(n + 1); // Initialisation du vecteur des successeurs critiques
    lc.resize(n + 1); // Initialisation du vecteur des dates au plus tôt
    appc[0] = n;
    lc[0] = n;

    int kc = 1; // Indice du prochain successeur critique
    int t, lg;

    lc[1] = 0; // Date au plus tôt de la première tâche
    fpc[1] = 0; // Initialisation du vecteur des successeurs critiques
    appc[1] = 0;

    // Parcours de toutes les tâches
    for(int s = 2; s <= n; s++)
    {
        lc[s] = 0; // Initialisation de la date au plus tôt de la tâche s
        appc[s] = kc + 1; // Initialisation de l'indice de départ des successeurs critiques de la tâche s

        // Parcours des tâches précédentes de la tâche s
        for(int k = app[s]; (t = fp[k]) != 0; k++)
        {
            // Calcul de la date au plus tôt de la tâche s
            lg = lc[t] + d[t];

            // Mise à jour de la date au plus tôt et des successeurs critiques si nécessaire
            if (lg >= lc[s])
            {
                if (lg > lc[s])
                {
                    lc[s] = lg;
                    kc = appc[s];
                    fpc[kc] = t;
                } else {
                    kc++;
                    fpc[kc] = t;
                }
            }
        }
        kc++;
        fpc[kc] = 0; // Marquage de la fin des successeurs critiques de la tâche s
    }
}

vector<vector<int>> grapheOV::matriceCouts(graphe& G, vector<arete> aretes)
{
    int ns = G.nbSommets(); //nombre de sommets
    int na = G.nbAretes(); //nombre d'aretes

    const int MAXPOIDS = INT_MAX;

    // Initialisation de matCout avec la taille correcte
    vector<vector<int>> matCout;

    matCout.resize(ns+1);

    for(int i = 0; i < matCout.size(); ++i)
    {
        matCout[i].resize(ns+1, MAXPOIDS);
    }

    matCout[0][0] = ns; //nombre de sommets
    matCout[0][1] = na; //nombre d'arêtes

    // Remplissage de matAdj avec les valeurs des arêtes
    for (const auto& arete : aretes) {
        int depart = arete.getDepart()->getNom().toInt();
        int arrivee = arete.getArrivee()->getNom().toInt();
        int valeur = arete.getValeur();
        matCout[depart][arrivee] = valeur;
    }

    // Attribution de 0 à la diagonale et aux valeurs des sommets sans arêtes sortantes
    for (int i = 1; i <= ns; i++) {
        matCout[i][i] = 0; // Attribution de 0 à la diagonale
    }

    return matCout;
}

void grapheOV::ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) {
    // Créer le répertoire "graphes" s'il n'existe pas
    fs::create_directories("graphes");

    // Ouvrir le fichier dans le répertoire courant + extension ou chemin absolu à donner
    ofstream fOUT("graphes/" + nomFichierOUT + ".txt");

    // Vérification de l'accès au fichier
    if (!fOUT.is_open()) {
        cerr << "Impossible d'ouvrir '" << nomFichierOUT << "' pour écrire dedans." << endl;
        return;
    } else {
        cout << "Fichier '" << nomFichierOUT << "' ouvert avec succès." << endl;
    }

    const int MAXPOIDS = INT_MAX;

    if (!matCout.empty() && matCout[0].size() >= 2) {
        fOUT << matCout[0][0] << " " << matCout[0][1] << endl;
        for(int i = 1; i < matCout.size(); ++i) {
            for(int j = 1; j < matCout[i].size(); ++j) {
                if (matCout[i][j] == MAXPOIDS) {
                    fOUT << "MAXPOIDS";
                } else {
                    fOUT << matCout[i][j];
                }
                // Ajouter un espace si ce n'est pas la dernière valeur de la ligne
                if (j < matCout[i].size() - 1) {
                    fOUT << " ";
                } else {
                    fOUT << ""; // Pas d'espace à la fin de la ligne
                }
            }
            fOUT << endl;
        }
        cout << "La matrice a été créée" << endl;
    } else {
        cerr << "La matrice est trop petite" << endl;
    }

    // Indique le type de graphe
    fOUT << "1" << endl;
    fOUT << "1" << endl;

    fOUT.close();
}

vector<vector<int>> grapheOV::lireMatDepuisFichier(const string& nomFichierIN) {
    ifstream fIN("graphes/" + nomFichierIN);
    if (!fIN) {
        cerr << "Impossible d'ouvrir le fichier " << nomFichierIN << endl;
        return {};
    }
    cout << "Lecture du fichier en cours..." << endl;
    int ns, na; // nombre de sommets, nombre d'arêtes
    fIN >> ns >> na; // première valeur = nb sommets

    int nb_col = ns + 1; // pour éviter de recalculer

    // Matrice d'adjacence pour construire le graphe
    vector<vector<int>> adjTmp(nb_col, vector<int>(nb_col, 0));

    // Initialisation de la première ligne et colonne à zéro
    for (int i = 0; i < nb_col; ++i) {
        adjTmp[0][i] = 0; // Première ligne
        adjTmp[i][0] = 0; // Première colonne
    }

    adjTmp[0][0] = ns; // Utilisation de la case (0,0) pour le nombre de sommets
    adjTmp[0][1] = na; // Case (0,1) pour le nombre d'arêtes

     const int MAXPOIDS = INT_MAX;

    // Lecture de la matrice
    for (int i = 1; i <= ns; ++i) {
        for (int j = 1; j <= ns; ++j) {
            string valeur;
            fIN >> valeur;
            if (valeur == "MAXPOIDS") {
                adjTmp[i][j] = MAXPOIDS; // Remplacer "∞" par 0
            } else {
                adjTmp[i][j] = stoi(valeur);
            }
        }
    }

    cout << "Lecture terminée." << endl;
    return adjTmp;
}
