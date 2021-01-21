#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 3
int RES = 1;

void bigpixel(int x, int y, int colour)
{
    int i, j;
    for (i = x; i <= x + RES; ++i)
    {
        for (j = y; j <= y + RES; ++j)
        {
            if ((i >= 0 && i <= 639) && (j >= 0 && j <= 479))
                putpixel(i, j, colour);
        }
    }
}

void cross(int x, int y, int color)
{
    int i;
    x = x * RES;
    y = y * RES;
    for (i = 1; i <= LEN; i++)
    {
        bigpixel(x + i * RES, y, color);
        bigpixel(x - i * RES, y, color);
        bigpixel(x, y + i * RES, color);
        bigpixel(x, y - i * RES, color);
    }
    bigpixel(x, y, BLACK);
}
void grid()
{
    int i, j;
    for (i = 0; i < 640; i = i + RES)
    {
        for (j = 0; j < 480; j = j + RES)
        {
            putpixel(i, j, RED);
        }
    }
}
void animation()
{
    int t = 10, x, y;
    while (t--)
    {
        x = rand() % (640 / RES);
        y = rand() % (480 / RES);
        cross(x, y, WHITE);
        delay(1000);
        cross(x, y, 0);
        grid();
    }
}
void mypixel(int x, int y, int color)
{
    x = x * RES;
    y = y * RES;
    bigpixel(round(x), round(y), color);
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
        mypixel(x, y, color);
        x = x + xinc;
        y = y + yinc;
        delay(100);
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
        mypixel(x, y, color);
        delay(100);
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
void mp_Circle(int x_centre, int y_centre, int r, int color)
{
    int x = 0, y = r;
    int h = 1 - r;
    int delE = 3, delSE = (-2 * r) + 5;
    while (y >= x)
    {
        drawCircle(x_centre, y_centre, x, y, color);
        delay(100);
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
void drawCircle(int xc, int yc, int x, int y, int color)
{
    mypixel(xc + x, yc + y, color);
    mypixel(xc - x, yc + y, color);
    mypixel(xc + x, yc - y, color);
    mypixel(xc - x, yc - y, color);
    mypixel(xc + y, yc + x, color);
    mypixel(xc - y, yc + x, color);
    mypixel(xc + y, yc - x, color);
    mypixel(xc - y, yc - x, color);
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
        delay(200);
    }
}
void midellipse(int rx, int ry, int xc, int yc)
{
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    while (dx < dy)
    {
        delay(100);
        mypixel(x + xc, y + yc, 5);
        mypixel(-x + xc, y + yc, 5);
        mypixel(x + xc, -y + yc, 5);
        mypixel(-x + xc, -y + yc, 5);

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
        delay(100);
        mypixel(x + xc, y + yc, 5);
        mypixel(-x + xc, y + yc, 5);
        mypixel(x + xc, -y + yc, 5);
        mypixel(-x + xc, -y + yc, 5);

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
}
int main()
{
    system("clear");
    int gd = DETECT;
    int gm, i, j, k, r, wy, wx;
    int x1, y1, x2, y2, a, b;
    int choice = 1;
    int pixel_RES;
    while (choice)
    {
        printf("\n1. Set Pixel RES\n2. Animate Cursor\n");
        printf("3. Set two cursor & draw DDA line\n");
        printf("4. Set two cursor & draw Bresenhem line\n");
        printf("5. Draw circle using Midpoint\n");
        printf("6. Draw circle using Bresenham\n");
        printf("7. Draw ellipse\n");
        printf("\n\nEnter your choice :");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            scanf("%d", &RES);
            break;
        case 2:
            initgraph(&gd, &gm, "");
            grid();
            animation();
            getch();
            closegraph();
            break;
        case 3: //DDA
            printf("Enter 1st co-ordinate: Limit (x:%d & y:%d)", 640 / RES, 480 / RES);
            scanf("%d %d", &x1, &y1);
            printf("Enter 2nd co-ordinate: Limit (x:%d & y:%d)", 640 / RES, 480 / RES);
            scanf("%d %d", &x2, &y2);
            if ((x1 > (640 / RES)) || (x2 > (640 / RES)) || (y1 > (480 / RES)) || (y2 > 480 / RES))
            {
                printf("Out of Ranage");
                break;
            }
            initgraph(&gd, &gm, "");
            grid();
            cross(x1, y1, WHITE);
            cross(x2, y2, WHITE);
            dda(x1, y1, x2, y2, GREEN);
            getch();
            closegraph();
            break;
        case 4: //Bresenhem
            printf("Enter 1st co-ordinate: Limit (x:%d & y:%d)", 640 / RES, 480 / RES);
            scanf("%d %d", &x1, &y1);
            printf("Enter 2nd co-ordinate: Limit (x:%d & y:%d)", 640 / RES, 480 / RES);
            scanf("%d %d", &x2, &y2);
            if ((x1 > (640 / RES)) || (x2 > (640 / RES)) || (y1 > (480 / RES)) || (y2 > 480 / RES))
            {
                printf("Out of Ranage");
                break;
            }
            initgraph(&gd, &gm, "");
            grid();
            cross(x1, y1, WHITE);
            cross(x2, y2, WHITE);
            dda(x1, y1, x2, y2, GREEN);
            Bresenham(x1, y1, x2, y2, YELLOW);
            getch();
            closegraph();
            break;
        case 5:
            printf("Enter center: Limit (x:%d & y:%d) and radius", 640 / RES, 480 / RES);
            scanf("%d %d %d", &x1, &y1, &r);
            initgraph(&gd, &gm, "");
            //grid();
            circle(x1, y1, r);
            mp_Circle(x1, y1, r, YELLOW);
            getch();

            closegraph();
            break;
        case 6:
            printf("Enter center: Limit (x:%d & y:%d) and radius", 640 / RES, 480 / RES);
            scanf("%d %d %d", &x1, &y1, &r);
            initgraph(&gd, &gm, "");
            //grid();
            mypixel(x1, y1, WHITE);
            circle(x1, y1, r);
            //mp_Circle(x1, y1, r, GREEN);
            delay(50);
            b_Circle(x1, y1, r, CYAN);
            getch();
            delay(1000);
            closegraph();
            break;
        case 7:
            printf("Enter center: Limit (x:%d & y:%d) and major and minor axis", 640 / RES, 480 / RES);
            scanf("%d %d %d %d", &x1, &y1, &a, &b);
            initgraph(&gd, &gm, "");
            grid();
            mypixel(x1, y1, 5);
            midellipse(a, b, x1, y1);
            getch();
            delay(1000);
            closegraph();
            break;
        default:
            choice = 0;
            break;
        }
    }
}