#ifndef _SPLINE_H_
#define _SPLINE_H_

#include <vector>

#include "BezierCurve.h"

class Spline : public Curve
{
	public:
		Spline();
		~Spline();

		Vector2& getPointAt(const int);
		void pushNodeParameter(float);

		void translate(float, float);
		void rotate(float);
		void scale(float, float);
		void transform(const Matrix3x3&);

		void compute();

		void draw();

	private:

		std::vector<float> mNodeParameters;
		std::vector<BezierCurve> mBezierCurves;
};

#endif