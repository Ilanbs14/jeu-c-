#ifndef TUILE_H_INCLUDED
#define TUILE_H_INCLUDED
#include "Image.h"
#include <string>

using namespace std;

class Tuile {
    string _nom ;
    int _x ;
    int _y ;
    string _propriete ;

public :
    Tuile(string, int, int, string);
    void afficher() const ;
    string getTuileNom() const ;
    int getTuileX() const ;
    int getTuileY() const ;
    string getTuilePropriete() const ;

};


#endif // PERSONNAGE_H_INCLUDED
