#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <math.h>
#include "helper.h"

#define PI 3.14159265

extern int WIDTH;
extern int HEIGHT;

enum Tool { t_LINE = 0, t_TRI, t_RECT, t_CIRCLE, t_POLY };

extern enum Tool currentTool;

extern bool toolSelectDrawn;
extern bool toolSelect;
extern double mouseX, mouseY;
extern double mouseMoveX, mouseMoveY;

extern bool drawing;
extern bool drawPoly;

extern int selectedColor;

void setTool(int x, int y);

void setToolSelect(bool b, int x, int y);

void reshapeCallback(int width, int height);

void keyboardCallback(unsigned char key, GLint x, GLint y);

void keyboardUpCallback(unsigned char key, int x, int y);

void specialCallback(int key, int x, int y);

void specialUpCallback(int key, int x, int y);

void motionCallback(int x, int y);

void passiveMotionCallback(int x, int y);

void mouseCallback(int button, int state, int x, int y);

#endif