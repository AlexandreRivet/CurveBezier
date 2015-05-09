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

	void translate(float, float);
	void rotate(float);
	void scale(float, float);
	void transform(const Matrix3x3&);

	void compute();
	void draw();

private:

	std::vector<Vector2> mComputedPoints;
};

#endif