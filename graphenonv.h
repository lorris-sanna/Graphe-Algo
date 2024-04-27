#ifndef GRAPHENONV_H
#define GRAPHENONV_H

#include "graphe.h"

#include <filesystem>
namespace fs = std::filesystem;

class grapheNoNv : public graphe
{
    public:
        grapheNoNv(const graphe& g);
        grapheNoNv(vector<int>& fs, vector<int>& aps);
        grapheNoNv();
        /*bool estOriente() const override;
        bool estValue() const override;
        void setOriente(bool o) override;
        void setValue(bool v) override;*/
        vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) override;
        void ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) override;
        vector<vector<int>> lireMatDepuisFichier(const string &nomFichierIN) override;
};

#endif // GRAPHENONV_H
