#ifndef DICTIONNAIRE_H_INCLUDED
#define DICTIONNAIRE_H_INCLUDED
#include <string>
#include <vector>
#include <fstream>
#include "Tuile.h"

class Dictionnaire{
    vector<Tuile> _tuile ;

public:
    Dictionnaire(ifstream& fichier);
    void afficher() const ;
    bool recherche (string,Tuile&) ;
};

#endif // PERSONNAGE_H_INCLUDED
