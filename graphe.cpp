#include "graphe.h"

graphe::graphe(vector<int> &fs,vector<int> &aps): d_fs{fs}, d_aps{aps}
{}

graphe::graphe(): d_fs{}, d_aps{}
{}

bool graphe::estOriente() const
{
    return oriente;
}

bool graphe::estValue() const
{
    return value;
}

void graphe::setOriente(bool o)
{
    oriente = o;
}

void graphe::setValue(bool v)
{
    value = v;
}

int graphe::nbSommets() const
{
    return d_aps[0];
}

int graphe::nbAretes() const
{
    int nbAretes = 0;
    // Parcourir le vecteur d_fs à partir de l'indice 1
    for (size_t i = 1; i < d_fs.size(); ++i) {
        // Si l'élément est différent de zéro, incrémenter le compteur
        if (d_fs[i] != 0) {
            nbAretes++;
        }
    }
    return nbAretes;
}

vector<int> graphe::getFS() const
{
    return d_fs;
}

vector<int> graphe::getAPS() const
{
    return d_aps;
}

vector<vector<int>> graphe::getMAT() const
{
    return d_mat;
}

void graphe::setFS(vector<int> fs)
{
    d_fs = fs;
}

void graphe::setAPS(vector<int> aps)
{
    d_aps = aps;
}

void graphe::setMAT(vector<vector<int>> mat)
{
    d_mat = mat;
}

vector<sommet> graphe::getSommets() const
{
    std::vector<sommet> listeSommets;
    std::vector<sommet*> sommetsExistants;

    // Parcourir les arêtes pour extraire les sommets uniques
    for (const auto& arete : getAretes()) {
        sommet* depart = arete.getDepart();
        sommet* arrivee = arete.getArrivee();

        // Vérifier si le sommet de départ est déjà dans la liste
        auto it_depart = std::find_if(sommetsExistants.begin(), sommetsExistants.end(), [depart](const sommet* s) {
            return s->getNom() == depart->getNom();
        });

        if (it_depart == sommetsExistants.end()) {
            listeSommets.push_back(*depart); // Ajouter le sommet de départ à la liste
            sommetsExistants.push_back(depart); // Ajouter le sommet à la liste des sommets existants
        }

        // Vérifier si le sommet d'arrivée est déjà dans la liste
        auto it_arrivee = std::find_if(sommetsExistants.begin(), sommetsExistants.end(), [arrivee](const sommet* s) {
            return s->getNom() == arrivee->getNom();
        });

        if (it_arrivee == sommetsExistants.end()) {
            listeSommets.push_back(*arrivee); // Ajouter le sommet d'arrivée à la liste
            sommetsExistants.push_back(arrivee); // Ajouter le sommet à la liste des sommets existants
        }
    }

    return listeSommets;
}

vector<arete> graphe::getAretes() const
{
    vector<arete> listeAretes;

    int nbSommets = this->nbSommets();

    // Parcourir les sommets et les arêtes pour créer les objets arete
    for (int i = 1; i <= nbSommets; ++i) {
        int indice_fs = d_aps[i]; // Indice de départ des successeurs du sommet i dans fs
        int successeur = d_fs[indice_fs]; // Premier successeur du sommet i
        while (successeur != 0) {
            sommet* sommetDepart = new sommet(QString::number(i)); // Créer un sommet de départ
            sommet* sommetArrivee = new sommet(QString::number(successeur)); // Créer un sommet d'arrivée
            arete nouvelleArete(sommetDepart, sommetArrivee); // Créer une nouvelle arete
            listeAretes.push_back(nouvelleArete); // Ajouter l'arete à la liste
            indice_fs++;
            successeur = d_fs[indice_fs]; // Successeur suivant
        }
    }

    return listeAretes;
}

vector<vector<int>> graphe::matriceDistance() const
{
    int nbSommet = this->nbSommets();
    //Matrice des distances a return
    vector<vector<int>> dist(nbSommet+1, vector<int>(nbSommet+1));

    //initialisation de la matrice des distance avec des -1 et des 0 sur la diagonale
    for(int i = 1 ; i <= nbSommet ; i++)
    {
        dist[i][0] = nbSommet;
        for(int j = 1 ; j <= nbSommet ; j++)
        {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = -1;
        }
    }
    //Remplir la matrice des distances
    int j,k;
    int distance;
    vector<int> file;
    int debut,fin;
    for(int i = 1 ; i <= nbSommet ; i++ )
    {
        distance = 1;
        j = d_aps[i];
        file.clear();
        file.push_back(0);
        debut = 0;
        fin = 1;
        k = 0;

        //enregistrement des sommets avec une distance de 1
        while(d_fs[j+k] != 0)
        {
            dist[i][d_fs[j+k]] = distance;
            file.push_back(d_fs[j+k]);
            k++;
            fin++;
        }

        //enregistrement des sommets avec une distance > 1
        while(debut < fin)
        {
            if( file[debut] == 0)
            {
                distance++;
                file.push_back(0);
            }
            else
            {
                j = d_aps[file[debut]];
                k = 0;
                while(d_fs[j+k] != 0)
                {
                    if(dist[i][d_fs[j+k]] == -1)
                    {
                        dist[i][d_fs[j+k]] = distance;
                        file.push_back(d_fs[j+k]);
                        fin++;
                    }
                    k++;
                }
            }
            debut++;
        }

    }
    return dist;
}


void graphe::fs_aps2adj(vector<int> aps, vector<int> fs, vector<vector<int>> &matAdj)
{
    int ns = aps[0]; //nombre de sommets
    int na = fs[0]-ns; //nombre d'aretes

    matAdj.resize(ns+1);

    for(size_t i = 0; i < matAdj.size(); ++i)
    {
        matAdj[i].resize(ns+1);
    }

    matAdj[0][0] = ns; //nombre de sommets
    matAdj[0][1] = na; //nombre d'aretes

    for (int i = 1; i <= ns; i++)
    {
        int indice_fs = aps[i];
        while(fs[indice_fs] != 0)
        {
            matAdj[i][fs[indice_fs]] = 1;
            indice_fs++;
        }
    }
}

void graphe::adj2fs_aps(const vector<vector<int>> matAdj, vector<int> &fs, vector<int>& aps)
{
    int ns = matAdj[0][0];
    int na = matAdj[0][1];

    aps.resize(ns + 1);
    fs.resize(ns + na + 1);
    aps[0] = ns;
    fs[0] = na + ns;

    int indice_fs = 1;
    for (int i = 1; i <= ns; ++i)
    {
        aps[i] = indice_fs;
        for (int j = 1; j <= ns; ++j)
        {
            if (matAdj[i][j] == 1)
            {
                fs[indice_fs++] = j;
            }
        }
        fs[indice_fs++] = 0;
    }
}

void graphe::couts2fs_aps(const vector<vector<int>>& matCout, vector<int>& fs, vector<int>& aps)
{
    int ns = matCout[0][0];
    int na = matCout[0][1];

    aps.resize(ns + 1);
    fs.resize(ns + na + 1);
    aps[0] = ns;
    fs[0] = na + ns;

    int indice_fs = 1;
    for (int i = 1; i <= ns; ++i)
    {
        aps[i] = indice_fs;
        for (int j = 1; j <= ns; ++j)
        {
            if (matCout[i][j] != INT_MAX && i != j)
            {
                fs[indice_fs++] = j;
            }
        }
        fs[indice_fs++] = 0;
    }
}

void graphe::fs_aps2fp_app(vector<int> fs, vector<int> aps, vector<int>& fp, vector<int>& app)
{
    // Assurez-vous que les vecteurs fs et aps ne sont pas vides
    if (fs.empty() || aps.empty()) {
        // Gérer ce cas selon vos besoins
        return;
    }

    // Assurez-vous que les vecteurs fp et app ont une taille suffisante
    int n = aps[0];
    fp.resize(fs[0] + 1);
    app.resize(n + 1);

    // Initialisez le premier élément de fp et app
    fp[0] = fs[0];
    app[0] = aps[0];

    // Initialisez le vecteur ddi
    vector<int> ddi(n + 1, 0);

    // Remplissez le vecteur ddi
    for (int i = 1; i <= fs[0]; i++) {
        ddi[fs[i]]++;
    }

    // Initialisez l'identifiant
    int id = 1;

    // Remplissez le vecteur app et mettez à jour l'identifiant
    for (int i = 1; i <= n; i++) {
        app[i] = id;
        id += ddi[i] + 1;
        fp[id - 1] = 0;
    }

    // Copiez les valeurs de app dans ddi
    for (int i = 1; i <= n; i++) {
        ddi[i] = app[i];
    }

    // Initialisez le numéro de nœud
    int noeud = 1;

    // Remplissez le vecteur fp en fonction de fs, aps, ddi et noeud
    for (int i = 1; i <= fs[0]; i++) {
        if (fs[i] == 0) {
            noeud++;
        } else {
            fp[ddi[fs[i]]] = noeud;
            ddi[fs[i]]++;
        }
    }
}

QString graphe::fsToString() const
{
    QString resultat;

    // Conversion du vecteur d_fs en chaîne de caractères
    resultat += "fs[" + QString::number(d_fs.size()) + "] = {";
    for (size_t i = 0; i < d_fs.size(); ++i) {
        if (i > 0) resultat += ", ";
        resultat += QString::number(d_fs[i]);
    }
    resultat += "}";

    return resultat;
}

QString graphe::apsToString() const
{
    QString resultat;

    // Conversion du vecteur d_aps en chaîne de caractères
    resultat += "aps[" + QString::number(d_aps.size()) + "] = {";
    for (size_t i = 0; i < d_aps.size(); ++i) {
        if (i > 0) resultat += ", ";
        resultat += QString::number(d_aps[i]);
    }
    resultat += "}";

    return resultat;
}
