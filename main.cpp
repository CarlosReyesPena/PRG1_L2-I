
#include <iostream>
#include <iomanip>


void Verticalbord(const char coin, const char vertical, const char W);

void spacetable(const char space, const char horizontal, const char W);

using namespace std;

int main() {

    string n = "test 1";
    string i = "test 2";
    cout.width(30); cout << left << n << endl;
    cout.width(30); cout << right << n << endl;

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

    // affichage de quel uber choisi
    const string fixedUber = "uber";
    string typeUber;
    //string uber = ChoixUber = 1? U + "X" : ChoixUber = 2? U + "POP" : U + "BLACK"; pourquoi ne marche pas?
    if (ChoixUber == 1) {
        typeUber =  "X";
    } else if (ChoixUber == 2) {
        typeUber =  "POP";
    } else {
        typeUber =  "BLACK";
    }
    const char space = ' ';
    //affichage course annulée
    const char coin = '+';
    const char vertical = '-';
    const char horizontal = '|';
    const char W = 28;
    const char T = 30;


    const char SEPARATOR = ':';
    const char E = 16;
    const char WIDHT_NUM = 6;
    cout << fixed << setprecision(2);
    if (MinutesEcoulees < 1)
    {
        double annulationfrais = 0;
        switch (ChoixUber) {
            case 1 :
            case 2 :
                annulationfrais = 6.00;
                break;
            case 3 :
                annulationfrais = 10.00;

        }

        Verticalbord(coin, vertical, W);
        spacetable(space, horizontal, W);
        cout << horizontal << right << setw(W/2) << fixedUber  << left << setw(T) << typeUber << horizontal << endl; //comment centrer?
        cout << horizontal << setfill(space) << setw(W) << horizontal << endl;
        cout << horizontal << space << left <<setw(E) << "Frais annulation"<< space << SEPARATOR
        << space << right << setw(WIDHT_NUM) << annulationfrais << space << horizontal << endl;
        Verticalbord(coin, vertical, W);

    }
    else
    {
        cout << "Combien de kilometres parcourus?" << endl;
        double KilometresParcourus;
        cin >> KilometresParcourus;
        cout << endl;
    }

    double min = 6.; //test affichage pour si prix min ou pas
    double prix; //entrer prix à la main pour voir si affiche 14 ou 16 |
    cout << "prix" << endl;
    cin >> prix;
    //affichage course

    cout << coin << setfill(vertical) << setw(W) << coin << endl;
    cout << horizontal << setfill(' ') << setw(W) << horizontal << endl;
    //int test = uber.length();
    // int UberWidth = (W-test-1)/2;
    cout << internal << horizontal << setw(14) << typeUber  << setw(14) << horizontal << endl; //comment centrer?
    cout << horizontal << setfill(' ') << setw(W) << horizontal << endl;
    cout << horizontal << setfill(' ') << setw(W) << horizontal << endl;




            for (int i = 0; i < 14; i++) {
                if (i == 1){

                    cout << horizontal << typeUber << horizontal << internal << endl; //comment centrer?
                }
                cout << horizontal << setfill(' ') << setw(W) << horizontal << endl;
            }

    cout << coin << setfill(vertical) << setw(W) << coin << endl;

    return 0;
}

void spacetable(const char space, const char horizontal, const char W) { cout << horizontal << setfill(space) << setw(W) << horizontal << endl; }

void Verticalbord(const char coin, const char vertical, const char W){
    cout << coin << setfill(vertical) << setw(W) << coin << endl;
}
