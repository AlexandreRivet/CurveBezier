#include "BezierCurve.h"

#include <string>

BezierCurve::BezierCurve()
{
	mStep = 1;
}

BezierCurve::~BezierCurve()
{
}

Vector2& BezierCurve::getPointAt(const int index)
{
	return mControlPoints[index];
}

void BezierCurve::draw()
{
	Curve::draw();

	Vector2 v;
	glColor3f(mColor[0], mColor[1], mColor[2]);
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < mComputedPoints.size(); i++)
	{
		v = mComputedPoints[i];
		glVertex2f(v.getX(), v.getY());
	}
	glEnd();

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