#include<bits/stdc++.h>
#include<windows.h>
#include <conio.h>

#define width 60
#define height 20
#define max_size 100

using namespace std;

void gotoxy (int x, int y);
void print (int x, int y, char c);

class Tail {
public:
	int x = 0, y = 0;
	int px = 0, py = 0;
	char body = 'o';
	
	void print_tail () {print (x, y, body);}
};

class Fruit {
	int x = 0, y = 0;
	bool flag = false;
public:
	int get_x() {return x;}
	int get_y() {return y;}
	
	void new_fruit ();
	void HideorShow ();
};

class Snake {
	int x, y, speed = 150 , score = 0, len = 0, dir = 0;
	Tail tail[max_size];
	Fruit fruit;
	
	void input ();
	void valid_press (int prev_dir);
	void make_snake ();
	void move_snake ();
	void print_walls ();
	void print_snake ();
	void print_tails ();
	bool check_win ();
	bool check_lose ();
	bool check_fruit ();
	void increase_speed ();
public:
	void execute ();
};

int main () {
	srand (time(NULL));
	Snake snake;
	snake.execute();
	return 0;
}

void gotoxy (int x, int y) {
	static HANDLE h = NULL;
	if (!h) 
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = {x, y};
	SetConsoleCursorPosition(h, c);
}

void print (int x, int y, char c) {
	gotoxy (x, y);
	cout << c;
}

void Snake::input () {
	int prev_dir = dir;
	if (_kbhit ()) {
		switch (_getch ()) {
		case 75:
			dir = 4;
			break;
		case 77:
			dir = 3;
			break;
		case 72:
			dir = 1;
			break;
		case 80:
			dir = 2 ;
			break;
		}
	}
	valid_press(prev_dir);
}

void Snake::valid_press (int prev_dir) {
	if (len != 0)
		if (dir == 4 && prev_dir == 3) dir = 3;
		else if (dir == 1 && prev_dir == 2) dir = 2;
		else if (dir == 3 && prev_dir == 4) dir = 4;
		else if (dir == 2 && prev_dir == 1) dir = 1;
}

void Snake::make_snake()  {
	x = width / 2;
	y = height / 2;
}

void Snake::move_snake()  {
	int prevX = tail[0].x;
	int prevY = tail[0].y;
	int prev2X, prev2Y;
	tail[0].px = tail[0].x;
	tail[0].py = tail[0].y;
	tail[0].x = x;
	tail[0].y = y;
	for (int i = 1; i < len; i++) {
		prev2X = tail[i].x;
		prev2Y = tail[i].y;
		tail[i].px = tail[i].x;
		tail[i].py = tail[i].y;
		tail[i].x = prevX;
		tail[i].y = prevY;
		prevX = prev2X;
		prevY = prev2Y ;
	}
	switch (dir) {
	case 4:
		x--;
		break;
	case 3:
		x++;
		break;
	case 1:
		y--;
		break;
	case 2:
		y++;
		break;
	default:
		break;
	}
}

void Snake::print_walls ()  {
	for (int i = 0; i <= width; i++) cout << "#";
	cout << endl;
	for (int i = 1; i <= height - 1; i++) cout << "#" << endl;
	gotoxy (0, height);
	for (int i = 0; i <= width; i++) cout << "#";
	for (int i = 0; i <= height; i++){
		gotoxy (width, i);
		cout << "#";
	}
}

void Snake::print_snake()  {
	print (tail[0].x, tail[0].y, ' ');
	print (x, y, 'O');
}

void Snake::print_tails() {
	for (int i = 0; i < len; i++) {
		print (tail[i].px, tail[i].py, ' ');
		print (tail[i].x, tail[i].y, tail[i].body);
	}
}

bool Snake::check_win()  {
	if (score == 60) {
		gotoxy (width / 2, height / 2);
		cout << "You Won! Your score is : " << score << endl;
		return true;
	}
	return false;
}

bool Snake::check_fruit ()  {
	if (x == fruit.get_x() && y == fruit.get_y()) {
		fruit.new_fruit();
		len ++;
		score ++;
		increase_speed();
		return true;
	}	
	return false;
}
	
bool Snake::check_lose ()  {
	if (x >= width || y >= height || x <= 0 || y <= 0) return true;
	for (int i = 0; i < len; i++)
		if (x == tail[i].x && y == tail[i].y) return true;
	return false;
}

// Afzayesh sorate mar ba khordane har 5 mive
void Snake::increase_speed () {
	if (score % 5 == 0)
		speed -= 10;
}

void Snake::execute () {
	bool win = false;
	system("cls");
	print_walls();
	make_snake();
	fruit.new_fruit();
	while (!check_lose()) {
		Sleep (speed);
		fruit.HideorShow();
		input();
		move_snake();
		print_snake();
		print_tails();
		check_fruit();
		if (check_win()) return;
	}
	system("cls");
	print_walls ();
	gotoxy (width / 2, height / 2);
	cout << "You Lost! Your score is : " << score << endl;	
}

void Fruit::HideorShow ()  {
	if (flag)
		print (x, y, 'X');
	else 
		print (x, y, ' ');
	flag = !flag;
}

void Fruit::new_fruit () {
	x = rand() % width;
	y = rand() % height;
	if (x == 0) x += 2;
	if (y == 0) y += 2;
}
