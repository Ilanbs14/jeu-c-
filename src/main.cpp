#include <vector>
#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"
#include "Dictionnaire.h"
#include "Niveau.h"
#include <string>
#include <fstream>

using namespace std;

int main(int, char**) // Version special du main, ne pas modifier
{
    // Initialisation du jeu
    Moteur moteur("Mon super jeu vidéo");

    // TODO: charger images, creer personnages, etc.

    int xheros = 16, yheros = 32 ;
    bool quitter = false;
    bool coffreEstOuvert = false ;

    // Boucle de jeu, appelee a chaque fois que l'ecran doit etre mis a jour
    // (en general, 60 fois par seconde)

    Image fond(moteur, "assets/fond.png");
    Image gameOver(moteur, "assets/gameover.png");
    Image bravo(moteur, "assets/bravo.png");
    Image pause(moteur, "assets/pause.png");

    Image coffreFermer (moteur, "assets/coffre_ferme.png");
    Image coffreOuvert (moteur, "assets/coffre_ouvert.png");
    Image personnage (moteur, "assets/personnages.png");
    Image objet (moteur,"assets/objets.png");

    int skin = 0, skinX = 0, skinY = 0;
    int ennemi1_x = 128, ennemi2_x = 160, ennemi3_x = 16;
    int ennemi1_y = 64, ennemi2_y = 64, ennemi3_y = 64;

    bool pauseAct = false;
    bool ennemisNiv4Cree = false;
    bool premierpassage = true;

    int tourNiveau = 0;

    ifstream DictionnaireTXT ("assets/dictionnaire.txt") ;
    ifstream Nv1TXT ("assets/niveau1.txt");
    ifstream Nv1bisTXT ("assets/niveau1bis.txt");
    ifstream Nv2TXT ("assets/niveau2.txt");
    ifstream Nv2bisTXT ("assets/niveau2bis.txt");
    ifstream Nv3TXT ("assets/niveau3.txt");
    ifstream Nv3bisTXT ("assets/niveau3bis.txt");
    Dictionnaire D1 (DictionnaireTXT) ;

    Niveau niveau1 (objet,Nv1TXT,D1);
    Niveau niveau1bis (objet, Nv1bisTXT, D1);
    Niveau niveau2 (objet,Nv2TXT,D1);
    Niveau niveau2bis (objet, Nv2bisTXT, D1);
    Niveau niveau3 (objet, Nv3TXT, D1);
    Niveau niveau3bis(objet, Nv3bisTXT, D1);

    vector<Niveau> jeuComplet = {niveau1, niveau1bis, niveau2, niveau2bis, niveau3, niveau3bis};
    /* Choix des skins souhaitable au début via l'invite de commande*/
    /*cout << " -homme(1) \n -chevalier(2) \n -princesse(3) \n -squelette(4) \n -slime(5) \n -chauve-souris(6) \n -fantome(7) \n -arraignee(8) \n Quel skin veux-tu ?  " ;
    cin >> skin;
    if (skin == 1 || skin == 2 || skin == 3 || skin == 4)
        skinY = 0;
    else
        skinY = 64;

    if (skin == 1 || skin == 5)
        skinX = 0;
    else if (skin == 2 || skin == 6)
        skinX = 64;
    else if (skin == 3 || skin == 7)
        skinX = 112;
    else if (skin == 4 || skin == 8)
        skinX = 160;*/

    personnage.selectionnerRectangle(skinX,skinY,16,16);
    Personnage heros (personnage, xheros, yheros, skinX, skinY, 0, jeuComplet[tourNiveau]);

    personnage.selectionnerRectangle(ennemi1_x,ennemi1_y,16,16);
    Personnage ennemi1 (personnage, 128, 32, ennemi1_x, ennemi1_y, 1, jeuComplet[tourNiveau]);

    personnage.selectionnerRectangle(ennemi2_x,ennemi2_y,16,16);
    Personnage ennemi2 (personnage, 16, 80, ennemi2_x, ennemi2_y, 0, jeuComplet[tourNiveau]);

    personnage.selectionnerRectangle(ennemi3_x,ennemi3_y,16,16);
    Personnage ennemi3 (personnage, 64, 16, ennemi3_x, ennemi3_y, 0, jeuComplet[tourNiveau]);

    Personnage ennemi4;
    Personnage ennemi5;
    bool goDroite = true, goHaut = true;

    moteur.initialiserRendu();
  while (!quitter)
  {
    // I. Gestion des evenements
    Evenement evenement = moteur.evenementRecu();

    while (evenement != AUCUN)
    {
      switch (evenement)
      {
        // QUITTER = croix de la fenetre ou Echap
        case QUITTER_APPUYE:
          quitter = true;
          break;
        case ESPACE_APPUYE:
            coffreEstOuvert = !coffreEstOuvert;
            break;
        case GAUCHE_APPUYE:
            heros.allerGauche();
            jeuComplet[tourNiveau].testerBonusEtPrendre(heros.getX(), heros.getY());
            break;
        case DROITE_APPUYE:
            heros.allerDroite();
            jeuComplet[tourNiveau].testerBonusEtPrendre(heros.getX(), heros.getY());
            break;
        case HAUT_APPUYE:
            heros.allerHaut();
            jeuComplet[tourNiveau].testerBonusEtPrendre(heros.getX(), heros.getY());
            break;
        case BAS_APPUYE:
            heros.allerBas();
            jeuComplet[tourNiveau].testerBonusEtPrendre(heros.getX(), heros.getY());
            break;
        case P_APPUYE:
            pauseAct = !pauseAct;
        // TODO: gerer les autres evenements
        default:
          break;

      }

        evenement = moteur.evenementRecu();
    }

    if (tourNiveau == 4 && !ennemisNiv4Cree) {
    personnage.selectionnerRectangle(160, 0, 16, 16);
    ennemi4 = Personnage(personnage, 144, 112, 160, 0, 1, jeuComplet[tourNiveau]);
    personnage.selectionnerRectangle(64, 64, 16, 16);
    ennemi5 = Personnage(personnage, 144, 0, 64, 64, 0, jeuComplet[tourNiveau]);
    ennemisNiv4Cree = true;
    }


    if (pauseAct) {
        pause.dessiner(30,50.5);
        moteur.finaliserRendu();
        continue;
    }
    // II. Mise à jour de l'état du jeu

    // TODO: faire bouger vos personnages, etc.

    // III. Generation de l'image à afficher
        if (moteur.animationsAmettreAjour()) {

            ennemi1.avancer();
            ennemi2.avancer();
            ennemi3.suivre(heros);
            if (tourNiveau == 4 || tourNiveau == 5) {
                ennemi4.avancer();
                ennemi5.avancer();
            }
        }

    // efface ce qui avait ete affiche precedemment et reinitalise en ecran noir
    fond.dessiner(0,0) ;
    jeuComplet[tourNiveau].dessiner();
    heros.dessiner();
    ennemi1.dessiner();
    ennemi2.dessiner();
    ennemi3.dessiner();

    if (ennemisNiv4Cree) {
        ennemi4.dessiner();
        ennemi5.dessiner();
    }
    if ((jeuComplet[tourNiveau].getBonus()) == 0 && tourNiveau == 0) {
        tourNiveau = 1;
        heros.changerNiveau(jeuComplet[tourNiveau]);
        ennemi1.changerNiveau(jeuComplet[tourNiveau]);
        ennemi2.changerNiveau(jeuComplet[tourNiveau]);
        ennemi3.changerNiveau(jeuComplet[tourNiveau]);
    }

    if (jeuComplet[tourNiveau].getBonus() == 0 && heros.getX() == 80 && heros.getY() == 112 && tourNiveau == 1 ) {
        tourNiveau = 2;
        heros.changerNiveau(jeuComplet[tourNiveau]);
        ennemi1.changerNiveau(jeuComplet[tourNiveau]);
        ennemi2.changerNiveau(jeuComplet[tourNiveau]);
        ennemi3.changerNiveau(jeuComplet[tourNiveau]);

        ennemi1.changerCoordonnees(64, 16);
        ennemi2.changerCoordonnees(16, 80);
        ennemi3.changerCoordonnees(64, 16);

    }
    if (premierpassage && tourNiveau == 2 && heros.getX() == 80 && heros.getY() == 96) {
        tourNiveau = 3;
        premierpassage = !premierpassage;
        heros.changerNiveau(jeuComplet[tourNiveau]);
        ennemi1.changerNiveau(jeuComplet[tourNiveau]);
        ennemi2.changerNiveau(jeuComplet[tourNiveau]);
        ennemi3.changerNiveau(jeuComplet[tourNiveau]);
    }
    if (jeuComplet[tourNiveau].getBonus() == 0 && heros.getX() == 0 && heros.getY() == 112 && tourNiveau == 3 ) {
        tourNiveau = 4;
        heros.changerNiveau(jeuComplet[tourNiveau]);
        ennemi1.changerNiveau(jeuComplet[tourNiveau]);
        ennemi2.changerNiveau(jeuComplet[tourNiveau]);
        ennemi3.changerNiveau(jeuComplet[tourNiveau]);

        ennemi1.changerCoordonnees(0, 0);
        ennemi2.changerCoordonnees(0, 0);
        ennemi3.changerCoordonnees(64, 48);

    }
    if (jeuComplet[tourNiveau].getBonus() == 4 && tourNiveau == 4 ) {
        tourNiveau = 5;
        heros.changerNiveau(jeuComplet[tourNiveau]);
        ennemi1.changerNiveau(jeuComplet[tourNiveau]);
        ennemi2.changerNiveau(jeuComplet[tourNiveau]);
        ennemi3.changerNiveau(jeuComplet[tourNiveau]);
        ennemi4.changerNiveau(jeuComplet[tourNiveau]);
        ennemi5.changerNiveau(jeuComplet[tourNiveau]);

    }
    /* Ouverture du coffre est ouvert ou fermeture à son emplacement sur la première séance*/
    /*if (coffreEstOuvert)
    {
        coffreOuvert.dessiner(144,112);
        bravo.dessiner(30,51.5);
        moteur.finaliserRendu();
        moteur.attendre(5);
        quitter = true;

    }
    else
    {
        coffreFermer.dessiner(144,112) ;
    }*/
    if (jeuComplet[tourNiveau].getBonus() == 0 && tourNiveau == 5) {
        bravo.dessiner(30,51.5);
        moteur.finaliserRendu();
        moteur.attendre(5);
        quitter = true;
    }
    moteur.finaliserRendu();
    if (heros.touche(ennemi1) || heros.touche(ennemi2) || heros.touche(ennemi3) || heros.touche(ennemi4) || heros.touche(ennemi5)) {
        gameOver.dessiner(30,51.5);
        moteur.finaliserRendu();
        moteur.attendre(5);
        quitter = true;
    }

    /*
      Affiche l'image en se cadencant sur la frequence de
      rafraichissement de l'ecran (donc va en general mettre le
      programme en pause jusqu'a ce que l'ecran soit rafraichi). En
      general, 60 images fois par seconde, mais ca peut dependre du
      materiel
    */

  }

  return 0;
}

