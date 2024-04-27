#include "graphevno.h"

grapheVnO::grapheVnO(const graphe& g): graphe(g)
{}

grapheVnO::grapheVnO(vector<int> &fs, vector<int> &aps): graphe{fs,aps}
{}

grapheVnO::grapheVnO()
{}

/*bool grapheVnO::estOriente() const
{
    return false;
}

bool grapheVnO::estValue() const
{
    return true;
}

void grapheVnO::setOriente(bool o)
{
    oriente = o;
}

void grapheVnO::setValue(bool v)
{
    value = v;
}*/

void grapheVnO::fusion(int s, int t, vector<int>& Nb)
{
    int cs = cfc[s];
    int ct = cfc[t];
    if (Nb[cs] < Nb[ct])
    {
        int y = cs;
        cs = ct;
        ct = y;
    }
    int x = prem[ct];
    cfc[x] = cs;
    while(pilch[x] != 0)
    {
        x = pilch[x];
        cfc[x] = cs;
    }
    pilch[x] = prem[cs];
    prem[cs] = prem[ct];
    Nb[cs] = Nb[cs] + Nb[ct];
}

void grapheVnO::ajouterArete(vector<arete>& arete, sommet* depart, sommet* arrivee, int valeur)
{
    class arete nouvelleArete(depart, arrivee, valeur);
    arete.push_back(nouvelleArete);
}

vector<arete> grapheVnO::kruskal(grapheVnO& T, vector<arete>& aretes)
{
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

    int nbAretesAjoutees = 0;

    // Créer un vecteur pour stocker les ensembles disjoints
    vector<int> Nb(n+1);
    cfc.resize(n+1);
    prem.resize(n+1);
    pilch.resize(n+1);

    // Initialiser chaque sommet dans son propre ensemble
    for (int i = 1; i <= n; i++) {
        cfc[i] = i;
        pilch[i] = 0;
        prem[i] = i;
        Nb[i] = 1;
    }

    pilch[0] = 0;

    // Fonction de comparaison pour trier les arêtes par poids croissant
    auto compareAretes = [](const arete &a, const arete &b) {
        return a.getValeur() < b.getValeur();
    };

    // Trier les arêtes par poids croissant
    sort(aretes.begin(), aretes.end(), compareAretes);

    vector<arete> vA;

    // Parcourir toutes les arêtes dans l'ordre croissant de poids
    for (auto& e : aretes) {
        sommet* s = e.getDepart();
        sommet* t = e.getArrivee();

        // Vérifier si l'ajout de cette arête ne forme pas de cycle dans T
        if (cfc[s->getNom().toInt()] != cfc[t->getNom().toInt()]) {
            //cout << "Ajout de l'arete (" << s->getNom().toInt() << ", " << t->getNom().toInt() << ") au graphe T." << endl;
            T.ajouterArete(aretes, s, t, e.getValeur()); // Ajouter l'arête à l'arbre couvrant minimal T
            arete aretesT(s,t,e.getValeur());
            vA.push_back(aretesT);
            fusion(s->getNom().toInt(), t->getNom().toInt(), Nb); // Fusionner les ensembles des sommets s et t

            nbAretesAjoutees++;

            // Si nous avons ajouté n-1 arêtes, nous pouvons arrêter le processus
            if (nbAretesAjoutees == n - 1) {
                break;
            }

            // Affichage des valeurs des vecteurs après fusion
            cout << "Apres fusion : " << endl;
            cout << "prem : ";
            for (int i = 1; i <= n; ++i) {
                cout << prem[i] << " ";
            }
            cout << endl;

            cout << "pilch : ";
            for (int i = 1; i <= n; ++i) {
                cout << pilch[i] << " ";
            }
            cout << endl;

            cout << "cfc : ";
            for (int i = 1; i <= n; ++i) {
                cout << cfc[i] << " ";
            }
            cout << endl;

            cout << "Nb : ";
            for (int i = 1; i <= n; ++i) {
                cout << Nb[i] << " ";
            }
            cout << endl;
        } else {
            cout << "L'arete (" << s->getNom().toInt() << ", " << t->getNom().toInt() << ") forme un cycle. Ignoree." << endl;
        }
    }
    return vA;
}

const vector<int>& grapheVnO::getPrem() const
{
    return prem;
}

const vector<int>& grapheVnO::getPilch() const
{
    return pilch;
}

const vector<int>& grapheVnO::getCfc() const
{
    return cfc;
}

vector<vector<int>> grapheVnO::matriceCouts(graphe& G, vector<arete> aretes) {
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

void grapheVnO::ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) {
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
    fOUT << "0" << endl;
    fOUT << "1" << endl;

    fOUT.close();
}

vector<vector<int>> grapheVnO::lireMatDepuisFichier(const string& nomFichierIN) {
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
