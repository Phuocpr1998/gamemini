#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

const int Height = 50;
const int Width = 50;
const int ConsoleHeight = 700;
const int ConsoleWidth = 1000;
const int NumberSlither = 5;
const int NumberItem = 20;
const int maxsize = 100;

enum status { LIE, DIE ,NOT};
enum trangthai { UP, DOWN, LEFT, RIGHT };
enum SH { SHOW, HIDE };
struct slither {
	int _x;
	int _y;
	SH _sh = SHOW;
};

struct statusslither {
	struct slither slither[maxsize];
	status _LD = NOT;
	trangthai _tt = LEFT;
	SH _sh = HIDE;
	int _score = 0;
	int _size = 3;
	int _colorbody;
	int _colorheard;
	int _vitri = 0;
	int _localslither = 0;
};

struct item {
	int _x;
	int _y;
	int _score;
	int _value = 0;
};
struct buffer {
	int _char;
	int _color = 7;
};
struct buffer buffer[Height][Width];
//set color
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//goto XY
void gotoXY(int line, int colum) {
	COORD coord;
	coord.X = colum;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//resize man hinh console
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
// set buffer
void setBuffer(int colum, int line, int _char, int color = 7) {
	if (line >= 0 && colum >= 0) {
		buffer[line][colum]._char = _char;
		buffer[line][colum]._color = color;
	}
}

//ve slither
void drawslither(statusslither slither) {
	for (int i = 1; i < slither._size; i++) {
		setBuffer(slither.slither[i]._x, slither.slither[i]._y, 219, slither._colorbody);
	}
	setBuffer(slither.slither[0]._x, slither.slither[0]._y, 30, slither._colorheard);
}
//ve bay slither
void drawslitherenemy(const statusslither slither[]) {
	for (int i = 0; i < NumberSlither; i++) {
		if (slither[i]._sh == SHOW) {
			for (int j = 1; j < slither[i]._size; j++) {
				if (slither[i].slither[j]._sh == SHOW) {
					setBuffer(slither[i].slither[j]._x, slither[i].slither[j]._y, 219, slither[i]._colorbody);
				}
			}
			if (slither[i].slither[0]._sh == SHOW) {
				setBuffer(slither[i].slither[0]._x, slither[i].slither[0]._y, 30, slither[i]._colorheard);
			}
		}
	}
}
//Tao slitherenemy
void creatslitherenemy(statusslither slitherenemy[], item item[]) {
	bool kt = false;// kiem tra xem co bao nhieu con ran tren man hinh
	for (int k=0;k< NumberSlither;k++){
		if (slitherenemy[k]._sh == HIDE) {
			kt = true;
			break;
		}
	}
	// khi co ran chua xuat hien ms tao
	if (kt) {
		srand((unsigned int)time(NULL));
		int i;
		do {
			i = rand() % NumberSlither;
		} while (slitherenemy[i]._sh == LIE);
		slitherenemy[i]._LD = LIE;
		slitherenemy[i]._sh = SHOW;
		slitherenemy[i]._size = 3;
		slitherenemy[i]._score = 0;
		slitherenemy[i]._colorbody = 238;
		slitherenemy[i]._colorheard = 153;
		for (int j = 0; j < slitherenemy[i]._size; j++) {
			slitherenemy[i].slither[j]._sh = SHOW;
		}
		slitherenemy[i].slither[0]._x = rand() % (Width - 3) + 2;
		slitherenemy[i].slither[0]._y = rand() % (Height - 3) + 2;

		int kc = sqrt(pow(slitherenemy[i].slither[0]._x - item[0]._x, 2.0) + pow(slitherenemy[i].slither[0]._y - item[0]._y, 2.0));
		for (int k = 1; k < NumberItem; k++) {
			if (item[k]._value != 0) {
				if (sqrt(pow(slitherenemy[i].slither[0]._x - item[k]._x, 2.0) + pow(slitherenemy[i].slither[0]._y - item[k]._y, 2.0)) < kc) {
					kc = sqrt(pow(slitherenemy[i].slither[0]._x - item[k]._x, 2.0) + pow(slitherenemy[i].slither[0]._y - item[k]._y, 2.0));
					slitherenemy[i]._vitri = k;
				}
			}
		}
		if (item[slitherenemy[i]._vitri]._x - slitherenemy[i].slither[0]._x < 0) {
			slitherenemy[i]._tt = RIGHT;
		}
		else slitherenemy[i]._tt = LEFT;
	}
}
//xac dinh vi tri
void  local(statusslither slitherenemy[], item item[], int i) {
	// vat pham gan nhat
	int typeitem = 1;// item == 1 la item, item == -1 la slither
	int kc = sqrt(pow(slitherenemy[i].slither[0]._x - item[0]._x, 2.0) + pow(slitherenemy[i].slither[0]._y - item[0]._y, 2.0));
	for (int k = 1; k < NumberItem; k++) {
		if (item[k]._value != 0) {
			if (sqrt(pow(slitherenemy[i].slither[0]._x - item[k]._x, 2.0) + pow(slitherenemy[i].slither[0]._y - item[k]._y, 2.0)) < kc) {
				kc = sqrt(pow(slitherenemy[i].slither[0]._x - item[k]._x, 2.0) + pow(slitherenemy[i].slither[0]._y - item[k]._y, 2.0));
				slitherenemy[i]._vitri = k;
			}
		}
	}
	// eat slither DIE
	for (int k = 0; k < NumberSlither; k++) {
		if (slitherenemy[k]._LD == DIE && slitherenemy[k]._sh == SHOW) {
			slitherenemy[i]._vitri = k;
			typeitem = -1;
			break;
		}
	}
	slitherenemy[i]._localslither = typeitem;
}
//tao vat pham
void creatitem(item item[]) {
	srand((unsigned int)time(0));
	int i;
	do {
		i = rand() % NumberItem;
	} while (item[i]._value != 0);
	item[i]._value = 1;
	item[i]._score = rand() % 5 + 1;
	item[i]._x = rand() % (Width - 3) + 2;
	item[i]._y = rand() % (Height - 3) + 2;
}
//ve item
void drawitem(const item item[]) {
	for (int i = 0; i < NumberItem; i++) {
		if (item[i]._value != 0) {
			int color = 119;
			setBuffer(item[i]._x, item[i]._y, 254, color);
		}
	}
}
//ve map
void drawmap() {
	for (int line = 0; line < Height; line++) {
		for (int colum = 0; colum < Width; colum++) {
			if (line == 0 || line == Height - 1) {
				setBuffer(colum, line, 196, 238);
			}
			else if (colum == 0 || colum == Width - 1) {
				setBuffer(colum, line, 179, 238);
			}
			if (line == 0 && colum == 0) {
				setBuffer(colum, line, 218, 238);
			}
			else if (line == 0 && colum == Width - 1) {
				setBuffer(colum, line, 191, 238);
			}
			else if (line == Height - 1 && colum == 0) {
				setBuffer(colum, line, 192, 238);
			}
			else if (line == Height - 1 && colum == Width - 1) {
				setBuffer(colum, line, 217, 238);
			}
		}
	}
}
//ddieu khien
void control(statusslither &slither, item item[]) {
	for (int i = slither._size - 1; i > 0; i--) {
		slither.slither[i]._x = slither.slither[i - 1]._x;
		slither.slither[i]._y = slither.slither[i - 1]._y;
	}
	if (_kbhit()) {
		int key = getch();
		if (key == 'A' || key == 'a') {
			slither._tt = RIGHT;
		}
		else if (key == 'D' || key == 'd') {
			slither._tt = LEFT;
		}
		else if (key == 'W' || key == 'w') {
			slither._tt = UP;
		}
		else if (key == 'S' || key == 's') {
			slither._tt = DOWN;
		}
	}

	if (slither._tt == LEFT) {
		if (slither.slither[0]._x < Width - 2) {
			slither.slither[0]._x++;
		}
		else slither.slither[0]._x = 1;
	}
	else if (slither._tt == RIGHT) {
		if (slither.slither[0]._x > 1) {
			slither.slither[0]._x--;
		}
		else slither.slither[0]._x = Width - 2;
	}
	else if (slither._tt == UP) {
		if (slither.slither[0]._y > 1) {
			slither.slither[0]._y--;
		}
		else slither.slither[0]._y = Height - 2;
	}
	else if (slither._tt == DOWN) {
		if (slither.slither[0]._y < Height - 2) {
			slither.slither[0]._y++;
		}
		else slither.slither[0]._y = 1;
	}

	for (int i = 0; i < NumberItem; i++) {
		if (item[i]._value != 0) {
			if (slither.slither[0]._x == item[i]._x && slither.slither[0]._y == item[i]._y) {
				slither._score += item[i]._score;
				item[i]._value = 0;
				if (slither._size < maxsize - 1) {
					slither._size += item[i]._score;
				}
				creatitem(item);
			}
		}
	}
}
//dieu khien bay ran
void controlenemyslither(statusslither slither[], item item[]) {
	//xac dinh toa do
	for (int k = 0; k < NumberSlither; k++) {
		if (slither[k]._LD == LIE) {
			if (slither[k]._localslither == 1) {
				if (item[slither[k]._vitri]._value != 0) {
					if (item[slither[k]._vitri]._x - slither[k].slither[0]._x < 0) {
						slither[k]._tt = RIGHT;
					}
					else if (item[slither[k]._vitri]._x - slither[k].slither[0]._x > 0) {
						slither[k]._tt = LEFT;
					}
					else if (item[slither[k]._vitri]._y - slither[k].slither[0]._y < 0) {
						slither[k]._tt = UP;
					}
					else if (item[slither[k]._vitri]._y - slither[k].slither[0]._y > 0) {
						slither[k]._tt = DOWN;
					}
					else {
						item[slither[k]._vitri]._value = 0;
						slither[k]._score += item[slither[k]._vitri]._score;
						for (int j = slither[k]._size; j < slither[k]._size + item[slither[k]._vitri]._score; j++) {
							slither[k].slither[j]._sh = SHOW;
						}
						if (slither[k]._size < maxsize - 1) {
							slither[k]._size += item[slither[k]._vitri]._score;
						}
						creatitem(item);
						local(slither, item, k);
					}
				}
				else local(slither, item, k);
			} 
			else if (slither[k]._localslither == -1) {
				bool ktef = true;
				for (int i = 0; i < slither[slither[k]._vitri]._size; i++) {
					if (slither[slither[k]._vitri].slither[i]._sh == SHOW) {
						if (slither[k].slither[0]._x - slither[slither[k]._vitri].slither[i]._x > 0) {
							slither[k]._tt = RIGHT;
						}
						else if (slither[k].slither[0]._x - slither[slither[k]._vitri].slither[i]._x < 0) {
							slither[k]._tt = LEFT;
						}
						else if (slither[k].slither[0]._y - slither[slither[k]._vitri].slither[i]._y > 0) {
							slither[k]._tt = UP;
						}
						else if (slither[k].slither[0]._y - slither[slither[k]._vitri].slither[i]._y < 0) {
							slither[k]._tt = DOWN;
						}
						ktef = false;
						break;
					}
				}
				if (ktef) local(slither, item, k);
			}
			else local(slither, item, k);
		}
	}
	//di chuyen ran
	for (int k = 0; k < NumberSlither; k++) {
		if (slither[k]._LD == LIE) {
			for (int i = slither[k]._size - 1; i > 0; i--) {
				slither[k].slither[i]._x = slither[k].slither[i - 1]._x;
				slither[k].slither[i]._y = slither[k].slither[i - 1]._y;
			}

			if (slither[k]._tt == LEFT) {
				if (slither[k].slither[0]._x < Width - 2) {
					slither[k].slither[0]._x++;
				}
				else slither[k].slither[0]._x = 1;
			}
			else if (slither[k]._tt == RIGHT) {
				if (slither[k].slither[0]._x > 1) {
					slither[k].slither[0]._x--;
				}
				else slither[k].slither[0]._x = Width - 2;
			}
			else if (slither[k]._tt == UP) {
				if (slither[k].slither[0]._y > 1) {
					slither[k].slither[0]._y--;
				}
				else slither[k].slither[0]._y = Height - 2;
			}
			else if (slither[k]._tt == DOWN) {
				if (slither[k].slither[0]._y < Height - 2) {
					slither[k].slither[0]._y++;
				}
				else slither[k].slither[0]._y = 1;
			}
			//tinh diem
			for (int i = 0; i < NumberItem; i++) {
				if (item[i]._value != 0) {
					if (slither[k].slither[0]._x == item[i]._x &&slither[k].slither[0]._y == item[i]._y) {
						item[i]._value = 0;
						slither[k]._score += item[i]._score;
						for (int j = slither[k]._size; j < slither[k]._size + item[i]._score; j++) {
							slither[k].slither[j]._sh = SHOW;
						}
						if (slither[k]._size < maxsize - 1) {
							slither[k]._size += item[i]._score;
						}
						creatitem(item);
					}
				}
			}
		}
	}
}
// kiem tra
void kiemtraDIELIE(statusslither &slither, statusslither slitherenemy[], item item[]) {
	//kiem tra slither dung nhau
	for (int i = 0; i < NumberSlither; i++) {
		if (slitherenemy[i]._LD == LIE) {
			//slither may dung nhau
			for (int j = 0; j < NumberSlither; j++) {
				bool kt = false;
				if (i != j) {
					if (slitherenemy[j]._LD == LIE) {
						for (int k = 1; k < slitherenemy[j]._size; k++) {
							if (slitherenemy[i].slither[0]._x == slitherenemy[j].slither[k]._x && slitherenemy[i].slither[0]._y == slitherenemy[j].slither[k]._y) {
								slitherenemy[i]._LD = DIE;
								slitherenemy[j]._score += slitherenemy[i]._score;
								slitherenemy[i]._score = 0;
								creatslitherenemy(slitherenemy, item);
								kt = true;
								break;
							}
						}
					}
					else if (slitherenemy[j]._sh == SHOW) {
						bool ktsh = false;
						for (int k = 0; k < slitherenemy[j]._size; k++) {
							if (slitherenemy[i].slither[0]._x == slitherenemy[j].slither[k]._x && slitherenemy[i].slither[0]._y == slitherenemy[j].slither[k]._y && slitherenemy[j].slither[k]._sh == SHOW) {
								slitherenemy[i]._score++;
								for (int j = slitherenemy[i]._size; j < slitherenemy[i]._size + 1; j++) {
									slitherenemy[i].slither[j]._sh = SHOW;
								}
								if (slitherenemy[i]._size < maxsize - 1) {
									slitherenemy[i]._size++;
								}
								slitherenemy[j].slither[k]._sh = HIDE;
							}
						}
						for (int k = 0; k < slitherenemy[j]._size; k++) {
							if (slitherenemy[j].slither[k]._sh == SHOW) {
								ktsh = true;
								break;
							}
						}
						if (ktsh == false) {
							slitherenemy[j]._sh = HIDE;
						}
					}
				}
			if (kt) break;
			}
			//slither nguoi dieu khien
			for (int j = 0; j < slitherenemy[i]._size; j++) {
				if (slither.slither[0]._x == slitherenemy[i].slither[j]._x && slither.slither[0]._y == slitherenemy[i].slither[j]._y) {
					slither._LD = DIE;
				}
			}
			for (int j = 1; j < slither._size; j++) {
				if (slitherenemy[i].slither[0]._x == slither.slither[j]._x && slitherenemy[i].slither[0]._y == slither.slither[j]._y) {
					slitherenemy[i]._LD = DIE;
					slither._score += slitherenemy[i]._score;
					slitherenemy[i]._score = 0;
					creatslitherenemy(slitherenemy, item);
					break;
				}
			}
		}
		else {
			for (int j = 0; j < slitherenemy[i]._size; j++) {
				if (slither.slither[0]._x == slitherenemy[i].slither[j]._x && slither.slither[0]._y == slitherenemy[i].slither[j]._y) {
					slither._score++;
					slitherenemy[i].slither[j]._sh = HIDE;
					if (slither._size < maxsize - 1) {
						slither._size++;
					}
				}
			}
		}
	}
	//Kiem tra LIE or DIE va cho mau
	for (int i = 0; i < NumberSlither; i++) {
		if (slitherenemy[i]._sh == SHOW) {
			if (slitherenemy[i]._LD == DIE) {
				slitherenemy[i]._colorbody = slitherenemy[i]._colorheard = 119;
			}
			else {
				slitherenemy[i]._colorbody = 238;
				slitherenemy[i]._colorheard = 153;
			}
		}
	}
	//khi diem dat muc thi tang ran
	if (slither._score % 100 == 0 && slither._score !=0) {
		creatslitherenemy(slitherenemy, item);
	}
}
// kiem tra attack
void attack(statusslither slither, statusslither slitherenemy[]) {
	for (int i = 0; i < NumberSlither; i++) {
		if (slitherenemy[i]._LD == LIE) {
			bool ne = false;
			int ktkc = 0;  // ktkc == 1 cung hang ktkc ==-1 cung cot

			for (int j = 1; j < slither._size; j++) {
				if (slither.slither[j]._x == slitherenemy[i].slither[0]._x) {
					ktkc = 1;
					if (abs(slither.slither[i]._y - slitherenemy[i].slither[0]._y) < 3 && slitherenemy[i]._score < slither._score) {
						ne = true;
						break;
					}
				}
				else if (slither.slither[i]._y == slitherenemy[i].slither[0]._y) {
					ktkc = -1;
					if (abs(slither.slither[j]._x - slitherenemy[i].slither[0]._x) < 3 && slitherenemy[i]._score < slither._score) {
						ne = true;
						break;
					}
				}
			}

			if (ne) {
				if (ktkc = -1) {
					if (slitherenemy[i]._tt == LEFT) {
						slitherenemy[i]._tt = RIGHT;
					}
					else if (slitherenemy[i]._tt == RIGHT) {
						slitherenemy[i]._tt = LEFT;
					}
				}
				else if (ktkc = 1) {
					if (slitherenemy[i]._tt == UP) {
						slitherenemy[i]._tt = DOWN;
					}
					else if (slitherenemy[i]._tt == DOWN) {
						slitherenemy[i]._tt = UP;
					}
				}
			}

		}
	}
}
//khoi tao gia tri
void khoitao(statusslither &slither, statusslither slitherenemy[], item item[]) {
	slither._size = 3;
	slither._score = 0;
	slither._LD = LIE;
	slither.slither[0]._x = 14;
	slither.slither[0]._y = 5;
	slither._colorbody = 204;
	slither._colorheard = 170;
	creatitem(item);
	resizeConsole(ConsoleWidth, ConsoleHeight);
	for (int i = 0; i < 10; i++) {
		creatitem(item);
	}
	for (int i = 0; i < 2; i++) {
		creatslitherenemy(slitherenemy, item);
	}
	

}
//ve buffer len man hinh
void hienthi(statusslither slither,statusslither slitherenemy[]) {
	for (int line = 0; line < Height; line++) {
		gotoXY(line, 25);
		for (int colum = 0; colum < Width; colum++) {
			setColor(buffer[line][colum]._color);
			putchar(buffer[line][colum]._char);
			buffer[line][colum]._char = ' ';
			buffer[line][colum]._color = 7;
			setColor(7);
		}
	}
	gotoXY(0, 0);
	setColor(203);
	printf("Diem cua ban la: %d", slither._score);
	for (int i = 0; i < NumberSlither; i++) {
		gotoXY(i+1, 0);
		printf("Slither %d : %d ", i, slitherenemy[i]._score);
		if (slitherenemy[i]._LD == LIE) {
			printf("LIE ");
		}
		else if (slitherenemy[i]._LD == DIE) {
			printf("DIE ");
		}
		else if (slitherenemy[i]._LD == NOT) {
			printf("NOT ");
		}
		if (slitherenemy[i]._sh == SHOW) {
			printf("SHOW");
		}
		else if (slitherenemy[i]._sh == HIDE) {
			printf("HIDE");
		}
	}
}
int main()
{
	statusslither slither;
	statusslither slitherenemy[20];
	item item[100];
	khoitao(slither, slitherenemy, item);
	bool gameover = false;
	while (1)
	{
		drawmap();
		drawslither(slither);
		drawslitherenemy(slitherenemy);
		drawitem(item);
		control(slither, item);
		controlenemyslither(slitherenemy, item);
		kiemtraDIELIE(slither, slitherenemy, item);
		attack(slither, slitherenemy);
		hienthi(slither,slitherenemy);
		if (slither._LD == DIE) {
			while (1) {
				gotoXY(NumberSlither, 0);
				setColor(203);
				printf("-----GAMEOVER-----");
				gotoXY(NumberSlither + 1, 0);
				printf("Nhan 'E' de thoat");
				if (_kbhit()) {
					int key = _getch();
					if (key == 'E' || key == 'e') {
						gameover = true;
						break;
					}
				}
			}
		}
		if (gameover) break;
		Sleep(200);
	}
	return 0;
}