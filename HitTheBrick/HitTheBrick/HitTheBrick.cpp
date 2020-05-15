#include <graphics.h>
#include <cstdio>
#include <time.h>
#include <cmath>

void nextlevel(int n);
void displaybricks(int level, int x = -1, double dir = -1, int deltay = 0);
void shoot(int n, float dir, int &x);

class brick {
public:
	int original;
	int num;
	int x, y;
	bool hasplus;
	bool istriangle;
	int triangletype; //1 -> 右上, 2 -> 左上, 3 -> 左下, 4 -> 右下

	brick(int _x, int _y) :x(_x), y(_y) {
		num = 0;
		original = 0;
		hasplus = false;
		istriangle = false;
		triangletype = 0;
	}

	void putbrick(int deltay = 0) {
		setfillcolor(hsv2rgb(220, 0.4 + 0.6 * ((double)num / original), 0.7 + 0.3 * ((double)num/original)));
		bar(x + 2, y + 62 + deltay, x + 58, y + 60 + 58 + deltay);
		setfillcolor(BLACK);
		bar(x + 5, y + 60 + 5 + deltay, x + 55, y + 60 + 55 + deltay);
	}

	void puttrianglebrick(int deltay = 0) {

		int triangleblock[] = {x + 58, y + 62 + deltay, x + 2, y + 62 + deltay,  x + 2, y + 60 + 58 + deltay, x + 58, y + 60 + 58 + deltay };
		int insidetriangle[] = {x + 55, y + 60 + 5 + deltay, x + 5, y + 60 + 5 + deltay,x + 5, y + 60 + 55 + deltay, x + 55, y + 60 + 55 + deltay };
		
		char str[8];
		sprintf(str, "%d", num);
		settextjustify(CENTER_TEXT, TOP_TEXT);
		setfont(20, 0, "宋体");
		int textx, texty;
		if (triangletype == 1) {
			triangleblock[4] = x + 30;
			triangleblock[5] = y + 90 + deltay;
			insidetriangle[2] += 3; insidetriangle[4] = x + 33; insidetriangle[5] = y + 90 + deltay; insidetriangle[7] -= 3;
			textx = x + 38; texty = y + 60 + 10 + deltay;
		} else if (triangletype == 2) {
			triangleblock[6] = x + 30;
			triangleblock[7] = y + 90 + deltay;
			insidetriangle[0] -= 3; insidetriangle[6] = x + 27; insidetriangle[7] = y + 90 + deltay; insidetriangle[5] -= 3;
			textx = x + 14; texty = y + 60 + 10 + deltay;
		} else if (triangletype == 3) {
			triangleblock[0] = x + 30;
			triangleblock[1] = y + 90 + deltay;
			insidetriangle[3] += 3; insidetriangle[0] = x + 27; insidetriangle[1] = y + 90 + deltay; insidetriangle[6] -= 3;
			textx = x + 14; texty = y + 60 + 30 + deltay;
		} else if (triangletype == 4) {
			triangleblock[2] = x + 30;
			triangleblock[3] = y + 90 + deltay;
			insidetriangle[4] += 3; insidetriangle[2] = x + 33; insidetriangle[3] = y + 90 + deltay; insidetriangle[1] += 3;
			textx = x + 38; texty = y + 60 + 30 + deltay;
		}
		setcolor(hsv2rgb(220, 0.5 + 0.5 * ((double)num / original), 0.7 + 0.3 * ((double)num / original)));
		setfillcolor(hsv2rgb(220, 0.5 + 0.5 * ((double)num / original), 0.7 + 0.3 * ((double)num / original)));
		fillpoly(4, triangleblock);
		setfillcolor(BLACK);
		fillpoly(4, insidetriangle);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		setcolor(0xEF3E0F);
		if (num >= 10) {
			textx -= 6;
		}
		outtextxy(textx, texty, str);
	}

	void displayplus(int deltay = 0) {
		//setcolor(0xFAEAD3);
		//setfillcolor(0xFAEAD3);
		setcolor(0xD7E972);
		setfillcolor(0xD7E972);
		fillellipse(x + 30, y + 90 + deltay, 18, 18);
		setfillcolor(BLACK);
		fillellipse(x + 30, y + 90 + deltay, 16, 16);
		//setfillcolor(0xFAEAD3);
		setfillcolor(0xD7E972);
		bar(x + 28, y + 81 + deltay, x + 32, y + 99 + deltay);
		bar(x + 21, y + 92 + deltay, x + 39, y + 88 + deltay);
	}
};

class ball {
public:
	bool inthesky = true;
	double x, y;
	double dx, dy;
	int r;
	void moveon() {
		x += dx;
		y += dy;
		if (y >= 600) {
			inthesky = false;
		}
	}
};

brick* bricks[8][7];
PIMAGE img;
ball balls[100];
double speed = 10.0;
int radius = 10;
int numofballs = 1;
PIMAGE back;

int main(){
	srand(time(NULL));
	initgraph(420, 680);
	back = newimage();
	getimage(back, "back.jpg");
	
	setfont(40, 0, "宋体");
	/*setfillcolor(BLUE);
	bar(2, 2, 58, 58);
	setfillcolor(BLACK);
	bar(5, 5, 55, 55);
	img = newimage();
	getimage(img, 0, 0, 60, 60);
	cleardevice();*/
	setcolor(0xFAEAD3);
	for (int i = 0; i >= -50; i--, delay_fps(60)) {
		setfont(105, 0, "宋体");
		outtextxy(70, 140 + i, "Hit");
		setfont(60, 0, "宋体");
		outtextxy(180, 235 + i, "the");
		setfont(100, 0, "宋体");
		outtextxy(120, 290 + i, "Brick");
	}
	
	mouse_msg msg = { 0 };
	bool canchangesize = true;
	for (; is_run(); delay_fps(20))
	{
		cleardevice();
		setcolor(0xFAEAD3);
		setfont(105, 0, "宋体");
		outtextxy(70, 90, "Hit");
		setfont(60, 0, "宋体");
		outtextxy(180, 185, "the");
		setfont(100, 0, "宋体");
		outtextxy(120, 240, "Brick");
		setfillcolor(0xFF1493);
		bar(120, 500, 300, 575);
		setfillcolor(BLACK);
		bar(125, 505, 295, 570);
		setfillcolor(0xF5DEB3);
		int triangle[] = { 193, 513, 193, 560, 226, 536 };
		fillpoly(3, triangle);
		setfont(15, 0, "宋体");
		char ballsizestr[10];
		switch (radius)
		{
		case 10:
			sprintf(ballsizestr, "Normal");
			speed = 10.0;
			break;
		case 5:
			sprintf(ballsizestr, "Small");
			speed = 5.0;
			break;
		case 15:
			sprintf(ballsizestr, "Big");
			speed = 10.0;
			break;
		}
		outtextxy(140, 590, "Ball:");
		outtextxy(215, 590, ballsizestr);
		int decreasetriangle[] = {190, 597, 197, 592, 197, 603};
		setfillcolor(0xF5DEB3);
		if (radius == 5) {
			setfillcolor(0x666666);
		}
		fillpoly(3, decreasetriangle);
		int increasetriangle[] = { 284, 597, 277, 592, 277, 603 };
		setfillcolor(0xF5DEB3);
		if (radius == 15) {
			setfillcolor(0x666666);
		}
		fillpoly(3, increasetriangle);
		while (mousemsg())
		{
			msg = getmouse();
		}
		if (msg.x >= 120 && msg.x <= 300 && msg.y >= 500 && msg.y <= 575 && (int)msg.is_left()) {
			break;
		}
		if (canchangesize) {
			if (msg.x >= 190 && msg.x <= 197 && msg.y >= 592 && msg.y <= 603 && (int)msg.is_left() && radius > 5) {
				radius -= 5;
				canchangesize = false;
			}
			if (msg.x >= 277 && msg.x <= 284 && msg.y >= 592 && msg.y <= 603 && (int)msg.is_left() && radius < 15) {
				radius += 5;
				canchangesize = false;
			}
		}
		if (!(msg.x >= 190 && msg.x <= 197 && msg.y >= 592 && msg.y <= 603 && (int)msg.is_left() && radius > 5) && !(msg.x >= 277 && msg.x <= 284 && msg.y >= 592 && msg.y <= 603 && (int)msg.is_left() && radius < 15)) {
			canchangesize = true;
		}

	}
	cleardevice();
	for (float v = 1.0f; v > 0; v -= 0.01, delay_fps(120)) {
		setcolor(hsv2rgb(35.385, 0.156, v));
		setfont(105, 0, "宋体");
		outtextxy(70, 90, "Hit");
		setfont(60, 0, "宋体");
		outtextxy(180, 185, "the");
		setfont(100, 0, "宋体");
		outtextxy(120, 240, "Brick");
		setcolor(hsv2rgb(327.574, 0.922, v));
		bar(120, 500, 300, 575);
		setfillcolor(BLACK);
		bar(125, 505, 295, 570);
		setcolor(hsv2rgb(39.091, 0.269, v));
	}

	while (1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 7; j++) {
				bricks[i][j] = new brick(j * 60, i * 60);
			}
		}
		cleardevice();
		setfont(40, 0, "宋体");
		int x = 210;
		double dir = PI / 2;
		bool gameover = false;
		int level = 1;
		for (; !gameover; level++) {
			cleardevice();
			if (level > 1) {
				for (int deltay = 0; deltay <= 60; deltay++, delay_fps(120)) {
					cleardevice();
					displaybricks(level, -1, -1, deltay);
				}
			}
			/*char levelstr[10];
			sprintf(levelstr, "Level %d", level);
			setfont(50, 0, "宋体");
			settextjustify(CENTER_TEXT, TOP_TEXT);
			for (float v = 0.0f; v <= 1; v += 0.02f, delay_fps(120)) {
				setcolor(hsv2rgb(0, 0, v));
				outtextxy(210, 250, levelstr);
			}
			for (float v = 1.0f; v > 0; v -= 0.01f, delay_fps(120)) {
				setcolor(hsv2rgb(0, 0, v));
				outtextxy(210, 250, levelstr);
			}
			settextjustify(LEFT_TEXT, TOP_TEXT);*/
			int k = 0;
			dir = PI / 2;

			nextlevel(level);
			while (k != key_space) {
				cleardevice();

				displaybricks(level, x, dir, 0);

				char numleftstr[10];
				sprintf(numleftstr, "x%d", level);
				setfont(20, 0, "宋体");
				settextjustify(CENTER_TEXT, TOP_TEXT);
				outtextxy(x, 610, numleftstr);
				settextjustify(LEFT_TEXT, TOP_TEXT);

				k = getch();
				if (k == 293 && dir <= 11 * PI / 12) {
					dir += .02f;
				}
				if (k == 295 && dir >= PI / 12) {
					dir -= .02f;
				}
			}
			
			shoot(numofballs, dir, x);
			for (int i = 0; i <= 6; i++) {
				if (bricks[7][i]->num) {
					setcolor(0xFFFAF4);
					settextjustify(CENTER_TEXT, TOP_TEXT);
					setfont(50, 0, "宋体");
					outtextxy(210, 250, "Game over");
					char scorestr[16];
					sprintf(scorestr, "Your score is %d", level);
					setfont(30, 0, "宋体");
					outtextxy(210, 305, scorestr);
					settextjustify(LEFT_TEXT, TOP_TEXT);
					gameover = true;
					numofballs = 1;
					getch();
					break;
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 7; j++) {
				delete bricks[i][j];
			}
		}
	}
	getch();
	return 0;
}



void nextlevel(int n) {
	int numofbricks = 0;
	for (int i = 7; i >= 1; i--) {
		for (int j = 0; j < 7; j++) {
			bricks[i][j]->num = bricks[i - 1][j]->num;
			bricks[i][j]->original = bricks[i - 1][j]->original;
			bricks[i][j]->hasplus = bricks[i - 1][j]->hasplus;
			bricks[i][j]->istriangle = bricks[i - 1][j]->istriangle;
			bricks[i][j]->triangletype = bricks[i - 1][j]->triangletype;
		}
	}
	for (int i = 0; i < 7; i++) {
		bricks[0][i]->num = 0;
		bricks[0][i]->original = 0;
		bricks[0][i]->hasplus = false;
		bricks[0][i]->istriangle = false;
		bricks[0][i]->triangletype = 0;

	}
	int idx;
	numofbricks = rand() % 4 + 3;
	if (numofbricks == 6) {
		numofbricks -= (rand() % 3);
	}
	for (int i = 1; i <= numofbricks; i++) {
		idx = rand() % 7;
		if (bricks[0][idx]->num == 0) {
			bricks[0][idx]->num = n;
			bricks[0][idx]->original = n;
			
			int randomtriangle = rand() % 4; //四分之一概率生成三角形
			if (!randomtriangle) {
				bricks[0][idx]->istriangle = true;
				randomtriangle = rand() % 4 + 1;
				bricks[0][idx]->triangletype = randomtriangle;
			}
		}
		else {
			i--;
		}
	} 
	while (1) {
		idx = rand() % 7;
		if (bricks[0][idx]->num == 0) {
			bricks[0][idx]->hasplus = true;
			break;
		}
	}
}

void displaybricks(int level, int x, double dir, int deltay) {
	setcolor(WHITE);
	putimage(0, 0, back);
	line(0, 600, 420, 600);
	if (x > 0 && dir > 0) {
		setcolor(0xFFFAF4);
		line(x, 600, x + 50 * cos(dir), 600 - 50 * sin(dir));
		line(x + 50 * cos(dir), 600 - 50 * sin(dir), x + 50 * cos(dir) + 10 * cos(5 * PI / 6 - dir), 600 - 50 * sin(dir) + 10 * sin(5 * PI / 6 - dir));
		line(x + 50 * cos(dir), 600 - 50 * sin(dir), x + 50 * cos(dir) + 10 * cos(7 * PI / 6 - dir), 600 - 50 * sin(dir) + 10 * sin(7 * PI / 6 - dir));
		setfillcolor(0xFFFAF4);
		float aimlinex = x + 50 * cos(dir), aimliney = 600 - 50 * sin(dir);
		while (1) {
			aimlinex += 30 * cos(dir);
			aimliney -= 30 * sin(dir);
			fillellipse(aimlinex, aimliney, 4, 4);
			if (aimlinex <= 5 || aimlinex >= 415 || aimliney <= 5) {
				break;
			}
			int yp = (int)aimliney / 60 - 1, xp = (int)aimlinex / 60;
			if (yp >= 0 && yp <= 7) {
				if (bricks[yp][xp]->num != 0) {
					break;
				}
			}
		}
		
	
		setcolor(0xEF3E0F);
		setfillcolor(0xEF3E0F);
		fillellipse(x, 600, radius, radius);
		
	}
	setcolor(WHITE);
	char levelstr[10];
	sprintf(levelstr, "Level %d", level);
	setfont(30, 0, "宋体");
	settextjustify(CENTER_TEXT, TOP_TEXT);
	outtextxy(210, 625, levelstr);
	settextjustify(LEFT_TEXT, TOP_TEXT);

	setcolor(RED);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			if (bricks[i][j]->num != 0) {
				if (!bricks[i][j]->istriangle) {
					//putimage(bricks[i][j]->x, bricks[i][j]->y + 60 + deltay, img);
					bricks[i][j]->putbrick(deltay);
					setcolor(0xEF3E0F);
					char str[8];
					sprintf(str, "%d", bricks[i][j]->num);
					if (bricks[i][j]->num >= 10) {
						setfont(30, 0, "宋体");
						outtextxy(j * 60 + 14, i * 60 + 60 + 16 + deltay, str);
					}
					else {
						setfont(40, 0, "宋体");
						outtextxy(j * 60 + 20, i * 60 + 60 + 11 + deltay, str);
					}
				}
				else {

					bricks[i][j]->puttrianglebrick(deltay);

				}
			}

			if (bricks[i][j]->hasplus) {
				bricks[i][j]->displayplus(deltay);
			}
		}
	}
}

void shoot(int n, float dir, int &x) {
	setfillcolor(0xEF3E0F);
	setcolor(RED);
	double t = fclock();
	int num = 1;
	bool positionset = false;
	bool allballshome = false;
	for (int i = 0; i < n; i++) {
		balls[i].x = x;
		balls[i].y = 600;
		balls[i].dx = (double)speed * cos(dir);
		balls[i].dy = -(double)speed * sin(dir);
		balls[i].r = radius;
		balls[i].inthesky = true;
	}

	for (; !allballshome; delay_fps(60)) {
		cleardevice();
		displaybricks(n, -1,-1,0);
		if (fclock() - t > 0.2) {
			t = fclock();
			if (num < n) ++num;
		}
		allballshome = true;
		for (int j = 0; j < num; j++) {
			if (balls[j].inthesky) {
				setcolor(RED);
				setfillcolor(0xEF3E0F);
				fillellipse(balls[j].x, balls[j].y, balls[j].r, balls[j].r);
				if ((n - num) != -1) {
					char numleftstr[10];
					sprintf(numleftstr, "x%d", n - num);
					setfont(20, 0, "宋体");
					settextjustify(CENTER_TEXT, TOP_TEXT);
					outtextxy(x, 610, numleftstr);
					settextjustify(LEFT_TEXT, TOP_TEXT);
				}
				balls[j].moveon();
				if ((balls[j].x < balls[j].r && balls[j].dx < 0) || (balls[j].x > (double)420 - balls[j].r && balls[j].dx > 0)) balls[j].dx = -balls[j].dx;
				if ((balls[j].y < balls[j].r && balls[j].dy < 0) || (balls[j].y > (double)640 - balls[j].r && balls[j].dy > 0)) balls[j].dy = -balls[j].dy;
				int p = (int)balls[j].x / 60, q = (int)balls[j].y / 60 - 1;

				if (q >= 0 && q <= 7 && p >= 0 && p <= 6) { //同一个格子内的三角形方块
					if (bricks[q][p]->num > 0 && bricks[q][p]->istriangle) {
						if (bricks[q][p]->triangletype == 1) {
							if (balls[j].x - balls[j].y >= (double)bricks[q][p]->x - bricks[q][p]->y - 60 - 1.414 * balls[j].r && ((balls[j].dx > 0 && balls[j].dy < 0)||(balls[j].dx >0 && balls[j].dy > 0 && balls[j].dx > balls[j].dy)||(balls[j].dx < 0 && balls[j].dy < 0 && balls[j].dx > balls[j].dy) )) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								/*if (balls[j].dx > 0 && balls[j].dy < 0) {
									balls[j].dx = -balls[j].dx;
									balls[j].dy = -balls[j].dy;
								}*/
								(bricks[q][p]->num)--;
							}
						}
						if (bricks[q][p]->triangletype == 2) {
							if (balls[j].x + balls[j].y <= (double)bricks[q][p]->x + bricks[q][p]->y + 120 + 1.414 * balls[j].r && ((balls[j].dx < 0 && balls[j].dy < 0) || (balls[j].dx > 0 && balls[j].dy < 0 && balls[j].dx < -balls[j].dy) || (balls[j].dx < 0 && balls[j].dy > 0 && -balls[j].dx > balls[j].dy))) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								//if (!(balls[j].dx < 0 && balls[j].dy < 0)) {
									balls[j].dx = -balls[j].dx;
									balls[j].dy = -balls[j].dy;
								//}
								(bricks[q][p]->num)--;
							}
						}
						if (bricks[q][p]->triangletype == 3) {
							if (balls[j].x - balls[j].y <= (double)bricks[q][p]->x - bricks[q][p]->y - 60 + 1.414 * balls[j].r && ((balls[j].dx < 0 && balls[j].dy > 0) || (balls[j].dx > 0 && balls[j].dy > 0 && balls[j].dx < balls[j].dy) || (balls[j].dx < 0 && balls[j].dy < 0 && balls[j].dx < balls[j].dy))) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								/*if (balls[j].dx < 0 && balls[j].dy > 0) {
									balls[j].dx = -balls[j].dx;
									balls[j].dy = -balls[j].dy;
								}*/
								(bricks[q][p]->num)--;
							}
						}
						if (bricks[q][p]->triangletype == 4) {
							if (balls[j].x + balls[j].y >= (double)bricks[q][p]->x + bricks[q][p]->y + 120 - 1.414 * balls[j].r && ((balls[j].dx > 0 && balls[j].dy > 0) || (balls[j].dx > 0 && balls[j].dy < 0 && balls[j].dx > -balls[j].dy) || (balls[j].dx < 0 && balls[j].dy > 0 && -balls[j].dx < balls[j].dy))) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								//if (!(balls[j].dx > 0 && balls[j].dy > 0)) {
									balls[j].dx = -balls[j].dx;
									balls[j].dy = -balls[j].dy;
								//}
								(bricks[q][p]->num)--;
							}
						}
					}
				}
				if (q < 9 && q > 0) { //上方的矩形、三角形
					if (bricks[q - 1][p]->istriangle) {
						if ((bricks[q - 1][p]->triangletype == 3 || bricks[q - 1][p]->triangletype == 4)&& (bricks[q - 1][p]->num > 0 && balls[j].y <= (double)q * 60 + 60 + balls[j].r && balls[j].dy < 0)) {
							balls[j].dy = -balls[j].dy; (bricks[q - 1][p]->num)--;
						}
						if (bricks[q - 1][p]->triangletype == 1 && (balls[j].x - balls[j].y >= (double)bricks[q - 1][p]->x - bricks[q - 1][p]->y - 1.414 * balls[j].r && ((balls[j].dx > 0 && balls[j].dy < 0) || (balls[j].dx > 0 && balls[j].dy > 0 && balls[j].dx > balls[j].dy) || (balls[j].dx < 0 && balls[j].dy < 0 && balls[j].dx > balls[j].dy)))){
							int temp = balls[j].dx;
							balls[j].dx = balls[j].dy;
							balls[j].dy = temp;
							//if (balls[j].dx > 0 && balls[j].dy < 0) {
							//	balls[j].dx = -balls[j].dx;
							//	balls[j].dy = -balls[j].dy;
							//}
							(bricks[q - 1][p]->num)--;
						}
						if (bricks[q - 1][p]->triangletype == 2 && balls[j].x + balls[j].y <= (double)bricks[q - 1][p]->x + bricks[q - 1][p]->y + 60 + 1.414 * balls[j].r && ((balls[j].dx < 0 && balls[j].dy < 0) || (balls[j].dx > 0 && balls[j].dy < 0 && balls[j].dx < -balls[j].dy) || (balls[j].dx < 0 && balls[j].dy > 0 && -balls[j].dx > balls[j].dy))) {
							int temp = balls[j].dx;
							balls[j].dx = balls[j].dy;
							balls[j].dy = temp;
							//if (!(balls[j].dx < 0 && balls[j].dy < 0)) {
								balls[j].dx = -balls[j].dx;
								balls[j].dy = -balls[j].dy;
							//}
							(bricks[q - 1][p]->num)--;
						}
					}
					else {
						if (bricks[q - 1][p]->num > 0 && balls[j].y <= (double)q * 60 + 60 + balls[j].r && balls[j].dy < 0) {
							balls[j].dy = -balls[j].dy; (bricks[q - 1][p]->num)--;
						}
					}
				}
				if (q < 7) { //下方的矩形、三角形
					if (bricks[q + 1][p]->istriangle) {
						if ((bricks[q + 1][p]->triangletype == 1 || bricks[q + 1][p]->triangletype == 2)&& (bricks[q + 1][p]->num > 0 && balls[j].y >= (double)q * 60 + 120 - balls[j].r && balls[j].dy > 0)) {
							balls[j].dy = -balls[j].dy; (bricks[q + 1][p]->num)--;
						}
						if (bricks[q + 1][p]->triangletype == 3 && balls[j].x - balls[j].y <= (double)bricks[q + 1][p]->x - bricks[q + 1][p]->y - 120 + 1.414 * balls[j].r && ((balls[j].dx < 0 && balls[j].dy > 0) || (balls[j].dx > 0 && balls[j].dy > 0 && balls[j].dx < balls[j].dy) || (balls[j].dx < 0 && balls[j].dy < 0 && balls[j].dx < balls[j].dy))) {
							int temp = balls[j].dx;
							balls[j].dx = balls[j].dy;
							balls[j].dy = temp;
							//if (balls[j].dx < 0 && balls[j].dy > 0) {
							//	balls[j].dx = -balls[j].dx;
							//	balls[j].dy = -balls[j].dy;
							//}
							(bricks[q + 1][p]->num)--;
						}
						if (bricks[q + 1][p]->triangletype == 4 && balls[j].x + balls[j].y >= (double)bricks[q + 1][p]->x + bricks[q + 1][p]->y + 180 - 1.414 * balls[j].r && ((balls[j].dx > 0 && balls[j].dy > 0) || (balls[j].dx > 0 && balls[j].dy < 0 && balls[j].dx > -balls[j].dy) || (balls[j].dx < 0 && balls[j].dy > 0 && -balls[j].dx < balls[j].dy))) {
							int temp = balls[j].dx;
							balls[j].dx = balls[j].dy;
							balls[j].dy = temp;
							//if (!(balls[j].dx > 0 && balls[j].dy > 0)) {
								balls[j].dx = -balls[j].dx;
								balls[j].dy = -balls[j].dy;
							//}
							(bricks[q + 1][p]->num)--;
						}
					}
					else {
						if (bricks[q + 1][p]->num > 0 && balls[j].y >= (double)q * 60 + 120 - balls[j].r && balls[j].dy > 0) {
							balls[j].dy = -balls[j].dy; (bricks[q + 1][p]->num)--;
						}
					}
				}
				if (q >= 0 && q <= 7 && p >= 1) { //左边的矩形、三角形
					if (bricks[q][p - 1]->num > 0 && balls[j].x <= (double)p * 60 + balls[j].r && balls[j].dx < 0) {
						if (bricks[q][p - 1]->istriangle) {
							if (bricks[q][p - 1]->triangletype == 1 || bricks[q][p - 1]->triangletype == 4) {
								balls[j].dx = -balls[j].dx; (bricks[q][p - 1]->num)--;
							}
							if (bricks[q][p - 1]->triangletype == 2 && balls[j].x + balls[j].y <= (double)bricks[q][p - 1]->x + bricks[q][p - 1]->y + 60 + 1.414 * balls[j].r && ((balls[j].dx < 0 && balls[j].dy < 0) || (balls[j].dx > 0 && balls[j].dy < 0 && balls[j].dx < -balls[j].dy) || (balls[j].dx < 0 && balls[j].dy > 0 && -balls[j].dx > balls[j].dy))) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								//if (!(balls[j].dx < 0 && balls[j].dy < 0)) {
									balls[j].dx = -balls[j].dx;
									balls[j].dy = -balls[j].dy;
								//}
								(bricks[q][p - 1]->num)--;
							}
							if (bricks[q][p - 1]->triangletype == 3 && balls[j].x - balls[j].y <= (double)bricks[q][p - 1]->x - bricks[q][p - 1]->y - 120 + 1.414 * balls[j].r && ((balls[j].dx < 0 && balls[j].dy > 0) || (balls[j].dx > 0 && balls[j].dy > 0 && balls[j].dx < balls[j].dy) || (balls[j].dx < 0 && balls[j].dy < 0 && balls[j].dx < balls[j].dy))) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								/*if (balls[j].dx < 0 && balls[j].dy > 0) {
									balls[j].dx = -balls[j].dx;
									balls[j].dy = -balls[j].dy;
								}*/
								(bricks[q][p - 1]->num)--;
							}
						}
						
						else {
							balls[j].dx = -balls[j].dx; (bricks[q][p - 1]->num)--;
						}
					}
				}

				if (q >= 0 && q <= 7 && p <= 5) { //右边的矩形、三角形
					if (bricks[q][p + 1]->num > 0 && balls[j].x >= (double)p * 60 + 60 - balls[j].r && balls[j].dx > 0) {
						if (bricks[q][p + 1]->istriangle) {
							if (bricks[q][p + 1]->triangletype == 2 || bricks[q][p + 1]->triangletype == 3) {
								balls[j].dx = -balls[j].dx; (bricks[q][p + 1]->num)--;
							}
							if (bricks[q][p + 1]->triangletype == 1 && balls[j].x - balls[j].y >= (double)bricks[q][p + 1]->x - bricks[q][p + 1]->y - 1.414 * balls[j].r && ((balls[j].dx > 0 && balls[j].dy < 0) || (balls[j].dx > 0 && balls[j].dy > 0 && balls[j].dx > balls[j].dy) || (balls[j].dx < 0 && balls[j].dy < 0 && balls[j].dx > balls[j].dy))) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								//if (balls[j].dx > 0 && balls[j].dy < 0) {
								//	balls[j].dx = -balls[j].dx;
								//	balls[j].dy = -balls[j].dy;
								//}
								(bricks[q][p + 1]->num)--;
							}
							if (bricks[q][p + 1]->triangletype == 4 && balls[j].x + balls[j].y >= (double)bricks[q][p + 1]->x + bricks[q][p + 1]->y + 180 - 1.414 * balls[j].r && ((balls[j].dx > 0 && balls[j].dy > 0) || (balls[j].dx > 0 && balls[j].dy < 0 && balls[j].dx > -balls[j].dy) || (balls[j].dx < 0 && balls[j].dy > 0 && -balls[j].dx < balls[j].dy))) {
								int temp = balls[j].dx;
								balls[j].dx = balls[j].dy;
								balls[j].dy = temp;
								//if (!(balls[j].dx > 0 && balls[j].dy > 0)) {
									balls[j].dx = -balls[j].dx;
									balls[j].dy = -balls[j].dy;
								//}
								(bricks[q][p + 1]->num)--;
							}
						}
						
						else {
							balls[j].dx = -balls[j].dx; (bricks[q][p + 1]->num)--;
						}
					}
				}

				if (p > 0 && q > 0 && q < 9) { //左上角
					double distance = sqrt((balls[j].x - (double)p * 60) * (balls[j].x - (double)p * 60) + (balls[j].y - (double)q * 60 - 60) * (balls[j].y - (double)q * 60 - 60));
					if ((bricks[q - 1][p - 1]->num > 0) &&(bricks[q - 1][p - 1]->triangletype != 2)&& (distance <= balls[j].r)) {
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan((balls[j].x - (double)p * 60) / (balls[j].y - (double)q * 60 - 60));
						if ((balls[j].dy < 0 && alpha > beta && balls[j].dx > 0) || ((balls[j].dy > 0 && alpha < beta && balls[j].dx < 0)) || ((balls[j].dx < 0 && balls[j].dy < 0))) {
							float redirect;
							if (balls[j].dy > 0 && alpha < beta && balls[j].dx < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							if (balls[j].dy < 0 && alpha > beta&& balls[j].dx > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dx < 0 && balls[j].dy < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q - 1][p - 1]->num)--;
						}
					} else if ((q <= 7) && (bricks[q][p - 1]->num > 0) && (bricks[q][p - 1]->triangletype == 2) && (distance <= balls[j].r)) { //左边三角块
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan((balls[j].x - (double)p * 60) / (balls[j].y - (double)q * 60 - 60));
						if ((balls[j].dy < 0 && alpha > beta&& balls[j].dx > 0) || ((balls[j].dy > 0 && alpha < beta && balls[j].dx < 0)) || ((balls[j].dx < 0 && balls[j].dy < 0))) {
							float redirect;
							if (balls[j].dy > 0 && alpha < beta && balls[j].dx < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							if (balls[j].dy < 0 && alpha > beta&& balls[j].dx > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dx < 0 && balls[j].dy < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q][p - 1]->num)--;
						}
					} else if ((bricks[q - 1][p]->num > 0) && (bricks[q - 1][p]->triangletype == 2) && (distance <= balls[j].r)) { //上方三角块
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan((balls[j].x - (double)p * 60) / (balls[j].y - (double)q * 60 - 60));
						if ((balls[j].dy < 0 && alpha > beta&& balls[j].dx > 0) || ((balls[j].dy > 0 && alpha < beta && balls[j].dx < 0)) || ((balls[j].dx < 0 && balls[j].dy < 0))) {
							float redirect;
							if (balls[j].dy > 0 && alpha < beta && balls[j].dx < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							if (balls[j].dy < 0 && alpha > beta&& balls[j].dx > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dx < 0 && balls[j].dy < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q - 1][p]->num)--;
						}
					}

				}
				if (p < 6 && q > 0 && q < 9) { //右上角
					double distance = sqrt(((double)p * 60 - balls[j].x + 60) * ((double)p * 60 - balls[j].x + 60) + (balls[j].y - (double)q * 60 - 60) * (balls[j].y - (double)q * 60 - 60));
					if ((bricks[q - 1][p + 1]->num > 0) && (bricks[q - 1][p + 1]->triangletype != 1) && (distance <= balls[j].r)) {
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan(((double)p * 60 - balls[j].x + 60) / (balls[j].y - (double)q * 60 - 60));
						if ((balls[j].dy < 0 && -alpha > beta&& balls[j].dx < 0) || (((balls[j].dy > 0 && -alpha < beta) && balls[j].dx > 0)) || ((balls[j].dx > 0 && balls[j].dy < 0))) {
							float redirect;
							if (balls[j].dx > 0 && balls[j].dy < 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							if (balls[j].dy < 0 && -alpha > beta && balls[j].dx < 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if ((balls[j].dy > 0 && -alpha < beta) && balls[j].dx > 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q - 1][p + 1]->num)--;
						}
					} else if ((bricks[q - 1][p]->num > 0) && (bricks[q - 1][p]->triangletype == 1) && (distance <= balls[j].r)) { //up tri 1
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan(((double)p * 60 - balls[j].x + 60) / (balls[j].y - (double)q * 60 - 60));
						if ((balls[j].dy < 0 && -alpha > beta&& balls[j].dx < 0) || (((balls[j].dy > 0 && -alpha < beta) && balls[j].dx > 0)) || ((balls[j].dx > 0 && balls[j].dy < 0))) {
							float redirect;
							if (balls[j].dx > 0 && balls[j].dy < 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							if (balls[j].dy < 0 && -alpha > beta&& balls[j].dx < 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if ((balls[j].dy > 0 && -alpha < beta) && balls[j].dx > 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q - 1][p]->num)--;
						}
					} else if ((q <= 7) && (bricks[q][p + 1]->num > 0) && (bricks[q][p + 1]->triangletype == 1) && (distance <= balls[j].r)) { //right tri 1
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan(((double)p * 60 - balls[j].x + 60) / (balls[j].y - (double)q * 60 - 60));
						if ((balls[j].dy < 0 && -alpha > beta&& balls[j].dx < 0) || (((balls[j].dy > 0 && -alpha < beta) && balls[j].dx > 0)) || ((balls[j].dx > 0 && balls[j].dy < 0))) {
							float redirect;
							if (balls[j].dx > 0 && balls[j].dy < 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							if (balls[j].dy < 0 && -alpha > beta&& balls[j].dx < 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if ((balls[j].dy > 0 && -alpha < beta) && balls[j].dx > 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q][p + 1]->num)--;
						}
					}
				}
				if (p > 0 && q < 7 && p < 8) { //左下角
					double distance = sqrt((balls[j].x - (double)p * 60) * (balls[j].x - (double)p * 60) + ((double)q * 60 + 120 - balls[j].y) * ((double)q * 60 + 120 - balls[j].y));
					if ((bricks[q + 1][p - 1]->num > 0) && (bricks[q + 1][p - 1]->triangletype != 3) && (distance <= balls[j].r)) {
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan((balls[j].x - (double)p * 60) / ((double)q * 60 + 120 - balls[j].y));
						if ((balls[j].dy < 0 && -alpha < beta&& balls[j].dx < 0) || ((balls[j].dy > 0 && -alpha > beta && balls[j].dx > 0)) || ((balls[j].dx < 0 && balls[j].dy > 0))) {
							float redirect;
							if (balls[j].dy < 0 && -alpha < beta && balls[j].dx < 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if (balls[j].dx < 0 && balls[j].dy > 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if (balls[j].dy > 0 && -alpha > beta && balls[j].dx > 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q + 1][p - 1]->num)--;
						}
					} else if ((bricks[q + 1][p]->num > 0) && (bricks[q + 1][p]->triangletype == 3) && (distance <= balls[j].r)) { //down
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan((balls[j].x - (double)p * 60) / ((double)q * 60 + 120 - balls[j].y));
						if ((balls[j].dy < 0 && -alpha < beta && balls[j].dx < 0) || ((balls[j].dy > 0 && -alpha > beta&& balls[j].dx > 0)) || ((balls[j].dx < 0 && balls[j].dy > 0))) {
							float redirect;
							if (balls[j].dy < 0 && -alpha < beta && balls[j].dx < 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if (balls[j].dx < 0 && balls[j].dy > 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if (balls[j].dy > 0 && -alpha > beta&& balls[j].dx > 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q + 1][p]->num)--;
						}
					} else if ((q >= 0) && (bricks[q][p - 1]->num > 0) && (bricks[q][p - 1]->triangletype == 3) && (distance <= balls[j].r)) { //left
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan((balls[j].x - (double)p * 60) / ((double)q * 60 + 120 - balls[j].y));
						if ((balls[j].dy < 0 && -alpha < beta && balls[j].dx < 0) || ((balls[j].dy > 0 && -alpha > beta&& balls[j].dx > 0)) || ((balls[j].dx < 0 && balls[j].dy > 0))) {
							float redirect;
							if (balls[j].dy < 0 && -alpha < beta && balls[j].dx < 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if (balls[j].dx < 0 && balls[j].dy > 0) {
								redirect = PI - 2 * beta - alpha;
							}
							if (balls[j].dy > 0 && -alpha > beta&& balls[j].dx > 0) {
								redirect = 2 * PI - 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q][p - 1]->num)--;
						}
					}
				}
				if (p < 6 && q < 7) { //右下角
					double distance = sqrt(((double)p * 60 - balls[j].x + 60) * ((double)p * 60 - balls[j].x + 60) + ((double)q * 60 + 120 - balls[j].y) * ((double)q * 60 + 120 - balls[j].y));
					if ((bricks[q + 1][p + 1]->num > 0) && (bricks[q + 1][p + 1]->triangletype != 4) && (distance <= balls[j].r)) {
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan(((double)p * 60 - balls[j].x + 60) / ((double)q * 60 + 120 - balls[j].y));
						if ((balls[j].dy < 0 && alpha < beta&& balls[j].dx > 0) || ((balls[j].dy > 0 && alpha > beta && balls[j].dx < 0)) || ((balls[j].dx > 0 && balls[j].dy > 0))) {
							float redirect;
							if (balls[j].dy < 0 && alpha < beta && balls[j].dx > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dx > 0 && balls[j].dy > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dy > 0 && alpha > beta&& balls[j].dx < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q + 1][p + 1]->num)--;
						}
					} else if ((q >= 0) && (bricks[q][p + 1]->num > 0) && (bricks[q][p + 1]->triangletype == 4) && (distance <= balls[j].r)) { //right
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan(((double)p * 60 - balls[j].x + 60) / ((double)q * 60 + 120 - balls[j].y));
						if ((balls[j].dy < 0 && alpha < beta && balls[j].dx > 0) || ((balls[j].dy > 0 && alpha > beta&& balls[j].dx < 0)) || ((balls[j].dx > 0 && balls[j].dy > 0))) {
							float redirect;
							if (balls[j].dy < 0 && alpha < beta && balls[j].dx > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dx > 0 && balls[j].dy > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dy > 0 && alpha > beta&& balls[j].dx < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q][p + 1]->num)--;
						}
					} else if ((bricks[q + 1][p]->num > 0) && (bricks[q + 1][p]->triangletype == 4) && (distance <= balls[j].r)) { //down
						double alpha = atan(-balls[j].dy / balls[j].dx), beta = atan(((double)p * 60 - balls[j].x + 60) / ((double)q * 60 + 120 - balls[j].y));
						if ((balls[j].dy < 0 && alpha < beta && balls[j].dx > 0) || ((balls[j].dy > 0 && alpha > beta&& balls[j].dx < 0)) || ((balls[j].dx > 0 && balls[j].dy > 0))) {
							float redirect;
							if (balls[j].dy < 0 && alpha < beta && balls[j].dx > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dx > 0 && balls[j].dy > 0) {
								redirect = 2 * beta - alpha;
							}
							if (balls[j].dy > 0 && alpha > beta&& balls[j].dx < 0) {
								redirect = PI + 2 * beta - alpha;
							}
							balls[j].dx = speed * cos(redirect);
							balls[j].dy = -speed * sin(redirect);
							(bricks[q + 1][p]->num)--;
						}
					}
				}
				if (abs(balls[j].dy) <= 1) { // 这不是bug，是特性
					int tempdir = rand() % 314;
					balls[j].dx = speed * cos((double)tempdir / 100);
					balls[j].dy = -speed * sin((double)tempdir / 100);
				}
				if (q >= 0 && q <= 7) { //加号
					if (bricks[q][p]->hasplus) {
						double distance = sqrt((balls[j].x - bricks[q][p]->x - 30) * (balls[j].x - bricks[q][p]->x - 30) + (balls[j].y - bricks[q][p]->y - 90) * (balls[j].y - bricks[q][p]->y - 90));
						if (distance <= 18.0 + balls[j].r) {
							bricks[q][p]->hasplus = false;
							numofballs++;
						}
					}
				}
			}
		}
		if (!positionset) {
			for (int j = 0; j < num; j++) {
				if (!balls[j].inthesky) {
					positionset = true;
					x = balls[j].x;
					break;
				}
			}
		}
		for (int j = 0; j < n; j++) {
			if (balls[j].inthesky) {
				allballshome = false;
				break;
			}
		}
		
	}

}