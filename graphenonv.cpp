#include "graphenonv.h"

grapheNoNv::grapheNoNv(const graphe& g): graphe(g)
{}

grapheNoNv::grapheNoNv(vector<int>& fs, vector<int>& aps): graphe(fs,aps)
{}

grapheNoNv::grapheNoNv()
{}

vector<int> grapheNoNv::codagePrufer(vector<vector<int>>& matAdj)
{
    int n = matAdj[0][0]; //nombre de sommets
    int m = matAdj[0][1]; //nombre d'arcs

    if(m != n-1)
    {
        cout << "le nombre d'aretes doit correspondre au nombre de sommets - 1";
        return {};
    }

    // Vecteur pour stocker le codage de Prufer
    vector<int> prf;
    prf.push_back(n-2);

    while (n > 2)
    {
        int v = -1; // Sommet feuille avec étiquette minimale
        for (int i = 0; i < matAdj.size(); ++i) {
            int degree = 0;
            for (int j = 0; j < matAdj[i].size(); ++j) {
                degree += matAdj[i][j];
            }
            if (degree == 1 && (v == -1 || i < v))
                v = i;
        }

        // Recherche du seul voisin de v
        int s = -1;
        for (int j = 0; j < matAdj[v].size(); ++j) {
            if (matAdj[v][j] == 1) {
                s = j;
                break;
            }
        }

        // Ajout du voisin au codage de Prufer
        prf.push_back(s);

        // Suppression du sommet v et de l'arête (s, v) de la matrice d'adjacence
        matAdj[v][s] = 0;
        matAdj[s][v] = 0;

        // Réduction du nombre de sommets
        --n;
    }

    return prf;
}

vector<vector<int>> grapheNoNv::decodagePrufer(vector<int>& prf)
{
    //création d'une matrice d'adjacence vierge
    vector<vector<int>> matAdj;

    matAdj.resize(prf.size()+2);

    for(int i = 0; i < matAdj.size(); ++i)
    {
        matAdj[i].resize(prf.size()+2);
    }

    int m = prf[0], n = m+2;

    vector<int> t;
    //nombre total de sommets de l'arbre + 1
    t.resize(n+1);


    //comptage du nombre d'occurences des sommets dans le code de Prufer
    for (int i = 1; i <= m; i++)
    {
        t[prf[i]]++;
    }

    //recherche du j premier élément non utilisé pour chaque i de la séquence de Prufer
    for (int i = 1; i <= m; i++)
    {
        int j = 1;
        while(t[j] != 0)
        {
            ++j;
        }
        //on marque l'élément comme utilisé et on supprime l'occurence de i
        t[prf[i]]--;
        t[j] = -1;
        //création du lien dans la matrice d'adjacence
        matAdj[prf[i]][j] = 1;
        matAdj[j][prf[i]] = 1;
    }

    //A la fin il reste 2 sommets qu'on relie
    //les autres sont à "-1"
    vector<int> ds;

    for (int i = 1; i <= n; i++)
    {
        if (t[i] == 0)
        {
            ds.push_back(i);
        }
    }
    //création du lien dans la matrice d'adjacence
    matAdj[ds[0]][ds[1]] = 1;
    matAdj[ds[1]][ds[0]] = 1;

    matAdj[0][0] = n;
    matAdj[0][1] = n - 1;

    return matAdj;
}

vector<vector<int>> grapheNoNv::matriceCouts(graphe& G, vector<arete> aretes) {
    return std::vector<std::vector<int>>();
}

void grapheNoNv::ecrireMatDansUnFichier(const vector<vector<int>>& matAdj, const std::string& nomFichierOUT) {
    // Créer le répertoire "graphes" s'il n'existe pas
    fs::create_directories("graphes");

    // Ouvrir le fichier dans répertoire graphes + extension ou chemin absolu à donner
    ofstream fOUT("graphes/" + nomFichierOUT + ".txt");

    // Vérification accès au fichier
    if (!fOUT.is_open()) {
        cerr << "Impossible d'ouvrir '" << nomFichierOUT << "' pour ecrire dedans." << endl;
        return;
    } else {
        cout << "Fichier '" << nomFichierOUT << "' ouvert avec succes." << endl;
    }
    if (!matAdj.empty() && matAdj[0].size() >= 2) {
        fOUT << matAdj[0][0] << " " << matAdj[0][1] << endl;
        for(int i = 1; i < matAdj.size(); ++i)
        {
            for(int j = 1; j < matAdj[i].size(); ++j)
            {

                if(j < matAdj.size() - 1)
                {
                    fOUT << matAdj[i][j] << " ";
                }
                else
                {
                    fOUT << matAdj[i][j];
                }
            }
            fOUT << endl;
        }
        cout << "La matrice a ete cree" << endl;
    } else {
        cerr << "La matrice est trop petite" << endl;
    }

    // Indique type de graphe
    fOUT << "0" << endl;
    fOUT << "0" << endl;

    // Fermeture du fichier
    fOUT.close();
}

vector<vector<int>> grapheNoNv::lireMatDepuisFichier(const string &nomFichierIN)
{
    ifstream fIN("graphes/" + nomFichierIN);
    if (!fIN)
    {
        cout << "Impossible d'ouvrir le fichier " << nomFichierIN << endl;
        return {};
    }
    cout << "Lecture du fichier en cours..." << endl;
    int ns, na; //nombre de sommets, nombre d'aretes
    fIN >> ns >> na; //première valeur = nb sommets
    int nb_col = ns + 1; //pour éviter recalcul
    //matrice d'adjacence pour construire graphe
    vector<vector<int>> adjTmp(nb_col, vector<int>(nb_col, 0));
    for (int i = 0; i < nb_col; ++i) {
        adjTmp[0][i] = 0; // Première ligne
        adjTmp[i][0] = 0; // Première colonne
    }
    adjTmp[0][0] = ns; //utilisation de la case (0,0) pour le nombre de sommets
    adjTmp[0][1] = na; //case (0,1) pour le nombre d'aretes

    for (int i = 1; i <= ns; ++i)
    {
        for (int j = 1; j <= ns; ++j)
        {
            fIN >> adjTmp[i][j];
        }
    }

    cout << "Lecture terminée." << endl;
    return adjTmp;
}
