#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "picker.h"

int canvas_window;
int color_window;

int p_height = 500;
int p_width = 150;

const int n_colors = 4;

bool color_window_open = false;

float a[n_colors][3] = {  
   { 0.1, 0.5, 0.2 } ,
   { 0.2, 0.2, 0.7 } ,
   { 0.5, 0, 0.5 } ,
   { 0.5, 0.5, 0.5 }
};

void init_2()
{
    // Set the clear color to white
    glClearColor(1.0,1.0,1.0,1);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1, 1.0, -1, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLineStipple(3, 0xAAAA);
}

void display_2(void)
{
	
	glClearColor(1.0,1.0,1.0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	int x = 75;
	int y = 250;
	int r = (p_width-x) / 4.0;

	for (int i = 0; i < n_colors; i++) {
		glColor3f(a[i][0], a[i][1], a[i][2]);

		glBegin(GL_POLYGON);
	        glVertex2f(x - r, y - r);
	        glVertex2f(x - r, y + r);
	        glVertex2f(x + r, y + r);
	        glVertex2f(x + r, y - r);
	    glEnd();

		x = p_width - x;

	    if (i%2 == 0) {

	    } else {
	    	// x = p_width - x;
	    	y += x;
	    }
	}

	glFlush();
}

// button = { GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON }
// state = { GLUT_UP, GLUT_DOWN }
void mouseCallback_2(int button, int state, int x, int y)
{
    printf("%d, %d\n", x, y);
}

void keyboardCallback_2(unsigned char key, GLint x, GLint y)
{
    switch (key)
    {
        // c
        case 99:
          color_window_open = false;
          glutSetWindow( color_window );
			glutHideWindow();
			glutSetWindow( canvas_window
		 );
          break;

    }

}

void reshapeCallback_2(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, p_width, 0, p_height);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_MODELVIEW);
	glutReshapeWindow( p_width, p_height);
}

void createColorPicker()
{
    // Create second window
    glutInitWindowPosition(700 + 10, 100);
    glutInitWindowSize(p_width, p_height);
    // glutInitWindowSize(700, 700);
    color_window = glutCreateWindow("Color Picker");
    glutKeyboardFunc(keyboardCallback_2);
    glutDisplayFunc(display_2);
    glutReshapeFunc(reshapeCallback_2);
    glutHideWindow();
}

void openColorPicker()
{
    glutSetWindow( color_window );
	glutShowWindow();
	glutSetWindow( canvas_window );

    color_window_open = true;
}

















