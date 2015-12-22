#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// To suppress deprecation warnings
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "draw.c"

void init() {
    // Set the clear color to white
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1, 1.0, -1, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLineStipple(3, 0xAAAA);

    create_linked_list();

    currentTool = t_RECT;
    currentColor = c_BLACK;
}

// void display2(void)
// {
// glClearColor(1.0,1.0,1.0,1);
// glClear(GL_COLOR_BUFFER_BIT);
// glLoadIdentity();
// printf("display2\n");
// glFlush();
// }

void display(void) {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    if (start != NULL)
    { 
        end = start;

        while (end != NULL)
        {
            // Set the drawing color
            switch (end->color)
            {
              case c_BLACK:
                glColor3f(0.0, 0.0, 0.0);
                break;
              case c_RED:
                glColor3f(1.0, 0.0, 0.0);
                break;
              case c_GREEN:
                glColor3f(0.0, 1.0, 0.0);
                break;
              case c_BLUE:  
                glColor3f(0.0, 0.0, 1.0);
                break;
            }

            if (end->filled)
            {
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            }
            else
            {
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            }

            if (end->type == INT)
            {
                //printf("%d\n", ((Integer *)end->num)->data);
            }
            else if (end->type == DOUBLE)
            {
                //printf("%f\n", ((Double *)end->num)->data);
            }
            else if (end->type == LINE)
            {
                glBegin(GL_LINES);
                    glVertex2f(((Line *)end->shape)->x1, ((Line *)end->shape)->y1);
                    glVertex2f(((Line *)end->shape)->x2, ((Line *)end->shape)->y2);
                glEnd();

                // printf("%f\n", ((Line *)end->shape)->x1);
                // printf("%f\n", ((Line *)end->shape)->x2);
                // printf("%f\n", ((Line *)end->shape)->y1);
                // printf("%f\n", ((Line *)end->shape)->y2);
            }
            else if (end->type == TRI)
            {
                DrawShape(((Triangle *)end->shape)->p, 3);
            }
            else if (end->type == RECT)
            {
                DrawShape(((Rectangle *)end->shape)->p, 4);
            }
            else if (end->type == CIRCLE)
            {
                DrawCircle(((Circle *)end->shape)->x, ((Circle *)end->shape)->y, ((Circle *)end->shape)->r, end->filled);
            }
            else if (end->type == LINE)
            {
                DrawLine_Out(mouseX, mouseY, mouseMoveX, mouseMoveY);
            }
            else if (end->type == POLY)
            {
                DrawPoly(((Poly *)end->shape));
            }

            if (end->next == NULL)
            {
                break;
            }

            end = end->next;
        }
    }

    if (drawing)
    {
        switch (currentTool)
        {
            case t_RECT:
                DrawRect4_Out(mouseX, mouseY, mouseMoveX, mouseMoveY);
                break;
            case t_TRI:
                DrawTri_Out(mouseX, mouseY, mouseMoveX - mouseX, mouseY - mouseMoveY);
                break;
            case t_CIRCLE:
                glColor3f(0, 0, 0);
                DrawCircle(mouseX, mouseY, Distance(mouseX, mouseY, mouseMoveX, mouseMoveY), false);
                break;
            case t_LINE:
                DrawLine_Out(mouseX, mouseY, mouseMoveX, mouseMoveY);
                break;
            case t_POLY:
                DrawPolyLine(customPoly, mouseMoveX, mouseMoveY);
                break;
        }
    }
    else if (toolSelect)
    {
        DrawToolSelect(mouseX, mouseY);
    }
    
    // Flush the buffer to force drawing of all objects thus far
    //glFlush();
    glutSwapBuffers();
}

// void display_both(void) {

//     glutSetWindow( window_1 );
//     display();  // Update screen with new rotation data
 
//     if (window_2_open) {
//         glutSetWindow( window_2 );
//         display_2();  // Update screen with new rotation data
//     }

// }

int main(int argc, char **argv) {
  // Initializes GLUT and processes commandline arguments, if any
  glutInit(&argc, argv);
  // glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(WIDTH,HEIGHT);

    // Make Main outer window
    window_1 = glutCreateWindow("Window 1");

  // Callback Registration
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardCallback);
  glutKeyboardUpFunc(keyboardUpCallback);
  glutMouseFunc(mouseCallback);
  glutMotionFunc(motionCallback);
  glutPassiveMotionFunc(passiveMotionCallback);
  glutSpecialFunc(specialCallback);
  glutSpecialUpFunc(specialUpCallback);
  glutReshapeFunc(reshapeCallback);
  init();

  createColorPicker();

  glutSetWindow(window_1);

  // Pass program control to tk's event handling code
  // In other words, loop forever
  glutMainLoop();

  return 0;
}