#ifndef SOMMET_H
#define SOMMET_H

#include <QString>

class sommet {

    public:
        sommet(QString nom);
        QString getNom() const;

    private:
        QString nom;
};

#endif // SOMMET_H
