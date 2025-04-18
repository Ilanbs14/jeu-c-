#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
#include "Image.h"
#include "Niveau.h"
#include <string>

using namespace std;

class Personnage {
    Image _image ;
    int _x ;
    int _y ;
    int _skinX;
    int _skinY;
    int _pos ; //0 = bas//1 = gauche//2 = droite// 3 = haut//
    Niveau _niveau ;

public :
    Personnage(Image, int, int, int, int, int, Niveau);
    Personnage();

    void dessiner() ;

    void allerDroite() ;
    void allerGauche() ;
    void allerHaut() ;
    void allerBas() ;
    int getX();
    int getY();
    bool touche(Personnage&);
    string bordAtteint();
    void avancer();
    void suivre(Personnage);
    void changerNiveau(Niveau);
    void changerCoordonnees(int,int);
};

#endif // PERSONNAGE_H_INCLUDED
