#ifndef OBJET_H_INCLUDED
#define OBJET_H_INCLUDED
#include "Dictionnaire.h"
#include "Image.h"

using namespace std;

class Objet{
    Image _image ;
    int _objx ;
    int _objy ;
    string _objPropriete ;

public :
    Objet(Image,string,Dictionnaire,int,int);
    void dessiner() ;
    string getObjetPropriete () const ;
    int getObjetX() const ;
    int getObjetY() const ;
    void cacher();
};

#endif // PERSONNAGE_H_INCLUDED
