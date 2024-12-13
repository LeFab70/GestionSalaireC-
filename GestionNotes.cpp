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
void evaluerChoixUser(int choixUser, int nbElt, double myArr[]);
void getNotes(int nbElt, double arrayOfNum[]);
void afficherNotes(int nbElt, double arrayOfNum[]);
double calculMoyenne(int nbElt, double arrayOfNum[]);
double findMax(int dimArray, double arrayOfNum[]);
double findMin(int dimArray, double arrayOfNum[]);

const unsigned short DIM_ARRAY = 100;
const unsigned short MIN_NOTE = 1;
const unsigned short MAX_NOTE = 20;

int main()
{
    int choix = 0;
    double notes[DIM_ARRAY] = {0};
    unsigned short dimArray = 0;
    cout << "Entrer le nombre de notes : ";
    cin >> dimArray;
    do
    {
        choix = displayMenu();
        if (choix != 5)
            evaluerChoixUser(choix, dimArray, notes);

        // system("clear"); // system("cls") A mettre si on veut clear lecran avec de quitter
    } while (choix != 5);

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
    system("clear"); // system("cls")
    cout << "1 – Entrer des notes"
         << endl
         << "2 – Afficher toutes les notes"
         << endl
         << "3 – Calculer la moyenne des notes"
         << endl
         << "4 – Obtenir max et min des notes"
         << endl
         << "5– Terminer le programme"
         << endl
         << "Entrez votre choix(1, 2, 3,4 ou 5) :";
    cin >> choixUser;

    return validationData<int>(1, 5, choixUser);
}

void evaluerChoixUser(int choixUser, int nbElt, double myArr[])
{

    {
        system("clear"); // system("cls")
        switch (choixUser)
        {
        case 1:
            cout << "Entrer des notes"
                 << endl;
            getNotes(nbElt, myArr);
            break;
        case 2:
            cout << " afficher les notes"
                 << endl;

            if (nbElt != 0)
                afficherNotes(nbElt, myArr);
            else
                cout << "Aucune note n'a été saisie"
                     << endl;
            break;
        case 3:
            if (nbElt != 0)
                cout << "Calcul moyenne des notes"
                     << endl
                     << "Moyenne des notes : " << calculMoyenne(nbElt, myArr) << endl;
            else
                cout << "Aucune note n'a été saisie"
                     << endl;
            break;
        case 4:
            if (nbElt != 0)
                cout << "Obtenir max et min des notes"
                     << endl
                     << "Max des notes : " << findMax(nbElt, myArr) << endl
                     << "Min des notes : " << findMin(nbElt, myArr) << endl;
            else
                cout << "Aucune note n'a été saisie"
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

void getNotes(int nbElt, double arrayOfNum[])
{
    for (int i = 0; i < nbElt; i++)
    {
        cout << "Fournir la note pour l'etudiant " << i + 1 << " > ";
        cin >> arrayOfNum[i];
        arrayOfNum[i] = validationData<double>(MIN_NOTE, MAX_NOTE, arrayOfNum[i]);
    }
}

void afficherNotes(int nbElt, double arrayOfNum[])
{
    for (int i = 0; i < nbElt; i++)
    {
        cout << "Note de l'etudiant " << i + 1 << " : "
             << arrayOfNum[i] << endl;
    }
}

double calculMoyenne(int nbElt, double arrayOfNum[])
{
    double moyenne = 0.0;
    double sumElt = 0.0;
    for (int i = 0; i < nbElt; i++)
    {
        sumElt += arrayOfNum[i];
    }
    moyenne = sumElt / nbElt;
    return moyenne;
}

double findMax(int dimArray, double arrayOfNum[])
{
    double max = arrayOfNum[0];
    for (int i = 1; i < dimArray; i++)
        if (max < arrayOfNum[i])
            max = arrayOfNum[i];
    return max;
}

double findMin(int dimArray, double arrayOfNum[])
{
    double min = arrayOfNum[0];
    for (int i = 1; i < dimArray; i++)
        if (min > arrayOfNum[i])
            min = arrayOfNum[i];
    return min;
}