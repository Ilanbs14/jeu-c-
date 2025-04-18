#include "Dictionnaire.h"
#include <string>

Dictionnaire::Dictionnaire(ifstream& fichier)
{
    if (!fichier){
        cerr << "Erreur : Fichier invalide !" << endl ;
        return ;
    }

    string ligne, nom, propriete;
    int change = 0, x = 0, y = 0, cpt = 0, nbtuiles = 0;

    getline(fichier,ligne);
    nbtuiles = stoi(ligne);

    // Lire chaque ligne du fichier
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
                    case 3 :   // Pour propriété
                        propriete += ligne[cpt];
                        break;
                    default:
                        break;
            }
            }
            cpt++;
        }
        //Nouvelle tuile
        Tuile T(nom, x, y, propriete);
        _tuile.push_back(T);

        cpt = 0;
    }

    fichier.close();
}

void Dictionnaire::afficher() const
{
    for (int i = 0 ; i < _tuile.size() ; i++)
    {
        _tuile[i].afficher() ;
    }
}


bool Dictionnaire::recherche(string nom, Tuile& T) {
    int debut = 0;
    int fin = _tuile.size()-1;
    int milieu;
    while (debut <= fin) {
        milieu = (debut+fin)/2;
        if (_tuile[milieu].getTuileNom() == nom)
        {
            T = _tuile[milieu];
            return true;
        }
        else if (_tuile[milieu].getTuileNom() < nom)
            debut = milieu+1;
        else
            fin = milieu-1;
    }
    return false;
}

