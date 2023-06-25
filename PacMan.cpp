#include <iostream>
#include <chrono>
#include <windows.h>
#include <ctime>
#include <thread>

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

char mapa[7][14] = {
	'Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z',
	'Z','O','O','O','O','Z','O','Z','O','Z','O','O','O','Z',
	'Z','O','Z','Z','O','O','O','Z','O','Z','O','Z','O','Z',
	'Z','O','Z','O','O','Z','O','O','O','O','O','Z','O','Z',
	'Z','O','Z','Z','O','Z','O','Z','Z','Z','O','O','O','Z',
	'Z','O','O','O','O','O','O','O','O','O','O','Z','O','Z',
	'Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z'
};

int x = 1, y = 1, kierunek=1, Xduszka1 = 8, Yduszka1 = 1, Xduszka2 = 8, Yduszka2 = 1;

void gdzieleziesz() {
	if (GetAsyncKeyState(VK_UP)) {
		kierunek = 1;
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		kierunek = 3;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		kierunek = 4;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		kierunek = 2;
	}

	if (kierunek == 1 && mapa[y - 1][x] != 'Z') {
		y--;
	}
	else if (kierunek == 2 && mapa[y][x + 1] != 'Z') {
		x++;
	}
	else if (kierunek == 3 && mapa[y + 1][x] != 'Z') {
		y++;
	}
	else if (kierunek == 4 && mapa[y][x - 1] != 'Z') {
		x--;
	}
}

int zebraniepunktu(int punkty) {
	if (mapa[y][x] == 'O')
	{
		punkty++;
		mapa[y][x] = 'P';
	}
	return punkty;
}

int narysowaniemapy() {
	int i = 0, j = 0, czywygral=0;
	while (i < 7) {
		while (j < 14) {
			if (j == Xduszka1 && Yduszka1 == i) {
				SetConsoleTextAttribute(h, 11);
			}
			else if (j == Xduszka2 && Yduszka2 == i) {
				SetConsoleTextAttribute(h, 12);
			}
			else if (i == y && j == x) {
				SetConsoleTextAttribute(h, 6);
			}
			else if (mapa[i][j] == 'Z') {
				SetConsoleTextAttribute(h, 7);
			}
			else if (mapa[i][j] == 'P') {
				SetConsoleTextAttribute(h, 2);
			}
			else {
				SetConsoleTextAttribute(h, 3);
				czywygral++;
			}
			cout << (char)(219) << (char)(219);
			j++;
		}
		cout << endl;
		j = 0;
		i++;
	}
	return czywygral;
}

bool ruchduszkow(bool czyduszkisieruszaja) {
	if (czyduszkisieruszaja == true)
	{
		int movementduszka;
		bool czymozeisc = false;
		while (czymozeisc == false) {
			movementduszka = rand() % 4 + 1;
			if (movementduszka == 1 && mapa[Yduszka1 - 1][Xduszka1] != 'Z') {
				czymozeisc = true;
				Yduszka1--;
			}
			else if (movementduszka == 2 && mapa[Yduszka1][Xduszka1 + 1] != 'Z') {
				czymozeisc = true;
				Xduszka1++;
			}
			else if (movementduszka == 3 && mapa[Yduszka1 + 1][Xduszka1] != 'Z') {
				czymozeisc = true;
				Yduszka1++;
			}
			else if (movementduszka == 4 && mapa[Yduszka1][Xduszka1 - 1] != 'Z') {
				czymozeisc = true;
				Xduszka1--;
			}
		}
		czymozeisc = false;
		while (czymozeisc == false) {
			movementduszka = rand() % 4 + 1;
			if (movementduszka == 1 && mapa[Yduszka2 - 1][Xduszka2] != 'Z') {
				czymozeisc = true;
				Yduszka2--;
			}
			else if (movementduszka == 2 && mapa[Yduszka2][Xduszka2 + 1] != 'Z') {
				czymozeisc = true;
				Xduszka2++;
			}
			else if (movementduszka == 3 && mapa[Yduszka2 + 1][Xduszka2] != 'Z') {
				czymozeisc = true;
				Yduszka2++;
			}
			else if (movementduszka == 4 && mapa[Yduszka2][Xduszka2 - 1] != 'Z') {
				czymozeisc = true;
				Xduszka2--;
			}
		}
	}
	else {
		czyduszkisieruszaja = true;
	}
	return czyduszkisieruszaja;
}

int main()
{
	using namespace std::this_thread;
	using namespace std::chrono;
	srand(time(NULL));
	bool czymozeisc = false, czyduszkisieruszaja=true;
	int j = 0, i = 0, punkty = 0, czywygral = 0;
	while (true) {
		gdzieleziesz();
		punkty=zebraniepunktu(punkty);
		czywygral = 0;
		czyduszkisieruszaja=ruchduszkow(czyduszkisieruszaja);
		czywygral=narysowaniemapy();
		cout << "Punkty: " << punkty << endl;
		if ((Xduszka1 == x && Yduszka1 == y) || (Xduszka2 == x && Yduszka2 == y)) {
			cout << "Przegrales!" << endl;
			sleep_for(seconds(2));
			return 0;
		}
		if (czywygral == 0) {
			cout << "Gratuluje wygranej!" << endl;
			sleep_for(seconds(2));
			return 0;
		}
		sleep_for(nanoseconds(75000000));
		system("cls");
	}
}
