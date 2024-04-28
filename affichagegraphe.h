#ifndef AFFICHAGEGRAPHE_H
#define AFFICHAGEGRAPHE_H

#include "sommet.h"
#include "arete.h"
#include "graphe.h"
#include "graphenonv.h"
#include "grapheonv.h"
#include "graphevno.h"
#include "grapheov.h"

#include <vector>
#include <QString>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

class affichagegraphe
{

    public:
        affichagegraphe();

        void setOriente(bool oriente);
        void setValue(bool value);
        bool estOriente() const;
        bool estValue() const;

        const std::vector<arete>& getAretes() const;
        std::map<QString, std::vector<QString>> getSuccesseurs(const QString& nomSommet) const;

        void ajouterSommets(QString nomSommetDepart, QString nomSommetArrivee);
        const graphe& creerGraphe();
        void ajouterArete(sommet* nomSommetDepart, sommet* nomSommetArrivee, int valeur = 0);
        void setAretes(vector<arete> aretes);
        void matAdj2Aretes(vector<vector<int>> matAdj);
        void matCout2Aretes(vector<vector<int>> matCout);
        void dessinerGraphe(QGraphicsScene* scene);
        void reset();
        bool isEmpty() const;

        sommet* trouverSommet(QString nom);
        void afficher();

    private:
        std::vector<sommet*> sommets;
        std::vector<arete> aretes;

        bool oriente, value;

};

#endif // AFFICHAGEGRAPHE_H
