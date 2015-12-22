#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "picker.h"

int canvas_window;
int color_window;

const int n_colors = 8;

const int colorSize = 30;
const int colorMargin = 10;

int p_height = 500;
int p_width = 2 * colorSize + 3 * colorMargin;

bool color_window_open = false;

float a[n_colors][3] = {  
	{ 0, 0, 0 } ,
	{ 1, 0, 0 } ,
	{ 0, 1, 0 } ,
	{ 0, 0, 1 } ,
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

	int x = colorMargin;
	int y = p_height - colorMargin;

	for (int i = 0; i < n_colors; i++) {

		if (selectedColor == i) {
		
			glColor3f(0, 0, 0);

			glBegin(GL_POLYGON);
		        glVertex2f(x - 5, y + 5);
		        glVertex2f(x - 5, y - colorSize - 5);
		        glVertex2f(x + colorSize + 5, y - colorSize - 5);
		        glVertex2f(x + colorSize + 5, y + 5);
		    glEnd();

		    glColor3f(1, 1, 1);

			glBegin(GL_POLYGON);
		        glVertex2f(x - 1, y + 1);
		        glVertex2f(x - 1, y - colorSize - 1);
		        glVertex2f(x + colorSize + 1, y - colorSize - 1);
		        glVertex2f(x + colorSize + 1, y + 1);
		    glEnd();
		}

		glColor3f(a[i][0], a[i][1], a[i][2]);

		glBegin(GL_POLYGON);
	        glVertex2f(x, y);
	        glVertex2f(x, y - colorSize);
	        glVertex2f(x + colorSize, y - colorSize);
	        glVertex2f(x + colorSize, y);
	    glEnd();

	    if (i%2 == 0) {
	    	x = p_width - colorSize - colorMargin;

	    } else {
	    	x = colorMargin;
	    	y -= colorSize + colorMargin;
	    }
	}

	glFlush();
}

// button = { GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON }
// state = { GLUT_UP, GLUT_DOWN }
void mouseCallback_2(int button, int state, int x, int y)
{
	int newColor = y / (colorSize + colorMargin) * 2;
	if (x > p_width / 2)
	{
		newColor++;
	}
	if (newColor <= n_colors) {
		selectedColor = newColor;
		custom_color[0] = a[selectedColor][0];
		custom_color[1] = a[selectedColor][1];
		custom_color[2] = a[selectedColor][2];
		custom_color[3] = a[selectedColor][3];

		glutSetWindow(color_window);
		glutPostRedisplay();
		glutSetWindow(canvas_window);
	}
	// printf("X: %d, Y: %d, Index: %d\r\n", x, y, selectedColor);
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
    glutInitWindowPosition(700 + 100, 100);
    glutInitWindowSize(p_width, p_height);
    // glutInitWindowSize(700, 700);
    color_window = glutCreateWindow("Color Picker");
    glutKeyboardFunc(keyboardCallback_2);
    glutDisplayFunc(display_2);
    glutReshapeFunc(reshapeCallback_2);
    glutMouseFunc(mouseCallback_2);
    glutHideWindow();
}

void openColorPicker()
{
    glutSetWindow( color_window );
	glutShowWindow();
	glutSetWindow( canvas_window );

    color_window_open = true;
}

















