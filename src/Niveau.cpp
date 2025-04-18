#include "Niveau.h"

using namespace std;

Niveau::Niveau(Image I,ifstream& fichier,Dictionnaire D)
{
     if (!fichier){
        cerr << "Erreur : Fichier invalide !" << endl ;
        return ;
    }

    string ligne, nom, propriete;
    int change = 0, x = 0, y = 0, cpt = 0, nbtuiles = 0;

    getline(fichier,ligne);
    nbtuiles = stoi(ligne);
    _nombreBonus = 0 ;

     while (getline(fichier, ligne))
    {
        nom = "";
        propriete = "";
        x = y = 0;
        change = 0;

        // Parcourir chaque caractère de la ligne
        while (cpt < ligne.size()) {
            if (ligne[cpt] == ' ') {  // Si on rencontre un espace on change de catégorie
                change += 1;
            } else {
                switch(change) {
                    case 0 :   // Pour le nom
                        nom += ligne[cpt];
                        break;
                    case 1 :   // Pour x
                        x = x * 10 + (ligne[cpt] - '0');
                        break;
                    case 2 :   // Pour y
                        y = y * 10 + (ligne[cpt] - '0');
                        break;
                    default:
                        break;
                }
            }
            cpt++;
        }
        Objet O (I,nom,D,x,y);
        _objet.push_back(O);
        if (O.getObjetPropriete() == "bonus")
            _nombreBonus++;
        cpt = 0;
    }
    fichier.close();
}

Niveau::Niveau()
{

}

void Niveau::dessiner()
{
    for (int i = 0 ; i < _objet.size() ; i++)
    {
        _objet[i].dessiner();
    }
}

bool Niveau::caseEstLibre(int x,int y)
{
    for(int i = 0 ; i < _objet.size() ; i++)
    {
        if (_objet[i].getObjetPropriete() == "solide")
        {
            if(_objet[i].getObjetX() == x && _objet[i].getObjetY() == y)
            {
                return false ;
            }
        }
    }
    return true ;
}

void Niveau::testerBonusEtPrendre(int x, int y) {
    for(int i = 0 ; i < _objet.size() ; i++)
    {
        if (_objet[i].getObjetPropriete() == "bonus")
        {
            if(_objet[i].getObjetX() == x && _objet[i].getObjetY() == y)
            {
                _nombreBonus--;
                _objet[i].cacher();

            }
        }
    }
}

int Niveau::getBonus() {
    return _nombreBonus;
}
