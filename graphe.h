#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <QString>

#include "sommet.h"
#include "arete.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;

class graphe
{
    public:
        graphe(vector<int> &fs, vector<int> &aps);
        graphe();
        bool estOriente() const;
        bool estValue() const;
        void setOriente(bool o);
        void setValue(bool v);
        int nbSommets() const;
        int nbAretes() const;
        vector<int> getFS() const;
        vector<int> getAPS() const;
        vector<vector<int>> getMAT() const;
        vector<arete> getAretes() const;
        vector<sommet> getSommets() const;
        void setAretes(const vector<arete>& nouvellesAretes);
        void setFS(vector<int> fs);
        void setAPS(vector<int> fs);
        void setMAT(vector<vector<int>> mat);
        vector<vector<int>> matriceDistance() const;
        void fs_aps2adj(vector<int> aps, vector<int> fs, vector<vector<int>> &matAdj);
        void adj2fs_aps(const vector<vector<int>> matAdj, vector<int> &fs, vector<int> &aps);
        void couts2fs_aps(const vector<vector<int>>& matCout, vector<int>& fs, vector<int>& aps);
        virtual vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) = 0;
        QString fsToString() const;
        QString apsToString() const;
        virtual vector<vector<int>> lireMatDepuisFichier(const string& nomFichierIN) = 0;
        virtual void ecrireMatDansUnFichier(const vector<vector<int>>& mat, const string& nomFichierOUT) = 0;

    private:
        vector<int> d_fs;
        vector<int> d_aps;
        vector<vector<int>> d_mat;

    protected:
        bool oriente, value;
};

#endif // GRAPHE_H
