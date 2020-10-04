#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;


double calculTVA(double prixCourse, double TAUX_TVA_POURCENT);

double CalculsPrix(int uberChoisi, double distanceParcourue, double minutesEcoulees);

void bordureHorizontale(const char W_TOTAL, const char PLUS, const char TIRET);

void bordureVerticale(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE);

void repmplissageTextes(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE, const char SEPARATEUR,
                        double chiffres, const string &textes);

void remplissageTextes(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE, const char SEPARATEUR,
                       double chiffres, const string &unites, const string &textes);

void remplissageTitre(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE, const string &titre);

int main()
{
    //Entrées
    cout << "Quel Uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK"<< endl;
    int uberChoisi;
    do {
        cin >> uberChoisi;
        if (uberChoisi < 1 || uberChoisi > 3){
            cout << "ERREUR, veuillez resaisir le numero correspondant a l'Uber choisi!" << endl;
        }
    }while (uberChoisi < 1 || uberChoisi > 3);
    double tempsEcoulees;
    double distanceParcourue;
    cout << "Combiens de minutes ecoulees?" << endl;
    cin >> tempsEcoulees;
    tempsEcoulees = int(ceil(tempsEcoulees)); //arrondi tempsEcoulees au supérieur ensuite converti en int

    //Variables de l'affichage
    const char W_TOTAL = 30;
    const char PLUS = '+';
    const char TIRET = '-';
    const char BARREVERTICALE = '|';
    const char ESPACE = ' ';
    const char SEPARATEUR = ':';
    double chiffres;
    string unites;
    string textes;

    //Quel uber affiché
    enum typeUber {UberX = 1, UberPOP, UberBLACK};
    string uberAffiche;
    double prixAnnulation = 6.00; //pour UberX et UberPOP
    if (uberChoisi == UberX){
        uberAffiche = "UberX";
    }else if(uberChoisi == UberPOP){
        uberAffiche = "UberPOP";
    }else{
        uberAffiche = "UberBLACK";
        prixAnnulation = 15.00;
    }
    cout << uberAffiche << endl;

    //variables de l'affichage
    const string PRIX = "prix";
    const string TVA = "(incl. TVA)";
    const double TAUX_TVA_POURCENT = 8.00;

    if (tempsEcoulees > 0){
        cout << "Combien de kilometres parcourus?" << endl;
        cin >> distanceParcourue;
        distanceParcourue = round(distanceParcourue * 100) / 100; //arrondi la distance aux 100m les plus proches
        //mettresetprecison(1) fixed à l'affichage!
    }else {
        cout << setprecision(2) << fixed;
        bordureHorizontale(W_TOTAL, PLUS, TIRET);
        bordureVerticale(W_TOTAL, BARREVERTICALE, ESPACE);
        const string ANNULATION = "Frais annulation";
        remplissageTitre(W_TOTAL, BARREVERTICALE, ESPACE, uberAffiche);
        bordureVerticale(W_TOTAL, BARREVERTICALE, ESPACE);
        repmplissageTextes(W_TOTAL, BARREVERTICALE, ESPACE, SEPARATEUR, prixAnnulation, ANNULATION);
        bordureVerticale(W_TOTAL, BARREVERTICALE, ESPACE);
        repmplissageTextes(W_TOTAL, BARREVERTICALE, ESPACE, SEPARATEUR, calculTVA(prixAnnulation, TAUX_TVA_POURCENT),
                           TVA);
        bordureVerticale(W_TOTAL, BARREVERTICALE, ESPACE);
        bordureHorizontale(W_TOTAL, PLUS, TIRET);
    }

    return EXIT_SUCCESS;
}



/*-------------------------------------------------------FONCTIONS----------------------------------------------------*/
//fonctions encadrage
void bordureHorizontale(const char W_TOTAL, const char PLUS, const char TIRET)
{
    cout << PLUS << setw(W_TOTAL - 1) << setfill(TIRET) << PLUS << endl;
}
void bordureVerticale(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE)
{
    cout << BARREVERTICALE << setw(W_TOTAL - 1) << setfill(ESPACE) << BARREVERTICALE << endl;
}


//fonction calculs prix
double CalculsPrix(int uberChoisi, double distanceParcourue, double tempsEcoulees)
{
    double prixBase = 3.00; //pour UberX et UberPOP
    double prixKilometre = 1.80; //pour UberX
    double prixMinute = 0.30; //pour UberX et UberPOP
    double prixMinimum = 6.00; //pour UberX et UberPOP
    if (uberChoisi == 3){
        prixBase = 8.00;
        prixKilometre = 3.60;
        prixMinute = 0.60;
        prixMinimum = 15.00;
    }
    else if (uberChoisi == 2){
        prixKilometre = 1.35;
    }
    double prixDistance = prixKilometre * distanceParcourue;
    double prixTemps = prixMinute * tempsEcoulees;
    double prixCourse = prixBase + prixDistance + prixTemps;
    prixCourse = prixCourse < prixMinimum? prixCourse = prixMinimum : prixCourse;
    return prixCourse;
}

//fonction calcul TVA
double calculTVA(double prixCourse, double TAUX_TVA_POURCENT)
{
    double tva = (prixCourse / (100 + TAUX_TVA_POURCENT)) * TAUX_TVA_POURCENT;
    cout << setprecision(2) << fixed;
    return tva;
}
/*------------------------------------------SOUCIS-DE-CADRAGE---------------------------------------------------------*/
//fonction remplissage textes, chiffres et unités
void remplissageTextes(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE, const char SEPARATEUR,
                       double chiffres, const string &unites, const string &textes){
    cout << BARREVERTICALE << ESPACE << setw(W_TOTAL / 3 * 2 - 3) << left << textes << SEPARATEUR << ESPACE
    << setw(W_TOTAL / 3 - (4 + unites.length())) << chiffres << ESPACE << unites << ESPACE << BARREVERTICALE << endl;
}
//focntion remplissage textes et chiffres
void repmplissageTextes(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE, const char SEPARATEUR,
                        double chiffres, const string &textes){
    cout << BARREVERTICALE << ESPACE << setw(W_TOTAL / 3 * 2 - 3) << left <<textes << ESPACE << SEPARATEUR << ESPACE
    << setw(W_TOTAL / 3 - 4) << left << chiffres << ESPACE << BARREVERTICALE << endl;
}
//fonction remplissage titre
void remplissageTitre(const char W_TOTAL, const char BARREVERTICALE, const char ESPACE, const string &titre)
{
    cout << BARREVERTICALE << ESPACE << titre << setw(W_TOTAL / 3) << setfill(ESPACE) <<
         setw(W_TOTAL / 3 * 2 - 1 - titre.length())  << ESPACE <<  BARREVERTICALE << endl;
}


