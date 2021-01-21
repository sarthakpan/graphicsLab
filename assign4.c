#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int xc = 320, yc = 240, n = 0;
int xs[1000], ys[1000];
void grid()
{
    int i, j;
    for (i = 0; i < 640; i = i)
    {
        for (j = 0; j < 480; j = j)
        {
            putpixel(i, j, RED);
        }
    }
}

void dda(int x1, int y1, int x2, int y2, int color)
{
    int i;
    int L = abs(x2 - x1);
    if (abs(y2 - y1) > L)
        L = abs(y2 - y1);
    float xinc = (x2 - x1) / (float)L;
    float yinc = (y2 - y1) / (float)L;
    float x = x1 + 0.1;
    float y = y1 + 0.1;
    for (i = 0; i <= L; i++)
    {
        putpixel(x, y, color);
        x = x + xinc;
        y = y + yinc;
        delay(10);
    }
}
void Bresenham(int x1, int y1, int x2, int y2, int color)
{
    int x = x1;
    int y = y1;
    int delx = abs(x2 - x1);
    int dely = abs(y2 - y1);
    int s1 = x1 < x2 ? 1 : -1;
    int s2 = y1 < y2 ? 1 : -1;
    int interchange = 0;
    int e, i;
    if (dely > delx)
    {
        int temp = delx;
        delx = dely;
        dely = temp;
        interchange = 1;
    }
    e = 2 * dely - delx;
    for (i = 0; i <= delx; i++)
    {
        putpixel(x, y, color);
        delay(10);
        if (e >= 0)
        {
            if (interchange == 1)
                x = x + s1;
            else
                y = y + s2;
            e = e - 2 * delx;
        }
        if (interchange == 1)
            y = y + s2;
        else
            x = x + s1;
        e = e + 2 * dely;
    }
}
void drawCircle(int xc, int yc, int x, int y, int color)
{
    putpixel(xc + x, yc + y, color);
    putpixel(xc - x, yc + y, color);
    putpixel(xc + x, yc - y, color);
    putpixel(xc - x, yc - y, color);
    putpixel(xc + y, yc + x, color);
    putpixel(xc - y, yc + x, color);
    putpixel(xc + y, yc - x, color);
    putpixel(xc - y, yc - x, color);
}
void mp_Circle(int x_centre, int y_centre, int r, int color)
{
    int x = 0, y = r;
    int h = 1 - r;
    int delE = 3, delSE = (-2 * r) + 5;
    while (y >= x)
    {
        drawCircle(x_centre, y_centre, x, y, color);
        delay(10);
        if (h < 0)
        {
            h += delE;
            delE += 2;
            delSE += 2;
            x++;
        }
        else
        {
            h += delSE;
            delE += 2;
            delSE += 4;
            x++;
            y--;
        }
    }
}

void b_Circle(int xc, int yc, int r, int color)
{
    int x = 0, y = r;
    int d = 3 - (2 * r);
    drawCircle(xc, yc, x, y, color);
    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y, color);
        delay(10);
    }
}
void midellipse(int rx, int ry, int xc, int yc)
{
    FILE *fp = fopen("initpoints.txt", "w");
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    while (dx < dy)
    {
        delay(10);
        // putpixel(x + xc, y + yc, 5);
        putpixel(-x + xc, y + yc, 5);
        fprintf(fp, "%0.0f %0.0f \n", -x + xc, y + yc);
        // putpixel(x + xc, -y + yc, 5);
        putpixel(-x + xc, -y + yc, 5);
        fprintf(fp, "%0.0f %0.0f \n", -x + xc, -y + yc);
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);
    while (y >= 0)
    {
        delay(10);
        // putpixel(x + xc, y + yc, 5);
        putpixel(-x + xc, y + yc, 5);
        fprintf(fp, "%0.0f %0.0f \n", -x + xc, y + yc);
        // putpixel(x + xc, -y + yc, 5);
        putpixel(-x + xc, -y + yc, 5);
        fprintf(fp, "%0.0f %0.0f \n", -x + xc, -y + yc);

        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
    fclose(fp);
}
void readpoint()
{
    FILE *fp = fopen("initpoints.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%d %d", &xs[n], &ys[n]);
        // printf("%d %d\n", xs[n], ys[n]);
        n++;
    }
    fclose(fp);
}
void reflect()
{
    int i;
    int tempYaxis = xc;
    FILE *fp = fopen("initpoints.txt", "a");
    for (i = 0; i < n; i++)
        xs[i] = tempYaxis + (tempYaxis - xs[i]);

    for (i = 0; i < n; i++)
    {
        putpixel(xs[i], ys[i], WHITE);
        fprintf(fp, "%d %d \n", xs[i], ys[i]);
        delay(10);
    }
}
void rotate(float th)
{
    float r11, r12, r21, r22, x, y;
    r11 = cos((th * 3.1428) / 180);
    r12 = sin((th * 3.1428) / 180);
    r21 = (-sin((th * 3.1428) / 180));
    r22 = cos((th * 3.1428) / 180);
    for (int i = 0; i < n - 1; i++)
    {
        x = (((xs[i] - xc) * r11) - ((ys[i] - yc) * r12)) + xc;
        y = (((xs[i] - xc) * r12) + ((ys[i] - yc) * r11)) + yc;
        if (x > 639 || y > 479)
            continue;
        putpixel(abs(x), abs(y), YELLOW);
        delay(5);
    }
}
void petal()
{
    midellipse(30, 60, xc, yc - 100);
    readpoint();
    reflect();
    readpoint();
    int count = 7;
    int val = 360 / count;
    for (int i = val; i <= 360 - val; i += val)
    {
        rotate(i);
    }
}
int main()
{
    // system("clear");
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    mp_Circle(xc, yc, 20, RED);
    petal();
    getch();
    delay(1000);
    closegraph();
}