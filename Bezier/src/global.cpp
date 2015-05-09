#include "global.h"

std::vector<BezierCurve*> curves;
BezierCurve bezier;

int BEZIER_EDITED = -1;
int CURRENT_CURVE_EDITED = -1;
int CURRENT_VERTEX_EDITED = 0;
bool MIDDLE_BUTTON_PRESSED = false;