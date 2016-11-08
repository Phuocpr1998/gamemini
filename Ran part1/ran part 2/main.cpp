#include <stdio.h>
#include <time.h>
#include "console.h"
#include <windows.h>
#include <conio.h>
int cot=40, dong=40, cRong = 1000, cDai = 500;
struct moto {
	int kitu;
	int mau;
};
moto buffer[31][31];
enum trangthai{phai,trai,len,xuong};
enum mucdo{de,trungbinh,kho};
struct ToaDo {
	int x, y, xcu, ycu;
	int diem;
	int dem;
	int ttvp;
	bool kt;
	mucdo md;
};
struct ran {
	ToaDo dot[600];
	int chieudai;
	trangthai tt;
};
// ve mot o tren buffer
void vemoto(int dong, int cot,int kitu,int mau=7 ) {
	if (dong >= 0 && cot >= 0 && dong <=40 && dong <=40) {
		buffer[dong][cot].kitu = kitu;
		buffer[dong][cot].mau = mau;
	}
}
// truyen thong so ran vao buffer
void veran(ran r) {
	vemoto(r.dot[0].y, r.dot[0].x, 2, 153);
	for (int i = 1; i < r.chieudai; i++) {
		vemoto(r.dot[i].y, r.dot[i].x, 2,204);
	}
}
// truyen thong so vat pham vao buffer
void vevatpham(ToaDo &vp) {
	srand(time(NULL));
	if (vp.ttvp == 1) {
		vp.xcu=vp.x = rand() % 29+1;
		vp.ycu=vp.y = rand() % 29+1;
		vemoto(vp.y, vp.x,2, 170);
	}
	else
		if (vp.ttvp == 2) vemoto(vp.ycu, vp.xcu,2,170);
		else
			if (vp.ttvp == 3) {
				vp.xcu = vp.x = rand() % 29 + 1;
				vp.ycu = vp.y = rand() % 29 + 1;
				vemoto(vp.y, vp.x, 2, 205);
			} else vemoto(vp.ycu, vp.xcu, 2, 205);
}
// truyen thong so map vao buffer
void vemap() {
	for (int dong = 0; dong <= 30; dong++) {
		for (int cot = 0; cot <= 30; cot++) {
			if (dong ==0  || cot == 0 || dong == 30 || cot == 30) {
				vemoto(dong, cot, 2, 177);
			}
		}
	}
}
// dieu khien ran
void dieukhien(ran &r) {
	for (int i = r.chieudai - 1; i > 0; i--) {
		r.dot[i].x = r.dot[i - 1].x;
		r.dot[i].y = r.dot[i - 1].y;
	}
	if (_kbhit()) {
		int key = _getch();
		if (key == 'A' || key == 'a') {
			r.tt = trai;
		} else if (key == 'D' || key == 'd') {
			r.tt = phai;
		}
		else if(key == 'W' || key == 'w') {
			r.tt = len;
		}
		else if(key == 'S' || key == 's') {
			r.tt = xuong;
		}
	}
	if (r.tt == trai) r.dot[0].x--;
	else if (r.tt == phai) r.dot[0].x++;
	else if(r.tt == len) r.dot[0].y--;
	else if(r.tt == xuong) r.dot[0].y++;
}
//ham tinh so diem
void tinhdiem(ran &r,ToaDo &vp,int &thoigian) {
	if (r.dot[0].x == vp.x && r.dot[0].y == vp.y) {
		if (vp.dem == 5) {
			vp.diem += 5;
			vp.ttvp = 3;
			vp.dem = 0;
			r.chieudai++;
			if (thoigian > 0) {
				thoigian -= 20;
			}
		}
		else {
			vp.ttvp = 1;
			vp.diem++;
			vp.dem++;
			r.chieudai++;
			if (thoigian > 0) {
				thoigian -= 20;
			}
		}
	}
	else if (vp.dem == 5) vp.ttvp = 4;
	else vp.ttvp = 2;
	if (thoigian >= 120) vp.md = de;
	else if (thoigian >= 40) vp.md = trungbinh;
	else vp.md = kho;
}
//kiem tra gameover
void kiemtra(ran r,ToaDo &vp) {
	if (r.dot[0].y == 0 || r.dot[0].x == 0 || r.dot[0].x == 30 || r.dot[0].y == 30) vp.kt = true;
	else {
		for (int i = 1; i < r.chieudai; i++) {
			if (r.dot[0].x == r.dot[i].x && r.dot[0].y == r.dot[i].y) { 
				vp.kt = true;
				break;
			}
		}
	}
}
//dua buffer len man hinh
void HienThi(ran &r, ToaDo &vp) {
	vemap();
	veran(r);
	vevatpham(vp);
	for (int dong = 0; dong <= 30; dong++) {
		gotoXY((80 - cot) / 2, dong);
		for (int cot = 0; cot <= 30; cot++) {
			TextColor(buffer[dong][cot].mau);
			putchar(buffer[dong][cot].kitu);
			buffer[dong][cot].kitu = ' ';
			buffer[dong][cot].mau = 7;
		}
		if (dong < 30) putchar('\n');
	}
	gotoXY(0, 0);
	TextColor(14);
	printf("Diem cua ban:%d", vp.diem);
	//in muc do
	gotoXY(0, 1);
	if (vp.md==de)
		printf("Muc do: De");
	else
		if(vp.md==trungbinh)
			printf("Muc do: Trung Binh");
		else printf("Muc do: Kho         ");

	//in huong dan
	gotoXY(55, 0);
	TextColor(15);
	printf("Huong dan:");
	gotoXY(55, 2);
	printf("Phim 'A' de qua trai");
	gotoXY(55, 3);
	printf("Phim 'D' de qua phai");
	gotoXY(55, 4);
	printf("Phim 'W' de len tren");
	gotoXY(55, 5);
	printf("Phim 'S' de xuong duoi");
	TextColor(7);
}
// khoi tao gia tri ban dau
void khoitao(ran &r,ToaDo &vp) {
	ThayDoiKichThuocMH(cRong, cDai);
	r.dot[0].x = 9;
	r.dot[0].y = 17;
	r.chieudai = 3;
	vp.ttvp = 1;
	r.tt = phai;
	vp.kt = false;
	vp.diem = 0;
	vp.dem = 0;
	vp.md = de;
}
int main()
{
	ran ran;
	int thoigiansleep=200;
	ToaDo vatpham;
	khoitao(ran, vatpham);
	while (1)
	{
		HienThi(ran,vatpham);
		dieukhien(ran);
		tinhdiem(ran, vatpham,thoigiansleep);
		kiemtra(ran, vatpham);
		if (vatpham.kt == true) {
			gotoXY((80 - cot) / 2+5, 12);
			TextColor(9);
			printf("------GAMEOVER------\n");
			gotoXY((80 - cot) / 2 + 5, 13);
			printf("Nhan phim 'E' de thoat");
			TextColor(7);
			break;
		}
		Sleep(thoigiansleep);
	}
	while (1)
	{
		if (_kbhit()) {
			int key = _getch();
			if (key == 'E' || key == 'e')
				break;
		}
	}
	_getch;
}