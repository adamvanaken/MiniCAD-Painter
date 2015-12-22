#include <GLUT/glut.h>

#include <stdio.h>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

typedef int bool;
#define true 1
#define false 0

int numLines;
typedef enum state
{
waitingforclick,
clickedonce,
} state;

typedef struct point
{
int x;
int y;
}point;


point lines[256][2] ;


int gState=waitingforclick;
bool lineisvalid=false;
int gHeight;
float gColor[3]={0,1,0};

void drawlines()
{
glColor3fv(gColor);
glBegin(GL_LINES);
for(int i=0; i<=numLines; i++)
{
glVertex2i(lines[i][0].x, gHeight-lines[i][0].y);
glVertex2i(lines[i][1].x, gHeight-lines[i][1].y);
}
glEnd();
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
drawlines();
glutSwapBuffers();
}

void menufunc(int val)
{
switch (val)
{
case 0:
gColor[0]=1;
gColor[1]=0;
gColor[2]=0;
break;
case 1:
gColor[0]=0;
gColor[1]=1;
gColor[2]=0;
break;
case 2:
gColor[0]=0;
gColor[1]=0;
gColor[2]=1;
break;
}
}

void createMenu()
{
int menu=glutCreateMenu(menufunc);
glutAddMenuEntry("Red", 0);
glutAddMenuEntry("Green", 1);
glutAddMenuEntry("Blue", 2);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void init()
{
glClearColor(0,0,0,1);
glMatrixMode(GL_PROJECTION);
glOrtho(-1, 1.0, -1, 1.0, -1.0, 1.0);
numLines=-1;
glMatrixMode(GL_MODELVIEW);
createMenu();
}

void reshape(int width, int height)
{
gHeight=height;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0, width, 0,height);

glMatrixMode(GL_MODELVIEW);
}


void mouseclick(int button, int state,int x, int y)
{
if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
{
switch(gState)
{

case waitingforclick:
printf("one clidk");
++numLines;
lines[numLines][0].x=x;
lines[numLines][0].y=y;
lines[numLines][1].x=x;
lines[numLines][1].y=y;
gState++;
break;
case clickedonce:
printf("2 clidk");
lines[numLines][1].x=x;
lines[numLines][1].y=y;
gState=waitingforclick; 
break;
}
}
glutPostRedisplay();
}

void mousedrag(int x, int y)
{
if(gState==clickedonce)
{lines[numLines][1].x=x;
lines[numLines][1].y=y;
}
glutPostRedisplay();
}

int main(int argc, char ** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
glutInitWindowPosition(100,100);
glutInitWindowSize(500,500);
glutCreateWindow("My Drawing App");
glutReshapeFunc(reshape);
glutDisplayFunc(display);
glutMouseFunc(mouseclick);
glutPassiveMotionFunc(mousedrag);

init();
glutMainLoop();
return 0;
}