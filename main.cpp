
//Libreries pour la gestion des string et des opérations mathematiques.
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef struct// Structure pour renvoyer les calculs du prix
{
    double prixBase;
    double prixDistance;
    double prixMinute;
    double prixFinal;
    double prixFacture;

}Rescalculs;

//prototypes des fonctions d'affichage et d'arrondi.
void horizontalBord(const char coin, const char vertical, const char W);

void spaceTable(const char space, const char horizontal, const char W);

void textNum(const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num );
void textNum(const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num, string unite);

double arrondisD(double value, unsigned char prec);


void uberShow(const string typeUber, const char horizontal, const char TotalWidht);

double TVACalcul(double TauxTVA, double Prix);

Rescalculs calculsPrix(int choixUber, double kmparcourus, double MinutesEcoulees);



int main() {
    //demande à l'utilisateur d'entrer les valeurs nécessaires.
    cout << "Quel uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK" << endl;
    int choixUber = 0;
    do {
        cin >> choixUber;
        if(choixUber >= 1 && choixUber <= 3) continue;
        cout << "Valeur incorrecte. Reessayez." << endl; //si le num entré n'est pas 1,2 ou 3 alors on envoie un message
        //d'erreur
    }while(choixUber < 1 || choixUber > 3); //tant que le numéro entré n'est pas le bon (1,2 ou 3) alors on continue de
    //la première question

    cout << "Combien de minutes ecoulees?" << endl;
    double minutesEcoulees;
    cin >> minutesEcoulees;
    minutesEcoulees = int(ceil(minutesEcoulees)); //arrondi tempsEcoulees au supérieur ensuite converti en int

    //enumeration afin de faciliter la lecture du choix Uber.
    enum posUber { uberX = 1, uberPOP, uberBLACK };
    string typeUber;

    if (choixUber == uberX) {//Formatage du string typeUber avec la chaîne de caractere correspondante au choix
        typeUber =  "uberX";
    } else if (choixUber == uberPOP) {
        typeUber =  "uberPOP";
    } else if (choixUber == uberBLACK){
        typeUber =  "uberBLACK";
    }
    else
    {
        cout << "ERREUR" << endl;
        return 1;
    }

    //variables d'affichage
    const char SPACE = ' ';
    const char COIN = '+';
    const char HORIZONTAL = '-';
    const char VERTICAL = '|';
    const char TOTAL_WIDHT = 30; //largeur totale du ticket
    const char SEPARATOR = ':';
    double tauxTva = 0.08;
    double TVA = 0;

    //condition pour voir si les minutes écoulées sont négatives ou égal à 0, dans ce cas, la 3ème question n'est pas
    //posée et la course est annulée. le ticket affiché est celui de la course annulée (ticket plus court que le normal)
    if (minutesEcoulees < 1)
    {
        cout << fixed << setprecision(2);
        double annulationFrais = 0;
        //les frais d'annulation ne sont pas les mêmes pour les 3 Uber alors on fait un swich pour attribuer le bon
        // frais d'annulation au bon Uber
        switch (choixUber) {
            case uberX :
            case uberPOP :
                annulationFrais = 6.00; //frais d'annulation de l'Ubere 1 et 2
                break;
            case uberBLACK :
                annulationFrais = 10.00; //frais d'annulation de l'Uber 3
                break;
        }
        TVA = TVACalcul(tauxTva, annulationFrais); //affiche la TVA
        cout << endl; //separation de la question et du tableau
        horizontalBord(COIN, HORIZONTAL, TOTAL_WIDHT); //affiche la bordure horizontale avec le + et -
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        uberShow(typeUber, VERTICAL, TOTAL_WIDHT); //l'uber choisi, il est centré
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Frais annulation", annulationFrais); //texte et prix
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Prix", annulationFrais); //texte et prix
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "(incl. TVA)", TVA);
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        horizontalBord(COIN, HORIZONTAL, TOTAL_WIDHT); //affiche la bordure horizontale avec le + et -
    }
    else //si les minutes écoulées sont supérieures à 0 alors on pose la 3ème question
    {
        cout << "Combien de kilometres parcourus?" << endl;
        double kmParcourus;
        do {
            cin >> kmParcourus;
            if(kmParcourus >= 0) continue;
            cout << "Impossible. Reessayez." << endl;
        }while(kmParcourus < 0); //tant que les km parcourus entrées ne sont pas >= 0 alors on repose la question

        //kmParcourus = (1./100.)
        kmParcourus = arrondisD(kmParcourus, 1);
        cout << endl; //separation de la question et du tableau

        //Calculs
        Rescalculs resultats;
        resultats = calculsPrix(choixUber, kmParcourus, minutesEcoulees);

        //Affichage du ticket
        horizontalBord(COIN, HORIZONTAL, TOTAL_WIDHT); //affiche la bordure horizontale avec le + et -
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        uberShow(typeUber, VERTICAL, TOTAL_WIDHT); //l'uber choisi, il est centré
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        cout << fixed << setprecision(1); //les km sont affichés avec 1 chiffre après la virgule
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "distance", kmParcourus, "km");
        cout << fixed << setprecision(0); //le temps est affiché avec 0 chiffre après la virgule
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "temps ecoule", minutesEcoulees, "min");
        cout << fixed << setprecision(2); //tous les prix et la tva sont affichés avec 2 chiffres après la virgule
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Prix de base", resultats.prixBase);
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Prix distance", resultats.prixDistance);
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Prix temps", resultats.prixMinute);
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Total", resultats.prixFinal);
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        //condition si le prix final est inférieur au prix minimum, alors c'est le prix minimum qui est affiché
        if(resultats.prixFinal != resultats.prixFacture )
        {
            textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Course mimimale", resultats.prixFacture);
            spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        }
        TVA = TVACalcul(tauxTva, resultats.prixFacture);
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "Prix", resultats.prixFacture);
        textNum(VERTICAL, SEPARATOR, TOTAL_WIDHT, "(incl. TVA)", TVA);
        spaceTable(SPACE, VERTICAL, TOTAL_WIDHT); //ligne vide
        horizontalBord(COIN, HORIZONTAL, TOTAL_WIDHT); //affiche la bordure horizontale avec le + et -
    }
    return 0;
}

/*---------------------------------------------FONCTIONS-UTILISEES----------------------------------------------------*/
//fonction calculs prix
Rescalculs calculsPrix(int choixUber, double kmparcourus, double MinutesEcoulees)
{
    Rescalculs resultats;
    resultats.prixBase = 3.00; //pour UberX et UberPOP
    double prixKilometre = 1.80; //pour UberX
    double prixMinute = 0.30; //pour UberX et UberPOP
    double prixMinimum = 6.00; //pour UberX et UberPOP
    if (choixUber == 3){
        resultats.prixBase = 8.00;
        prixKilometre = 3.60;
        prixMinute = 0.60;
        prixMinimum = 15.00;
    }
    else if (choixUber == 2){
        prixKilometre = 1.35;
    }
    resultats.prixDistance = prixKilometre * kmparcourus;
    resultats.prixMinute = prixMinute * MinutesEcoulees;
    resultats.prixFinal = resultats.prixBase + resultats.prixDistance + resultats.prixMinute;
    resultats.prixFacture = resultats.prixFinal < prixMinimum ? prixMinimum : resultats.prixFinal;
    return resultats;
}

//calcul de la TVA
double TVACalcul(double TauxTVA, double Prix)
{
    return Prix - (Prix / (1 + TauxTVA));
}

//affichge du type d'Uber
void uberShow(const string typeUber, const char horizontal, const char TotalWidht) {
    string firstHalfWord = typeUber.substr(0, typeUber.length() / 2);
    string secondHalfWord = typeUber.substr(typeUber.length() / 2, typeUber.length() / 2 + 1);
    if((TotalWidht % 2)/*paire?*/ == 0)
    {
        cout << horizontal << right << setw(TotalWidht / 2 - 1) << firstHalfWord << left << setw(TotalWidht / 2 - 1)
             << secondHalfWord << horizontal << endl;
    }
    else
    {
        cout << horizontal << right << setw(TotalWidht / 2 - 1) << firstHalfWord << left << setw(TotalWidht / 2 - 1)
             << secondHalfWord << ' ' << horizontal << endl;
    }
}

//affichage des textes avec chiffres
void textNum(const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num )
{
    const char SPACE = ' ';
    cout << setfill(SPACE);

    if((TotalWidht % 3)/*divisible par 3?*/ == 0){
        cout << horizontal << SPACE << left << setw(TotalWidht * 2 / 3 - 4/*2 spaces*/) << text << SPACE << SEPARATOR
             << SPACE << right << setw(TotalWidht / 3 - 3) << Num << SPACE << horizontal << endl;
    }
    else
    {
        cout << horizontal << SPACE << left << setw(TotalWidht * 2 / 3 - 4/*2 spaces*/) << text << SPACE << SEPARATOR
             << SPACE << right << setw(TotalWidht / 3 - 2) << Num << SPACE << horizontal << endl;
    }
}

//affichage des textes avec chiffres et unités
void textNum(const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num, string unite )
{
    const char SPACE = ' ';
    cout << setfill(SPACE);
    if((TotalWidht % 3)/*divisible par 3?*/ == 0) {
        cout << horizontal << SPACE << left << setw(TotalWidht * 2 / 3 - 4/*2 spaces*/) << text << SPACE << SEPARATOR
             << SPACE << right << setw(TotalWidht / 3 - (4 + unite.length())) << Num << SPACE
             << unite << SPACE << horizontal << endl;
    }
    else
    {
        cout << horizontal << SPACE << left << setw(TotalWidht * 2 / 3 - 4/*2 spaces*/) << text << SPACE << SEPARATOR
             << SPACE << right << setw(TotalWidht / 3 - (3 + unite.length())) << Num << SPACE
             << unite << SPACE << horizontal << endl;
    }
}

//affichage des lignes vides
void spaceTable(const char space, const char horizontal, const char W)
{
    cout << horizontal << right << setfill(space) << setw(W-1) << horizontal << endl;
}

//affichage de la ligne horizontale de l'encadrage
void horizontalBord(const char coin, const char vertical, const char W)
{
    cout << coin << right << setfill(vertical) << setw(W-1) << coin << endl;
}

//arrondi de la distance aux 100m les plus proches
double arrondisD(double value, unsigned char prec)
{
    double puissance10 = pow(10., (double)prec);
    return round(value * puissance10) / puissance10;
}