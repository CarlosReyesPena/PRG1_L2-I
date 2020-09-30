
#include <iostream>
#include <iomanip>

using namespace std;

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

    // affichage de quel uber choisi
    const string U = "uber";
    string uber;
    //string uber = ChoixUber = 1? U + "X" : ChoixUber = 2? U + "POP" : U + "BLACK"; pourquoi ne marche pas?
    if (ChoixUber == 1) {
        uber = U + "X";
    } else if (ChoixUber == 2) {
        uber = U + "POP";
    } else {
        uber = U + "BLACK";
    }
    cout << uber << endl;

    //affichage course annulée
    const int W = 28;
    if (MinutesEcoulees < 1)
    {
        cout << '+' << setfill('-') << setw(W) << '+' << endl;
        for (int i = 0; i < 8; i++){
            if (i == 1){
                cout << '|' << uber << setw(W) << '|' << endl; //comment centrer?
            }
            cout << '|' << setfill(' ') << setw(W) << '|' << endl;
        }
        cout << '+' << setfill('-') << setw(W) << '+' << endl;


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
    cout << '+' << setfill('-') << setw(W) << '+' << endl;
        if ((1 || 2 || 3) && prix < min) {
            for (int i = 0; i < 16; i++) {
                if (i == 1){
                    cout << '|' << uber << setw(W) << '|' << endl; //comment centrer?
                }
                cout << '|' << setfill(' ') << setw(W) << '|' << endl;
            }
        } else{
            for (int i = 0; i < 14; i++) {
                if (i == 1){
                    cout << '|' << uber << setw(W) << '|' << endl; //comment centrer?
                }
                cout << '|' << setfill(' ') << setw(W) << '|' << endl;
            }
        }
    cout << '+' << setfill('-') << setw(W) << '+' << endl;

    return 0;
}
