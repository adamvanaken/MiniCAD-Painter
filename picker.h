#ifndef PICKER_H
#define PICKER_H

#include "draw.h"

extern int canvas_window;
extern int color_window;

extern int p_height;
extern int p_width;

extern const int n_colors;

extern bool color_window_open;

void init_2();

void display_2(void);

void mouseCallback_2(int button, int state, int x, int y);

void keyboardCallback_2(unsigned char key, GLint x, GLint y);

void reshapeCallback_2(int width, int height);

void createColorPicker();

void openColorPicker();

#endif