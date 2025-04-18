#include <SDL_image.h>
#include <exception>
#include "Tuile.h"

using namespace std;

Tuile::Tuile(string nom, int x , int y , string propriete)
{
    _nom = nom ;
    _x = x ;
    _y = y ;
    _propriete = propriete ;
}

void Tuile::afficher() const
{
    cout << _nom << ": x=" << _x <<", y=" << _y << ", " << _propriete << endl ;
}

string Tuile::getTuileNom() const
{
    return _nom ;
}

int Tuile::getTuileX() const
{
    return _x ;
}

int Tuile::getTuileY() const
{
    return _y ;
}

string Tuile::getTuilePropriete() const
{
    return _propriete ;
}
