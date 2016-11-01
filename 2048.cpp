#include <iostream>
#include "console.h"
#include <time.h>
#include <windows.h>
#include <conio.h>


const int cDong = 20;
const int cCot = 36;
const int daiMap = 4;
const int rongMap = 4;

enum trangthai{phai, trai, len, xuong,Null};
struct moto {
	int _kitu;
	int _mamau;
	int _giatri;
};
moto buffer[cDong][cCot];
struct ToaDo {
	int _x ;
	int _y;
	unsigned int _giatri;
	trangthai _tt=Null;
	trangthai _ttcu=Null;
};
ToaDo giatri[4][4];
struct TinhDiem {
	int _diem;
	int _ktrandom;
	bool _ktgame;
	bool _ktgameover;
	bool _ktloop;
	bool _ktdc;
};
// set map
void setbuffer(int dong, int cot, int kitu, int mau = 7) {

		buffer[dong][cot]._kitu = kitu;
		buffer[dong][cot]._mamau = mau;
}
//can giua va dua du lieu vao map
void setvalue(int dong, int cot,int giatri,int mau=7) {
	//can giua
	if (giatri < 10) {
		buffer[dong][cot]._giatri = giatri;
		buffer[dong][cot]._mamau = mau;
	}
	else if (giatri < 100) {
		setvalue(dong, cot, giatri / 10,mau);
		setvalue(dong, cot + 1, giatri % 10,mau);
	}
	else if (giatri < 1000) {
		setvalue(dong, cot, giatri / 100,mau);
		setvalue(dong, cot + 1, giatri % 100,mau);
	}
	else if (giatri < 10000) {
		setvalue(dong, cot, giatri / 1000,mau);
		setvalue(dong, cot + 1, giatri % 1000,mau);
	} 
}
//ve tung o trong ban do
void vemoto(int odong, int ocot ,int giatri,int mamau,int mamaugt=7) {
	int dongConsole = odong * 5;
	int cotConsole = ocot * 9;
	for (int dong =dongConsole;dong<dongConsole +5;dong++)
		for (int cot = cotConsole; cot < cotConsole + 9; cot++) {
			setbuffer(dong, cot, ' ', mamau);
		}
	if (giatri > 0) {
		if (giatri < 100)
			setvalue(dongConsole + 2, cotConsole + 4, giatri, mamaugt);
		else if (giatri < 10000)
			setvalue(dongConsole + 2, cotConsole + 3, giatri, mamaugt);
		else if (giatri < 100000)
			setvalue(dongConsole + 2, cotConsole + 2, giatri, mamaugt);
	}
}
//ve map len buffer
void paintmap(){
	for (int idong=0;idong<4;idong++)
		for (int icot = 0; icot < 4; icot++) {
			if (giatri[idong][icot]._giatri == 0) {
				vemoto(idong, icot, 0, 16, 3);
			}
			else {
				switch (giatri[idong][icot]._giatri)
				{
				case 2:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 119, 124);
					break;
				case 4:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 102, 110);
					break;
				case 8:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 136, 139);
					break; 
				case 16:
						vemoto(idong, icot, giatri[idong][icot]._giatri, 187, 172);
						break;
				case 32:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 238, 236);
					break;
				case 64:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 68, 75);
					break;
				case 128:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 85, 90);
					break;
				case 256:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 51, 59);
					break;
				case 512:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 119, 122);
					break;
				case 1024:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 102, 108);
					break;
				case 2048:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 126, 138);
					break;
				case 4096:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 187, 174);
					break;
				case 8192:
					vemoto(idong, icot, giatri[idong][icot]._giatri, 238, 228);
					break;
				}
			}
		}
}
//tao so ngau nhien va kiem tra ket thuc gam
void random(TinhDiem &d) {
	srand(time(0));
	int dong, cot;
	d._ktrandom = 0;
	while (d._ktrandom == 0)
	{
		dong = rand() % 4;// a + rand() % (b – a + 1)
		cot = rand() % 4;// a + rand() % (b – a + 1)
		if (giatri[dong][cot]._giatri == 0) {
			d._ktrandom = 1;
			break;
		}
	}
	if (d._ktrandom == 1) {
		giatri[dong][cot]._giatri = 2;
	}
	d._ktgame = true;
	for (int dong =0;dong<4;dong++)
		for (int cot = 0; cot < 4; cot++) 
			if (giatri[dong][cot]._giatri == 0) {
				d._ktgame = false;
				break;
			}
	if (d._ktgame == true) {
		d._ktgameover = true;
		for (int dong=0;dong<4;dong ++)
			for (int cot = 0; cot < 4; cot++) {
				if (dong == 0 && cot == 0) {
					if (giatri[dong][cot]._giatri == giatri[dong + 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot + 1]._giatri) d._ktgameover = false;
				} 
				else if (dong == 0 && cot == 3) {
					if (giatri[dong][cot]._giatri == giatri[dong + 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot - 1]._giatri) d._ktgameover = false;
				}
				else if (dong == 3 && cot == 0) {
					if (giatri[dong][cot]._giatri == giatri[dong - 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot+1]._giatri) d._ktgameover = false;
				}
				else if (dong == 3 && cot == 3) {
					if (giatri[dong][cot]._giatri == giatri[dong - 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot - 1]._giatri) d._ktgameover = false;
				}
				else if (dong == 0) {
					if (giatri[dong][cot]._giatri == giatri[dong + 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot + 1]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot - 1]._giatri) d._ktgameover = false;
				}
				else if (dong == 3) {
					if (giatri[dong][cot]._giatri == giatri[dong - 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot + 1]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot - 1]._giatri) d._ktgameover = false;
				}
				else if (cot == 0) {
					if (giatri[dong][cot]._giatri == giatri[dong + 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot + 1]._giatri || giatri[dong][cot]._giatri == giatri[dong-1][cot]._giatri) d._ktgameover = false;
				}
				else if (cot == 3) {
					if (giatri[dong][cot]._giatri == giatri[dong + 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot - 1]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot - 1]._giatri) d._ktgameover = false;
				}
				else 
					if (giatri[dong][cot]._giatri == giatri[dong + 1][cot]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot + 1]._giatri || giatri[dong][cot]._giatri == giatri[dong][cot - 1]._giatri|| giatri[dong][cot]._giatri == giatri[dong-1][cot]._giatri) d._ktgameover = false;
			}

	}
}
//dieu khien cong don va tinh diem
void control(ToaDo &c, TinhDiem &d) {
	if (_kbhit()) {
		int key = _getch();
		if (key == 'W' || key == 'w') c._tt = len;
		else if (key == 'S' || key == 's') c._tt = xuong;
		else if (key == 'A' || key == 'a') c._tt = trai;
		else if (key == 'D' || key == 'd') c._tt = phai;
		// cong don
		if (c._tt == xuong) {
			d._ktdc = false;
			for (int cot=0;cot <4;cot++){
				d._ktloop = true;
				for (int dong = 3; dong >= 0; dong--) {
					if ( giatri[dong][cot]._giatri != 0 && d._ktloop==true) {
						for (int idong = dong - 1; idong >= 0; idong--) {
							if (giatri[idong][cot]._giatri != 0) {
								if (giatri[idong][cot]._giatri == giatri[dong][cot]._giatri) {
									giatri[dong][cot]._giatri *= 2;
									giatri[idong][cot]._giatri = 0;
									d._ktloop = false;
									d._diem += 20;
									d._ktdc = true;
									break;
								}
								else break;
							}
						}
					}
				}
				for(int dong=3;dong>=0;dong--)
					if(giatri[dong][cot]._giatri==0)
						for (int idong = dong-1; idong >= 0; idong--) 
							if (giatri[idong][cot]._giatri != 0) {
								giatri[dong][cot]._giatri = giatri[idong][cot]._giatri;
								giatri[idong][cot]._giatri = 0;
								d._ktdc = true;
								break;
							}
			}
			if (d._ktdc==true) random(d);
		}

		else
			if (c._tt == len) {
				d._ktdc = false;
				for (int cot = 0; cot <4; cot++) {
					d._ktloop = true;
					for (int dong = 0; dong <4 ; dong++) {
						if (giatri[dong][cot]._giatri != 0 && d._ktloop == true) {
							for (int idong = dong + 1; idong <4 ; idong++) {
								if (giatri[idong][cot]._giatri != 0) {
									if (giatri[idong][cot]._giatri == giatri[dong][cot]._giatri) {
										giatri[dong][cot]._giatri *= 2;
										giatri[idong][cot]._giatri = 0;
										d._ktloop = false;
										d._diem += 20;
										d._ktdc = true;
										break;
									}
									else break;
								}
							}
						}
					}
					for (int dong = 0; dong < 4; dong++)
						if (giatri[dong][cot]._giatri == 0)
							for (int idong = dong + 1; idong <4 ; idong++)
								if (giatri[idong][cot]._giatri != 0) {
									giatri[dong][cot]._giatri = giatri[idong][cot]._giatri;
									giatri[idong][cot]._giatri = 0;
									d._ktdc = true;
									break;
								}
				}
				if (d._ktdc==true) random(d);
			}

			else
				if (c._tt == phai) {
					d._ktdc = false;
					for (int dong = 0; dong <4; dong++) {
						d._ktloop = true;
						for (int cot = 3; cot >= 0; cot--) {
							if (giatri[dong][cot]._giatri != 0 && d._ktloop == true) {
								for (int icot = cot - 1; icot >= 0; icot--) {
									if (giatri[dong][icot]._giatri != 0) {
										if (giatri[dong][icot]._giatri == giatri[dong][cot]._giatri) {
											giatri[dong][cot]._giatri *= 2;
											giatri[dong][icot]._giatri = 0;
											d._ktloop = false;
											d._diem += 20;
											d._ktdc = true;
											break;
										}
										else break;
									}
								}
							}
						}
						for (int cot = 3; cot >= 0; cot--)
							if (giatri[dong][cot]._giatri == 0)
								for (int icot = cot - 1; icot >= 0; icot--)
									if (giatri[dong][icot]._giatri != 0) {
										giatri[dong][cot]._giatri = giatri[dong][icot]._giatri;
										giatri[dong][icot]._giatri = 0;
										d._ktdc = true;
										break;
									}
					}
					if (d._ktdc==true) random(d);
				}
				else
					if (c._tt == trai) {
						d._ktdc = false;
						for (int dong = 0; dong <4; dong++) {
							d._ktloop = true;
							for (int cot = 0; cot < 4; cot++) {
								if (giatri[dong][cot]._giatri != 0 && d._ktloop == true) {
									for (int icot = cot + 1; icot  <4; icot++) {
										if (giatri[dong][icot]._giatri != 0) {
											if (giatri[dong][icot]._giatri == giatri[dong][cot]._giatri) {
												giatri[dong][cot]._giatri *= 2;
												giatri[dong][icot]._giatri = 0;
												d._ktloop = false;
												d._diem += 20;
												d._ktdc = true;
												break;
											}
											else break;
										}
									}
								}
							}
							for (int cot = 0; cot <4 ; cot++)
								if (giatri[dong][cot]._giatri == 0)
									for (int icot = cot + 1; icot < 4; icot++)
										if (giatri[dong][icot]._giatri != 0) {
											giatri[dong][cot]._giatri = giatri[dong][icot]._giatri;
											giatri[dong][icot]._giatri = 0;
											d._ktdc = true;
											break;
										}
						}
						if (d._ktdc==true) random(d);
					}
	}
	else c._tt = Null;
	
	
}
//ve buffer len Console
void paintbuffer(TinhDiem d) {
	for (int dong = 0; dong < cDong; dong++) {
		gotoXY(30,dong+2);
		for (int cot = 0; cot < cCot; cot++) {
			if (buffer[dong][cot]._giatri != 0) {
				TextColor(buffer[dong][cot]._mamau);
				printf("%d", buffer[dong][cot]._giatri);
				buffer[dong][cot]._giatri = 0;
			}
			else {
				TextColor(buffer[dong][cot]._mamau);
				putchar(buffer[dong][cot]._kitu);
				buffer[dong][cot]._kitu = ' ';
				buffer[dong][cot]._mamau = 7;
			}
		}
		if (dong<cDong) putchar('\n');
	}
	TextColor(6);
	gotoXY(0, 0);
	printf("Diem cua ban la: %d", d._diem);
}
//set value ban dau
void khoitao(ToaDo &c,TinhDiem &d) {
	for (int dong = 0; dong < 4; dong++)
		for (int cot = 0; cot < 4; cot++)
			giatri[dong][cot]._giatri = 0;
	random(d);
	random(d);
	d._diem = 0;
	resizeConsole(1000, 500);
}
int main()
{
	ToaDo m;
	TinhDiem diem;
	khoitao(m, diem);
	while (1)
	{
		paintmap();
		paintbuffer(diem);
		control(m, diem);
		if (diem._ktgameover == true) {
			gotoXY(0, 1);
			printf("Gameover");
		}
		Sleep(200);
	}
	return 0;
}