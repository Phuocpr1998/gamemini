
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "console.h"
#include <time.h>
#include <conio.h>

int const rong = 30;
int const dai = 30;
int const cRong = 1000;
int const cDai = 500;
char map[30][30];
enum trangthai {xuong,len,trai,phai};

struct toaDo {
	int x,y;// x la chieu ngang,y la chieu doc
	int xcu, ycu;
};

struct ran {
	trangthai tt;
	toaDo dot[60];
	int chieuDai;
	int diem, dem;
};
//khoi tao game
void khoitao(ran &r,toaDo &vp) {
	r.chieuDai = 3;
	r.dot[0].x = 30;
	r.dot[0].y = 10;
	r.tt = phai;
	vp.xcu=vp.x = 30;
	vp.ycu=vp.y = 17;
	r.diem = 0;
	r.dem = 0;
}
//ve ran
void veran(ran r) {
	TextColor(153);
	gotoXY(r.dot[0].x,r.dot[0].y);
	printf("*");
	TextColor(204);
	for (int i = 1; i < r.chieuDai; i++) {
		gotoXY(r.dot[i].x, r.dot[i].y);
		printf("*");
	}
	TextColor(7);
}
// dieu khien ran
void DiChuyenRan(ran &r) {
	for (int i = r.chieuDai - 1; i > 0; i--) {
		r.dot[i].x = r.dot[i - 1].x;
		r.dot[i].y = r.dot[i - 1].y;
	}
	if (_kbhit()) {
		int key = _getch();
		//Nhan dieu khien
		if (key == 'A' || key == 'a') {
			r.tt = trai;
		}
		else if (key == 'D' || key == 'd') {
			r.tt = phai;
		}
		else if (key == 'W' || key == 'w') {
			r.tt = len;
		}
		else if (key == 'S' || key == 's') {
			r.tt = xuong;
		}
	}
	//Dieu khien
	if (r.tt == trai) {
		r.dot[0].x--;
	}
	else if (r.tt == phai) {
		r.dot[0].x++;
	}
	else if (r.tt == len) {
		r.dot[0].y--;
	}
	else if (r.tt == xuong) {
		r.dot[0].y++;
	}
}
// khoi tao vat pham
void taovatpham(toaDo &vp, int trangthai) {

	if (trangthai == 1) {
		vp.xcu = vp.x = rand() % 27 + 27;//rand()%(b-a+1)+a lấy giá trị ngẫu nhiên từ a-->b
		vp.ycu = vp.y = rand() % 27 + 1;
		gotoXY(vp.x, vp.y);
		TextColor(170);
		printf("@");
		TextColor(7);
	}
	else if (trangthai == 2) {
		gotoXY(vp.xcu, vp.ycu);
		TextColor(170);
		printf("@");
		TextColor(7);
	}
	else if (trangthai == 3) {
		vp.xcu = vp.x = rand() % 27 + 27;//rand()%(b-a+1)+a lấy giá trị ngẫu nhiên từ a-->b
		vp.ycu = vp.y = rand() % 27 + 1;
		gotoXY(vp.x, vp.y);
		TextColor(204);
		printf("@");
		TextColor(7);
	}
	else if (trangthai == 4) {
		gotoXY(vp.xcu, vp.ycu);
		TextColor(204);
		printf("@");
		TextColor(7);
	}
}
//khoi tao ban do
void taomap() 
{
	for (int i = 0; i < rong; i++) {
		for (int j = 0; j < dai; j++) {
			if ((i == 0) || (j == 0) || (i == (rong - 1)) || (j == (dai - 1))) { 
				map[i][j] = '0';
			}
			else map[i][j] = ' ';
		}
	}
}
//ve ban do ra man hinh
void vemap(int manchoi,int diem) {
	ThayDoiKichThuocMH(cRong, cDai);
	for (int i = 0; i < rong; i++) {
		gotoXY((80-rong)/2, i);
		for (int j = 0; j < dai; j++) {
			if ((i == 0) || (j == 0) || (i == (rong - 1)) || (j == (dai - 1))) {
				TextColor(238);
				printf("%c", map[i][j]);
				TextColor(7);
			}
			else printf("%c", map[i][j]);
		}
		printf("\n");
	}
	TextColor(12);
	gotoXY(0, 0);
	printf("Man choi:%d", manchoi);
	gotoXY(0, 1);
	printf("Diem cua ban:%d", diem);
	TextColor(7);
	
}
// kiem tra gia tri game
int kiemtra(ran r) {
		int ktt;
		if  ( r.dot[0].x == (80 - rong) / 2 +1 || r.dot[0].y == 0 || r.dot[0].y == rong - 2 || r.dot[0].x == ((80 - rong) / 2) + 29) {
			ktt= 1;
		}
		else ktt = 0; 	
		for (int i = 1; i < r.chieuDai; i++) {
				if (r.dot[0].x == r.dot[i].x && r.dot[0].y == r.dot[i].y) {
					ktt= 1;
					break;
				}
			}
		return ktt;
	
}
// tinh diem
void tinhdiem(ran &r, toaDo &vp,int &thoigian) {
	if (r.dot[0].x == vp.x && r.dot[0].y == vp.y) {
		if (r.dem == 5) {
			r.diem += 5;
			taovatpham(vp, 3);
			r.dem = 0;
			r.chieuDai++;
			if (thoigian > 30) {
				thoigian -= 20;
			}
		}
		else {
			taovatpham(vp, 1);
			r.dem++;
			r.diem++;
			r.chieuDai++;
			if (thoigian > 30) {
				thoigian -= 20;
			}
		}
	}
	else {
		if (r.diem == 5) {
			taovatpham(vp, 4);
		}
		else taovatpham(vp, 2);
	}
}
int main()
{
	ran ran;
	toaDo vatpham;
	khoitao(ran,vatpham);
	int kt = 0;
	int thoigiansleep = 200;
	while (1) {
		srand(time(NULL));
		clrscr(); 
		taomap();
		vemap(1, ran.diem);
		kt = kiemtra(ran);
		veran(ran);
		//tinh diem 
		tinhdiem(ran, vatpham,thoigiansleep);
		if (kt==1) {
			gotoXY(0, 4);
			TextColor(9);
			printf("GAMEOVER");
			TextColor(7);
			break;
		};
		DiChuyenRan(ran);
		Sleep(thoigiansleep);
	}
	_getch();
	return 0;
} 