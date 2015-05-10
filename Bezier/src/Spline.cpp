#include "Spline.h"

#define PI 3.14159

Spline::Spline()
{
}

Spline::~Spline()
{
}

void Spline::pushNodeParameter(float value)
{
	mNodeParameters.push_back(value);
}

static Vector2 barycentre(const Vector2& v1, const Vector2& v2, float lambda)
{
	float x = (1.f - lambda) * v1.getX() + lambda * v2.getX();
	float y = (1.f - lambda) * v1.getY() + lambda * v2.getY();
	return Vector2(x, y);
}

void Spline::compute()
{
	int nbPoints = mControlPoints.size();
	Vector2 controlePoint_tmp = Vector2();
	Vector2 startControlePoint_tmp = Vector2();

	for (unsigned int i = 1; i <= nbPoints - 3; ++i)
	{
		Vector2 p1 = mControlPoints[i];
		Vector2 p2 = mControlPoints[i + 1];
		Vector2 p3 = mControlPoints[i + 2];
		float r0, r1, r2, lambda0, lambda1, lambda2;
		std::vector<Vector2> controlPoints_tmp = std::vector<Vector2>();
		if (i == 1)
		{
			controlPoints_tmp.push_back(mControlPoints[i - 1]);
			controlPoints_tmp.push_back(mControlPoints[i]);
			r0 = mNodeParameters[1] - mNodeParameters[0];
			r1 = mNodeParameters[2] - mNodeParameters[1];
			lambda0 = r0 / (r0 + r1);

			Vector2 lambdaP1P2 = barycentre(p1, p2, lambda0);
			r0 = mNodeParameters[1] - mNodeParameters[0];
			r1 = mNodeParameters[2] - mNodeParameters[1];
			r2 = mNodeParameters[3] - mNodeParameters[2];
			lambda1 = r0 / (r0 + r1 + r2);
			Vector2 lambdaP2P3 = barycentre(p2, p3, lambda1);

			startControlePoint_tmp = barycentre(lambdaP1P2, lambdaP2P3, lambda0);
			controlPoints_tmp.push_back(lambdaP1P2);
			controlPoints_tmp.push_back(startControlePoint_tmp);

			BezierCurve bezier_tmp;
			bezier_tmp.addControlPoints(controlPoints_tmp);
			bezier_tmp.compute();
			mBezierCurves.push_back(bezier_tmp);

			controlePoint_tmp = lambdaP2P3;
		}
		else if (i == nbPoints - 3)
		{
			controlPoints_tmp.clear();
			controlPoints_tmp.push_back(startControlePoint_tmp);
			controlPoints_tmp.push_back(controlePoint_tmp);
			controlPoints_tmp.push_back(p2);
			controlPoints_tmp.push_back(p3);

			BezierCurve bezier_tmp;
			bezier_tmp.addControlPoints(controlPoints_tmp);
			bezier_tmp.compute();
			mBezierCurves.push_back(bezier_tmp);
		} else {
			controlPoints_tmp.clear();

			controlPoints_tmp.push_back(startControlePoint_tmp);
			controlPoints_tmp.push_back(controlePoint_tmp);

			r0 = mNodeParameters[i - 1] - mNodeParameters[i - 2];
			r1 = mNodeParameters[i] - mNodeParameters[i - 1];
			r2 = mNodeParameters[i + 1] - mNodeParameters[i];
			lambda0 = (r0 + r1) / (r0 + r1 + r2);
			Vector2 lambdaP1P2 = barycentre(p1, p2, lambda0);

			r0 = mNodeParameters[i] - mNodeParameters[i - 1];
			r1 = mNodeParameters[i + 1] - mNodeParameters[i];
			if (i == nbPoints - 4)
			{
				lambda1 = r0 / (r0 + r1);
			} else {
				r2 = mNodeParameters[i + 2] - mNodeParameters[i + 1];
				lambda1 = r0 / (r0 + r1 + r2);
			}
			Vector2 lambdaP2P3 = barycentre(p2, p3, lambda1);

			r0 = mNodeParameters[i] - mNodeParameters[i - 1];
			r1 = mNodeParameters[i + 1] - mNodeParameters[i];
			lambda2 = r0 / (r0 + r1);
			startControlePoint_tmp = barycentre(lambdaP1P2, lambdaP2P3, lambda2);

			controlPoints_tmp.push_back(lambdaP1P2);
			controlPoints_tmp.push_back(startControlePoint_tmp);

			BezierCurve bezier_tmp;
			bezier_tmp.addControlPoints(controlPoints_tmp);
			bezier_tmp.compute();
			mBezierCurves.push_back(bezier_tmp);

			controlePoint_tmp = lambdaP2P3;
		}
	}
}

void Spline::draw()
{
	Curve::draw(1.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < mBezierCurves.size(); ++i)
		mBezierCurves[i].draw(false);
}

void Spline::translate(float x, float y)
{
	// Création de la matrice de translation
	Matrix3x3 mat = Matrix3x3(
		1.0f, 0.0f, x,
		0.0f, 1.0f, y,
		0.0f, 0.0f, 1.0f);

	transform(mat);
}

void Spline::rotate(float angle)
{
	float radian = angle * PI / 180.0f;

	// Création de la matrice de translation
	Matrix3x3 mat = Matrix3x3(
		cos(radian), -sin(radian), 0.0f,
		sin(radian), cos(radian), 0.0f,
		0.0f, 0.0f, 1.0f);

	transform(mat);
}

void Spline::scale(float x, float y)
{
	// Création de la matrice de translation
	Matrix3x3 mat = Matrix3x3(
		x, 0.0f, 0.0f,
		0.0f, y, 0.0f,
		0.0f, 0.0f, 1.0f);

	transform(mat);
}

void Spline::transform(const Matrix3x3& mat)
{
	for (unsigned int i = 0; i < mControlPoints.size(); ++i)
	{
		Vector2 tmp = mControlPoints[i];
		Vector3 res = mat * Vector3(tmp.getX(), tmp.getY(), 1.0f);
		mControlPoints[i] = Vector2(res.getX(), res.getY());
	}

	compute();
}
