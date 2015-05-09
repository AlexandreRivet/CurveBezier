#ifndef _CURVE_H_
#define _CURVE_H_

#include <vector>

#include "includes.h"
#include "Vector2.h"

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

	void draw();

	virtual void compute();

protected:

	float mStep;
	float* mColor;
	std::vector<Vector2> mControlPoints;
};

#endif