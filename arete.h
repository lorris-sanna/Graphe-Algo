#ifndef ARETE_H
#define ARETE_H

#include "sommet.h"

class arete
{
    public:
        arete(sommet* depart, sommet* arrivee, int valeur = 0);
        sommet* getDepart() const;
        sommet* getArrivee() const;
        int getValeur() const;
        bool aInverse(const arete& autre) const; // Méthode pour vérifier si l'arête a son inverse

    private:
        sommet* depart;
        sommet* arrivee;
        int valeur;
};

#endif // ARETE_H
