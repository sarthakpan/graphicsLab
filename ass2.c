#include<graphics.h>
#define RES 5
#define LEN 2
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

int main()
{
    
    int x1,y1,y2,x2,i;
    printf("Enter Coodinates 1 ");
    scanf("%d %d",&x1,&y1);
    printf("Enter Coodinates 2 ");
    scanf("%d %d",&x2,&y2);
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    putpixel(x1,y1,RED);
    for(i=1;i<=LEN;i++)
    {
        putpixel(x1+i*RES,y1,WHITE);
        putpixel(x1-i*RES,y1,WHITE);
        putpixel(x1,y1+i*RES,WHITE);
        putpixel(x1,y1-i*RES,WHITE);
    }
    putpixel(x2,y2,GREEN);
    for(i=1;i<=LEN;i++)
    {
        putpixel(x2+i*RES,y2,WHITE);
        putpixel(x2-i*RES,y2,WHITE);
        putpixel(x2,y2+i*RES,WHITE);
        putpixel(x2,y2-i*RES,WHITE);
    }
    DDA(x1,y1,x2,y2);
    delay(1000000);
    closegraph();
    return 0;
}
