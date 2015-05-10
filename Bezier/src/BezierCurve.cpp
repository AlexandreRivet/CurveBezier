#include "BezierCurve.h"

#include <string>
#include <cmath>

#define PI 3.14159

BezierCurve::BezierCurve()
{
	mStep = 10;
	mA = 0;
	mB = 1;
	mComputable = true;
}

BezierCurve::~BezierCurve()
{
}

Vector2& BezierCurve::getPointAt(const int index)
{
	return mControlPoints[index];
}

void BezierCurve::setParametricSpace(int a, int b)
{
	mA = a;
	mB = b;
}

int BezierCurve::getStart() const
{
	return mA;
}

int BezierCurve::getEnd() const
{
	return mB;
}

void BezierCurve::draw(bool withDebug)
{
	if (withDebug)
		Curve::draw(0.0f, 1.0f, 0.0f);
	
	Vector2 v;
	glColor3f(mColor[0], mColor[1], mColor[2]);
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < mComputedPoints.size(); i++)
	{
		v = mComputedPoints[i];
		glVertex2f(v.getX(), v.getY());
	}
	glEnd();

	if (withDebug)
	{
		glBegin(GL_QUADS);
		for (unsigned int i = 0; i < mComputedPoints.size(); i++)
		{
			v = mComputedPoints[i];
			glVertex2f(v.getX() - 2, v.getY() - 2);
			glVertex2f(v.getX() + 2, v.getY() - 2);
			glVertex2f(v.getX() + 2, v.getY() + 2);
			glVertex2f(v.getX() - 2, v.getY() + 2);
		}
		glEnd();
	}
	
	
	/*
	std::string msg("");
	msg += std::string("Control Points: ") + std::to_string(mControlPoints.size());
	msg += "  - ";
	msg += std::string("Step: ") + std::to_string((int)mStep);
	renderString(80, 10, GLUT_BITMAP_9_BY_15, msg.c_str(), 1.0f, 1.0f, 1.0f);
	*/
}

static Vector2 DeCastelJau(float step, std::vector<Vector2> points)
{
	std::vector<std::vector<Vector2>> tmpList;
	tmpList.push_back(points);
	for (unsigned int i = 1; i < points.size(); ++i)
	{
		tmpList.push_back(std::vector<Vector2>());
		for (unsigned j = 0; j < tmpList[i - 1].size() - 1; ++j)
		{
			tmpList[i].push_back((tmpList[i - 1][j + 1] * step) + (tmpList[i - 1][j] * (1.0 - step)));
		}
	}
	return tmpList.back().back();
}

void BezierCurve::compute()
{
	if (!mComputable)
		return;

	mComputedPoints.clear();
	if (mControlPoints.size() < 3)
		return;

	mComputedPoints.push_back(Vector2(mControlPoints[0]));
	for (unsigned int k = 1; k < mStep; ++k)
	{
		float step = (float)k / (float)mStep;
		mComputedPoints.push_back(DeCastelJau(step, mControlPoints));
	}
	mComputedPoints.push_back(mControlPoints[mControlPoints.size() - 1]);
}

void BezierCurve::translate(float x, float y)
{
	// Création de la matrice de translation
	Matrix3x3 mat = Matrix3x3(
		1.0f, 0.0f, x,
		0.0f, 1.0f, y,
		0.0f, 0.0f, 1.0f);

	transform(mat);
}

void BezierCurve::rotate(float angle)
{
	float radian = angle * PI / 180.0f;

	// Création de la matrice de translation
	Matrix3x3 mat = Matrix3x3(
		cos(radian),	-sin(radian),		0.0f,
		sin(radian),	cos(radian),		0.0f,	
		0.0f,			0.0f,				1.0f);

	transform(mat);
}

void BezierCurve::scale(float x, float y)
{
	// Création de la matrice de translation
	Matrix3x3 mat = Matrix3x3(
		x,		0.0f,	0.0f,
		0.0f,	y,		0.0f,
		0.0f,	0.0f,	1.0f);

	transform(mat);
}

void BezierCurve::transform(const Matrix3x3& mat)
{
	for (unsigned int i = 0; i < mControlPoints.size(); ++i)
	{
		Vector2 tmp = mControlPoints[i];
		Vector3 res = mat * Vector3(tmp.getX(), tmp.getY(), 1.0f);
		mControlPoints[i] = Vector2(res.getX(), res.getY());
	}

	compute();
}
