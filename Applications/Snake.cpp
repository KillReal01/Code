#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESCAPE 27 

struct BodySnake {
	int x, y;
	BodySnake* Next, * Prev;
};

const int Column = 52, Line = 22;//размеры поля
const int size_menu = 2;
int snake_time = 400;
BodySnake* Snake;
bool end = false, quit = false;
int food_x, food_y;
std::string MOVE;

void PrintField();
void gotoxy(int x, int y);
void GetInf();
void PrintMenu(int chosen);

void AddTail(BodySnake* Beg);
int ListLength(BodySnake* Beg);
void DeleteSnake(BodySnake* Beg);
BodySnake* ListLastPoint(BodySnake* Beg);
bool CheckSnake(BodySnake* Beg);

void Play();
void SetUp();
void ControlSnake();
void CreateFood();
void MoveSnake();
void GameOver();
void GameProcess();

int ReadFile();
void WriteFile(int score);

int main() {
	system("title Snake");
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	Play();
	return 0;
}

void Play() {
	int chosen = 0;
	int c;
	while (!quit) {
		PrintMenu(chosen);
		c = _getch();
		switch (c) {
		case KEY_UP:
			chosen = (chosen + size_menu - 1) % size_menu;
			break;
		case KEY_DOWN:
			chosen = (chosen + size_menu + 1) % size_menu;
			break;
		case ENTER:
			switch (chosen) {
			case 0:
				GameProcess();
				break;
			case 1:
				quit = true;
				break;
			}
			break;
		}
		system("cls");
	}
}

void PrintMenu(int chosen) {
	std::string MenuPoint[2];
	std::string arrow = "-->";
	MenuPoint[0] = "Start game";
	MenuPoint[1] = "Quit the game";

	for (int i = 0; i < size_menu; i++) {
		if (i == chosen) {
			gotoxy((80 - MenuPoint[1].length()) / 2 - arrow.length(), 8 + i * 2);
			std::cout << arrow;
		}
		gotoxy((80 - MenuPoint[1].length()) / 2, 8 + i * 2);
		std::cout << MenuPoint[i];
	}
}

void GameProcess() {
	srand(time(NULL));
	int max_score = ReadFile();
	end = false;
	system("cls");
	SetUp();
	GetInf();
	while (!end && CheckSnake(Snake)) {
		ControlSnake();
		while (!_kbhit() && !end && CheckSnake(Snake)) {
			MoveSnake();
			GetInf();
		}
	}
	int score = (ListLength(Snake) - 1) * 10;
	if (score > max_score) {
		WriteFile(score);
	}
	DeleteSnake(Snake);
	GameOver();
}

void DeleteSnake(BodySnake* Beg) {
	BodySnake* Curr = Beg;
	while (Beg) {
		Curr = Beg->Next;
		delete Beg;
		Beg = Curr;
	}
}

void GameOver() {
	system("cls");
	std::string msg = "Game over!";
	gotoxy((80 - msg.length()) / 2, Line / 2);
	std::cout << msg;
	_getch();
}

void gotoxy(int x, int y) {//Перемещение курсора
	HANDLE hCon;
	COORD cCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cCon.X = x;
	cCon.Y = y;
	SetConsoleCursorPosition(hCon, cCon);
}

int ReadFile() {
	int score;
	std::ifstream File;
	File.open("score.txt");  // Открыли файл
	if (!File.is_open())  //  Проверили удалось ли открыть файл
	{
		return 0;   // Файл не открыт
	}
	File >> score;
	File.close();  // Закрываем файл
	return score;
}

void WriteFile(int score) {
	std::ofstream File;
	File.open("score.txt");  // Открыли файл
	if (File.is_open())  //  Проверили удалось ли открыть файл
	{
		File << score;
	}
	File.close();  // Закрываем файл
}

void PrintField() {
	for (int j = 0; j < Column + 2; j++) {
		gotoxy(j, 0);
		std::cout << '-';
		gotoxy(j, Line + 1);
		std::cout << '-';
	}
	for (int j = 0; j < Line + 2; j++) {
		gotoxy(0, j);
		std::cout << '-';
		gotoxy(Column + 1, j);
		std::cout << '-';
	}
}

void AddTail(BodySnake* Beg) {
	BodySnake* New;
	while (Beg->Next) {
		Beg = Beg->Next;
	}
	New = new BodySnake;
	Beg->Next = New;
	New->Prev = Beg;
	New->Next = NULL;
}

int ListLength(BodySnake* Beg) {
	int count = 0;
	while (Beg) {
		Beg = Beg->Next;
		count++;
	}
	return count;
}

BodySnake* ListLastPoint(BodySnake* Beg) {
	while (Beg->Next) {
		Beg = Beg->Next;
	}
	return Beg;
}

bool CheckSnake(BodySnake* Beg) {
	BodySnake* Curr = Beg;
	if (Beg->Next) {
		Curr = Curr->Next;
		while (Curr) {
			if (Curr->x == Beg->x && Curr->y == Beg->y) {
				return false;
			}
			Curr = Curr->Next;
		}
	}
	return true;
}

void SetUp() {
	int max_score = ReadFile();
	PrintField();

	Snake = new BodySnake;
	Snake->Next = NULL;
	Snake->Prev = NULL;

	int head_x, head_y;
	head_x = rand() % Column;
	head_y = rand() % Line;
	Snake->x = head_x;
	Snake->y = head_y;

	gotoxy(head_x + 1, head_y + 1);
	std::cout << '0';
	CreateFood();

	gotoxy(Column + 5, 2);
	std::cout << "PageUp - up";
	gotoxy(Column + 5, 3);
	std::cout << "PageDown - down";
	gotoxy(Column + 5, 4);
	std::cout << "PageLeft - left";
	gotoxy(Column + 5, 5);
	std::cout << "PageRight - right";
	gotoxy(Column + 5, 6);
	std::cout << "Escape - exit";
	gotoxy(Column + 5, 8);
	std::cout << "Max score: " << max_score;
}

void GetInf() {
	gotoxy(Column + 5, 10);
	std::cout << "Your score: " << (ListLength(Snake) - 1) * 10;
}

void CreateFood() {
	BodySnake* Curr;
	bool food;
	do {
		Curr = Snake;
		food = true;
		food_x = rand() % Column;
		food_y = rand() % Line;
		while (Curr) {
			if (Curr->x == food_x && Curr->y == food_y) {
				food = false;
			}
			Curr = Curr->Next;
		}
		
	} 	while (!food);
	gotoxy(food_x + 1, food_y + 1);
	std::cout << '+';
}

void ControlSnake() {
	int c;
	c = _getch();
	switch (c) {
	case KEY_UP:
		if (MOVE != "down") {
			MOVE = "up";
		}
		break;
	case KEY_DOWN:
		if (MOVE != "up") {
			MOVE = "down";
		}
		break;
	case KEY_LEFT:
		if (MOVE != "right") {
			MOVE = "left";
		}
		break;
	case KEY_RIGHT:
		if (MOVE != "left") {
			MOVE = "right";
		}
		break;
	case ESCAPE:
		end = true;
		break;
	}
}

void MoveSnake() {
	//логика
	BodySnake* Last;
	Last = ListLastPoint(Snake);

	//съела еду
	if (food_x == Snake->x && food_y == Snake->y) {
		CreateFood();
		AddTail(Snake);
		Last->Next->x = Last->x;
		Last->Next->y = Last->y;
	}
	else {
		//конец хвоста стираем
		gotoxy(Last->x + 1, Last->y + 1);
		std::cout << ' ';
	}

	//координаты последующей в текущую
	while (Last != Snake) {
		Last->x = Last->Prev->x;
		Last->y = Last->Prev->y;
		Last = Last->Prev;
	}
	if (MOVE == "up") {
		Snake->y--;
		if (Snake->y == -1)
			end = true;
	}
	if (MOVE == "down") {
		Snake->y++;
		if (Snake->y == Line)
			end = true;
	}
	if (MOVE == "left") {
		Snake->x--;
		if (Snake->x == -1)
			end = true;
	}
	if (MOVE == "right") {
		Snake->x++;
		if (Snake->x == Column)
			end = true;
	}

	if (!end) {
		//отрисовка головы
		gotoxy(Snake->x + 1, Snake->y + 1);
		std::cout << '0';
		gotoxy(0, 0);
		Sleep(snake_time - ListLength(Snake) * 7);
	}
}
