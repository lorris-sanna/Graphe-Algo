#include "sommet.h"

sommet::sommet(QString nom) : nom(nom)
{}

QString sommet::getNom() const
{
    return nom;
}
