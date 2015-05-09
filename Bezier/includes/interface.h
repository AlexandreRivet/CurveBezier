#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "includes.h"
#include "Vector2.h"

void specialKey(int, int, int);
void key(unsigned char, int, int);
void mouse(int, int, int, int);
void motion(int, int);

void mouseDown(int, int, int);
void mouseUp(int, int, int);

void initMenu();
void select(int selection);
void selectCurve(int selection);
void editCurve(int selection);
void addCurveItem(int parent, int index);
void setColor(int selection);

#endif