#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "helper.h"

Shape *start;
Shape *end;

Poly *customPoly;
int customPolyCount = 0;

bool fill = true;

enum Color currentColor;
enum Color customColor;
float custom_color[4];

double Distance(double x1, double y1, double x2, double y2)
{
    return sqrt( pow(x1-x2, 2) + pow(y1-y2, 2) );
}

void AddPointToPoly(int x, int y)
{
    Point p;
    p.x = x;
    p.y = y;
    customPolyCount++;

    if(customPoly == NULL)
    {
        customPoly = make_poly(p);
    }
    else
    {
        Poly *newPoly = make_poly(p);
        Poly *last = customPoly;

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = newPoly;
    }
    glutPostRedisplay();
}

void AddPoly(Poly *p)
{
    Poly *customPoly_copy = customPoly;
    
    // i.e. we have at least 3 defined points for our poly
    if (customPolyCount > 2)
    {
        Shape *s = make_shape(POLY, customPoly_copy);
        s->filled = fill;
        s->color[0] = custom_color[0];
        s->color[1] = custom_color[1];
        s->color[2] = custom_color[2];
        s->color[3] = custom_color[3];

        s->prev = end;
        end->next = s;
        end = s;
        end->next = NULL;
    }
    else
    {
        Line *l = make_line(p->p.x, p->p.y, p->next->p.x, p->next->p.y);
        Shape *s = make_shape(LINE, l);
        s->filled = fill;
        s->color[0] = custom_color[0];
        s->color[1] = custom_color[1];
        s->color[2] = custom_color[2];
        s->color[3] = custom_color[3];

        s->prev = end;
        end->next = s;
        end = s;
        end->next = NULL;
    }

    // Clear current custom poly
    // NOTE: Do not want to free it, since it is being pointed to
    //  by some shape in our doubly-linked list
    customPoly = NULL;
    customPolyCount = 0;

    glutPostRedisplay();
}

void AddLine(double x1, double y1, double x2, double y2)
{
    Line *l = make_line(x1, y1, x2, y2);
    Shape *n = make_shape(LINE, l);
    n->filled = fill;
    n->color[0] = custom_color[0];
    n->color[1] = custom_color[1];
    n->color[2] = custom_color[2];
    n->color[3] = custom_color[3];

    n->prev = end;
    end->next = n;
    end = n;
    end->next = NULL;
    glutPostRedisplay();
}

void AddCircle(double x, double y, double r)
{
    Circle *c = make_circle(x, y, r);
    Shape *n = make_shape(CIRCLE, c);
    n->filled = fill;
    n->color[0] = custom_color[0];
    n->color[1] = custom_color[1];
    n->color[2] = custom_color[2];
    n->color[3] = custom_color[3];

    n->prev = end;
    end->next = n;
    end = n;
    end->next = NULL;
    glutPostRedisplay();
}

void AddRectangle(double x_1, double y_1, double x_2, double y_2)
{
    Rectangle *r = make_rectangle(x_1, y_1, x_1, y_2, x_2, y_2, x_2, y_1);
    Shape *n = make_shape(RECT, r);
    n->filled = fill;
    n->color[0] = custom_color[0];
    n->color[1] = custom_color[1];
    n->color[2] = custom_color[2];
    n->color[3] = custom_color[3];

    n->prev = end;
    end->next = n;
    end = n;
    end->next = NULL;
    glutPostRedisplay();
}

void AddTriangle(double x_1, double y_1, double width, double height)
{
    Triangle *t = make_triangle(x_1, y_1, width, height);
    Shape *n = make_shape(TRI, t);
    n->filled = fill;
    n->color[0] = custom_color[0];
    n->color[1] = custom_color[1];
    n->color[2] = custom_color[2];
    n->color[3] = custom_color[3];

    n->prev = end;
    end->next = n;
    end = n;
    end->next = NULL;
    glutPostRedisplay();
}

void create_linked_list()
{
    Integer *i = make_int(0);
    start = make_shape(INT, i);
    start->next = NULL;
    end = start;
    end->next = NULL;
}

void free_poly(Poly *p)
{
    Poly *next;

    while (p != NULL)
    {
        next = p->next;
        free(p);
        p = next;
    }
}

void free_shape(Shape *s)
{
    if (s->type == POLY)
    {
        free_poly(s->shape);
    }
    else if (s->shape != NULL)
        free(s->shape);
    free(s);
}

void Clear()
{
    Shape *next;

    while (start != NULL)
    {
        next = start->next;
        free_shape(start);
        start = next;
    }

    // Reset pointers
    create_linked_list();
    glutPostRedisplay();
}