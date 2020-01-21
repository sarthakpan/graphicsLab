#include<graphics.h>
//#define RES 5
#define LEN 2
int RES;
void DDA(int X0, int Y0, int X1, int Y1) 
{ 
    int i;
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
    float X = X0; 
    float Y = Y0; 
    for (i = 0; i <= steps; i++) 
    { 
        putpixel (X,Y,RED); 
        X += Xinc;           
        Y += Yinc;  
        delay(10);      
    } 
} 
void bigpixel(int x,int y,int c,int RES)
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
void crossbar(int x,int y,int c,int RES)
{
    int i;
    for(i=1;i<=LEN;i++)
    {
        bigpixel(x+i*RES,y,c,RES);
        bigpixel(x-i*RES,y,c,RES);
        bigpixel(x,y+i*RES,c,RES);
        bigpixel(x,y-i*RES,c,RES);
    }
    bigpixel(x,y,BLACK,RES);
}
int main()
{
    
    int x1,y1,y2,x2,i,ch;
    printf("Enter Coodinates 1 ");
    scanf("%d %d",&x1,&y1);
    printf("Enter Coodinates 2 ");
    scanf("%d %d",&x2,&y2);
    printf("Enter algo 1 for DDA 2 brasanham");
    scanf("%d",&ch);
    printf("Enter Resolution 0 for default");
    scanf("%d",&RES);
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    if(RES!=0)
    {
        crossbar(x1,y1,WHITE,RES);
        crossbar(x2,y2,WHITE,RES);
    }
    else if(RES==0)
    {
        putpixel(x1,y1,RED);
        for(i=1;i<=LEN;i++)
        {
            putpixel(x1+i,y1,WHITE);
            putpixel(x1-i,y1,WHITE);
            putpixel(x1,y1+i,WHITE);
            putpixel(x1,y1-i,WHITE);
        }
        putpixel(x2,y2,GREEN);
        for(i=1;i<=LEN;i++)
        {
            putpixel(x2+i,y2,WHITE);
            putpixel(x2-i,y2,WHITE);
            putpixel(x2,y2+i,WHITE);
            putpixel(x2,y2-i,WHITE);
        }
    }
    DDA(x1,y1,x2,y2);
    delay(1000000);
    closegraph();
    return 0;
}
