#ifndef GRAPHEOV_H
#define GRAPHEOV_H

#include "arete.h"
#include "graphe.h"

#include <filesystem>
namespace fs = std::filesystem;

class grapheOV : public graphe
{
    public:
        grapheOV(const graphe& g);
        grapheOV(vector<int>& fs, vector<int>& aps);
        grapheOV();

        void dijkstra(const vector<int>& fs, const vector<int>& aps, const vector<vector<int>>& p, int s, vector<int>& d, vector<int>& pr);
        void dantzig(vector<vector<int>>& c);
        void afficherVecteur(const std::vector<int>& vecteur);

        vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) override;
        void ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) override;
        vector<vector<int>> lireMatDepuisFichier(const string &nomFichierIN) override;
};

#endif // GRAPHEOV_H
