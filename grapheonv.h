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
        vector<int> tarjan() const;
        void traverseeTarjan(int &sommet, vector<bool> &visiter,vector<int>&num,vector<int> &low, stack<int> &pile, int &compteur, vector<int> &cfc,int &compteurcfc) const;
        vector<vector<int>> composanteCFC() const;
        void graphReduit(vector<int> &fsReduit, vector<int> &apsReduit) const;

        vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) override;
        void ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) override;
        vector<vector<int>> lireMatDepuisFichier(const string &nomFichierIN) override;
};

#endif // GRAPHEONV_H
