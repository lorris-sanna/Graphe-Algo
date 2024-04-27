#include "grapheonv.h"

grapheOnV::grapheOnV(const graphe& g): graphe(g)
{}

grapheOnV::grapheOnV(vector<int>& fs, vector<int>& aps): graphe(fs,aps)
{}

grapheOnV::grapheOnV()
{}

/*bool grapheOnV::estOriente() const
{
    return true;
}

bool grapheOnV::estValue() const
{
    return false;
}

void grapheOnV::setOriente(bool o)
{
    oriente = o;
}

void grapheOnV::setValue(bool v)
{
    value = v;
}*/

vector<vector<int>> grapheOnV::matriceCouts(graphe& G, vector<arete> aretes) {
    return std::vector<std::vector<int>>();
}

void grapheOnV::ecrireMatDansUnFichier(const vector<vector<int>>& matAdj, const std::string& nomFichierOUT) {
    // Créer le répertoire "graphes" s'il n'existe pas
    fs::create_directories("graphes");

    // Ouvrir le fichier dans répertoire courant + extension ou chemin absolu à donner
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
    fOUT << "1" << endl;
    fOUT << "0" << endl;

    fOUT.close();
}

vector<vector<int>> grapheOnV::lireMatDepuisFichier(const string &nomFichierIN)
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
