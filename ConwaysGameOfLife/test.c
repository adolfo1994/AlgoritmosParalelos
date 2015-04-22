/*  demo.c*/
#include<graphics.h> 
int main()
{
   int gd = DETECT,gm,left=100,top=100,right=200,bottom=200,x= 300,y=150,radius=50;
   initgraph(&gd,&gm,NULL);
   /*rectangle(left, top, right, bottom);
   circle(x, y, radius);
   bar(left + 300, top, right + 300, bottom);
   line(left - 10, top + 150, left + 410, top + 150);
   ellipse(x, y + 200, 0, 360, 100, 50);
   outtextxy(left + 100, top + 325, "C Graphics Program");
*/
int i = 0;
int j = 0;
int diff = 1;

   while(1){
    putpixel(i, j, RED);
    i += diff;
    j += diff;
    if(i>200)
       diff = -1;
    if(i < 10)
       diff = 1;
    delay(500);
}
   delay(5000);
   closegraph();
   return 0;
}
