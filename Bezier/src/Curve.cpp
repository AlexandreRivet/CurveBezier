#include "Curve.h"

Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::incStep()
{
	mStep++;
	if (mStep > 50)
		mStep = 50;
}

void Curve::decStep()
{
	mStep--;
	if (mStep < 2)
		mStep = 2;
}

int Curve::getNbVertices() const
{
	return mControlPoints.size();
}

void Curve::add(const Vector2& v)
{
	mControlPoints.push_back(v);
}

void Curve::insert(int index, const Vector2& v)
{
	mControlPoints.insert(mControlPoints.begin() + index, v);
}

void Curve::remove(int index)
{
	mControlPoints.erase(mControlPoints.begin() + index);
}

void Curve::reset()
{
	mControlPoints.clear();
}

void Curve::draw()
{
	Vector2 v;

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < mControlPoints.size(); i++)
	{
		v = mControlPoints[i];
		glVertex2f(v.getX(), v.getY());
	}

	glEnd();
}

void Curve::compute()
{

}