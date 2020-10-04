
//Libreries pour la gestion des string et des opérations mathematiques.
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


//prototypes des fonctions d'affichage et d'arrondi.
void Verticalbord(const char coin, const char vertical, const char W);

void spacetable(const char space, const char horizontal, const char W);

void TextNum(const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num );
void TextNum(const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num, string unite);

double ArrondisD(double value, unsigned char prec);


void UberShow(string typeUber, const char horizontal, const char TotalWidht);

double TVACalcul(double TauxTVA, double Prix);

int main() {

    cout << "Quel uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK" << endl;
    int ChoixUber = 0;
    do {
        cin >> ChoixUber;
        if(ChoixUber >= 1 && ChoixUber <= 3) continue;
        cout << "Valeur incorrecte. Reessayez." << endl;
    }while(ChoixUber < 1 || ChoixUber > 3);

    cout << "Combien de minutes ecoulees?" << endl;
    double MinutesEcoulees;
    cin >> MinutesEcoulees;

    if((MinutesEcoulees - (int)MinutesEcoulees) > 0.0)
    {
        MinutesEcoulees = (int)MinutesEcoulees + 1;
    }

    enum PosUber { uberX = 1, uberPOP, uberBLACK };

    // affichage de quel uber choisi
    string typeUber;
    //string uber = ChoixUber = 1? U + "X" : ChoixUber = 2? U + "POP" : U + "BLACK"; pourquoi ne marche pas?
    if (ChoixUber == uberX) {
        typeUber =  "uberX";
    } else if (ChoixUber == uberPOP) {
        typeUber =  "uberPOP";
    } else if (ChoixUber == uberBLACK){
        typeUber =  "uberBLACK";
    }
    else
    {
        cout << "ERREUR" << endl;
        return 1;
    }
    const char space = ' ';
    //affichage course annulée
    const char coin = '+';
    const char vertical = '-';
    const char horizontal = '|';
    const char TotalWidht = 30;


    const char SEPARATOR = ':';

    double TauxTVA = 0.08;
    double TVA = 0;

    if (MinutesEcoulees < 1)
    {
        cout << fixed << setprecision(2);

        double annulationfrais = 0;
        switch (ChoixUber) {
            case uberX :
            case uberPOP :
                annulationfrais = 6.00;
                break;
            case uberBLACK :
                annulationfrais = 10.00;
                break;

        }
        TVA = TVACalcul(TauxTVA, annulationfrais);
        cout << endl;//separation de la question et du tableau

        Verticalbord(coin, vertical, TotalWidht);
        spacetable(space, horizontal, TotalWidht);
        UberShow( typeUber, horizontal, TotalWidht);
        spacetable(space, horizontal, TotalWidht);
        TextNum(horizontal, SEPARATOR,TotalWidht,"Frais annulation",annulationfrais);
        spacetable(space, horizontal, TotalWidht);
        TextNum(horizontal, SEPARATOR,TotalWidht,"Prix",annulationfrais);
        TextNum(horizontal, SEPARATOR,TotalWidht,"(incl. TVA)",TVA);
        spacetable(space, horizontal, TotalWidht);
        Verticalbord(coin, vertical, TotalWidht);

    }
    else
    {
        cout << "Combien de kilometres parcourus?" << endl;
        double kmparcourus;
        do {
            cin >> kmparcourus;
            if(kmparcourus >= 0) continue;
            cout << "Impossible. Reessayez." << endl;
        }while(kmparcourus < 0);

        //kmparcourus = (1./100.) *
        kmparcourus = ArrondisD(kmparcourus,1);
        cout << endl;//separation de la question et du tableau

        bool CourseMinbool = false;
        double Prixbase = 3.0;
        double Prixkm = 0.0;
        double Prixdistance = 0.0;
        double Prixtemps = 0.0;
        double Prixminute = 0.3;
        double Prixfinal = 0.0;
        double Prixminimal = 6.0;
        switch (ChoixUber) {
            case uberX :
                Prixkm = 1.8;
                break;
            case uberPOP :
                Prixkm = 1.35;
                break;
            case uberBLACK :
                Prixbase = 8.0;
                Prixkm = 3.6;
                Prixminute = 0.6;
                Prixminimal = 15.0;
                break;

        }
        //Calculs
        Prixdistance = kmparcourus * Prixkm;
        Prixtemps = MinutesEcoulees * Prixminute;
        Prixfinal = Prixbase + Prixdistance + Prixtemps;

        if(Prixfinal < Prixminimal)
        {
            CourseMinbool = true;
        }
        else
        {
            TVA = TVACalcul(TauxTVA, Prixfinal);
        }

        Verticalbord(coin, vertical, TotalWidht);
        spacetable(space, horizontal, TotalWidht);
        UberShow( typeUber, horizontal, TotalWidht);
        spacetable(space, horizontal, TotalWidht);

        cout << fixed << setprecision(1);

        TextNum(horizontal, SEPARATOR,TotalWidht,"distance",kmparcourus,"km");

        cout << fixed << setprecision(0);

        TextNum(horizontal, SEPARATOR,TotalWidht,"temps ecoule",MinutesEcoulees,"min");

        cout << fixed << setprecision(2);

        spacetable(space, horizontal, TotalWidht);
        TextNum(horizontal, SEPARATOR,TotalWidht,"Prix de base",Prixbase);
        TextNum(horizontal, SEPARATOR,TotalWidht,"Prix distance",Prixdistance);
        TextNum(horizontal, SEPARATOR,TotalWidht,"Prix temps",Prixtemps);
        TextNum(horizontal, SEPARATOR,TotalWidht,"Total",Prixfinal);
        spacetable(space, horizontal, TotalWidht);
        if(CourseMinbool == true)
        {
            TextNum(horizontal, SEPARATOR,TotalWidht,"Course minimale",Prixminimal);
            spacetable(space, horizontal, TotalWidht);
            Prixfinal = Prixminimal;
            TVA = TVACalcul(TauxTVA, Prixfinal);
        }
        TextNum(horizontal, SEPARATOR,TotalWidht,"Prix",Prixfinal);
        TextNum(horizontal, SEPARATOR,TotalWidht,"(incl. TVA)",TVA);
        spacetable(space, horizontal, TotalWidht);
        Verticalbord(coin, vertical, TotalWidht);

    }
    return 0;
}

double TVACalcul(double TauxTVA, double Prix) { return Prix - (Prix / (1 + TauxTVA)); }

void UberShow(const string typeUber, const char horizontal, const char TotalWidht) {
    string firsthalfword = typeUber.substr(0,typeUber.length()/2);
    string secondhalfword = typeUber.substr(typeUber.length()/2,typeUber.length()/2 + 1);
    if((TotalWidht % 2)/*paire?*/ == 0)
    {
        cout << horizontal << right << setw(TotalWidht / 2 - 1) << firsthalfword << left << setw(TotalWidht / 2 - 1)
             << secondhalfword << horizontal << endl;
    }
    else
    {
        cout << horizontal << right << setw(TotalWidht / 2 - 1) << firsthalfword << left << setw(TotalWidht / 2 - 1)
             << secondhalfword <<' '<< horizontal << endl;
    }

}

void TextNum( const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num )
{
    const char space = ' ';
    cout << setfill(space);

    if((TotalWidht % 3)/*divisible par 3?*/ == 0){
        cout << horizontal << space << left << setw(TotalWidht*2/3-4/*2 spaces*/) << text  << space << SEPARATOR
             << space << right << setw(TotalWidht/3 - 3) << Num << space << horizontal << endl;
    }
    else
    {
        cout << horizontal << space << left << setw(TotalWidht*2/3-4/*2 spaces*/) << text  << space << SEPARATOR
             << space << right << setw(TotalWidht/3 - 2) << Num << space << horizontal << endl;
    }
}
void TextNum( const char horizontal, const char SEPARATOR, const char TotalWidht, string text, double Num,string unite )
{
    const char space = ' ';
    cout << setfill(space);
    if((TotalWidht % 3)/*divisible par 3?*/ == 0) {
        cout << horizontal << space << left << setw(TotalWidht * 2 / 3 - 4/*2 spaces*/) << text << space << SEPARATOR
             << space << right << setw(TotalWidht / 3 - (4 + unite.length())) << Num << space
             << unite << space << horizontal << endl;
    }
    else
    {
        cout << horizontal << space << left << setw(TotalWidht * 2 / 3 - 4/*2 spaces*/) << text << space << SEPARATOR
             << space << right << setw(TotalWidht / 3 - (3 + unite.length())) << Num << space
             << unite << space << horizontal << endl;
    }
}

void spacetable(const char space, const char horizontal, const char W) {

    cout << horizontal << right << setfill(space) << setw(W-1) << horizontal << endl;
}

void Verticalbord(const char coin, const char vertical, const char W){
    cout << coin << right << setfill(vertical) << setw(W-1) << coin << endl;
}

double ArrondisD(double value, unsigned char prec)
{
    double Puissance10 = pow(10., (double)prec);
    return round(value * Puissance10) / Puissance10;
}