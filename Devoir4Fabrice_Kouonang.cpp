/*
     Programmeur: Fabrice Kouonang
     Date: 2022-02-22
     Description: Programme qui permet de produire des factures

*/

#include <iostream>
#include <iomanip>

using namespace std;

/*
**************************
Prototypes des fonctions
**************************
*/

// genericité
template <typename T>
T validationData(T valMin, T valMax, T valeur);

int displayMenu(void);

int main()
{
     int choix = 0;

     do
     {
          choix = displayMenu();
          if (choix != 4)
          {
               system("clear");
               switch (choix)
               {
               case 1:
                    cout << "Entrer des informations de la facturation";
                    break;
               case 2:
                    cout << " Calculer et afficher la facture";
                    break;
               case 3:
                    cout << "Afficher les grands totaux de facturation pour la journée";
                    break; // default
               }
               cin.ignore();
               cout << endl
                    << "Appuyer sur une touche pour revenir au menu"
                    << endl;
               getchar();
          }
     } while (choix != 4);

     cout << endl
          << "Fermeture du programme, \n pressez surla touche entrée,pour quitter le programme"
          << endl
          << endl;
     getchar();
     return 0;
}

/*
**************************
Definitions des fonctions
**************************
*/

// utilisation des templates
template <typename T>
T validationData(T valMin, T valMax, T valeur)
{
     while (!cin || !(valeur >= valMin && valeur <= valMax))
     {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Veuillez saisir une valeur comprise entre " << valMin << " et "
               << valMax << " : ";
          cin >> valeur;
     }
     return T(valeur);
}

int displayMenu(void)
{
     int choixUser;
     system("clear");
     cout << "1 – Entrer des informations de facturation."
          << endl
          << "2 – Calculer et afficher la facture"
          << endl
          << "3 – Afficher les grands totaux de facturation pour la journée"
          << endl
          << "4 – Terminer le programme"
          << endl
          << "Entrez votre choix(1, 2, 3 ou 4) :";
     cin >> choixUser;
     system("clear");
     return validationData<int>(1, 4, choixUser);
} 





