#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
int size = 1, sizex = 1, sizey = 1, X = 639, Y = 479, MAX_REF = 10, BX1 = 0, BX2 = 639, BY1 = 0, BY2 = 479;
void copy()
{
	int x, y;
	FILE *fp, *fp1;
	fp = fopen("old.txt", "w");
	fp1 = fopen("cur.txt", "r");
	while (fscanf(fp1, "%d %d", &x, &y) != EOF)
	{
		fprintf(fp, "%d %d\n", x, y);
	}
	fclose(fp);
	fclose(fp1);
}
void myputpixel2(int x, int y, int color)
{
	int i, j;
	x *= sizex;
	y *= sizey;
	for (i = 1; i <= sizex; i++)
	{
		for (j = 1; j <= sizey; j++)
		{
			if ((x + i) < getmaxx() && (y + j) < getmaxy() && (x + i) >= 0 && (y + j) >= 0)
				putpixel(x + i, y + j, color);
		}
	}
}
void myputpixel3(int x, int y, int color)
{
	if (x < BX2 && y < BY2 && x > BX1 && y > BY1)
		putpixel(x, y, color);
}
void mid_point(int x1, int y1, int x2, int y2, int color, FILE *fp1)
{
	int x, y, delx, dely, s1, s2, temp, i, inter, e;
	FILE *fp;
	fp = fopen("whole.txt", "a");
	x = x1;
	y = y1;
	delx = abs(x2 - x1);
	dely = abs(y2 - y1);
	s1 = (x2 > x1) ? 1 : -1;
	s2 = (y2 > y1) ? 1 : -1;
	if (dely > delx)
	{
		temp = delx;
		delx = dely;
		dely = temp;
		inter = 1;
	}
	else
		inter = 0;
	e = 2 * dely - delx;
	for (i = 0; i < delx; i++)
	{
		myputpixel2(x, y, color);
		fprintf(fp1, "%d %d\n", x, y);
		fprintf(fp, "%d %d\n", x, y);
		if (e > 0)
		{
			if (inter == 1)
				x = x + s1;
			else
				y = y + s2;
			e = e - 2 * delx;
		}
		if (inter == 1)
			y = y + s2;
		else
			x = x + s1;
		e = e + 2 * dely;
	}
	fclose(fp);
}
void box(int minx, int miny, int maxx, int maxy, int color)
{
	FILE *fp;
	BX1 = minx;
	BX2 = maxx;
	BY1 = miny;
	BY2 = maxy;
	fp = fopen("border.txt", "w");
	mid_point(minx, miny, maxx, miny, color, fp);
	mid_point(minx, miny, minx, maxy, color, fp);
	mid_point(maxx, maxy, maxx, miny, color, fp);
	mid_point(maxx, maxy, minx, maxy, color, fp);
	fclose(fp);
}

void dda(int x1, int y1, int x2, int y2, int color)
{
	float x, y, incx, incy;
	int L, i, delx, dely;
	FILE *fp;
	int x3, y3;
	fp = fopen("old.txt", "w");
	if (fp == NULL)
	{
		exit(1);
	}
	L = abs(x2 - x1);
	if (abs(y2 - y1) > L)
		L = abs(y2 - y1);
	incx = (float)(x2 - x1) / L;
	incy = (float)(y2 - y1) / L;
	x = x1 + 0.5;
	y = y1 + 0.5;
	x3 = x;
	y3 = y;
	while (1)
	{
		if (x3 > BX2 || y3 > BY2 || x3 < BX1 || y3 < BY1)
			break;
		myputpixel3(x, y, color);
		x3 = x;
		y3 = y;
		fprintf(fp, "%d %d\n", x3, y3);
		x += incx;
		y += incy;
		x3 = x;
		y3 = y;
	}
	fclose(fp);
}
void multiply(int firstMatrix[][3], int secondMatrix[][3], int mult[][3], int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{
	int i, j, k;
	if (columnFirst != rowSecond)
		return;

	for (i = 0; i < rowFirst; ++i)
	{
		for (j = 0; j < columnSecond; ++j)
		{
			mult[i][j] = 0;
		}
	}
	for (i = 0; i < rowFirst; ++i)
	{
		for (j = 0; j < columnSecond; ++j)
		{
			for (k = 0; k < columnFirst; ++k)
			{
				mult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}
}
void refy(int xc)
{
	int point[1][3], r[3][3], res[1][3], t1[3][3], t2[3][3], res1[1][3], res2[1][3];
	int i, j, x, y, x1, y1;
	FILE *fp1, *fp2, *fp3;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			r[i][j] = 0;
	r[0][0] = -1;
	r[1][1] = 1;
	r[2][2] = 1;
	fp1 = fopen("old.txt", "r");
	fp2 = fopen("cur.txt", "w");
	fp3 = fopen("whole.txt", "a");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
			{
				t1[i][j] = 1;
				t2[i][j] = 1;
			}
			else
			{
				t1[i][j] = 0;
				t2[i][j] = 0;
			}
		}
	}
	t1[2][0] = (-1) * xc;
	t2[2][0] = xc;
	while (fscanf(fp1, "%d %d", &x, &y) != EOF)
	{

		point[0][0] = x;
		point[0][1] = y;
		point[0][2] = 1;
		multiply(point, t1, res1, 1, 3, 3, 3);
		multiply(res1, r, res2, 1, 3, 3, 3);
		multiply(res2, t2, res, 1, 3, 3, 3);
		x1 = res[0][0];
		y1 = res[0][1];
		fprintf(fp2, "%d %d\n", x1, y1);
		fprintf(fp3, "%d %d\n", x1, y1);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}
void refx(int yc)
{
	int point[1][3], r[3][3], res[1][3], t1[3][3], t2[3][3], res1[1][3], res2[1][3];
	int i, j, x, y, x1, y1;
	FILE *fp1, *fp2, *fp3;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			r[i][j] = 0;
	r[0][0] = 1;
	r[1][1] = -1;
	r[2][2] = 1;
	fp1 = fopen("old.txt", "r");
	fp2 = fopen("cur.txt", "w");
	fp3 = fopen("whole.txt", "a");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
			{
				t1[i][j] = 1;
				t2[i][j] = 1;
			}
			else
			{
				t1[i][j] = 0;
				t2[i][j] = 0;
			}
		}
	}
	t1[2][1] = (-1) * yc;
	t2[2][1] = yc;
	while (fscanf(fp1, "%d %d", &x, &y) != EOF)
	{

		point[0][0] = x;
		point[0][1] = y;
		point[0][2] = 1;
		multiply(point, t1, res1, 1, 3, 3, 3);
		multiply(res1, r, res2, 1, 3, 3, 3);
		multiply(res2, t2, res, 1, 3, 3, 3);
		x1 = res[0][0];
		y1 = res[0][1];
		fprintf(fp2, "%d %d\n", x1, y1);
		fprintf(fp3, "%d %d\n", x1, y1);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

void kladi(int minx, int miny, int maxx, int maxy, int color)
{
	int i, maxref, x1, y1, x2, y2, x, y, xend, yend, xcur, ycur;
	FILE *fp;
	maxref = MAX_REF;
	x1 = minx;
	x2 = rand() % (maxx - minx);
	x2 = x2 + minx;
	y1 = rand() % (maxy - miny);
	y1 += miny;
	y2 = maxy;
	dda(x1, y1, x2, y2, color);
	for (i = 0; i < maxref; i++)
	{
		if ((x2 == BX2 && y2 == BY1) || (x2 == BX2 && y2 == BY2) || (x2 == BX1 && y2 == BY1) || (x2 == BX1 && y2 == BY2))
			break;
		if (x2 <= BX1 || x2 >= BX2)
			refx(y2);
		else if (y2 <= BY1 || y2 >= BY2)
			refy(x2);
		else
			break;
		copy();
		fp = fopen("old.txt", "r");
		fscanf(fp, "%d %d", &x, &y);
		while (fscanf(fp, "%d %d", &xcur, &ycur) != EOF)
		{
			xend = xcur;
			yend = ycur;
		}
		fclose(fp);
		dda(xend, yend, x, y, color);
		fp = fopen("old.txt", "r");
		while (fscanf(fp, "%d %d", &xcur, &ycur) != EOF)
		{
			xend = xcur;
			yend = ycur;
		}
		x2 = xend;
		y2 = yend;
		fclose(fp);
	}
}
int main()
{
	int gd = DETECT;
	int gm, i, n;
	FILE *fp;
	srand(time(0));
	printf("Enter the number of beams : ");
	scanf("%d", &n);
	initgraph(&gd, &gm, NULL);
	box(5, 5, 470, 470, WHITE);
	fp = fopen("whole.txt", "w");
	fclose(fp);
	for (i = 1; i <= n && i < 16; i++)
		kladi(5, 5, 470, 470, i % 15);
	box(BX1, BY1, BX2, BY2, WHITE);
	getch();
	closegraph();
	getch();
	return 0;
}