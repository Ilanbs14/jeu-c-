#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED
#include "Objet.h"

using namespace std;

class Niveau{
    vector<Objet> _objet ;
    int _nombreBonus ;
public :
    Niveau(Image,ifstream&,Dictionnaire);
    Niveau();
    void dessiner() ;
    bool caseEstLibre(int,int);
    void testerBonusEtPrendre(int,int);
    int getBonus();

};


#endif // PERSONNAGE_H_INCLUDED
