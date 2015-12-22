#ifndef DLINKED_H
#define DLINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef int bool;
#define true 1
#define false 0

#define INT 0
#define DOUBLE 1
#define LINE 2
#define TRI 3
#define RECT 4
#define CIRCLE 5
#define POLY 6

enum Color { c_RED = 0, c_GREEN, c_BLUE, c_BLACK, c_PICKER } ;

typedef struct _shape {
  int type; 
  void *shape;
  // enum Color color;
  float color[4];
  int filled;
  struct _shape *prev;
  struct _shape *next;
} Shape;

typedef struct _integer {
  int data;
} Integer;

typedef struct _double {
  double data;
} Double;

typedef struct _point {
    int x;
    int y;
} Point;

typedef struct _line {
    double x1;
    double y1;
    double x2;
    double y2;
} Line;

typedef struct _triangle {
    Point p[3];
} Triangle;

typedef struct _rectangle {
    Point p[4];
} Rectangle;

typedef struct _circle {
    double x;
    double y;
    double r;
} Circle;

typedef struct Poly Poly;
struct Poly {
    Point p;
    Poly *next;
};

Integer *make_int(int x);

Double *make_double(double x);

Shape *make_shape(int type, void *shape);

Line *make_line(double x_1, double y_1, double x_2, double y_2);

Triangle *make_triangle(double x_1, double y_1, double width, double height);

Rectangle *make_rectangle(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, double x_4, double y_4);

Circle *make_circle(double x, double y, double r);

Poly *make_poly(Point p);

#endif