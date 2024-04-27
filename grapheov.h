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

        /*bool estOriente() const override;
        bool estValue() const override;
        void setOriente(bool o) override;
        void setValue(bool o) override;*/

        void dantzig(vector<vector<int>>& c, vector<arete>& aretes);

        vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) override;
        void ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) override;
        vector<vector<int>> lireMatDepuisFichier(const string &nomFichierIN) override;
};

#endif // GRAPHEOV_H
