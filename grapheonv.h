#ifndef GRAPHEONV_H
#define GRAPHEONV_H

#include "graphe.h"

#include <filesystem>
namespace fs = std::filesystem;

class grapheOnV : public graphe
{
    public:
        grapheOnV(const graphe& g);
        grapheOnV(vector<int>& fs, vector<int>& aps);
        grapheOnV();
        /*bool estOriente() const override;
        bool estValue() const override;
        void setOriente(bool o) override;
        void setValue(bool o) override;*/
        vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) override;
        void ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) override;
        vector<vector<int>> lireMatDepuisFichier(const string &nomFichierIN) override;
};

#endif // GRAPHEONV_H
