#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_

#include <vector>

#include "Curve.h"

class BezierCurve : public Curve
{
public:
	BezierCurve();
	~BezierCurve();

	Vector2& getPointAt(const int);

	void compute();
	void draw();

private:

	std::vector<Vector2> mComputedPoints;
};

#endif