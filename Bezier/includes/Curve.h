#ifndef _CURVE_H_
#define _CURVE_H_

#include <vector>

#include "includes.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3x3.h"

class Curve
{
public:
	Curve();
	~Curve();

	void incStep();
	void decStep();
	int getNbVertices() const;

	void add(const Vector2&);
	void insert(int, const Vector2&);
	void remove(int);
	void reset();
	void setColor(float, float, float);

	virtual void translate(float, float) = 0;
	virtual void rotate(float) = 0;
	virtual void scale(float, float) = 0;
	virtual void transform(const Matrix3x3&) = 0;

	void draw();

	virtual void compute();

protected:

	float mStep;
	float* mColor;
	std::vector<Vector2> mControlPoints;
};

#endif