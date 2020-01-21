#include<graphics.h>
#define RES 5
#define LEN 2
void bigpixel(int x,int y,int c)
{
    int i,j;
    for(i=x;i<=x+RES;i++)
	{
		for(j=y;j<=y+RES;j++)
		{
			putpixel(j, i, c);
		}
	}
}
void crossbar(int x,int y,int c)
{
    int i;
    for(i=1;i<=LEN;i++)
    {
        bigpixel(x+i*RES,y,c);
        bigpixel(x-i*RES,y,c);
        bigpixel(x,y+i*RES,c);
        bigpixel(x,y-i*RES,c);
    }
    bigpixel(x,y,BLACK);
}
int main()
{
    
    int x1,y1,y2,x2,i;
    printf("Enter Coodinates 1 ");
    scanf("%d %d",&x1,&y1);
    printf("Enter Coodinates 2 ");
    scanf("%d %d",&x2,&y2);
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    crossbar(x1,y1,WHITE);
    crossbar(x2,y2,WHITE);
    delay(1000000);
    closegraph();
    return 0;
}