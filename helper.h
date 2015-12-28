#ifndef HELPER_H
#define HELPER_H

#include "dlinked.h"

extern Shape *start;
extern Shape *end;

extern Poly *customPoly;
extern int customPolyCount;

extern bool fill;

extern enum Color currentColor;
extern float custom_color[4];

extern float buf[1000];
extern float zoom_level;

double Distance(double x1, double y1, double x2, double y2);

void AddPointToPoly(int x, int y);

void AddPoly(Poly *p);

void AddLine(double x1, double y1, double x2, double y2);

void AddCircle(double x, double y, double r);

void AddRectangle(double x_1, double y_1, double x_2, double y_2);

void AddTriangle(double x_1, double y_1, double width, double height);

void create_linked_list();

void free_poly(Poly *p);

void free_shape(Shape *s);

void Clear();

void hsl_to_rgb(float *h, float *s, float *l);

void zoom(bool in);

#endif