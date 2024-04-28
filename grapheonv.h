#ifndef GRAPHEONV_H
#define GRAPHEONV_H

#include "graphe.h"

#include <stack>

#include <filesystem>
namespace fs = std::filesystem;

using std::stack;

class grapheOnV : public graphe
{
    public:
        grapheOnV(const graphe& g);
        grapheOnV(vector<int>& fs, vector<int>& aps);
        grapheOnV();

        // Rang
        vector<int> ddi() const;
        vector<int> rang() const;

        // Tarjan
        void dfsTarjan(int u, vector<int>& num, vector<int>& low, vector<bool>& onStack, stack<int>& path, vector<vector<int>>& scc, int& counter) const;
        vector<vector<int>> tarjan() const;

        vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) override;
        void ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) override;
        vector<vector<int>> lireMatDepuisFichier(const string &nomFichierIN) override;
};

#endif // GRAPHEONV_H
