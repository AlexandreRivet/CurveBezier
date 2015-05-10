#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "BezierCurve.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

enum TransformationMode
{
	NONE,
	TRANSLATION,
	ROTATION,
	SCALING,
	SHEARING
};

extern std::vector<BezierCurve*> curves;

extern int BEZIER_EDITED;
extern int CURRENT_CURVE_EDITED;
extern int CURRENT_VERTEX_EDITED;
extern bool MIDDLE_BUTTON_PRESSED;
extern int FIRST_CURVE;
extern int SECOND_CURVE;
extern Vector2 D;

extern TransformationMode TRANSFORMATION_MODE;

#endif