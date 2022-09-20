#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string hasło;
string VIN, tablica, marka, uszkodzone_części, model, miesiąc_produkcji, kolor, masa, kraj_pochodzenia, napis;
ifstream plik;

unsigned short rok_produkcji, wybór;

unsigned char dzień_produkcji;

//zmienne pomocnicze
char v_VIN[3] = { 'I', 'O', 'Q'};

void dźwięk() {
	Beep(1000, 300);
	Beep(1000, 300);
	Sleep(2000);
}

void zła_opcja(unsigned short pomocnicza) {
	if (pomocnicza == 1) {
		system("cls");
		cout << "Zła opcja!";
		dźwięk();
	}
	else if (pomocnicza == 2) {
		system("cls");
		cout << "Złe hasło!";
		dźwięk();
	}

	else if (pomocnicza == 3) {
		cout << endl << "Niepoprawny VIN!" << endl;
		cout << "VIN nie może zawierać znaków\"O, Q oraz I\"";
		dźwięk();
	}

	else {
		system("cls");
		dźwięk();
	}
}

void zapis_samochodów() {
	ofstream samochody;
	samochody.open("C:\\moje aplikacje\\CEPIK(baza danych pojazdów)\\CEPIK(baza danych pojazdów)\\database_VIN\\VIN " + VIN, ios::app);
	samochody << "VIN: " << VIN << endl;
	samochody << "Tablica rejestracyjna: "      << tablica          << endl;
	samochody << "Kolor pojazzdu: " << kolor    << endl;
	samochody << "Marka pojazdu: "  << marka    << endl;
	samochody << "Model pojazdu: "  << model    << endl;
	samochody << "Kraj pochodzenia pojazdu: "   << kraj_pochodzenia << endl;
	samochody << "Masa dopuszczalna pojazdu: "  << masa << endl;
	samochody << "Data produkcji pojazdu: "     << rok_produkcji << "-" << miesiąc_produkcji << "-" << dzień_produkcji;
	samochody.close();
}

void dodawanie_samochodu() {
	bool v2;
	string wczytywanie_tablicy[2];

	do {
		system("cls");
		cout << "Podaj VIN auta: ";
		cin.sync();
		cin  >> VIN;
		cout << "Podaj tablicę rejestracyjną: "; cin >> wczytywanie_tablicy[0] >> wczytywanie_tablicy[1];
		cout << "Podaj markę: "; cin >> marka;
		cout << "Podaj model: "; cin >> model;
		cout << "Podaj kolor: "; cin >> kolor;
		cout << "Podaj kraj pochodzenia: ";  cin >> kraj_pochodzenia;
		cout << "Podaj masę dopuszczalną pojazdu w kg: "; cin >> masa;
		cout << "Podaj rok produkcji: ";     cin >> rok_produkcji;
		cout << "Podaj miesiąc produkcji: "; cin >> miesiąc_produkcji;
		cout << "Podaj dzień produkcji: ";   cin >> dzień_produkcji;
		transform(VIN.begin(), VIN.end(), VIN.begin(), ::toupper);
		for (char p = 0; p <= 2; p++) {
			if (VIN.find(v_VIN[p]) == !string::npos) {
				v2 = true;
				break;
			}
			else v2 = false;
		}
		if (v2) zła_opcja(3);
	} while (v2);

	tablica = wczytywanie_tablicy[0] + ' ' + wczytywanie_tablicy[1];
}
void odczyt_samochodów() {
	system("cls");
	cout << "Wprowadź VIN: "; cin >> VIN;
	plik.open("C:\\moje aplikacje\\CEPIK(baza danych pojazdów)\\CEPIK(baza danych pojazdów)\\database_VIN\\VIN " + VIN);
	if (!plik.is_open()) {
		cout << "Nie istnieje taki VIN!";
		zła_opcja(4);
		exit(0);
	}
	else {
		while (getline(plik, napis), plik.eof()) cout << napis;
	}
}

void menu() {
	bool v1;
	do {
		system("cls");
		cout << "Baza danych pojazów" << endl;
		cout << "1 = dodaj nowy samochód do bazy" << endl;
		cout << "2 = odzcytaj dane z samochodów" << endl;
		cout << "3 = wyjście z programu" << endl;
		cout << "4 = dołącz informacje do VINu(na razie nie działa)" << endl;
		cout << "Co wybierasz?: ";
		cin  >> wybór;
		v1 = !(wybór == 1 or wybór == 2 or wybór == 3);
		if (v1) zła_opcja(1);
	} while (v1);
}

void przekierowywanie() {
	bool v3;

	switch (wybór) {
	case 1:
		do {
 			system("cls");
			cout << "Podaj hasło: "; cin >> hasło;
			if (hasło != "JKI2250") {
				zła_opcja(2);
				v3 = true;
			}
			else v3 = false;
		} while (v3);
		system("cls");

		dodawanie_samochodu();
		zapis_samochodów();

		break;
	case 2:
 		odczyt_samochodów();
	case 3: exit(0);
	}
}
