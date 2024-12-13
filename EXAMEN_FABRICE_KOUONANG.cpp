/*
     Programmer: Fabrice Kouonang
     Date:       09/12/2024
     But:        Demander les informations sur les employés (nom, titre, année experience...)
                 puis calculer le salaire de chacun des employés et génére diverses statistique.
*/

// note : les données sont fictives et ne doivent pas être utilisées dans un contexte réel.
// Moy: 99.5/100 Bravo
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;
/*
==================================================
 |       Definitions des constantes               |
 |                                                |
==================================================
*/
const unsigned short DIM_ARRAY = 50; // Taille de l'array
const double SALAIRE_CHEF = 45000.00;
const double SALAIRE_SERVEUR = 28000.00;
const double SALAIRE_PREPOSE = 22000.00;
const unsigned short MIN_ANNEE_EXP = 0; // Année d'experience
const unsigned short MAX_ANNEE_EXP = 35;
const unsigned short MIN_EMPLOYE = 2;
const unsigned short MAX_EMPLOYE = 20;
const double BONIS_PERFORMATION = 300.00;                                                                   // en $
const unsigned short MIN_EXP_CADEAU = 10;                                                                   // en année minimun experience pour avoir un cadeau exceptionnel
const string LISTE_CADEAU[4] = {"Bouteille de vin", "Carte cadeau de 50$", "Montre Suisse", "Journee Spa"}; // liste des cadeaux possibles

/*
==================================================
 |      Prototypes des fonctions                  |
 |                                                |
==================================================
*/
// genericité
template <typename T>
T lireValiderEntierEntre(T valMin, T valMax, T value); // Fonction de validation dans un intervalle donné
template <typename T>
T lireValider3Char(T firstVal, T secondVal, T thirdVal, T value);
int displayMenu(void);                                      // Affiche le menu
void evaluerChoixUser(int choixUser, double myArrDouble[]); // Fonction qui calculer et afficher les données en fonction du choix de l'utilisateu
void obtenirInfoEmploye(int nbElt, double myArrDouble[]);   // fonction qui permet d'obtenir les informations des employes
template <typename T>
double calculMoyenne(int nbElt, T arrayOfNum[]); // fonction qui permet de calculer la moyenne
void afficherStats(int nbAnnee, string nomEmploye);

// Variable globale pour stocker les info communes aux fonctions
unsigned short nbEmployes = 0;
string nomEmployePerfo = "";
unsigned short maxAnneeCumule = 0; // annee d'experience de l'employe le plus performance
bool isExistEmployePerfo = false;  // pour recuperer sil existe un employé performant

int main()
{
    // Liste des inputs du programmes
    int choix = 0;
    double salaireEmploye[DIM_ARRAY] = {0};

    do
    {
        choix = displayMenu(); // Afficher le menu puis recuperer et valider le choix de l'utilisateur
        if (choix != 4)
            evaluerChoixUser(choix, salaireEmploye); // Evaluer le choix de l'utilisateur dans le switch avec des fonctions

        // system("clear"); // system("cls") A mettre si on veut clear lecran avec de quitter
    } while (choix != 4);

    cout << endl
         << endl
         << "MERCI ! BONNE VACANCES !., \n pressez une touche pour quitter le programme"
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
T lireValiderEntierEntre(T valMin, T valMax, T value) // Validation des entrées
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

template <typename T>
T lireValider3Char(T firstVal, T secondVal, T thirdVal, T value)
{
    // validation pour deux valeurs
    while (!cin || !(toupper(value) == toupper(firstVal) || toupper(value) == toupper(secondVal) || toupper(value) == toupper(thirdVal)))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl
             << "Incorrect, entrer "
             << firstVal << " ou " << secondVal << " ou " << thirdVal << " : ";
        cin >> value;
    }
    return T(value);
}

int displayMenu(void) // affiche le menu
{
    int choixUser;
    system("clear"); // system("cls")
    cout << "==== GESTION DES SALAIRES - RESTAURANT ===="
         << endl
         << "1 – Calculer le salaire des employes"
         << endl
         << "2 – Employe le plus performant"
         << endl
         << "3 - Moyenne des salaires"
         << endl
         << "4 – Terminer le programme"
         << endl
         << "Entrez votre choix(1, 2, 3, ou 4) :";
    cin >> choixUser;

    return lireValiderEntierEntre<int>(1, 4, choixUser);
}

// Evaluation des choix de utilisateur

void evaluerChoixUser(int choixUser, double myArrDouble[])
{
    {
        system("clear"); // system("cls")
        switch (choixUser)
        {
        case 1:
            cout << "==== CALCUL DES SALAIRES ===="
                 << endl
                 << "Nombre d'employes (entre 2 et 20 incl.) ? : ";
            cin >> nbEmployes;
            nbEmployes = lireValiderEntierEntre<unsigned short>(MIN_EMPLOYE, MAX_EMPLOYE, nbEmployes);
            obtenirInfoEmploye(nbEmployes, myArrDouble);
            break;
        case 2:
            if (nbEmployes != 0)
            {
                if (isExistEmployePerfo)
                    afficherStats(maxAnneeCumule, nomEmployePerfo);
                else
                    cout << "Aucun employe exceptionnel trouve"
                         << endl
                         << endl;
            }
            else
                cout << "Aucune donnees n'a été saisie"
                     << endl;
            break;
        case 3:
            if (nbEmployes != 0)
                cout << "==== MOYENNE DES SALAIRES ===="
                     << endl
                     << "Moyenne des salaires : " << calculMoyenne<double>(nbEmployes, myArrDouble)
                     << " $"
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

void obtenirInfoEmploye(int nbElt, double myArrDouble[]) // fonction pour obtenir les informations des employes
{
    // Liste des entrées manipulées dans la fonction
    string nomEmploye = "";
    char titreEmploye = ' ';
    string libelleTitreEmploy = "";
    unsigned short anneeExpEmploye = 0;
    unsigned short performanceExcep = 0; // par defaut definir sur non =0
    double salaireBaseEmploye = 0;
    double salaireCumuleEmploye = 0;
    double bonisExp = 0;
    maxAnneeCumule = 0;
    nomEmployePerfo = "";
    isExistEmployePerfo = false; // on n'a pas un employé performant au debut
    // random number
    srand((int)time(NULL));
    rand();
    string cadeauOffert = "";

    for (int j = 0; j < nbElt; j++)
    {
        cin.ignore();
        cout << "Nom de l'employe # " << j + 1 << " : ";
        getline(cin, nomEmploye);
        cout << "Titre (C=Chef, S=Serveur, P=Prepose) ? ";
        cin >> titreEmploye;
        titreEmploye = lireValider3Char<char>('c', 's', 'p', titreEmploye);
        cout << "Annees d'experiences (entre 0 et 35) ? ";
        cin >> anneeExpEmploye;
        anneeExpEmploye = lireValiderEntierEntre<unsigned short>(MIN_ANNEE_EXP, MAX_ANNEE_EXP, anneeExpEmploye);
        cout << "Performance exceptionnlle ? (1=Oui et 0= Non) : ";
        cin >> performanceExcep;
        performanceExcep = lireValiderEntierEntre<unsigned short>(0, 1, performanceExcep);
        // traitement et afficher des informations sur employés
        // Recuperation des infos sur employé libelle--salaire--bonis
        switch (toupper(titreEmploye))
        {
        case 'C':
            libelleTitreEmploy = "CHEF";
            salaireBaseEmploye = SALAIRE_CHEF;
            break;
        case 'S':
            libelleTitreEmploy = "Serveur";
            salaireBaseEmploye = SALAIRE_SERVEUR;
            break;
        default:
            libelleTitreEmploy = "Prepose";
            salaireBaseEmploye = SALAIRE_PREPOSE;
            break;
        }

        bonisExp = 0;
        salaireCumuleEmploye = salaireBaseEmploye;
        // recuperation de du bonis et cadeaux puis employé performant
        if (performanceExcep == 1)
        {
            salaireCumuleEmploye = salaireBaseEmploye + BONIS_PERFORMATION;
            bonisExp = BONIS_PERFORMATION;
            if (anneeExpEmploye > MIN_EXP_CADEAU)
            {
                // Generation d.un nombre aletoire entre 0 et 3 pour le liste des cadeaux
                int cadeau = rand() % 4;
                cadeauOffert = LISTE_CADEAU[cadeau];
            }
            isExistEmployePerfo = true; // on a trouvé un employé performant
            if (nomEmployePerfo == "")
            {
                nomEmployePerfo = nomEmploye;
                maxAnneeCumule = anneeExpEmploye; // initialisation au premier employé le plus performant
            }
            else // Il existe deja un employé performant on compare les valeurs
            {
                if (maxAnneeCumule < anneeExpEmploye)
                {
                    maxAnneeCumule = anneeExpEmploye;
                    nomEmployePerfo = nomEmploye; // mise a jour de l'employe le plus performant
                }
            }
        }

        // Culmul du salaire dans le tableau pour calculer la moyenne
        myArrDouble[j] = salaireCumuleEmploye;
        cout << setprecision(2) << fixed
             << endl
             << "Nom : "
             << nomEmploye
             << endl
             << "Titre: "
             << libelleTitreEmploy
             << endl
             << "Salaire de base : "
             << salaireBaseEmploye << " $."
             << endl
             << "Bonus performance : "
             << bonisExp << " $"
             << endl
             << "SALAIRE TOTAL: "
             << salaireCumuleEmploye << " $"
             << endl;
        if (cadeauOffert != "") // afficher c message si cadeau offert
            cout << "CADEAUX OFFERT: "
                 << cadeauOffert
                 << endl
                 << endl;
        else
            cout << endl
                 << endl;
    }
}

template <typename T>
double calculMoyenne(int nbElt, T arrayOfNum[]) // fonction pour calculer la moyenne
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

void afficherStats(int nbAnnee, string nomEmploye)
{
    cout << endl
         << "Nom : "
         << nomEmploye
         << endl
         << "ANNEE EXPERIENCE :"
         << nbAnnee << " ans"
         << endl
         << endl;
}
