#include <stdio.h>
#include <graphics.h>
#include <math.h>
#define ROUND(n) ((int)(n + 0.1))
int array[20] = {0}, x[20] = {0};
int n1, dx, dy;
int tp1, res;
int max(int a, int b) { return (a > b) ? a : b; }

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int findgcd(int arr[], int n)
{
    int result = arr[0];
    for (int i = 1; i < n; i++)
    {
        result = gcd(arr[i], result);

        if (result == 1)
        {
            return 1;
        }
    }
    return result;
}
void grid()
{
    int i, j;
    for (i = 0; i < 640; i++)
        putpixel(i, 0, 1);
    for (i = 0; i < 480; i++)
        putpixel(0, i, 1);
    for (i = 0; i < 640; i++)
        putpixel(i, 479, 1);
    for (i = 0; i < 480; i++)
        putpixel(639, i, 1);
    for (i = 1; i < 480; i += dx)
    {
        for (j = 1; j < 640; j += dy)
            putpixel(j, i, 1);
    }
    delay(1000);
}
void pixel(int x, int y, int c)
{
    for (int i = x; i <= x + dx + 40; i++)
    {
        for (int j = y; j <= y + dy; j++)
        {
            putpixel(i, j, c);
        }
    }
}
void bigpixel(int x, int y, int c)
{
    int i = 0, j = 0;
    i = dx * (x - 1);
    j = dy * (y - 1);
    pixel(i, j, c);
}
void DDA(int x1, int y1, int x2, int y2, int c1)
{
    int d = 1;
    int L = abs(x2 - x1);
    if (abs(y2 - y1) > L)
        L = abs(y2 - y1);
    float xinc = (x2 - x1) / (float)L;
    float yinc = (y2 - y1) / (float)L;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= L; i++)
    {
        bigpixel(ROUND(x), ROUND(y), c1);
        x = x + xinc;
        y = y + yinc;
    }
}
int printknapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n + 1][W + 1];
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] +
                                  K[i - 1][w - wt[i - 1]],
                              K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int res1 = K[n][W];
    res = K[n][W];
    // printf("%d\n", res);

    w = W;

    n1 = 0;
    for (i = n; i > 0 && res > 0; i--)
    {

        if (res == K[i - 1][w])
            continue;
        else
        {

            array[n1] = val[i - 1];
            n1++;
            res = res - val[i - 1];
            w = w - wt[i - 1];
        }
    }
    return res1;
}
double p[20];

void knapsack(int n, float weight[], float profit[], int capacity)
{
    float x[20];
    float tp = 0;
    int i, j, u;
    u = capacity;

    for (i = 0; i < n; i++)
        x[i] = 0.0;

    for (i = 0; i < n; i++)
    {
        if (weight[i] > u)
            break;
        else
        {
            x[i] = 1.0;
            tp = tp + profit[i];
            u = u - weight[i];
        }
    }

    if (i < n)
        x[i] = u / weight[i];

    tp = tp + (x[i] * profit[i]);

    for (i = 0; i < n; i++)
        // printf("%f",profit[i]*x[i]);
        p[i] = profit[i] * x[i];
    // printf("%f",tp)
    tp1 = tp;
}

int main()
{
    float ratio[20], temp;
    int val[] = {6, 20, 12};
    int wt[] = {30, 20, 10};
    int n = sizeof(val) / sizeof(val[0]);
    float val1[20], wt1[20];
    int gc = findgcd(wt, n);
    int W = 50, i, j;
    int gd, gm;
    dx = gc, dy = gc;

    for (int i = 0; i < n; i++)
    {
        val1[i] = val[i];
        wt1[i] = wt[i];
    }
    int res1 = printknapSack(W, wt, val, n);
    for (i = 0; i < n; i++)
    {
        ratio[i] = val1[i] / wt1[i];
    }

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (ratio[i] < ratio[j])
            {
                temp = ratio[j];
                ratio[j] = ratio[i];
                ratio[i] = temp;

                temp = wt1[j];
                wt1[j] = wt1[i];
                wt1[i] = temp;

                temp = val1[j];
                val1[j] = val1[i];
                val1[i] = temp;
            }
        }
    }

    knapsack(n, wt1, val1, W);
    // printf("%d %d",res,tp1);
    gd = DETECT;
    initgraph(&gd, &gm, NULL);
    grid();
    printf("\nY-Axis---->Profit(**shown in different color for different values)\n");
    printf("\nprofit for fractional knapsack: %d", tp1);
    printf("\nprofit for 0/1 knapsack: %d", res1);
    printf("\n\nDifference of Profit :( %d-%d) = %d", tp1, res1, abs(res1 - tp1));
    outtextxy(30, 100, "Barchart for 0/1 knapsack");
    outtextxy(350, 100, "Barchart for fractional Knapsack");

    delay(100);
    int x_axis = 100 / dx, y_axis = 480 / dy;
    for (int i = 0; i < n1; i++)
    {
        DDA(x_axis, y_axis, x_axis, y_axis - array[i], i + 1);
        y_axis = y_axis - array[i];
    }
    x_axis += 350 / dx, y_axis = 480 / dy;
    int point[20];
    for (int i = 0; i < n; i++)
    {
        point[i] = p[i];
    }
    for (int i = 0; i < n; i++)
    {
        DDA(x_axis, y_axis, x_axis, y_axis - point[i], i + 3);
        y_axis = y_axis - point[i];
    }
    getch();
    delay(1000);
    closegraph();
    return 0;
}