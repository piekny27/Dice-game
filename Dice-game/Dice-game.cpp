#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

#pragma region funkcje i procedury

void przeniesKursor(short x, short y) {
	COORD kursorPos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, kursorPos);
}
void pokazKursor(bool stan)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = stan;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void rozmiarKonsoli(int szerokosc, int wysokosc)
{
	RECT r;
	HWND console = GetConsoleWindow();
	HWND desktop = GetDesktopWindow();
	GetWindowRect(desktop, &r);
	//zmiana wielkosci i polozenia konsoli
	MoveWindow(console, (r.right / 2) - (szerokosc / 2), (r.bottom / 2) - (wysokosc / 2), szerokosc, wysokosc, TRUE);
}

void dodajTekst(string tekst, int x, int y)
{
	przeniesKursor(x, y);
	cout << tekst;
}
void dodajScene(string nazwaSceny)
{
	ifstream plik("Assets/" + nazwaSceny);
	string linie = "";
	if (plik)
	{
		while (plik.good())
		{
			string temp;
			getline(plik, temp);
			temp += "\n";
			linie += temp;
		}
	}
	else  linie = "Blad podczas ladowania pliku.";
	przeniesKursor(0, 0);
	cout << linie << endl;
	plik.close();
}
void dodajObiekt(string nazwaObjektu, int x, int y)
{
	string linie = "";
	ifstream plik("Assets/" + nazwaObjektu);

	if (plik)
	{
		int licznik = 0;
		while (plik.good())
		{
			string temp;
			getline(plik, temp);
			przeniesKursor(x, y + licznik);
			cout << temp;
			licznik++;
		}
	}
	else
	{
		przeniesKursor(x, y);
		cout << "Plik nie istnieje";
	}
	plik.close();
}
void usunObszar(int x1, int y1, int x2, int y2)
{
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			przeniesKursor(i, j);
			cout << ' ';
		}
	}

}

void AnimacjaRzutu(int czasMS)
{
	const int iloscKlatek = 5;
	int kostka1Tab[iloscKlatek][2] = { {58,19}, {54,19}, {53,20}, {50,21}, {49,22} };
	int kostka2Tab[iloscKlatek][2] = { {59,21}, {56,21}, {51,22}, {45,24}, {44,25} };

	usunObszar(44, 18, 69, 25);
	dodajObiekt("obiekt15.txt", 60, 18); //obiekt "kubekPionwy"
	Sleep(1000);
	dodajObiekt("obiekt16.txt", 60, 18); //obiekt "kubekPoziomy"

	for (int i = 0;i < iloscKlatek;i++)
	{
		przeniesKursor(kostka1Tab[i][0], kostka1Tab[i][1]);
		cout << 'o';
		przeniesKursor(kostka2Tab[i][0], kostka2Tab[i][1]);
		cout << 'o';
		Sleep(czasMS);
		przeniesKursor(kostka1Tab[i][0], kostka1Tab[i][1]);
		if (i != iloscKlatek - 1) cout << ' ';
		przeniesKursor(kostka2Tab[i][0], kostka2Tab[i][1]);
		if (i != iloscKlatek - 1) cout << ' ';
	}

}
void LosujKosci(int kosciTab[], int& suma)
{
	int p = 1;
	int k = 6;
	suma = 0;
	for (int i = 0;i < 2;i++)
	{
		int temp = rand() % (k - p + 1) + p;
		kosciTab[i] = temp;
		suma += temp;
	}
}
void PrzeliczPunkty(int& numerRundy, int& sumaRundyDodatk, int& wybor, int& sumaPunktow, int& sumaPieniedzy)
{
	if (numerRundy == 1) //runda 1
	{
		if (sumaPunktow == 7 || sumaPunktow == 11)
		{
			wybor = 3; //wygrales
			sumaPieniedzy += 10;
		}
		if (sumaPunktow == 2 || sumaPunktow == 3 || sumaPunktow == 12)
		{
			wybor = 4; //przegrales
			sumaPieniedzy -= 15;
		}
		if (sumaPunktow == 4 || sumaPunktow == 5 || sumaPunktow == 6 || sumaPunktow == 8 || sumaPunktow == 9 || sumaPunktow == 10)
		{
			wybor = 5; //grasz dalej
			sumaRundyDodatk = sumaPunktow;
			numerRundy++;
		}
	}
	else //kolejne rundy
	{
		if (sumaPunktow != 7)
		{
			if (sumaPunktow == sumaRundyDodatk)
			{
				wybor = 3; //wygrales
				sumaPieniedzy += 10;
				numerRundy = 1;
			}
			else
			{
				wybor = 5; //grasz dalej
				//sumaRundyDodatk = sumaPunktow;
				numerRundy++;
			}
		}
		else
		{
			wybor = 4; //przegrales
			sumaPieniedzy -= 15;
			numerRundy = 1;
		}
	}
}
void WyswietlKosci(int kosciTab[])
{
	usunObszar(10, 4, 44, 11);
	int kosciPosTab[2][2] = { {10,4}, {30,4} };

	for (int i = 0; i < 2; i++)
	{
		switch (kosciTab[i])
		{
		case 1:
			dodajObiekt("obiekt18.txt", kosciPosTab[i][0], kosciPosTab[i][1]); //obiekt "kosc1"
			break;
		case 2:
			dodajObiekt("obiekt19.txt", kosciPosTab[i][0], kosciPosTab[i][1]); //obiekt "kosc2"
			break;
		case 3:
			dodajObiekt("obiekt20.txt", kosciPosTab[i][0], kosciPosTab[i][1]); //obiekt "kosc3"
			break;
		case 4:
			dodajObiekt("obiekt21.txt", kosciPosTab[i][0], kosciPosTab[i][1]); //obiekt "kosc4"
			break;
		case 5:
			dodajObiekt("obiekt22.txt", kosciPosTab[i][0], kosciPosTab[i][1]); //obiekt "kosc5"
			break;
		case 6:
			dodajObiekt("obiekt23.txt", kosciPosTab[i][0], kosciPosTab[i][1]); //obiekt "kosc6"
			break;
		}
	}
}

void Menu(int& wybor)
{
	int licznik = 100;
	int przycisk = 0;

	//budowa sceny
	dodajScene("scena2.txt");//scena "ramka"
	dodajObiekt("objekt3.txt", 38, 1); //objekt "kostki"
	dodajObiekt("objekt13.txt", 42, 17); //przycisk "autor"
	dodajObiekt("objekt12.txt", 42, 21); //przycisk "instrukcja"
	dodajObiekt("objekt9.txt", 42, 25); //przycisk "wyjscie"
	dodajObiekt("objekt10.txt", 42, 13); //objekt "zaznaczenie"
	dodajObiekt("objekt8.txt", 42, 13); //przycisk "nowa gra"
	//obsluga menu
	do
	{
		przycisk = _getch();
		switch (przycisk)
		{
		case 72:
			licznik--;
			break;
		case 80:
			licznik++;
			break;
		}
		wybor = (abs(licznik) % 4) + 1;
		switch (wybor)
		{
		case 1:
			usunObszar(42, 13, 62, 28);
			dodajObiekt("objekt13.txt", 42, 17); //przycisk "autor"
			dodajObiekt("objekt12.txt", 42, 21); //przycisk "instrukcja"
			dodajObiekt("objekt9.txt", 42, 25); //przycisk "wyjscie"
			dodajObiekt("objekt10.txt", 42, 13); //objekt "zaznaczenie"
			dodajObiekt("objekt8.txt", 42, 13); //przycisk "nowa gra"
			break;
		case 2:
			usunObszar(42, 13, 62, 28);
			dodajObiekt("objekt8.txt", 42, 13); //przycisk "nowa gra"
			dodajObiekt("objekt12.txt", 42, 21); //przycisk "instrukcja"
			dodajObiekt("objekt9.txt", 42, 25); //przycisk "wyjscie"
			dodajObiekt("objekt10.txt", 42, 17); //objekt "zaznaczenie"
			dodajObiekt("objekt13.txt", 42, 17); //przycisk "autor"
			break;
		case 3:
			usunObszar(42, 13, 62, 28);
			dodajObiekt("objekt8.txt", 42, 13); //przycisk "nowa gra"
			dodajObiekt("objekt13.txt", 42, 17); //przycisk "autor"
			dodajObiekt("objekt9.txt", 42, 25); //przycisk "wyjscie"
			dodajObiekt("objekt10.txt", 42, 21); //objekt "zaznaczenie"
			dodajObiekt("objekt12.txt", 42, 21); //przycisk "instrukcja"
			break;
		case 4:
			usunObszar(42, 13, 62, 28);
			dodajObiekt("objekt8.txt", 42, 13); //przycisk "nowa gra"
			dodajObiekt("objekt13.txt", 42, 17); //przycisk "autor"
			dodajObiekt("objekt12.txt", 42, 21); //przycisk "instrukcja"
			dodajObiekt("objekt10.txt", 42, 25); //objekt "zaznaczenie"
			dodajObiekt("objekt9.txt", 42, 25); //przycisk "wyjscie"
			break;
		}
	} while (przycisk != 13);
}
void Menu2(int& wybor)
{
	int przycisk = 0;
	int licznik = 100;

	dodajObiekt("obiekt25.txt", 74, 27); //przycisk "poddaj sie"
	dodajObiekt("objekt10.txt", 76, 23); //objekt "zaznaczenie"
	dodajObiekt("obiekt24.txt", 74, 23); //przycisk "rzuc kostka"

	do
	{

		przycisk = _getch();
		switch (przycisk)
		{
		case 72:
			licznik--;
			break;
		case 80:
			licznik++;
			break;
		}
		wybor = (abs(licznik) % 2) + 1;
		switch (wybor)
		{
		case 1:
			usunObszar(74, 23, 94, 30);
			dodajObiekt("obiekt25.txt", 74, 27); //przycisk "poddaj sie"
			dodajObiekt("objekt10.txt", 76, 23); //objekt "zaznaczenie"
			dodajObiekt("obiekt24.txt", 74, 23); //przycisk "rzuc kostka"

			break;
		case 2:
			usunObszar(74, 23, 94, 30);
			dodajObiekt("obiekt24.txt", 74, 23); //przycisk "rzuc kostka"
			dodajObiekt("objekt10.txt", 76, 27); //objekt "zaznaczenie"
			dodajObiekt("obiekt25.txt", 74, 27); //przycisk "poddaj sie"
			break;
		}
	} while (przycisk != 13);
}
void Instrukcja(int czasMS)
{
	dodajObiekt("objekt2.txt", 28, 0); //napis "instrukcja"
	Sleep(1000);
	dodajTekst("Gracz rzuca dwie kosci. Kazda z nich ma 6 scianek.", 26, 5);
	Sleep(czasMS);
	dodajTekst("Kiedy kosci zostaja rzucone, obliczana jest suma punktow.", 23, 6);
	Sleep(czasMS);
	dodajTekst("Jezeli przy pierwszym rzucie suma wynosi 7 lub 11 gracz wygrywa.", 20, 7);
	Sleep(czasMS);
	dodajTekst("Jesli suma wynosi przy pierwszym rzucie 2, 3 lub 12 gracz przegrywa.", 18, 8);
	Sleep(czasMS);
	dodajTekst("Jezeli suma wynosi 4, 5, 6, 8, 9 lub 10 przy pierwszym rzucie, wtedy suma", 16, 9);
	Sleep(czasMS);
	dodajTekst("staje sie 'punktami' gracza. Chcac wygrac musi kontynuowac rzucanie koscmi, az", 13, 10);
	Sleep(czasMS);
	dodajTekst("do uzyskania 'swoich punktow'. Gracz przegrywa wyrzucajac 7.", 22, 11);
	Sleep(500);
	dodajObiekt("objekt4.txt", 28, 12); //napis "sterowanie"
	Sleep(1000);
	dodajObiekt("objekt5.txt", 30, 16); //objekt "enter"
	Sleep(czasMS);
	dodajObiekt("objekt6.txt", 48, 16); //objekt "strzalkaUP"
	Sleep(czasMS);
	dodajObiekt("objekt7.txt", 58, 16); //objekt "strzalkaDOL"

}
void Gra()
{
	int kosciTab[2];
	int sumaPunktow = 0;
	int sumaPieniedzy = 100;
	int numerRundy = 1;
	int sumaRundyDodatk;
	int wybor;

	Sleep(1000);
	dodajObiekt("obiekt14.txt", 6, 13); //obiekt "stol"
	dodajObiekt("obiekt27.txt", 24, 29); //obiekt "ramkaNaTekst"
	Sleep(1000);

	do
	{
		Menu2(wybor);

		if (wybor == 1) //rzut kostka
		{
			usunObszar(27, 31, 71, 31);
			AnimacjaRzutu(500);
			LosujKosci(kosciTab, sumaPunktow);
			WyswietlKosci(kosciTab);
			PrzeliczPunkty(numerRundy, sumaRundyDodatk, wybor, sumaPunktow, sumaPieniedzy);
			dodajTekst(to_string(sumaPunktow) + "   ", 63, 4);
			dodajTekst(to_string(sumaPieniedzy) + " PLN  ", 80, 4);
		}

		switch (wybor)
		{
		default:
			break;
		case 3:
			dodajTekst("Brawo. Wygrales!!!", 40, 31); //napis wygrales
			break;
		case 4:
			dodajTekst("Moze nastepnym razem dopisze Ci szczescie...", 27, 31); //napis przegrales
			break;
		case 5:
			dodajTekst("Pudlo. Czy odwazysz sie grac dalej???", 30, 31); //napis grasz dalej 
			break;
		}

		if (sumaPieniedzy <= 0) // koniec gry
		{
			system("CLS");
			dodajScene("scena2.txt");//scena "ramka"
			Sleep(100);
			dodajObiekt("obiekt26.txt", 35, 11); //obiekt "koniec gry"
			Sleep(3000);
			dodajObiekt("objekt5.txt", 45, 23); //obiekt "enter"
			wybor = 2;
			getchar();
		}
	} while (wybor != 2); //wyjscie
}

#pragma endregion

int main()
{
	//deklaracja zmiennych
	int wybor;
	//ustawienia
	rozmiarKonsoli(850, 600);
	pokazKursor(false);
	srand(time(0));
	//intro
	dodajScene("scena1.txt");//scena "gra w kosci"
	Sleep(2000);
	dodajScene("scena2.txt");//scena "ramka"
	Sleep(2000);
	//wyswietlenie instrukcji
	Instrukcja(300);
	Sleep(2000);
	dodajObiekt("objekt1.txt", 21, 23); //napis "nacisnij enter"
	getchar();
	//menu
	do
	{
		system("CLS");
		Menu(wybor);
		switch (wybor)
		{
		default:
			break;
		case 1: //nowa gra
			dodajScene("scena4.txt");//scena "gra"
			Gra();
			break;
		case 2: //autor
			dodajScene("scena3.txt");//scena "autor"
			Sleep(3000);
			dodajObiekt("objekt5.txt", 45, 26); //obiekt "enter"
			getchar();
			break;
		case 3: //instrukcja
			dodajScene("scena2.txt");//scena "ramka"
			Instrukcja(100);
			Sleep(1000);
			dodajObiekt("objekt1.txt", 21, 23); //napis "nacisnij enter"
			getchar();
			break;
		}
	} while (wybor != 4); //wyjscie

	//wyjscie
	przeniesKursor(0, 34);
	return 0;
}

