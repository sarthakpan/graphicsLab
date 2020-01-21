#include<graphics.h>
#define RES 5
#define LEN 2

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
    delay(1000000);
    closegraph();
    return 0;
}