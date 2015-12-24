#include "draw.h"

int canvas_window;

void DrawRect(int x, int y, int r)
{
    glBegin(GL_POLYGON);
        glVertex2f(x - r, y - r);
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y - r);
    glEnd();
}

void DrawRect4_Out(int x, int y, int x2, int y2)
{
    glColor3f(0.0, 0.0, 0.0);
    glEnable(GL_LINE_STIPPLE);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x2, y);
        glVertex2f(x2, y2);
        glVertex2f(x, y2);
    glEnd();

    if (fill)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    glDisable(GL_LINE_STIPPLE);
}

void DrawTri(int x, int y, int width, int height)
{
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x - width, y - height);
        glVertex2f(x + width, y - height);
    glEnd();
}

void DrawTri_Out(int x, int y, int width, int height)
{
    glColor3f(0.0, 0.0, 0.0);
    glEnable(GL_LINE_STIPPLE);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    DrawTri(x, y, width, height);

    if (fill)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    glDisable(GL_LINE_STIPPLE);
}

void DrawCircle(int c_x, int c_y, int r, bool f)
{
    if (f)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < RES; i++)
            {
                double theta = 2.0f * PI * i / RES;
                double x = r * cosf(theta);
                double y = r * sinf(theta);
                glVertex2f(x + c_x, y + c_y);
            }
        glEnd();

        if (!fill)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
    }
    else
    {
        glBegin(GL_LINES);
            for (int i = 0; i < RES; i++)
            {
                double theta = 2.0f * PI * i / RES;
                double x = r * cosf(theta);
                double y = r * sinf(theta);
                glVertex2f(x + c_x, y + c_y);
            }
        glEnd();   
    }
}

void DrawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void DrawLine_Out(int x1, int y1, int x2, int y2)
{
    glColor3f(0.0, 0.0, 0.0);
    glEnable(GL_LINE_STIPPLE);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    DrawLine(mouseX, mouseY, mouseMoveX, mouseMoveY);

    if (fill)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    glDisable(GL_LINE_STIPPLE);
}

void DrawShape(Point p[], int p_len)
{
    // for (int i = 0; i < p_len; i++) {
    //     glBegin(GL_POLYGON);
    //         glVertex2f(p[(i)%p_len].x, p[(i)%p_len].y);
    //         glVertex2f(p[(i+1)%p_len].x, p[(i+1)%p_len].y);
    //         glVertex2f(p[(i+2)%p_len].x, p[(i+2)%p_len].y);
    //     glEnd();   
    // }

    glBegin(GL_POLYGON);
        for (int i = 0; i < p_len; i++)
        {
            glVertex2f(p[i].x, p[i].y);
        }
    glEnd();
}

void DrawPolyLine(Poly *p, int x, int y)
{
    glColor3f(0.0, 0.0, 0.0);
    glEnable(GL_LINE_STIPPLE);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // i.e. if we have defined 2 points, and the mouse cursor
    //  acts as our third...
    if (customPolyCount >= 2)
    {
        Poly *next = p;
        glBegin(GL_POLYGON);
            while (next != NULL)
            {
                glVertex2f(next->p.x, next->p.y);
                next = next->next;
            }
            glVertex2f(x, y);
        glEnd();
    }
    else
    {
        DrawLine_Out(p->p.x, p->p.y, x, y);   
    }

    if (fill)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    glDisable(GL_LINE_STIPPLE);
}

void DrawPoly(Poly *p)
{
    Poly *next = p;
    glBegin(GL_POLYGON);
        while (next != NULL)
        {
            glVertex2f(next->p.x, next->p.y);
            next = next->next;
        }
    glEnd();
}

void DrawToolSelect(int c_x, int c_y)
{
    glColor3f(0, 0, 0);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(c_x, c_y);
        for (int i = 0; i <= 4; i++)
        {
            double theta = 2.0f * PI * i / 4 + (PI / 4);
            double x = 70 * cosf(theta);
            double y = 70 * sinf(theta);
            glVertex2f(x + c_x, y + c_y);
        }
    glEnd(); 

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glColor3f(1, 1, 1);
    //DrawRect(c_x, c_y, 20);
    DrawCircle(c_x, c_y, 20, true);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glColor3f(0, 0, 0);
    //DrawRect(c_x, c_y, 20);
    DrawCircle(c_x, c_y, 20, false);
    DrawLine(c_x - 5, c_y - 5, c_x + 5, c_y + 5);
    DrawRect(c_x + 35, c_y, 10);
    DrawCircle(c_x, c_y - 35, 10, false);
    DrawTri(c_x, c_y + 45, 15, 15);
    glPushMatrix();
        glTranslated(c_x - 35, c_y, 0);
        glutWireTeapot(10);
    glPopMatrix();

    if (fill)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
}