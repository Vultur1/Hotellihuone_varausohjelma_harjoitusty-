// Tekijä: Tuomas Tuuri
// Hotellihuoneenvarausohjelma harjoitustyö
// Tavoite 3p

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

// Aliohjelmien prototyypit
bool onkoVapaa(int huonenumero, const vector<bool>& varatut);
int arvoValilta(int min, int max);
int arvoVarausnumero(const vector<int>& varausnumerot);
int haeVarausnumerolla(const vector<int>& varausnumerot, int numero);
int haeVarausnimella(const vector<string>& nimet, const string& nimi);
int lueKokonaisluku(const string& kehotus);

int main() {
    srand(time(0));

    int huoneidenMaara = arvoValilta(30, 70);
    int hinta = arvoValilta(80, 100);

    vector<bool> varatut(huoneidenMaara, false);
    vector<int> varausnumerot(huoneidenMaara, 0);
    vector<string> varaajienNimet(huoneidenMaara, "");
    vector<int> oidenMaara(huoneidenMaara, 0);

    while (true) {
        setlocale(LC_ALL, "fi-FI");     //Suomalaiset aakoset
        cout << "\nHotellin varausjärjestelmä\n";
        cout << "1) Tee varaus\n2) Hae varaus numerolla\n3) Hae varaus nimellä\n4) Lopeta\n";

        int valinta = lueKokonaisluku("Valitse toiminto: ");

        if (valinta == 1) {
            // Varaus
            int vapaita = 0;
            for (bool v : varatut) if (!v) vapaita++;
            if (vapaita == 0) {
                cout << "Kaikki huoneet on varattu\n";
                continue;
            }

            // Arvotaan vapaa huone
            int huone;
            do {
                huone = arvoValilta(1, huoneidenMaara);
            } while (!onkoVapaa(huone, varatut));

            cout << "Huoneesi numero on " << huone << "\n";

            // Varaajan nimi
            cout << "Anna varaajan nimi: ";
            string nimi;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nimi);

            // Öiden määrä
            int yot = lueKokonaisluku("Anna öiden määrä: ");

            // Varausnumero
            int varausnro = arvoVarausnumero(varausnumerot);

            // Tallennetaan tiedot
            varatut[huone - 1] = true;
            varausnumerot[huone - 1] = varausnro;
            varaajienNimet[huone - 1] = nimi; 
            oidenMaara[huone - 1] = yot; 

            int summa = yot * hinta;

            cout << "Varaus tehty, Varausnumero: " << varausnro << "\n";
            cout << "Loppusumma: " << summa << " euroa.\n";
        }
        else if (valinta == 2) {
            int numero = lueKokonaisluku("Anna varausnumero: ");
            int huone = haeVarausnumerolla(varausnumerot, numero);
            if (huone == -1) cout << "Varausta ei löytynyt. \n";
            else {
                cout << "Varaus löytyi huoneesta " << huone + 1 << "\n";
                cout << "Nimi: " << varaajienNimet[huone] << "\n";
                cout << "Yöt: " << oidenMaara[huone] << "\n"; 
            }
        }
        else if (valinta == 3) {
            cout << "Anna nimi: ";
            string nimi;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nimi);

            int huone = haeVarausnimella(varaajienNimet, nimi);
            if (huone == -1) cout << "Varausta ei löytynyt. \n";
            else {
                cout << "Varaus löytyi huoneesta " << huone + 1 << "\n";
                cout << "Varausnumero: " << varausnumerot[huone] << "\n";
                cout << "Yöt: " << oidenMaara[huone] << "\n"; 
            }
        }
        else if (valinta == 4) {
            cout << "Ohjelma lopetetaan.\n";
            break;
        }
        else {
            cout << "Virheellinen valinta\n";
        }
    }

    return 0;
}

// Aliohjelmat
bool onkoVapaa(int huonenumero, const vector<bool>& varatut) {
    return !varatut[huonenumero - 1];
}

int arvoValilta(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int arvoVarausnumero(const vector<int>& varausnumerot) {
    int numero;
    bool uniikki;
    do {
        numero = arvoValilta(10000, 99999);
        uniikki = true;
        for (int n : varausnumerot) if (n == numero) uniikki = false;
    } while (!uniikki);
    return numero;
}

int haeVarausnumerolla(const vector<int>& varausnumerot, int numero) {
    for (size_t i = 0; i < varausnumerot.size(); i++)
        if (varausnumerot[i] == numero) return i;
    return -1;
}

int haeVarausnimella(const vector<string>& nimet, const string& nimi) {
    for (size_t i = 0; i < nimet.size(); i++)
        if (nimet[i] == nimi) return i;
    return -1;
}

int lueKokonaisluku(const string& kehotus) {
    int luku;
    while (true) {
        cout << kehotus;
        if (cin >> luku) return luku;
        cout << "Virheellinen syöte, yritä uudelleen.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}