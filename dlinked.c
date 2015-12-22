#include <stdio.h>
#include <stdlib.h>
#include "dlinked.h"

Integer *make_int(int x)
{
  Integer *i = malloc(sizeof *i);
  i->data = x;
  return i;
}

Double *make_double(double x)
{
  Double *d = malloc(sizeof *d);
  d->data = x;
  return d;
}

Shape *make_shape(int type, void *shape)
{
  Shape *n = malloc(sizeof *n);
  n->type = type;
  n->shape = shape;
  return n;
}

Line *make_line(double x_1, double y_1, double x_2, double y_2)
{
  Line *l = malloc(sizeof *l);
  l->x1 = x_1;
  l->y1 = y_1;
  l->x2 = x_2;
  l->y2 = y_2;
  return l;
}

Triangle *make_triangle(double x_1, double y_1, double width, double height)
{
  Triangle *t = malloc(sizeof *t);
  t->p[0].x = x_1;
  t->p[0].y = y_1;
  t->p[1].x = x_1 - width;
  t->p[1].y = y_1 - height;
  t->p[2].x = x_1 + width;
  t->p[2].y = y_1 - height;
  return t;
}

Rectangle *make_rectangle(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, double x_4, double y_4)
{
  Rectangle *r = malloc(sizeof *r);
  r->p[0].x = x_1;
  r->p[0].y = y_1;
  r->p[1].x = x_2;
  r->p[1].y = y_2;
  r->p[2].x = x_3;
  r->p[2].y = y_3;
  r->p[3].x = x_4;
  r->p[3].y = y_4;
  return r;
}

Circle *make_circle(double x, double y, double r)
{
    Circle *c = malloc(sizeof *c);
    c->x = x;
    c->y = y;
    c->r = r;
    return c;
}

Poly *make_poly(Point p)
{
    Poly *pol = malloc(sizeof *pol);
    pol->next = NULL;
    pol->p = p;
    return pol;
}