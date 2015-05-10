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
	void setParametricSpace(int, int);
	int getStart() const;
	int getEnd() const;

	void translate(float, float);
	void rotate(float);
	void scale(float, float);
	void transform(const Matrix3x3&);

	void compute();
	void draw(bool);

private:

	int mA;
	int mB;
	bool mComputable;

	std::vector<Vector2> mComputedPoints;
};

#endif