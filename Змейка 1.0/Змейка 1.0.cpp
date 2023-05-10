
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
int main()
{
	srand(time(0));
	system("mode con cols=51 lines=31");
	MoveWindow(GetConsoleWindow(), 150, 150, 520, 535, true);
	const int width = 60, height = 30;
	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false }; //Убирает курсор поля ввода 
	SetConsoleCursorInfo(h, &cci);//Убирает курсор поля ввода 
	bool flag= true;
	int  sleep_time = 100;
	int dx = 1, dy = 0;
	const int max_lenght = 50;
	int length = 1;
	int snake_X[max_lenght];
	int snake_Y[max_lenght];
	char head = 1;
	char snake = '*';
	snake_X[0] = width / 2;
	snake_Y[0] = height / 2;
	int X_apple;
	int Y_apple;
	char apple = 'o';
	do {
		X_apple = rand() % (width - 2) + 1;
		Y_apple = rand() % (height - 2) + 1;
	} while (X_apple != snake_X[length - 1] && Y_apple != snake_Y[length - 1]);

	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			char s;
			if (x == 0 && y == 0) {
				s = 218;
			}
			else if (x == 0 && y == height - 1) {
				s = 192;
			}
			else if (y == 0 && x == width - 1) {
				s = 191;
			}
			else if (y == height - 1 && x == width - 1) {
				s = 217;
			}
			else if (y == 0 || y == height - 1) {
				s = 196;
			}
			else if (x == 0 || x == width - 1) {
				s = 179;
			}
			else s = ' ';
			putchar(s);
		}
		cout << endl;
	}
	c.X = X_apple;
	c.Y = Y_apple;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 14); //Желтый 
	putchar(apple);
	c.X = snake_X[0];
	c.Y = snake_Y[0];
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 10);//Зеленый
	putchar(head);
	do {
		Sleep(sleep_time);

		if (_kbhit()) {
			int k = _getch();
			if (k == 0 || k == 224) {
				k = _getch();
			}
			switch (k) {
				case 80: if (dy == -1) break;
					dy = 1; dx = 0; break; //клавиша вниз
				case 72: if (dy == 1) break;
					dy = -1; dx = 0; break; //клавиша вверх
				case 75: if (dx == 1) break;
					dy = 0; dx = -1; break; //клавиша влево
				case 77: if (dx == -1) break;
					dy = 0; dx = 1; break; //клавиша вправо
				case 27: 
					flag = false; break; //клавиша ESC
			}
		}
		int X = snake_X[length - 1] + dx;
		int Y = snake_Y[length - 1] + dy;
		if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) {
			flag = false;
		}
		else if (X == X_apple && Y == Y_apple) {
			c.X = snake_X[length - 1];
			c.Y = snake_Y[length - 1];
			SetConsoleCursorPosition(h, c);
			putchar(snake);
			length++;
			c.X = snake_X[length - 1] = X;
			c.Y = snake_Y[length - 1] = Y;
			SetConsoleCursorPosition(h, c);
			putchar(head);

			if (length == max_lenght)
				break;


			int i;

			do {
				X_apple = rand() % (width - 2) + 1;
				Y_apple = rand() % (height - 2) + 1;
				i = 0;
				for (; i < length; i++) {
					if (X_apple == snake_X[i] && Y_apple == snake_Y[i])
						break;
				}
			} while (i < length);
			c.X = X_apple;
			c.Y = Y_apple;
			SetConsoleCursorPosition(h, c);
			SetConsoleTextAttribute(h, 14);
			putchar(apple);
			SetConsoleTextAttribute(h, 10);

		}
		else {
			//c.X = X_apple;
			//c.Y = Y_apple;
			//SetConsoleCursorPosition(h, c);
			//SetConsoleTextAttribute(h, 14);
			//putchar(apple);
			//SetConsoleTextAttribute(h, 10);
			int i = 1;
			for (; i < length; i++) {
				if (X == snake_X[i] && Y == snake_Y[i])
					break;
			}
			if (i < length)
				break;

			c.X = snake_X[0];
			c.Y = snake_Y[0];
			SetConsoleCursorPosition(h, c);
			putchar(' ');

			if (length > 1)
			{
				c.X = snake_X[length - 1];
				c.Y = snake_Y[length - 1];
				SetConsoleCursorPosition(h, c);
				putchar(snake);
			}

			for (int i = 0; i < length - 1; i++) {
				snake_X[i] = snake_X[i + 1];
				snake_Y[i] = snake_Y[i + 1];
			}

			c.X = snake_X[length - 1] = X;
			c.Y = snake_Y[length - 1] = Y;
			SetConsoleCursorPosition(h, c);
			putchar(head);
		}
		
		
	} while (flag);
	system("cls");//очистка консоли
	cout << "Game over\n";
	system("pause");
}

 