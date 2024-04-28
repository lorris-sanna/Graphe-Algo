#include "grapheonv.h"

grapheOnV::grapheOnV(const graphe& g): graphe(g)
{}

grapheOnV::grapheOnV(vector<int>& fs, vector<int>& aps): graphe(fs,aps)
{}

grapheOnV::grapheOnV()
{}

vector<int> grapheOnV::ddi()const
{
    //creation de ddi remplis de zero taille = nombres de sommets
    vector<int> ddi(getAPS()[0],0);

    int taille = getFS()[0];
    //Nombre de predecesseur de chacun des sommets
    for(int i = 1 ; i < taille ; i++)
    {
        ddi[getFS()[i]]++;
    }
    ddi[0] = this->nbSommets();
    return ddi;
}

//ASSERT : Il ne faut pas qu'un des sommets pointes sur lui meme
vector<int> grapheOnV::rang()const
{
    vector<int> rang;
    int taille = this->nbSommets();
    //marquer tout les sommets par -1 = + l'infinis
    vector<int> derDegInt = ddi();
    vector<int> pile;
    int debut = 0, fin = 0;
    int niveauRang = 0;
    for(int i = 0 ; i <= taille ; i++)
    {
        if(derDegInt[i] == 0 )
        {
            rang.push_back(niveauRang);
            pile.push_back(i);
            fin++;
        }
        else
            rang.push_back(-1);
    }
    pile.push_back(0);
    niveauRang++;
    int i,j;
    while(debut < fin)
    {
        if(pile[debut] == 0)
        {
            pile.push_back(0);
            niveauRang++;
            debut++;
            fin++;
        }
        i = getAPS()[pile[debut]];
        j=0;

        while(getFS()[i+j] !=0)
        {
            derDegInt[getFS()[i+j]]--;
            if(derDegInt[getFS()[i+j]] == 0)
            {
                rang[getFS()[i+j]] = niveauRang;
                pile.push_back(getFS()[i+j]);
                fin++;
            }
            j++;
        }
        debut++;
    }
    rang[0] = this->nbSommets();

    std::cout << "Pilch :\n";
    for (int i = 0; i < pile.size(); ++i) {
        std::cout << "Sommet " << i << " : " << pile[i] << std::endl;
    }

    return rang;
}

// Fonction pour effectuer le parcours en profondeur de Tarjan
void grapheOnV::dfsTarjan(int u, vector<int>& num, vector<int>& low, vector<bool>& onStack, stack<int>& path, vector<vector<int>>& scc, int& counter) const {
    // Marquer le sommet u comme découvert et lui attribuer un numéro de découverte et une valeur de basse
    num[u] = low[u] = counter++;
    // Ajouter le sommet u au chemin parcouru et le marquer comme étant dans la pile de parcours
    path.push(u);
    onStack[u] = true;

    // Parcours des successeurs de u dans le graphe
    for (int i = getAPS()[u]; i < (getAPS()[u+1])-1; ++i) {
        int v = getFS()[i];
        // Si le successeur v de u n'a pas encore été découvert
        if (num[v] == -1) {
            // Faire un parcours en profondeur récursif depuis v
            dfsTarjan(v, num, low, onStack, path, scc, counter);
            // Mettre à jour la valeur de basse de u avec la valeur de basse de v
            low[u] = std::min(low[u], low[v]);
        }
        // Sinon, si v est dans la pile de parcours
        else if (onStack[v]) {
            // Mettre à jour la valeur de basse de u avec le numéro de découverte de v
            low[u] = std::min(low[u], num[v]);
        }
    }

    // Si u est racine d'une composante fortement connexe
    if (num[u] == low[u]) {
        // Créer une nouvelle composante fortement connexe temporaire
        vector<int> sccTemp;
        // Extraire tous les sommets de la pile de parcours jusqu'à u inclusivement
        while (true) {
            int v = path.top();
            path.pop();
            // Marquer v comme étant hors de la pile de parcours
            onStack[v] = false;
            // Ajouter v à la composante fortement connexe temporaire
            sccTemp.push_back(v);
            // Si u est atteint à nouveau, arrêter l'extraction
            if (u == v) break;
        }
        // Ajouter la composante fortement connexe temporaire à la liste des composantes fortement connexes
        scc.push_back(sccTemp);
    }
}

// Méthode principale de l'algorithme de Tarjan pour trouver les composantes fortement connexes
vector<vector<int>> grapheOnV::tarjan() const {
    int V = this->nbSommets(); // Nombre de sommets
    vector<int> num(V + 1, -1); // Numéro de découverte
    vector<int> low(V + 1); // Valeur de basse
    vector<bool> onStack(V + 1, false); // Indique si un sommet est dans la pile de parcours
    stack<int> path; // Chemin parcouru
    vector<vector<int>> scc; // Composantes fortement connexes
    int counter = 0; // Compteur pour les numéros de découverte

    // Parcours de tous les sommets du graphe à partir du sommet 1
    for (int u = 1; u <= V; u++) { // Commencer à partir de 1
        if (num[u] == -1) {
            dfsTarjan(u, num, low, onStack, path, scc, counter);
        }
    }

    return scc;
}

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
