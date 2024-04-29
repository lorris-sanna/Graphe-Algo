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

// Méthode pour calculer le rang de chaque sommet du graphe.
// ASSERT : Il ne faut pas qu'un des sommets pointe sur lui-même.
vector<int> grapheOnV::rang() const
{
    vector<int> rang; // Vecteur pour stocker le rang de chaque sommet
    int taille = this->nbSommets(); // Taille du graphe
    vector<int> derDegInt = ddi(); // Vecteur pour stocker le degré entrant de chaque sommet
    vector<int> pile; // Pile pour effectuer le parcours en largeur
    int debut = 0, fin = 0; // Indices pour marquer le début et la fin de la file
    int niveauRang = 0; // Niveau de rang initial
    // Initialisation du vecteur de rang en marquant tous les sommets par -1, sauf le premier qui représente l'infini
    for(int i = 0 ; i <= taille ; i++)
    {
        if(derDegInt[i] == 0)
        {
            rang.push_back(niveauRang); // Si le degré entrant est 0, attribuer le niveau de rang au sommet
            pile.push_back(i); // Ajouter le sommet à la pile
            fin++; // Incrémenter la fin de la file
        }
        else
            rang.push_back(-1); // Si le degré entrant est non nul, marquer le sommet par -1 (non attribué)
    }
    pile.push_back(0); // Marquer la fin de la première étape de parcours
    niveauRang++; // Incrémenter le niveau de rang
    int i, j;
    // Parcours en largeur pour calculer le rang de chaque sommet
    while(debut < fin)
    {
        if(pile[debut] == 0)
        {
            pile.push_back(0); // Marquer la fin de chaque niveau de parcours
            niveauRang++; // Incrémenter le niveau de rang
            debut++; // Passer au prochain sommet dans la pile
            fin++; // Incrémenter la fin de la file
        }
        i = getAPS()[pile[debut]]; // Accéder au premier successeur du sommet
        j = 0;
        // Parcourir tous les successeurs du sommet
        while(getFS()[i + j] != 0)
        {
            derDegInt[getFS()[i + j]]--; // Réduire le degré entrant du successeur
            if(derDegInt[getFS()[i + j]] == 0)
            {
                rang[getFS()[i + j]] = niveauRang; // Attribuer le niveau de rang au successeur si le degré entrant devient 0
                pile.push_back(getFS()[i + j]); // Ajouter le successeur à la pile
                fin++; // Incrémenter la fin de la file
            }
            j++;
        }
        debut++; // Passer au prochain sommet dans la pile
    }
    rang[0] = this->nbSommets(); // Attribuer le niveau de rang de l'infini au premier sommet
    return rang; // Retourner le vecteur de rang
}


// Méthode pour trouver les composantes fortement connexes du graphe en utilisant l'algorithme de Tarjan.
vector<int> grapheOnV::tarjan() const
{
    int Taille = this->nbSommets() + 1; // Taille du vecteur pour stocker les composantes fortement connexes
    vector<int> low(Taille, -1); // Vecteur pour stocker les valeurs low de chaque sommet
    vector<bool> visiter(Taille, false); // Vecteur pour marquer les sommets visités
    vector<int> num(Taille, -1); // Vecteur pour stocker les numéros de découverte des sommets
    vector<int> cfc(Taille, 0); // Vecteur pour stocker les composantes fortement connexes
    stack<int> pile; // Pile pour effectuer le parcours en profondeur
    int compteur = 0; // Compteur pour les numéros de découverte
    int compteurcfc = 1; // Compteur pour les composantes fortement connexes
    // Parcourir tous les sommets du graphe
    for(int sommet = 1 ; sommet < Taille ; sommet++)
    {
        if(num[sommet] == -1)
        {
            // Si le sommet n'a pas été visité, lancer le parcours en profondeur à partir de ce sommet
            traverseeTarjan(sommet, visiter, num, low, pile, compteur, cfc, compteurcfc);
        }
    }
    cfc[0] = compteurcfc - 1; // Stocker le nombre total de composantes fortement connexes dans la première case
    return cfc; // Retourner le vecteur des composantes fortement connexes
}

// Méthode récursive pour effectuer le parcours en profondeur et trouver les composantes fortement connexes.
void grapheOnV::traverseeTarjan(int &sommet, vector<bool> &visiter,vector<int>&num,vector<int> &low, stack<int> &pile, int &compteur, vector<int> &cfc,int &compteurcfc) const
{
    compteur++; // Incrémenter le compteur de découverte
    num[sommet] = compteur; // Attribuer le numéro de découverte au sommet
    low[sommet]  = compteur; // Initialiser la valeur low du sommet
    pile.push(sommet); // Empiler le sommet
    visiter[sommet] = true; // Marquer le sommet comme visité
    int successeur;
    int i = getAPS()[sommet]; // Accéder au premier successeur du sommet
    // Parcourir tous les successeurs du sommet
    while (getFS()[i] != 0) {
        successeur = getFS()[i];
        if (num[successeur] == -1) {
            // Si le successeur n'a pas été visité, poursuivre le parcours en profondeur depuis ce successeur
            traverseeTarjan(successeur, visiter, num, low, pile, compteur, cfc, compteurcfc);
            low[sommet] = std::min(low[sommet], low[successeur]); // Mettre à jour la valeur low du sommet
        } else if (visiter[successeur]) {
            // Si le successeur a été visité, mettre à jour la valeur low du sommet
            low[sommet] = std::min(low[sommet], num[successeur]);
        }
        i++;
    }
    // Si le sommet est racine d'une composante fortement connexe
    if (num[sommet] == low[sommet])
    {
        // Créer une nouvelle composante fortement connexe temporaire
        vector<int> cfcTemp;

        // Extraire tous les sommets de la pile de parcours jusqu'à u inclusivement
        do
        {
            successeur = pile.top();
            pile.pop();
            visiter[successeur] = false; // Marquer le sommet comme non visité
            cfcTemp.push_back(successeur); // Ajouter le sommet à la composante fortement connexe temporaire
        } while (sommet != successeur);
        // Ajouter la composante fortement connexe temporaire à la liste des composantes fortement connexes
        for(unsigned long long i = 0 ; i < cfcTemp.size(); i++)
        {
            cfc[cfcTemp[i]] = compteurcfc;
        }
        compteurcfc++; // Incrémenter le compteur de composantes fortement connexes
    }
}


// Cette fonction identifie les composantes fortement connexes (CFC) du graphe
// en utilisant l'algorithme de Tarjan. Elle retourne un vecteur de vecteurs
// où chaque vecteur interne contient les sommets appartenant à une CFC.
vector<vector<int>> grapheOnV::composanteCFC() const
{
    // Exécute l'algorithme de Tarjan pour trouver les CFC
    vector<int> cfc = tarjan();

    // Initialise un vecteur de vecteurs pour stocker les CFC
    vector<vector<int>> composante(cfc[0] + 1, vector<int>());

    // Récupère les sommets de chaque CFC
    for (unsigned long long i = 1; i < cfc.size(); i++)
    {
        composante[cfc[i]].push_back(i);
    }
    // Ajoute le nombre total de CFC au début du vecteur
    composante[0].push_back(cfc[0]);

    return composante;
}

// Cette fonction construit le graphe réduit à partir du graphe d'origine.
// Le graphe réduit est représenté par les vecteurs fsReduit et apsReduit.
void grapheOnV::graphReduit(vector<int> &fsReduit, vector<int> &apsReduit) const
{
    // Exécute l'algorithme de Tarjan pour trouver les CFC
    vector<int> cfc = tarjan();

    // Initialise la taille du graphe réduit
    int taille = cfc.size();

    // Initialise un vecteur pour suivre les sommets déjà traités
    vector<bool> dejaMis(taille);

    // Initialise un compteur de successeurs
    int k, successeur;

    // Initialise une pile pour stocker les successeurs des CFC
    stack<int> pileSuccesseur;

    // Ajoute un sommet de fin à fsReduit et apsReduit
    fsReduit.push_back(0);
    apsReduit.push_back(cfc[0]);

    // Parcours les CFC pour construire le graphe réduit
    for (int i = 1; i <= cfc[0]; i++)
    {
        // Réinitialise le vecteur déjàMis pour chaque CFC
        for (int j = 0; j < taille; j++)
            dejaMis[j] = false;

        // Parcours les sommets pour chaque CFC
        for (int j = 1; j < taille; j++)
        {
            // Vérifie si le sommet appartient à la CFC actuelle
            if (cfc[j] == i)
            {
                dejaMis[cfc[j]] = true;
                k = 0;
                successeur = getFS()[getAPS()[j] + k];

                // Parcours les successeurs du sommet
                while (successeur != 0)
                {
                    // Vérifie si le successeur appartient à une autre CFC
                    if (dejaMis[cfc[successeur]] == false)
                    {
                        dejaMis[cfc[successeur]] = true;

                        // Ajoute le successeur à la pile s'il appartient à une autre CFC
                        if (cfc[successeur] != i)
                        {
                            pileSuccesseur.push(cfc[successeur]);
                        }
                    }
                    k++;
                    successeur = getFS()[getAPS()[j] + k];
                }
            }
        }
        // Met à jour apsReduit avec la taille de fsReduit
        apsReduit.push_back(fsReduit.size());

        // Transfère les successeurs de la pile à fsReduit
        while (!pileSuccesseur.empty())
        {
            fsReduit.push_back(pileSuccesseur.top());
            pileSuccesseur.pop();
        }

        // Ajoute un sommet de fin à fsReduit pour cette CFC
        fsReduit.push_back(0);
    }
    // Met à jour la taille du vecteur fsReduit pour indiquer le dernier index
    fsReduit[0] = fsReduit.size() - 1;
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
