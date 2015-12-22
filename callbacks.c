#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "callbacks.h"

int WIDTH = 700, HEIGHT = 700;

// enum Tool { t_LINE = 0, t_TRI, t_RECT, t_CIRCLE, t_POLY } ;

enum Tool currentTool;

bool toolSelectDrawn = false;
bool toolSelect = false;
double mouseX, mouseY;
double mouseMoveX, mouseMoveY;

bool drawing = false;
bool drawPoly = false;

void setTool(int x, int y)
{
    float distance = Distance(mouseX, mouseY, x, HEIGHT - y);
    if (distance <= 20)
    {
        currentTool = t_LINE;
    }
    else
    {
        float deltaY = (HEIGHT - y) - mouseY;
        float deltaX = x - mouseX;
        if (fabsf(deltaY) > fabsf(deltaX))
        {
            if (deltaY > 0)
            {
                currentTool = t_TRI;
            }
            else
            {
                currentTool = t_CIRCLE;
            }
        }
        else
        {
            if (deltaX > 0)
            {
                currentTool = t_RECT;
            }
            else
            {
                currentTool = t_POLY;
            }
        }
    }
}

void setToolSelect(bool b, int x, int y)
{
    if (toolSelectDrawn && b)
    {
        return;
    }
    toolSelect = b;
    if (!toolSelect)
    {
        toolSelectDrawn = false;
        setTool(x, y);
    }
    else
    {
        toolSelectDrawn = true;
        mouseX = x;
        mouseY = HEIGHT - y;
    }
    glutPostRedisplay();
}

void reshapeCallback(int width, int height)
{
  HEIGHT=height;
  WIDTH=width;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WIDTH, 0,HEIGHT);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_MODELVIEW);
  //glutReshapeWindow(HEIGHT, WIDTH);
}

// int glutGetModifiers(void);
// GLUT_ACTIVE_SHIFT
// Set if the Shift modifier or Caps Lock is active.
// GLUT_ACTIVE_CTRL
// Set if the Ctrl modifier is active.
// GLUT_ACTIVE_ALT
// Set if the Alt modifier is active.
void keyboardCallback(unsigned char key, GLint x, GLint y)
{
    switch (key)
    {
        // escape, Q, q
        case 27:
        case 81:
        case 113:
          exit (0);
          break;
        // T
        case 84:
          setToolSelect(true, x, y);
          break; 
        // p
        case 112:
          openColorPicker();
          break;
        // r
        case 114:
          if (currentColor == c_RED)
            currentColor = c_BLACK;
          else
            currentColor = c_RED;
          break;
        // g
        case 103: 
          if (currentColor == c_GREEN)
            currentColor = c_BLACK;
          else
            currentColor = c_GREEN;
          break;
        // b
        case 98:
          if (currentColor == c_BLUE)
            currentColor = c_BLACK;
          else
            currentColor = c_BLUE;
          break;
        // f
        case 102:
          fill = !fill;
          if (fill)
          {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
          }
          else
          {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
          }
          break;
        // c
        case 99:
          Clear();
          break;
    }
}

void keyboardUpCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
        // T
        case 84:
            setToolSelect(false, x, y);
            break;
    }
}

void specialCallback(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            setToolSelect(true, x, y);
            break;
        case GLUT_KEY_F1:
            currentTool = t_LINE;
            break;
        case GLUT_KEY_F2:
            currentTool = t_TRI;
            break;
        case GLUT_KEY_F3:
            currentTool = t_RECT;
            break;
        case GLUT_KEY_F4:
            currentTool = t_CIRCLE;        
            break;
        case GLUT_KEY_F5:
            currentTool = t_POLY;
            break;
    }
}

void specialUpCallback(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            setToolSelect(false, x, y);
            break;
    }
}

void motionCallback(int x, int y)
{
    if (currentTool != t_POLY)
    {
        mouseMoveX = x;
        mouseMoveY = HEIGHT - y;
        glutPostRedisplay();
    }
}

void passiveMotionCallback(int x, int y)
{
    if (currentTool == t_POLY)
    {
        mouseMoveX = x;
        mouseMoveY = HEIGHT - y;
        glutPostRedisplay();
    }
}

// button = { GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON }
// state = { GLUT_UP, GLUT_DOWN }
void mouseCallback(int button, int state, int x, int y)
{
    glutPostRedisplay();  // Update screen with new rotation data

    switch (button)
    {
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN)
            {
                setToolSelect(true, x, y);
            }
            else
            {
                setToolSelect(false, x, y);
            }
            break;
        case GLUT_LEFT_BUTTON:
            switch (currentTool)
            {
                case t_RECT:
                    if (state == GLUT_DOWN)
                    {
                        mouseX = x;
                        mouseY = HEIGHT - y;
                        mouseMoveX = mouseX;
                        mouseMoveY = mouseY;
                        drawing = true;
                    }
                    else
                    {
                        AddRectangle(mouseX, mouseY, x, HEIGHT - y);
                        drawing = false;
                    }
                    break;
                case t_TRI:
                    if (state == GLUT_DOWN)
                    {
                        mouseX = x;
                        mouseY = HEIGHT - y;
                        mouseMoveX = mouseX;
                        mouseMoveY = mouseY;
                        drawing = true;
                    }
                    else
                    {
                        AddTriangle(mouseX, mouseY, x - mouseX, mouseY - (HEIGHT - y));
                        drawing = false;
                    }
                    break;
                case t_CIRCLE:
                    if (state == GLUT_DOWN)
                    {
                        mouseX = x;
                        mouseY = HEIGHT - y;
                        mouseMoveX = mouseX;
                        mouseMoveY = mouseY;
                        drawing = true;
                    }
                    else
                    {
                        AddCircle(mouseX, mouseY, Distance(mouseX, mouseY, mouseMoveX, mouseMoveY));
                        drawing = false;
                    }
                    break;
                case t_LINE:
                    if (state == GLUT_DOWN)
                    {
                        mouseX = x;
                        mouseY = HEIGHT - y;
                        mouseMoveX = mouseX;
                        mouseMoveY = mouseY;
                        drawing = true;
                    }
                    else
                    {
                        AddLine(mouseX, mouseY, mouseMoveX, mouseMoveY);
                        drawing = false;
                    }
                    break;
                case t_POLY:
                    if (state == GLUT_DOWN)
                    {
                        mouseX = x;
                        mouseY = HEIGHT - y;
                        mouseMoveX = mouseX;
                        mouseMoveY = mouseY;
                        drawing = true;
                        if (drawPoly)
                        {
                            AddPointToPoly(mouseX, mouseY);
                        }
                        else
                        {
                            drawPoly = true;
                            AddPointToPoly(mouseX, mouseY);
                            glutPostRedisplay();
                        }
                    }
                    break;
            }
            break;

        case GLUT_RIGHT_BUTTON:
            switch (currentTool)
            {
                case t_POLY:
                if (state == GLUT_UP)
                {
                    AddPoly(customPoly);
                    drawPoly = false;
                    drawing = false;
                }
                break;
                case t_LINE:
                case t_TRI:
                case t_RECT:
                case t_CIRCLE:
                    break;
            }
        break;
    }
}
