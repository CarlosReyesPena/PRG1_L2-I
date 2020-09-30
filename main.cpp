
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
    if (MinutesEcoulees < 0)
    {
        cout << '+' << setfill('-') << setw(28) << '+' << endl;
        cout << '|' << setfill(' ') << setw(28) << '|';

    }
    else
    {
        cout << "Combien de kilometres parcourus?" << endl;
        double KilometresParcourus;
        cin >> KilometresParcourus;

    }


    return 0;
}
