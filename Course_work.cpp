#define WIDTH_CONSOLE 80 //Ширина консоли
#define HIGH_CONSOLE 25 //Высота консоли
#define _WIN32_WINNT 0x0500
#define TIME 50//Время задержки
#define SIZE_MENU 3 //Размер меню

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESCAPE 27 
#define SPACE 32

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <io.h>

std::string ms;

const int EMPTY = 0, CLOUD = 1, SNOW = 2, MAP = 3;

const char EMPTY_symbol = ' ',//Пустота
		   CLOUD_symbol = '_',//Туча
		   SNOW_symbol = '*',//Снежинка
		   MAP_symbol = 'X';//Карта

struct T_List {//Структура списка
	int col, line;
	char point = ' ';
	int id = EMPTY;
	T_List* Next, * Prev;
};

void Start();//Старт игры
void Gaming();//Логика игры
void CreateMap();//Создание карты
void PreviewMap();//Предпросмотр карт

void PrintMenuPoint(int selected, int N, std::string MenuPoint);
void PrintMenu(int selected);

T_List* CreateList();//Создание списка
void DeleteList(T_List*& List);//Удаление списка
void PrintList(T_List* List);//Вывод списка
void PrintNewItem(T_List* List, T_List* Curr);//Обновление элемента консоли
void Converting_from_id(T_List* List);//Конвертация в символ

void gotoxy(int x, int y);//Перемещение курсора
T_List* GoDown(T_List* Curr);//Проверка на элемент ниже текущего
T_List* GoUp(T_List* Curr);//Проверка на элемент выше текущего
bool CheckDownLeft(T_List* Curr);//Да - свободно, нет - занято (снизу слева)
bool CheckDownRight(T_List* Curr);//Да - свободно, нет - занято (снизу справа)

void Print_to_file(T_List* Map);//Печать в файл
T_List* Read_from_file(std::string FileName);//Чтение файла
void Delete_file(char* FileName);//Удаление файла
bool OpenMap(char** NameMap, int& Size_Map, bool& end);//Открываем карты из папки да - есть файлы / нет - пусто

void MoveCloud(T_List* List, T_List*& Cloud, char c);//Передвижение тучи
void MoveSnowflake(T_List* List, T_List* Cloud);//Падение снежинок 
T_List* FallSnowflake(T_List* List, T_List* Snow);//Падение снежинок вниз
T_List* LogicSnowflake(T_List* List, T_List* Snow);//Логика снежинок
void FallRight(T_List* List, T_List*& Curr); //Скатывается вправо
void FallLeft(T_List* List, T_List*& Curr);//Скатывается влево

int main()
{
	setlocale(LC_ALL, "ru");
	system("MODE CON COLS=80 LINES=25");
	system("title Снежинка");
	HWND consoleWindow = GetConsoleWindow(); SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	Start();
	return 0;
}

void Start() {//Старт игры
	char c;
	bool end = false;
	int selected = 0;
	PrintMenu(selected + 1);
	while (!end) {
		c = _getch();
		switch (c) {
		case KEY_UP:
			selected = (selected - 1 + SIZE_MENU) % SIZE_MENU;
			break;
		case KEY_DOWN:
			selected = (selected + 1 + SIZE_MENU) % SIZE_MENU;
			break;
		case ENTER:
			switch (selected) {
			case 0:
				system("cls");
				Gaming();
				break;
			case 1:
				system("cls");
				CreateMap();
				break;
			case 2:
				system("cls");
				PreviewMap();
				break;
			}
			break;
		case ESCAPE:
			end = true;
			break;
		}
		PrintMenu(selected + 1);
	}
}

void Gaming() {//Логика игры       ///// сделать выбор карт
	char c;
	bool end = false;
	std::string FileName = "";
	ms = "Введите название файла (карты)";
	gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 3);
	std::cout << ms;
	gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 5);
	ms = "Карта: ";
	std::cout << ms;
	std::cin >> FileName;

	T_List* List = Read_from_file(FileName);//загрузка карты
	T_List* Curr = List;
	T_List* Cloud = List;
	if (List) {
		Cloud->id = CLOUD;
		gotoxy(0, 0);
		std::cout << CLOUD_symbol;
		PrintList(List);
		while (!end) {
			c = _getch();
			MoveCloud(List, Cloud, c);//Передвижение тучи + снежинка
			if (c == ESCAPE) {
				end = true;
				DeleteList(List);
			}
		}
	}
}

void PreviewMap() {//Предпросмотр карт
	char c;
	bool end = false;
	int Size_Map = 0;
	int selected = 0;
	char** NameMap;

	while (!end) {
		NameMap = new char* [50];
		bool f = OpenMap(NameMap, Size_Map, end);
		if (f) {
			T_List* List = Read_from_file(NameMap[selected]);
			gotoxy(0, 0);
			for (int i = 0; i < WIDTH_CONSOLE; ++i) {
				std::cout << " ";
			}
			ms = "Название файла: ";
			ms = ms + NameMap[selected] + "   (Пробел - удалить карту)";
			gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 0);
			std::cout << ms;

			PrintList(List);

			gotoxy(WIDTH_CONSOLE - 1, HIGH_CONSOLE - 1);

			//работа с клавиатурой
			c = _getch();
			switch (c) {
			case KEY_LEFT:
				selected = (selected - 1 + Size_Map) % Size_Map;
				break;
			case KEY_RIGHT:
				selected = (selected + 1 + Size_Map) % Size_Map;
				break;
			case SPACE:
				Delete_file(NameMap[selected]);
				if (Size_Map != 1) Size_Map--;
				selected = (selected - 1 + Size_Map) % Size_Map;
				break;
			case ESCAPE:
				end = true;
				break;
			}
			//Очищаем память
			for (int i = 0; i < Size_Map; ++i) {
				delete[] NameMap[i];
			}
			delete[] NameMap;
			DeleteList(List);
		}
	}
}

void Print_to_file(T_List* Map) {//Печать в файл
	ms = "Напишите название файла,";
	gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 3);
	std::cout << ms;
	ms = "не забудьте указать расширение.txt";
	gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 4);
	std::cout << ms;
	gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 6);
	ms = "Название: ";

	std::cout << ms;
	std::string FileName = "";
	std::cin >> FileName;
	FileName = "Map\\" + FileName;
	std::ofstream File;
	File.open(FileName);  // Открыли файл
	if (!File.is_open())  //  Проверили удалось ли открыть файл
		std::cout << "\tОткрыть файл не удалось!\n";
	else {
		while (Map) {// Записываем  в файл
			File << Map->id;
			if (Map->col == WIDTH_CONSOLE) File << "\n";
			Map = Map->Next;
		}
		File.close();  // Закрываем файл
	}
}

T_List* Read_from_file(std::string FileName) {
	FileName = "Map\\" + FileName;
	std::ifstream File;   // Создали поток ввода для чтения данных из файла
	File.open(FileName);  // Открыли файл
	if (!File.is_open()) {  //  Проверили удалось ли открыть файл
		ms = "Открыть файл не удалось!";
		gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 7);
		std::cout << ms;
		gotoxy(WIDTH_CONSOLE - 1, HIGH_CONSOLE - 1);
		_getch();
		return 0;
	}
	else {
		T_List* Map = CreateList();
		T_List* Curr = Map;
		char ch;
		while (!File.eof()) // Читаем 
		{
			File >> ch;
			if (Curr) {
				Curr->id = ch - '0';
				Curr = Curr->Next;
			}
		}
		File.close();
		return Map;
	}
}

void Delete_file(char* FileName) {//Удаление файла
	char Folder[60] = "Map\\";
	strcat_s(Folder, FileName);
	system("cls");
	if (remove(Folder) != 0) {
		ms = "Ошибка удаления файла!";
		gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 3);
		std::cout << ms;
		_getch();
	}
}

void PrintNewItem(T_List* List, T_List* Curr) {//Обновление элемента консоли
	Converting_from_id(List);
	gotoxy(Curr->col - 1, Curr->line - 1);
	std::cout << Curr->point;
	gotoxy(WIDTH_CONSOLE - 1, HIGH_CONSOLE - 1);
}

void gotoxy(int x, int y) {//Перемещение курсора
	HANDLE hCon;
	COORD cCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cCon.X = x;
	cCon.Y = y;
	SetConsoleCursorPosition(hCon, cCon);
}

void CreateMap() {//Создание карты
	T_List* Map = CreateList();
	T_List* Curr = GoDown(Map);
	T_List* Cursor = Curr;
	Cursor->id = MAP;
	PrintList(Map);

	ms = "Нарисуйте карту, пробел - сохранить";
	gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 0);
	std::cout << ms;
	gotoxy(WIDTH_CONSOLE - 1, HIGH_CONSOLE - 1);

	char c;
	bool end = false;
	bool enter = false;
	int empty = 1;//1-заполнено -1-пусто
	while (!end) {
		c = _getch();
		switch (c) {
		case ENTER:
			enter = true;
			empty *= -1;
			break;
		case KEY_UP:
			if (Cursor->line != 2) {
				Cursor = GoUp(Cursor);
			}
			break;
		case KEY_DOWN:
			if (Cursor->line != HIGH_CONSOLE) {
				Cursor = GoDown(Cursor);
			}
			break;
		case KEY_LEFT:
			if (Cursor->col != 1) {
				Cursor = Cursor->Prev;
			}
			break;
		case KEY_RIGHT:
			if (Cursor->col != WIDTH_CONSOLE) {
				Cursor = Cursor->Next;
			}
			break;
		case ESCAPE:
			DeleteList(Map);
			end = true;
			break;
		case SPACE:
			system("cls");
			Print_to_file(Map);
			DeleteList(Map);
			end = true;
			break;
		}

		if (end) break;
		Cursor->id = MAP;
		PrintNewItem(Map, Cursor);
		if (!enter) {
			if (empty == 1) {
				Cursor->id = EMPTY;
				gotoxy(Cursor->col - 1, Cursor->line - 1);
				std::cout << MAP_symbol;
			}
			else Cursor->id = MAP;
		}
		if (Curr != Cursor) PrintNewItem(Map, Curr);
		enter = false;
		Curr = Cursor;
	}
}

bool OpenMap(char** NameMap, int& Size_Map, bool& end) {//Открываем карты из папки да - есть файлы / нет - пусто
	struct _finddata_t txt_file;
	intptr_t hFile;

	if ((hFile = _findfirst("Map\\*.txt", &txt_file)) == -1L) {
		ms = "Нет доступных карт для игры!";
		gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 3);
		std::cout << ms;
		ms = "Сделайте карту в разделе 'Создать карту'";
		gotoxy((WIDTH_CONSOLE - 1 - ms.length()) / 2, 5);
		std::cout << ms;
		gotoxy(WIDTH_CONSOLE - 1, HIGH_CONSOLE - 1);
		_getch();
		end = true;
		return false;
	}
	else {
		Size_Map = 0;
		do {
			NameMap[Size_Map] = new char[50];
			strcpy_s(NameMap[Size_Map], 50, txt_file.name);
			++Size_Map;

		} while (_findnext(hFile, &txt_file) == 0);
		_findclose(hFile);
		return true;
	}
}

void MoveCloud(T_List* List, T_List*& Cloud, char c) {//Передвижение тучи
	switch (c) {
	case KEY_LEFT://Движение тучи
		if (Cloud->col != 1) {
			Cloud->id = EMPTY;
			PrintNewItem(List, Cloud);
			Cloud = Cloud->Prev;
			Cloud->id = CLOUD;
			PrintNewItem(List, Cloud);
		}
		break;
	case KEY_RIGHT://Движение тучи
		if (Cloud->col != WIDTH_CONSOLE) {
			Cloud->id = EMPTY;
			PrintNewItem(List, Cloud);
			Cloud = Cloud->Next;
			Cloud->id = CLOUD;
			PrintNewItem(List, Cloud);
		}
		break;
	case ENTER://Снежинка высирается
		MoveSnowflake(List, Cloud);//Падение снега
		break;
	}
}

void MoveSnowflake(T_List* List, T_List* Cloud) {//Падение снежинок
	T_List* Curr = 0;
	Curr = FallSnowflake(List, Cloud);
	Curr = LogicSnowflake(List, Curr);
	if (Curr->line != HIGH_CONSOLE) {
		while (GoDown(Curr)->id == EMPTY || CheckDownLeft(Curr) || CheckDownRight(Curr)) {////////
			if (GoDown(Curr)->id == MAP) break;
			Curr = FallSnowflake(List, Curr);
			Curr = LogicSnowflake(List, Curr);
		}
	}
}

T_List* FallSnowflake(T_List* List, T_List* Snow) {//Падение снежинок вниз
	T_List* Curr = GoDown(Snow);
	T_List* Temp = GoDown(Curr);
	if (!Curr->id) {
		if (Snow->line != 1) {
			Snow->id = EMPTY;
			PrintNewItem(List, Snow);
			Sleep(TIME);
		}
		Curr->id = SNOW;
		PrintNewItem(List, Curr);
		Sleep(TIME);
		while ((!Temp->id) || (Temp->line != HIGH_CONSOLE)) {
			if (Temp->id) break;
			Curr->id = EMPTY;
			PrintNewItem(List, Curr);
			Curr = Temp;
			Curr->id = SNOW;
			Temp = GoDown(Temp);
			PrintNewItem(List, Curr);
			Sleep(TIME);
		}
	}
	else {
		return Snow;
	}
	return Curr;
}

T_List* LogicSnowflake(T_List* List, T_List* Snow) {//Логика снежинок
	T_List* Curr = Snow;
	T_List* Temp = Curr;
	srand(time(0));
	int random = rand() % 2;

	if (Curr->Next) {
		if (random) {
			FallRight(List, Curr);
			FallLeft(List, Curr);
		}
		else {
			FallLeft(List, Curr);
			FallRight(List, Curr);
		}
		PrintNewItem(List, Curr);
		Sleep(TIME);
	}
	return Curr;
}

void FallRight(T_List* List, T_List*& Curr) {//Скатывается вправо
	if (Curr->Next->id == EMPTY && CheckDownRight(Curr) && GoDown(Curr)->id == SNOW) {
		if (Curr->line != HIGH_CONSOLE) {
			if (Curr->id != CLOUD) {
				Curr->id = EMPTY;
			}
			PrintNewItem(List, Curr);
			Curr = GoDown(Curr->Next);
			Curr->id = SNOW;
		}
	}
}

void FallLeft(T_List* List, T_List*& Curr) {//Скатывается влево
	if (Curr->Prev->id == EMPTY && CheckDownLeft(Curr) && GoDown(Curr)->id == SNOW) {
		if (Curr->line != HIGH_CONSOLE) {
			if (Curr->id != CLOUD) {
				Curr->id = EMPTY;
			}
			PrintNewItem(List, Curr);
			Curr = GoDown(Curr->Prev);
			Curr->id = SNOW;
		}
	}
}

void PrintMenuPoint(int selected, int N, std::string MenuPoint) {
	gotoxy((WIDTH_CONSOLE - 1 - MenuPoint.length()) / 2, 2 * N + 3);
	if (N == selected) {
		std::cout << MenuPoint << "<--";
	}
	else {
		std::cout << MenuPoint;
	}
}

void PrintMenu(int selected) {
	system("cls");
	PrintMenuPoint(selected, 1, "Играть");
	PrintMenuPoint(selected, 2, "Создать карту");
	PrintMenuPoint(selected, 3, "Предпросмотр карт");
	gotoxy(WIDTH_CONSOLE - 1, HIGH_CONSOLE - 1);
}

T_List* CreateList() {//Создание списка
	T_List* Next = 0, * Beg = 0, * Prev = 0;
	for (int i = 1; i <= WIDTH_CONSOLE * HIGH_CONSOLE; i++) {
		Beg = new T_List;
		Beg->Next = Next;
		if (Beg->Next) {
			Beg->Next->Prev = Beg;
		}
		Next = Beg;
	}
	Beg->Prev = 0;
	T_List* Curr = Beg;
	while (Curr) {
		for (int i = 1; i <= HIGH_CONSOLE; ++i) {
			for (int j = 1; j <= WIDTH_CONSOLE; ++j) {
				Curr->line = i;
				Curr->col = j;
				Curr = Curr->Next;
			}
		}
	}
	return Beg;
}

void DeleteList(T_List*& List) {//Удаление списка
	T_List* Temp;
	while (List) {
		Temp = List->Next;
		delete List;
		List = Temp;
	}
}

void Converting_from_id(T_List* List) {//Конвертация в символ
	T_List* Curr = List;
	while (Curr) {
		switch (Curr->id) {
		case EMPTY:
			Curr->point = EMPTY_symbol;//Пустота
			break;
		case CLOUD:
			Curr->point = CLOUD_symbol;//Туча
			break;
		case SNOW:
			Curr->point = SNOW_symbol;//Снежинка
			break;
		case MAP:
			Curr->point = MAP_symbol;//Карта
			break;
		}
		Curr = Curr->Next;
	}
}

void PrintList(T_List* List) {//Вывод списка
	T_List* Curr = List;
	Converting_from_id(List);
	gotoxy(0, 1);
	while (Curr) {
		if (Curr->line != 1) {
			std::cout << Curr->point;
		}
		if (Curr->col == WIDTH_CONSOLE && Curr->line != HIGH_CONSOLE && Curr->line != 1) {
			std::cout << std::endl;
		}
		Curr = Curr->Next;
	}
}

T_List* GoDown(T_List* Curr) {//Проверка на элемент ниже текущего
	if (Curr->line != HIGH_CONSOLE) {
		for (int i = 0; i < WIDTH_CONSOLE; ++i) {
			Curr = Curr->Next;
		}
	}
	return Curr;
}

T_List* GoUp(T_List* Curr) {//Проверка на элемент выше текущего
	if (Curr->line != 1) {
		for (int i = 0; i < WIDTH_CONSOLE; ++i) {
			Curr = Curr->Prev;
		}
	}
	return Curr;
}

bool CheckDownLeft(T_List* Curr) {//Да - свободно, нет - занято (снизу слева)
	if (Curr->line != HIGH_CONSOLE && Curr->col != 1) {
		if (Curr->Prev->id == EMPTY) {
			Curr = GoDown(Curr->Prev);
			if (Curr->id == EMPTY) {
				return true;
			}
		}
	}
	return false;
}

bool CheckDownRight(T_List* Curr) {//Да - свободно, нет - занято (снизу справа)
	if (Curr->line != HIGH_CONSOLE && Curr->col != WIDTH_CONSOLE) {
		if (Curr->Next->id == EMPTY) {
			Curr = GoDown(Curr->Next);
			if (Curr->id == EMPTY) {
				return true;
			}
		}
	}
	return false;
}

