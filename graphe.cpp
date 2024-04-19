#include "graphe.h"

graphe::graphe(vector<int> &fs,vector<int> &aps): d_fs{fs}, d_aps{aps}
{}

int graphe::nbSommet() const
{
    return d_aps[0];
}

vector<vector<int>> graphe::distance() const
{
    int nbSommet = this->nbSommet();
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

void graphe::fs_aps2adj(vector<int> aps, vector<int> fs, vector<vector<int>> &a) {
    int n = aps[0];
    int m = fs[0];
    a.resize(n + 1); // Redimensionner a pour contenir n+1 vecteurs

    a[0].resize(2); // Redimensionner le premier vecteur pour contenir 2 éléments
    a[0][0] = n;
    a[0][1] = m;

    for (int i = 1; i < n; i++) {
        int nbs = aps[i + 1] - aps[i] - 1;
        a[i].resize(nbs + 1); // Redimensionner le i-ème vecteur pour contenir nbs + 1 éléments
        a[i][0] = nbs;
        for (int j = 1; fs[aps[i] + j - 1] != 0; j++)
            a[i][j] = fs[aps[i] + j - 1];
    }

    int nbs = fs[0] - aps[n];
    a[n].resize(nbs + 1); // Redimensionner le dernier vecteur pour contenir nbs + 1 éléments
    a[n][0] = nbs;
    for (int j = 1; fs[aps[n] + j - 1] != 0; j++)
        a[n][j] = fs[aps[n] + j - 1];
}

void adj2fs_aps(const vector<vector<int>> a, vector<int> &fs, vector<int> &aps) {
    int n = a[0][0];
    int m = a[0][1];

    fs.resize(n+1);
    aps.resize(n+1);

    fs[0] = n+m;
    aps[0] = n;

    int i = 1;
    for (int lig = 1; lig <= n; lig++) {
        aps[lig] = i;
        for (int col = 1; col <= n; col++) {
            if (a[lig][col] == 1) {
                fs[i] = col;
                i++;
            }
        }
        fs[i] = 0;
        i++;
    }
}

void graphe::afficher() {
    cout << "fs[" << d_fs.size() << "]" << " = ";
    cout << " {";
    for (size_t i = 0; i < d_fs.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << d_fs[i];
    }
    cout << "}" << endl;

    cout << "aps[" << d_aps.size() << "]" << " = ";
    cout << " {";
    for (size_t i = 0; i < d_aps.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << d_aps[i];
    }
    cout << "}" << endl;
}
