/*
     Programmer: Fabrice Kouonang
     Date:       09/12/2024
     But:        Demander les informations du nombre de verre consomme, age debut de la consommation et age actuel de l'utilisateur
                 puis calculer le nombre de jours de vie perdus selon la consommation de vin ainsi que les montants mensuels et annuels
                 de depenses engagees sur la periode de conssommation.
*/
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
// rappeller a David pour le clear et cls

/*
==================================================
 |       Definitions des constantes               |
 |                                                |
==================================================
*/
const unsigned short DIM_ARRAY = 50; // Taille de l'array
const double MIN_POIDS = 85.0;
const double MAX_POIDS = 175.0;
const unsigned short MIN_AGE = 18;
const unsigned short MAX_AGE = 35;

/*
==================================================
 |      Prototypes des fonctions                  |
 |                                                |
==================================================
*/
// genericité
template <typename T>
T validationBetween(T valMin, T valMax, T value); // Fonction de validation dans un intervalle donné
template <typename T>
T validationEqual(T firstVal, T secondVal, T value);
int displayMenu(void);                                                                                         // Affiche le menu
void evaluerChoixUser(int choixUser, double myArrDouble[], unsigned short myArrShort[], string myArrString[]); // Fonction qui calculer et afficher les données en fonction du choix de l'utilisateur
void obtenirInfoJoueur(int nbElt, double myArrDouble[], unsigned short myArrShort[], string myArrString[]);    // fonction qui permet d'obtenir les informations des joueurs
template <typename T>
double calculMoyenne(int nbElt, T arrayOfNum[]); // fonction qui permet de calculer la moyenne
int findMax(int dimArray, double arrayOfNum[]);  // fonction qui permet de trouver l'index de l'element maximum dans le tableau
template <typename T>
void afficherArray(int nbElt, T arrayOfNum[]);

// Variable globale pour stocker le nbre de joueurs à entrer
unsigned short nbJoueur = 0;

int main()
{
    // Liste des inputs du programmes
    int choix = 0;
    double poidsJoueur[DIM_ARRAY] = {0};
    unsigned short ageJoueur[DIM_ARRAY] = {0};
    string nomJoueur[DIM_ARRAY] = {""};

    // Listes des variables intermediaires

    // Liste des outputs du programmes

    do
    {
        choix = displayMenu(); // Afficher le menu puis recuperer et valider le choix de l'utilisateur
        if (choix != 6)
            evaluerChoixUser(choix, poidsJoueur, ageJoueur, nomJoueur); // Evaluer le choix de l'utilisateur dans le switch avec des fonctions

        // system("clear"); // system("cls") A mettre si on veut clear lecran avec de quitter
    } while (choix != 6);

    cout << endl
         << endl
         << "Au revoir et merci. Fermeture du programme, \n pressez une touche pour quitter le programme"
         << endl;
    getchar();
    return 0;
}
/*
==================================================
 |       Definitions des fonctions               |
 |                                               |
==================================================
*/
// utilisation des templates
template <typename T>
T validationBetween(T valMin, T valMax, T value) // Validation des entrées
{
    while (!cin || !(value >= valMin && value <= valMax))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Veuillez saisir une valeur comprise entre " << valMin << " et "
             << valMax << " : ";
        cin >> value;
    }
    return T(value);
}

int displayMenu(void) // affiche le menu
{
    int choixUser;
    system("clear"); // system("cls")
    cout << "1 – Entrer des informations (nom, poids et age) des joueurs de la ligue"
         << endl
         << "2 – Afficher la moyenne d'age des joueurs de la ligue"
         << endl
         << "3-Afficher les informations des equipes"
         << endl
         << "4 – Afficher la moyenne de poids des joueurs de la ligne"
         << endl
         << "5 – Afficher le nom et le poids du joueur le  plus lourd de la ligue"
         << endl
         << "6– Terminer le programme"
         << endl
         << "Entrez votre choix(1, 2, 3,4,5 ou 6) :";
    cin >> choixUser;

    return validationBetween<int>(1, 5, choixUser);
}
void evaluerChoixUser(int choixUser, double myArrDouble[], unsigned short myArrShort[], string myArrString[])
{
    // Voir si je peux mettre une variable globale pour gerer le cas du nombre de joueurs et inserer plutot dans case 1 la demande des infos nbre joueurs

    {
        system("clear"); // system("cls")
        switch (choixUser)
        {
        case 1:
            cout << "Entrer des informations"
                 << endl
                 << "Entrer le nombre de joueurs par equipe : ";
            cin >> nbJoueur; // Attetntion ici le nbre de joueurs nestque par equipe donc faut faire x3 lors du calcul moyenne ou rechercher max
            obtenirInfoJoueur(nbJoueur, myArrDouble, myArrShort, myArrString);
            break;
        case 2:
            if (nbJoueur != 0)
                cout << "Afficher les moyennes des ages"
                     << endl
                     << "L'age moyennes des joueurs de la ligue est de : " << calculMoyenne<unsigned short>(nbJoueur * 3, myArrShort) // Attetntion ici le nbre de joueurs nestque par equipe donc faut faire x3 lors du calcul moyenne ou rechercher max
                     << " ans"
                     << endl;
            else
                cout << "Aucune donnees n'a été saisie"
                     << endl;
            break;

        case 3:
            if (nbJoueur != 0)
                cout << "Afficher la moyenne des poids"
                     << endl
                     << "Moyenne des poids : " << calculMoyenne<double>(nbJoueur * 3, myArrDouble) // Attetntion ici le nbre de joueurs nestque par equipe donc faut faire x3 lors du calcul moyenne ou rechercher max
                     << " kilo"
                     << endl;

            else
                cout << "Aucune donnees n'a été saisie"
                     << endl;
            afficherArray<string>(nbJoueur * 3, myArrString);  /// test affichage juste pour les noms des joueurs mais on doit passer les parametre des autres tableaux
            break;
        case 4:
            if (nbJoueur != 0)
                cout << "Afficher le nom et le poids du joueur le plus lourd" // Attetntion ici le nbre de joueurs nestque par equipe donc faut faire x3 lors du calcul moyenne ou rechercher max
                     << endl
                     << "le joueur le plus lourd est : " << myArrString[findMax(nbJoueur * 3, myArrDouble)]
                     << " et pèse : " << myArrDouble[findMax(nbJoueur * 3, myArrDouble)]
                     << endl;

            else
                cout << "Aucune donnees n'a été saisie"
                     << endl;
            break;
        }

        cin.ignore();
        cout << endl
             << "Appuyer sur une touche pour revenir au menu"
             << endl;
        getchar();
    }
}

void obtenirInfoJoueur(int nbElt, double myArrDouble[], unsigned short myArrShort[], string myArrString[]) // fonction pour obtenir les informations des joueurs
{
    // Boucle pour obtenir les informations des joueurs sur 3 equipes
    // Attetntion ici le nbre de joueurs nestque par equipe donc faut faire x3 lors du calcul moyenne ou rechercher max
    // de plus definir index pour parcourir tableau de nbjoueur x 3 equipes sinon la donnees est ecrasée sur lindex 0 a nbjoueur-1
    unsigned short indexArray = 0;
    for (int i = 0; i < 3; i++)
    {
        cout << "Equipe # :" << i + 1 << endl;
        for (int j = 0; j < nbElt; j++)
        {
            cout << "Joueur # " << j + 1 << " > ";
            cout << "Nom : ";
            cin.ignore();
            getline(cin, myArrString[indexArray++]);
            cout << "Poids (entre"
                 << MIN_POIDS
                 << " et "
                 << MAX_POIDS << " Kilo inclusivement): ";
            cin >> myArrDouble[indexArray];
            myArrDouble[indexArray] = validationBetween<double>(MIN_POIDS, MAX_POIDS, myArrDouble[indexArray]);

            cout << "Age : "
                 << MIN_AGE
                 << " et "
                 << MAX_AGE << " ans inclusivement): ";
            cin >> myArrShort[indexArray];
            myArrShort[indexArray] = validationBetween<unsigned short>(MIN_AGE, MAX_AGE, myArrShort[indexArray]);

            // arrayOfNum[i] = validationData<double>(MIN_NOTE, MAX_NOTE, arrayOfNum[i]);
        }
    }
}

template <typename T>
T validationEqual(T firstVal, T secondVal, T value)
{
    // validation pour deux valeurs
    while (!cin || !(toupper(value) == firstVal || toupper(value) == secondVal))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl
             << "Incorrect, entrer "
             << firstVal << " ou " << secondVal << " : ";
        cin >> value;
    }
    return T(value);
}

template <typename T>
double calculMoyenne(int nbElt, T arrayOfNum[]) // fonction pour calculer la moyenne des ages et poids
{
    double moyenne = 0.0;
    double sumElt = 0.0;
    for (int i = 0; i < nbElt; i++)
    {
        sumElt += arrayOfNum[i];
    }
    moyenne = sumElt / nbElt;
    return T(moyenne);
}

int findMax(int dimArray, double arrayOfNum[]) // fonction pour trouver l'index du plus grand element dans un tableau
{
    double max = 0;
    int index = 0;
    for (int i = 1; i < dimArray; i++)
        if (max < arrayOfNum[i])
            index = i;
    return index;
}
template <typename T>
void afficherArray(int nbElt, T arrayOfNum[])
{
    for (int i = 0; i < nbElt; i++)
    {
        cout << "Joueur " << i + 1 << " : "
             << arrayOfNum[i] << endl;
    }
}