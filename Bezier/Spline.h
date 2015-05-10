#pragma once

#include <vector>

#include "BezierCurve.h"

class Spline
{
	public:
		Spline();
		~Spline();
		void computeSpline();

	private:
		std::vector<Vector2> mControlPointsLine;
		std::vector<float> mNodeParameters;
		std::vector<BezierCurve> mBezierCurves;
};

