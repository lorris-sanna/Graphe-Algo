#include "grapheov.h"

grapheOV::grapheOV(const graphe& g): graphe(g)
{}

grapheOV::grapheOV(vector<int>& fs, vector<int>& aps): graphe(fs,aps)
{}

grapheOV::grapheOV()
{}

/*bool grapheOV::estOriente() const
{
    return true;
}

bool grapheOV::estValue() const
{
    return true;
}

void grapheOV::setOriente(bool o)
{
    oriente = o;
}

void grapheOV::setValue(bool v)
{
    value = v;
}*/

void grapheOV::dantzig(vector<vector<int>>& c, vector<arete>& aretes)
{
    int x;

    vector<int> sommetsNonAjoutes;
    for (const auto& arete : aretes) {
        int depart = arete.getDepart()->getNom().toInt();
        int arrivee = arete.getArrivee()->getNom().toInt();
        if (find(sommetsNonAjoutes.begin(), sommetsNonAjoutes.end(), depart) == sommetsNonAjoutes.end()) {
            sommetsNonAjoutes.push_back(depart);
        }
        if (find(sommetsNonAjoutes.begin(), sommetsNonAjoutes.end(), arrivee) == sommetsNonAjoutes.end()) {
            sommetsNonAjoutes.push_back(arrivee);
        }
    }

    // Récupérer le nombre de sommets dans le graphe
    int n = sommetsNonAjoutes.size();

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

vector<vector<int>> grapheOV::matriceCouts(graphe& G, vector<arete> aretes) {
    int ns = G.nbSommets(); //nombre de sommets
    int na = G.nbAretes(); //nombre d'aretes

    const int INFINI = std::numeric_limits<int>::max(); // Constante pour représenter l'infini

    // Initialisation de matCout avec la taille correcte
    vector<vector<int>> matCout(ns + 1, vector<int>(ns + 1, INFINI));

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

    const int INFINI = std::numeric_limits<int>::max(); // Constante pour représenter l'infini

    if (!matCout.empty() && matCout[0].size() >= 2) {
        fOUT << matCout[0][0] << " " << matCout[0][1] << endl;
        for(int i = 1; i < matCout.size(); ++i) {
            for(int j = 1; j < matCout[i].size(); ++j) {
                if (matCout[i][j] == INFINI) {
                    fOUT << "∞";
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
    int ns, na; //nombre de sommets, nombre d'aretes
    fIN >> ns >> na; //première valeur = nb sommets

    vector<vector<int>> matrice(ns, vector<int>(ns));

    // Lecture de la matrice
    for (int i = 0; i < ns; ++i) {
        for (int j = 0; j < ns; ++j) {
            string valeur;
            fIN >> valeur;
            if (valeur == "∞") {
                matrice[i][j] = std::numeric_limits<int>::max();
            } else {
                matrice[i][j] = stoi(valeur);
            }
        }
    }

    cout << "Lecture terminée." << endl;
    return matrice;
}
