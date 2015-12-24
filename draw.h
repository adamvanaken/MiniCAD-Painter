#ifndef DRAW_H
#define DRAW_H

#include "callbacks.h"

#define RES 400

extern int canvas_window;

void DrawRect(int x, int y, int r);

void DrawRect4_Out(int x, int y, int x2, int y2);

void DrawTri(int x, int y, int width, int height);

void DrawTri_Out(int x, int y, int width, int height);

void DrawCircle(int c_x, int c_y, int r, bool f);

void DrawLine(int x1, int y1, int x2, int y2);

void DrawLine_Out(int x1, int y1, int x2, int y2);

void DrawShape(Point p[], int p_len);

void DrawPolyLine(Poly *p, int x, int y);

void DrawPoly(Poly *p);

void DrawToolSelect(int c_x, int c_y);

#endif