#ifndef AFFICHAGEGRAPHE_H
#define AFFICHAGEGRAPHE_H

#include "sommet.h"
#include "arete.h"
#include "graphe.h"

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

        std::map<QString, std::vector<QString>> getSuccesseurs(const QString& nomSommet) const;

        void ajouterSommets(QString nomSommetDepart, QString nomSommetArrivee);
        graphe creerGraphe();
        void ajouterArete(sommet* nomSommetDepart, sommet* nomSommetArrivee, int valeur = 0);
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
