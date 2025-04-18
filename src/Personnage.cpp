#include <SDL_image.h>
#include <exception>
#include "Image.h"
#include "Personnage.h"
#include <string>

using namespace std;

Personnage::Personnage(Image image, int x , int y, int skinX, int skinY, int pos, Niveau niveau)
{
    _image = image ;
    _x = x ;
    _y = y ;
    _skinX = skinX;
    _skinY = skinY;
    _pos = pos ;
    _niveau = niveau ;
}

Personnage::Personnage() {}

void Personnage::dessiner ()
{
    _image.dessiner(_x,_y);
}

void Personnage::allerGauche()
{
    if(_niveau.caseEstLibre(_x-16,_y))
    {
        if(_x != 0)
            _x -= 16 ;
    }
    _pos = 1 ;
    _image.selectionnerRectangle(_skinX,(_pos * 16) + _skinY,16,16);
}

void Personnage::allerDroite()
{
    if(_niveau.caseEstLibre(_x+16,_y))
    {
        if(_x != 144)
            _x += 16 ;
    }
    _pos = 2 ;
    _image.selectionnerRectangle(_skinX,(_pos * 16) + _skinY,16,16);
}

void Personnage::allerBas()
{
    if(_niveau.caseEstLibre(_x,_y+16))
    {
        if(_y != 112)
            _y += 16 ;
    }
    _pos = 0 ;
    _image.selectionnerRectangle(_skinX,(_pos * 16) + _skinY,16,16);
}

void Personnage::allerHaut()
{
    if(_niveau.caseEstLibre(_x,_y-16))
    {
        if(_y != 0)
            _y -= 16 ;
    }
    _pos = 3 ;
    _image.selectionnerRectangle(_skinX,(_pos * 16) + _skinY,16,16);
}

int Personnage::getX() {
    return _x;
}

int Personnage::getY() {
    return _y;
}

bool Personnage::touche(Personnage& p) {
    return ((_x == p.getX()) && (_y == p.getY()));
}

void Personnage::avancer()
{
    if (_pos == 0)
    {
        if (bordAtteint()[1] == 'B' || !_niveau.caseEstLibre(_x,_y+16))
        {
            _pos = 3 ;
        }
        else{
            allerBas();
        }
    }
    else if (_pos == 1)
    {
        if (bordAtteint()[0] == 'G' || !_niveau.caseEstLibre(_x-16,_y))
        {
            _pos = 2 ;
        }
        else{
            allerGauche();
        }
    }
    else if (_pos == 2)
    {
        if (bordAtteint()[0] == 'D' || !_niveau.caseEstLibre(_x+16,_y))
        {
            _pos = 1 ;
        }
        else{
            allerDroite();
        }
    }
     else if (_pos == 3)
    {
        if (bordAtteint()[1] == 'H' || !_niveau.caseEstLibre(_x,_y-16))
        {
            _pos = 0 ;
        }
        else{
            allerHaut();
        }
    }
}

string Personnage::bordAtteint()
{
    string result = "" ;
    if (_x == 0)
        result += "G";
    else if (_x == 144)
        result += "D" ;
    else
        result += " ";


    if (_y == 0)
        result += "H";
    else if (_y == 112)
        result += "B" ;
    else
        result += " ";

    return result ;
}

void Personnage::suivre(Personnage P)
{
    int xdiff = P.getX() - getX();
    int ydiff = P.getY()- getY();
    if (xdiff < 0)
        xdiff *= -1;
    if (ydiff < 0)
        ydiff *= -1;
    if ( xdiff < ydiff) {
        if (P.getY() > getY())
            allerBas();
        else
            allerHaut();
    }
    else {
        if (P.getX() > getX())
            allerDroite();
        else
            allerGauche();
    }
}

void Personnage::changerNiveau(Niveau niveau) {
    _niveau = niveau;
}

void Personnage::changerCoordonnees(int x, int y) {
    _x = x;
    _y = y;
}

