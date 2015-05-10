#include "global.h"

std::vector<BezierCurve*> curves;

int BEZIER_EDITED = -1;
int CURRENT_CURVE_EDITED = -1;
int CURRENT_VERTEX_EDITED = 0;
bool MIDDLE_BUTTON_PRESSED = false;
int FIRST_CURVE = -1;
int SECOND_CURVE = -1;
Vector2 D;

TransformationMode TRANSFORMATION_MODE = NONE;