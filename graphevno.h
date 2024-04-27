#ifndef GRAPHEVNO_H
#define GRAPHEVNO_H

#include "graphe.h"
#include "arete.h"

class grapheVnO : public graphe
{
    public:
        grapheVnO(const graphe& g);
        grapheVnO(vector<int> &fs, vector<int> &aps);
        grapheVnO();

        bool estOriente() const override;
        bool estValue() const override;
        void setOriente(bool o) override;
        void setValue(bool o) override;
        void ajouterArete(vector<arete>& arete, sommet* depart, sommet* arrivee, int valeur);

        void fusion(int s, int t, vector<int>& nb);
        vector<arete> kruskal(grapheVnO& T, vector<arete>& aretes);

        const vector<int>& getPrem() const;
        const vector<int>& getPilch() const;
        const vector<int>& getCfc() const;

        vector<vector<int>> matriceCouts(graphe& G, vector<arete> aretes) override;
        void ecrireMatDansUnFichier(const vector<vector<int>>& matCout, const std::string& nomFichierOUT) override;
        vector<vector<int>> lireMatDepuisFichier(const string &nomFichierIN) override;

    private:
        vector<int> prem;
        vector<int> pilch;
        vector<int> cfc;
};

#endif // GRAPHEVNO_H
