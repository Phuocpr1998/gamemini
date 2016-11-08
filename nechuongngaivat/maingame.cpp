#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "console.h"
const int Width=1000;
const int Height=500;
const int cLine = 20;
const int cColum = 25;
struct buffer {
	int _char;
	int _color;
};
struct ToaDo {
	int _x=0;
	int _y=0;
	int _seat=6;
	int _char = 0;
};
struct item {
	int _x = 0;
	int _y = 0;
	int _char = 0;
	int _color = 7;
};
struct he_thong {
	int dem = 0;
	int i = 0;
	int Toc_do = 0;
	int Time_sleep = 0;
	int diem = 0;
	bool gameover = false;
	int level = 0;
};
ToaDo nguoi[5];
struct buffer buffer[20][25];
struct item item[25];
//set buffer
void setbuffer(int line, int colum, int _char, int color = 7) {
	buffer[line][colum]._char = _char;
	buffer[line][colum]._color = color;
}
//setplayer
void setplayer(int line, int colum, int _char, int stt, int color = 7) {
	buffer[line][colum]._char = _char;
	buffer[line][colum]._color = color;
	nguoi[stt]._x = line;
	nguoi[stt]._y = colum;
}
// ve khung
void drawmap() {
	for (int line = 0; line < cLine; line++) {
		for (int colum = 0; colum < cColum; colum++) {
			if (line == 0 && colum == 0) {
				setbuffer(line, colum, 218,14);
			}
			else if (line == 0 && colum == cColum-1) {
				setbuffer(line, colum, 191,14);
			}
			else if (line == cLine-1 && colum == 0) {
				setbuffer(line, colum, 192,14);
			}
			else if (line == cLine-1 && colum == cColum-1) {
				setbuffer(line, colum, 217,14);
			}
			else if (line == 0 || line == cLine - 1 ) {
				setbuffer(line, colum, 196,14);
			}
			else if (colum == 0 || colum ==cColum - 1) {
				setbuffer(line, colum, 179,14);
			}
		}
	}
}
// ve nguoi
void drawplayer(ToaDo &n,int color=7) {
	setplayer(cLine - 4 ,n._seat, 234, 0, color);
	setplayer(cLine - 3, n._seat, 232, 1, color);
	setplayer(cLine - 3, n._seat - 1, 47, 2, color);
	setplayer(cLine - 3, n._seat + 1, 92, 3, color);
	setplayer(cLine - 2, n._seat, 227, 4, color);
	
}
//tao vat the ngau nhien
void creat_item(int stt){
	srand(time(0));
	int randi = 2 + rand() % 22;;
	item[stt]._char = 219;
	item[stt]._x = randi;
	item[stt]._y = 0;
	item[stt]._color = 2 + rand() % 10;
}
//ve vat the
void drawitem() {
	for (int i = 0; i < 25; i++) {
		if (item[i]._char != 0) {
			setbuffer(item[i]._y, item[i]._x, item[i]._char, item[i]._color);
		}
	}
}
//dieu khien nguoi
void control(ToaDo &n,he_thong &h) {
	if (_kbhit()) {
		int key = _getch();
		if ((key == 'a' || key == 'A' )&& n._seat>2) {
			n._seat--;
		}
		else if ((key == 'd' || key == 'D')&& n._seat<cColum-3) {
			n._seat++;
		}
	}
	//tao vat the roi lien tuc
	if (h.i < 25) {
		if (item[h.i]._char == 0 && h.dem == 0) {
			creat_item(h.i);
		}
		h.i++;

	} else h.i = 0;

	//Tao chuyen dong va kiem tra gamover
	for (int j = 0; j < 25; j++) {
		if (item[j]._y < cLine - 2 && item[j]._char != 0) {
			item[j]._y++;
		} else if (item[j]._char != 0) {
			item[j]._char = 0;
			item[j]._color = 7;
			h.diem++;	
			if (h.diem % 5 == 0) {
				h.Toc_do++;
				if (h.level > 0) {
					h.level -= h.Time_sleep;
				}
			}
		}
		//kiem tra toa do cua vat va nguoi neu bang thi gamover
		if (item[j]._char != 0) {
			for (int k = 0; k < 5; k++) {
				if (item[j]._y == nguoi[k]._x && item[j]._x == nguoi[k]._y) {
					h.gameover = true;
					break;
				}
			}
		}
		if (h.gameover == true) break;
	}


	//khoang cach roi giua hai vat the
	if (h.dem == (2* h.Time_sleep + h.level)) {
		h.dem = 0;		
	}
	else h.dem += h.Time_sleep;
}
// hien thi man hinh game
void hienthi(ToaDo n,he_thong h) {
	for (int line = 0; line < cLine; line++) {
		gotoXY(25, line+3);
		for (int colum = 0; colum < cColum; colum++) {
			TextColor(buffer[line][colum]._color);
			putchar(buffer[line][colum]._char);
			setbuffer(line, colum, ' ', 7);
		}
		if (line<cLine) putchar('\n');
	}
	TextColor(10);
	gotoXY(0, 0);
	printf("Diem cua ban la: %d", h.diem);
	gotoXY(0, 3);
	printf("Nhan phim 'A' hoac 'D' \n     de di chuyen");
	TextColor(7);
}
//khoi tao gia tri
void khoitao(he_thong &h) {
	clrscr();
	for (int i = 0; i < 25; i++) {
		item[i]._char = 0;
		item[i]._x = 0;
		item[i]._y = 0;
	}
	h.diem = 0;
	h.Time_sleep = 100;
	h.i = 0;
	h.Toc_do = 1;
	h.gameover = false;
	h.level = 3*h.Time_sleep;
}
int main()
{
	resizeConsole(Width, Height);
	ToaDo nguoi;
	he_thong h;	
loop:
	khoitao(h);
	while (1)
	{

		drawmap();
		drawplayer(nguoi,6);
		drawitem();
		hienthi(nguoi,h);
		control(nguoi,h);
		if (h.gameover == true) {
			TextColor(10);
			gotoXY(26, 10);
			printf("-------GAMEOVER-------\n");
			gotoXY(26, 11);
			printf("-----Choi lai?(y/n)----");
			TextColor(7);
			while (1)
			{
				int k = _getch();
				if (k == 'N' || k == 'n') break;
				else if (k == 'Y' || k == 'y') goto loop;
			}
		}
		if (h.gameover == true) break;
		Sleep(h.Time_sleep);
	}
	return 0;
}