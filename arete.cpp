#include "arete.h"

arete::arete(sommet* depart, sommet* arrivee, int valeur) : depart(depart), arrivee(arrivee), valeur(valeur)
{}

sommet* arete::getDepart() const
{
    return depart;
}

sommet* arete::getArrivee() const
{
    return arrivee;
}

int arete::getValeur() const
{
    return valeur;
}
