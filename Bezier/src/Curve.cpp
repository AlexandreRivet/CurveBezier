#include "Curve.h"

Curve::Curve()
{
	mColor = new float[3];
	mColor[0] = 1.0f;
	mColor[1] = 1.0f;
	mColor[2] = 1.0f;
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

void Curve::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
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