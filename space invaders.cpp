#include "mygraphics.h"
#include <time.h>
#include <stdio.h>
#include <cstdlib>


void alien_move(int x[],int y[],int alienhorde,int pos,int t[]) {
	for (int i = 0; i < alienhorde ; ++i) {
		if (x[i] != -110) {
			//alien 1
			if (t[i] == 1) {
				drawEllipse(x[i], y[i] + pos, x[i] + 20, (y[i] + 20) + pos, 20, 20, 25, 20, 20, 25);
				drawEllipse(x[i] + 5, (y[i] + 5) + pos, x[i] + 15, (y[i] + 15) + pos, 20, 20, 25, 20, 20, 25);
			}
			//alien 2
			else {
				drawEllipse(x[i], y[i] + pos, x[i] + 20, (y[i] + 20) + pos, 20, 20, 25, 20, 20, 25);
				drawRectangle(x[i] + 5, (y[i] + 20) + pos, x[i] + 15, (y[i] + 30) + pos, 20, 20, 25, 20, 20, 25);
			}
		}
	}
}

void create_aliens(int alienhorde,int x[],int y[],int pos,int t[]) {
	for (int i = 0; i < alienhorde; ++i) {
		if (x[i] != 0) {
			if (t[i] == 1) {
				drawEllipse(x[i], y[i] + pos, x[i] + 20, (y[i] + 20) + pos, 128, 0, 0, 128, 0, 0);
				drawEllipse(x[i] + 5, (y[i] + 5) + pos, x[i] + 15, (y[i] + 15) + pos, 0, 0, 0, 0, 0, 0);
			}
			else {
				drawEllipse(x[i], y[i] + pos, x[i] + 20, (y[i] + 20) + pos, 0, 0, 125, 0, 0, 125);
				drawRectangle(x[i] + 5, (y[i] + 20) + pos, x[i] + 15, (y[i] + 30) + pos, 20, 120, 125, 20, 120, 125);
			}
		}
	}
}

void alien_dead(int x,int y,int pos,int t) {
	if (t == 1) {
		drawEllipse(x, y + pos, x + 20, (y + 20) + pos, 20, 20, 25, 20, 20, 25);
		drawEllipse(x + 5, (y + 5) + pos, x + 15, (y + 15) + pos, 20, 20, 25, 20, 20, 25);
	}
	else {
		drawRectangle(x, y + pos, x + 50, ((y + 20) + pos)+20, 20, 20, 25, 20, 20, 25);
	}
}

bool lost(int y[],int horde,int pos,int x[]) {
	for (int i = 0; i < horde; ++i) {
		if ((y[i]+pos) >= 659 && x[i]!=0 && y[i]!=100) {
			y[i] = 100;
			return true;
		}
	}
	return false;
}
 
bool horde_passed(int y[],int horde,int pos) {
	int pass = 0;
	for (int i = 0; i < horde; ++i) {
		if ((y[i] + pos) >= 659 ) {
			pass++;
		}
	}
	if (pass == horde)
		return true;
	else
	{
		return false;
	}
}

int main() {
	begin:;
	// Initialising
	srand(time(0));
	int w = 0, h = 0;
	getWindowDimensions(w, h);
	cls();
	showConsoleCursor(false);
	w += 100;
	h += 100;
	int border = 1200;
	int alien_horde = 10;
	drawRectangle(0, 0, w+1000, h+1000, 20, 20, 25, 20, 20, 25);
	drawLine(1200, 0, 1200, 300, 250);
	drawLine(1200, 300, 1400, 300, 250);
	drawRectangle(1230, 30, 1250, 40, 0, 128, 0, 0, 128, 0);
	drawRectangle(1220, 40, 1260, 50, 0, 128, 0, 0, 128, 0);
	drawRectangle(1230, 90, 1250, 100, 0, 128, 0, 0, 128, 0);
	drawRectangle(1220, 100, 1260, 110, 0, 128, 0, 0, 128, 0);
	drawRectangle(1230, 150, 1250, 160, 0, 128, 0, 0, 128, 0);
	drawRectangle(1220, 160, 1260, 170, 0, 128, 0, 0, 128, 0);
	// main event loop
	int score = 0;
	int lives=3;
	int yi = 659;
	int ball_c = 0;
	int i = 0;
	int c = 0;
start:;
	int j = 0;
	int deadcounter = 0;
	int pos = 0;
	int* alien_shooter = new int[alien_horde];
	for (int a = 0; a < alien_horde; ++a) {
		alien_shooter[a] = 0;
	}
	bool hit = false;
	bool fired = false;
	int* type = new int[alien_horde];
	for (int a = 0; a < alien_horde; ++a) {
		type[a] = rand() % 2 + 1;
	}
	int* alien_x = new int[alien_horde];
	int* alien_y = new int[alien_horde];
	for (int a = 0; a < alien_horde; ++a) {
		alien_x[a] = rand() % 1100 + 20;
		alien_y[a] = rand() % 100 + 1;
	}
	while (true) {
		hit = false;
		//player
		drawRectangle(i+((w / 2) - 10), 660,i+ ((w / 2) + 10), 680, 0, 128, 0, 0, 128, 0);
		drawRectangle(i+((w / 2) - 50), 680, i+((w / 2) + 50), 700, 0, 128, 0, 0, 128, 0);
		//alien1
		create_aliens(alien_horde, alien_x, alien_y, pos,type);
		if (GetKeyState(VK_SPACE) & 0x8000) {
			ball_c = 0;
			int x = i + ((w / 2) - 10);
			int yi = 650;
			while (yi > 0 && hit==false) {
				drawEllipse(x + 5, 650 - ball_c, x + 15, 659 - ball_c, 240, 240, 240, 240, 240, 240);
				delay(12);
				drawEllipse(x + 5, 650 - ball_c, x + 15, 659 - ball_c, 20, 20, 25, 20, 20, 25);
				ball_c += 8;
				yi = 654 - ball_c;
				for (int a = 0; a < alien_horde; ++a) {
					if (x + 5 >= (alien_x[a]) && x + 5 <= (alien_x[a] + 20) && yi <= alien_y[a]+pos || x + 15 >= (alien_x[a]) && x + 15 <= (alien_x[a] + 20) && yi <= alien_y[a]+pos){ 
						drawEllipse(x + 5, 650 - ball_c, x + 15, 659 - ball_c, 20, 20, 25, 20, 20, 25);
						alien_dead(alien_x[a], alien_y[a], pos, type[a]);
						alien_x[a] = 0;
						deadcounter++;
						score += 10;
						hit = true;
						break;
					}
				}
			}
		}
		for (int a = 0; a < alien_horde; ++a) {
			if (alien_shooter[a] == 1) {
				drawEllipse(alien_x[a] + 8, (alien_y[a] + 32) + pos + j, alien_x[a] + 12, (alien_y[a] + 35) + pos + j, 240, 240, 240, 240, 240, 240);
			}
		}
		for (int a = 0; a < alien_horde; ++a) {
			if (type[a] != 1) {
				if (alien_x[a] >= i + ((w / 2) - 50) && i + ((w / 2) + 50)) {
					alien_shooter[a] = 1;
					drawEllipse(alien_x[a] + 8, (alien_y[a] + 32) + pos + j, alien_x[a] + 12, (alien_y[a] + 35) + pos + j, 240, 240, 240, 240, 240, 240);
					if ((alien_y[a] + 35) + pos + j >= 660 && (alien_y[a] + 35) + pos + j <= 690 && alien_x[a] + 12 >= i + ((w / 2) - 50) && alien_x[a] + 12 <= i + ((w / 2) + 50)) {
						goto dead;
					}
				}
			}
		} 
		//time delay
		delay(40);
		//alien animation
		for (int a = 0; a < alien_horde; ++a) {
			if (alien_shooter[a] == 1) {
				drawEllipse(alien_x[a] + 8, (alien_y[a] + 32) + pos + j, alien_x[a] + 12, (alien_y[a] + 35) + pos + j, 20, 20, 25, 20, 20, 25);
			}
		} 
		j+=3;
		alien_move(alien_x, alien_y, alien_horde, pos,type);
		pos += 3;
		//presses right
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			if ((i + ((w / 2) - 10)) <= border) {
				drawRectangle(i + ((w / 2) - 10), 660, i + ((w / 2) + 10), 680, 20, 20, 25, 20, 20, 25);
				drawRectangle(i + ((w / 2) - 50), 680, i + ((w / 2) + 50), 700, 20, 20, 25, 20, 20, 25);
				i += 20;
			}
		} 
		//presses left key 
		if (GetKeyState(VK_LEFT) & 0x8000) {
			if ((i + ((w / 2) - 10)) >= 10) {
				drawRectangle(i + ((w / 2) - 10), 660, i + ((w / 2) + 10), 680, 20, 20, 25, 20, 20, 25);
				drawRectangle(i + ((w / 2) - 50), 680, i + ((w / 2) + 50), 700, 20, 20, 25, 20, 20, 25);
				i -= 20;
			}
		}  
		if (lost(alien_y, alien_horde,pos,alien_x) == true) {
		dead:;
			--lives;
			if (lives == 2)
				drawRectangle(1210, 20, 1260, 60, 20, 20, 25, 20, 20, 25);
			else if(lives==1)
				drawRectangle(1210, 70, 1260, 120, 20, 20, 25, 20, 20, 25);
			else if (lives == 0) {
				drawRectangle(1210, 130, 1260, 190, 20, 20, 25, 20, 20, 25);
				break;
			}
		}
		if (deadcounter == alien_horde || horde_passed(alien_y, alien_horde, pos) == true) {
			deadcounter = 0;
			alien_horde += 10;
			delete[] alien_x;
			delete[] alien_y;
			goto start;
		}
	}
	// cleaning
	drawLine(0, 5, w, 5, 0);
	drawEllipse(w - 10, 0, w, 10, 0, 0, 0, 0, 0, 0);
	cls();
	showConsoleCursor(true);
	gotoxy(0, 0);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	printf("Score = %i\n",score);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	printf("PRESS ANY OTHER TO EXIT : ");
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
	return 0;
}

