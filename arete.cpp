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

bool arete::aInverse(const arete& autre) const
{
    // Vérifier si les sommets de départ et d'arrivée de l'arête actuelle correspondent
    // aux sommets d'arrivée et de départ de l'autre arête
    return (depart == autre.getArrivee() && arrivee == autre.getDepart());
}
