#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class graphe
{
    public:
        graphe(vector<int> &fs,vector<int> &aps);
        int nbSommet() const;
        vector<vector<int>> distance() const;
        void fs_aps2adj(vector<int> aps, vector<int> fs, vector<vector<int>> &a);
        void adj2fs_aps(const vector<vector<int>> a, vector<int> &fs, vector<int> &aps);
        void afficher();

    private:
        vector<int> d_fs;
        vector<int> d_aps;
};

#endif // GRAPHE_H
