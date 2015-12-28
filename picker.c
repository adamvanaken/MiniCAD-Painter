#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "picker.h"

int color_window;

const int n_colors = 8;

const int colorSize = 30;
const int colorMargin = 10;

const int p_height = 500;
const int p_width = 2 * colorSize + 3 * colorMargin;

#define max_width p_width + picker_size

int picker_size = p_height - colorMargin - colorMargin;

bool color_window_open = false;

float color_palette[n_colors][4] = {  
	{ 0, 0, 0, 1 } ,
	{ 1, 0, 0, 1 } ,
	{ 0, 1, 0, 1 } ,
	{ 0, 0, 1, 1 } ,
	{ 0.1, 0.5, 0.2, 1 } ,
	{ 0.2, 0.2, 0.7, 1 } ,
	{ 0.5, 0, 0.5, 1 } ,
	{ 0.5, 0.5, 0.5, 1 }
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

		glColor3f(color_palette[i][0], color_palette[i][1], color_palette[i][2]);

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

	int x_off = p_width + colorMargin;
	int y_off = p_height - colorMargin;

	glBegin(GL_POINTS);
	for (float i = 0; i < 360; i++)
	{
		for (float j = 0; j < 1; j += 0.01) {

			// float r = 181;
			float r = i;
			float g = 1;
			// float b = 0.5;
			float b = j;
			
			// printf("%f, %f, %f ", r, g, b);

			hsl_to_rgb(&r, &g, &b);
			glColor3f(r, g, b);

			// printf("%f, %f, %f\r\n", r, g, b);

			
			glVertex2f(x_off + i, y_off - (100 * j));
		}
	}
	glEnd();

	glFlush();
}

void updatePickedColor(int x, int y)
{
	// selectedColor = 0;

	float h = x - colorSize - colorMargin - colorMargin - colorMargin - colorMargin - colorSize;
	float s = 1;
	float l = (y - colorMargin) / 100.0;

	hsl_to_rgb(&h, &s, &l);

	color_palette[selectedColor][0] = h;
	color_palette[selectedColor][1] = s;
	color_palette[selectedColor][2] = l;
	glutSetWindow(color_window);
	glutPostRedisplay();
	glutSetWindow(canvas_window);

	custom_color[0] = color_palette[selectedColor][0];
	custom_color[1] = color_palette[selectedColor][1];
	custom_color[2] = color_palette[selectedColor][2];
	custom_color[3] = color_palette[selectedColor][3];
}

void motionCallback_2(int x, int y)
{
	if (x >= colorSize + colorSize + colorMargin + colorMargin + colorMargin && x <= colorSize + colorSize + colorMargin + colorMargin + colorMargin + 360 && y <= 100 + colorMargin && y >= colorMargin)
	{
    	updatePickedColor(x, y);
	}
}

// button = { GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON }
// state = { GLUT_UP, GLUT_DOWN }
void mouseCallback_2(int button, int state, int x, int y)
{
	if (x < colorSize + colorMargin + colorSize + colorMargin) {
		int newColor = y / (colorSize + colorMargin) * 2;
		if (x > p_width / 2)
		{
			newColor++;
		}
		if (newColor <= n_colors) {
			selectedColor = newColor;
			custom_color[0] = color_palette[selectedColor][0];
			custom_color[1] = color_palette[selectedColor][1];
			custom_color[2] = color_palette[selectedColor][2];
			custom_color[3] = color_palette[selectedColor][3];

			glutSetWindow(color_window);
			glutPostRedisplay();
			glutSetWindow(canvas_window);
		}
		// printf("X: %d, Y: %d, Index: %d\r\n", x, y, selectedColor);

	} else if (x >= colorSize + colorSize + colorMargin + colorMargin + colorMargin && x <= colorSize + colorSize + colorMargin + colorMargin + colorMargin + 360 && y <= 100 + colorMargin && y >= colorMargin){
		updatePickedColor(x, y);
	}
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
	gluOrtho2D(0, max_width, 0, p_height);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_MODELVIEW);
	glutReshapeWindow( max_width, p_height);
}

void createColorPicker()
{
    // Create second window
    glutInitWindowPosition(700 + 100, 100);
    glutInitWindowSize(max_width, p_height);
    // glutInitWindowSize(700, 700);
    color_window = glutCreateWindow("Color Picker");
    glutKeyboardFunc(keyboardCallback_2);
    glutDisplayFunc(display_2);
    glutReshapeFunc(reshapeCallback_2);
    glutMotionFunc(motionCallback_2);
    glutMouseFunc(mouseCallback_2);
    glEnable(GL_POINT_SMOOTH);
    glutHideWindow();
}

void openColorPicker()
{
    glutSetWindow( color_window );
	glutShowWindow();
	glutSetWindow( canvas_window );

    color_window_open = true;
}

















