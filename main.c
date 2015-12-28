// To suppress deprecation warnings
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// #include "draw.h"
#include "picker.h"

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

void display(void) {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    if (start != NULL)
    { 
        end = start;

        while (end != NULL)
        {
            glColor3f(end->color[0], end->color[1], end->color[2]);

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

    if (zoom_level != 0) {

        int w = WIDTH;
        int h = HEIGHT;
        int buf_size = w/2 * h/2 * 3 * sizeof(float);
        int p_size = pow(2, zoom_level);
        // glPointSize(p_size);

        // glBegin(GL_POINTS);
        int buf_idx = 0;
        for (int i = 0; i < 100; i += p_size) {
            printf("(%d, %d), %f, %f, %f\r\n", p_size * (i % w/2), p_size * (i / h/2), buf[buf_idx], buf[buf_idx+1], buf[buf_idx+2]);
            glColor3f(buf[buf_idx++], buf[buf_idx++], buf[buf_idx++]);
            glVertex2f(p_size * (i % w/2) + 100, p_size * (i / h/2) + 100);
            // glBegin(GL_POLYGON);
            //     glVertex2f(p_size * (i % w/2), p_size * (i / h/2));
            //     glVertex2f(p_size * (i % w/2) + p_size, p_size * (i / h/2));
            //     glVertex2f(p_size * (i % w/2) + p_size, p_size * (i / h/2) + p_size);
            //     glVertex2f(p_size * (i % w/2), p_size * (i / h/2) + p_size);
            // glEnd();
        }
        // glEnd();
    }
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
  // Initializes GLUT and processes commandline arguments, if any
  glutInit(&argc, argv);
  // glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(WIDTH,HEIGHT);

  // Make Main outer window
  canvas_window = glutCreateWindow("Window 1");

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

  glutSetWindow(canvas_window);

  glutMainLoop();

  return 0;
}