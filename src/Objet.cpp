#include "Objet.h"

using namespace std;

Objet::Objet(Image I,string nom,Dictionnaire D,int x,int y)
{
    Tuile T ("inconnu",0,0,"inconnu");
    D.recherche(nom,T);
    _image = I ;
    _image.selectionnerRectangle(T.getTuileX()*16,T.getTuileY()*16,16,16);
    _objPropriete = T.getTuilePropriete() ;
    _objx = x*16 ;
    _objy = y*16 ;
}

void Objet::dessiner()
{
    if (_objPropriete != "cache")
        _image.dessiner(_objx,_objy);
}

string Objet::getObjetPropriete() const
{
    return _objPropriete ;
}

int Objet::getObjetX() const
{
    return _objx ;
}

int Objet::getObjetY() const
{
    return _objy ;
}

void Objet::cacher() {
    _objPropriete = "cache";
}
