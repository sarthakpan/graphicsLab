#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int xc = 50, yc = 135, n = 0;
int xs[1000], ys[1000];
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
        delay(5);
        // putpixel(x + xc, y + yc, 5);
        // putpixel(-x + xc, y + yc, 5);
        putpixel(x + xc, -y + yc, 5);
        fprintf(fp, "%0.0f %0.0f\n", x + xc, -y + yc);
        putpixel(-x + xc, -y + yc, 5);
        fprintf(fp, "%0.0f %0.0f\n", -x + xc, -y + yc);

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
        delay(5);
        // putpixel(x + xc, y + yc, 5);
        // putpixel(-x + xc, y + yc, 5);
        putpixel(x + xc, -y + yc, 5);
        fprintf(fp, "%0.0f %0.0f\n", x + xc, -y + yc);
        putpixel(-x + xc, -y + yc, 5);
        fprintf(fp, "%0.0f %0.0f\n", -x + xc, -y + yc);
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
    int tempYaxis = getmaxx() / 2;
    for (i = 0; i < n; i++)
        xs[i] = tempYaxis + (tempYaxis - xs[i]);

    for (i = 0; i < n; i++)
    {
        putpixel(xs[i], ys[i], WHITE);
        delay(2);
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
        xs[i] = (((xs[i]) * r11) - ((ys[i]) * r12));
        ys[i] = (((xs[i]) * r12) + ((ys[i]) * r11));
        // putpixel((x), (y), YELLOW);
        // delay(5);
    }
}
void scale(float sx, float sy)
{
    float x, y;
    for (int i = 0; i < n - 1; i++)
    {
        xs[i] = xs[i] * sx;
        ys[i] = ys[i] * sy;
        // putpixel(abs(x), abs(y), YELLOW);
        // delay(5);
    }
}
void tranlation(float t1, float t2)
{
    for (int i = 0; i < n - 1; i++)
    {
        xs[i] = xs[i] + t1;
        ys[i] = ys[i] + t2;
        // putpixel(abs(x), abs(y), YELLOW);
        // delay(5);
    }
}
void printpoint(int color)
{
    for (int i = 0; i < n - 1; i++)
    {
        putpixel(xs[i], ys[i], color);
        delay(2);
    }
}
void appendpoint()
{
    FILE *fp = fopen("initpoints.txt", "a");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d %d\n", xs[i], ys[i]);
    }
    fclose(fp);
}
void wave()
{
    midellipse(40, 30, xc, yc - 100);
    readpoint();
    scale(0.5, 0.5);
    tranlation(-yc, -xc);
    rotate(180);
    printpoint(YELLOW);
    appendpoint();
    readpoint();
    for (int i = 1; i <= 1; i++)
    {
        tranlation(xc + yc / 2, 0);
        appendpoint();
        printpoint(RED);
    }
    readpoint();
    reflect();
    for (int i = 0; i < 5; i++)
    {
        tranlation(0, 50);
        printpoint(GREEN);
    }
}
int main()
{
    // system("clear");
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    wave();
    getch();
    delay(1000);
    closegraph();
}