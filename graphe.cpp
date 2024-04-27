#include "graphe.h"

graphe::graphe(vector<int> &fs,vector<int> &aps): d_fs{fs}, d_aps{aps}
{}

graphe::graphe(): d_fs{}, d_aps{}
{}

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

vector<vector<int>> graphe::distance() const
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
    int j;
    int compteurDist = 0;
    for(int i = 1 ; i <= nbSommet ; i++ )
    {
        //fil d'attente
        vector<int> fil;
        fil[0] = i;
        int rangFil = 0;
        int finFil = 1;
        j = d_aps[i];
        //remplir fil et rez avec les sommets adjacents
        while(rangFil < finFil)
        {
            while(d_fs[fil[rangFil]] != 0)
            {
                if(dist[i][d_fs[j]] == -1)
                {
                    fil.push_back(d_fs[j]);
                    dist[i][d_fs[j]] = d_fs[j];
                    j++;
                }
            }

        }
        return dist;
    }
}

void graphe::fs_aps2adj(vector<int> aps, vector<int> fs, vector<vector<int>> &matAdj)
{
    int ns = aps[0]; //nombre de sommets
    int na = fs[0]-ns; //nombre d'aretes

    matAdj.resize(ns+1);

    for(int i = 0; i < matAdj.size(); ++i)
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
