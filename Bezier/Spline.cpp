#include "Spline.h"


Spline::Spline()
{
}


Spline::~Spline()
{
}

void Spline::computeSpline()
{
	/**********************************************************************\
								PSEUDO CODE
	\**********************************************************************/
		clear();
		int nbPoints = getNbControlPoints();
		Vector2 controlePoint_tmp = Vector2();
		Vector2 startControlePoint_tmp = Vector2();

		for (int i = 1; i <= nbPoints - 3; i++)
		{
			Vector2 p1 = getControlePointAt(i);
			Vector2 p2 = getControlePointAt(i + 1);
			Vector2 p3 = getControlePointAt(i + 2);
			float r1, r2, r3, lambda0, lambda1, lambda2;
			std::vector<Vector2> controlPoints_tmp = std::vector<Vector2>();
			if (i == 1)
			{
				controlPoints_tmp.push_back(getControlePointAt(i - 1));
				r1 = mNodeParameters[1] - mNodeParameters[0];
				r2 = mNodeParameters[2] - mNodeParameters[1];
				lambda0 = r1 / (r1 + r2);
				Vector2 lambdaP1P2 = baryCentre(p1, p2, lambda0);

				r1 = mNodeParameters[1] - mNodeParameters[0];
				r2 = mNodeParameters[2] - mNodeParameters[1];
				r3 = mNodeParameters[3] - mNodeParameters[2]
					lambda1 = r1 / (r1 + r2 + r3);
				Vector2 lambdaP2P3 = baryCentre(p2, p3, lambda1);

				startControlePoint_tmp = baryCentre(lambdaP1P2, lambdaP2P3, lambda0);
				controlPoints_tmp.push_back(lambdaP1P2);
				controlPoints_tmp.push_back(startControlePoint_tmp);

				BezierCurve bezier_tmp = computeBezier(controlPoints_tmp);
				mBezierCurves.push_back(bezier_tmp);

				controlePoint_tmp = lambdaP2P3;
			}
			else {
				controlPoints_tmp.clear();
				controlPoints_tmp.push_back(startControlePoint_tmp);
				controlPoints_tmp.push_back(controlePoint_tmp);


				r1 = mNodeParameters[i - 1] - mNodeParameters[i - 2];
				r2 = mNodeParameters[i] - mNodeParameters[i-1];
				r3 = mNodeParameters[i + 1] - mNodeParameters[i]
				lambda0 = r3 / (r1 + r2 + r3);
				Vector2 lambdaP1P2 = baryCentre(p1, p2, lambda0);

				r1 = mNodeParameters[i] - mNodeParameters[i - 1];
				r2 = mNodeParameters[i+1] - mNodeParameters[i];
				r3 = mNodeParameters[i + 2] - mNodeParameters[i+1]
				lambda1 = r1 / (r1 + r2 + r3);
				Vector2 lambdaP2P3 = baryCentre(p2, p3, lambda1);

				r1 = mNodeParameters[i] - mNodeParameters[i - 1];
				r2 = mNodeParameters[i + 1] - mNodeParameters[i]
				lambda2 = r1 / (r1 + r2);
				startControlePoint_tmp = baryCentre(lambdaP1P2, lambdaP2P3, lambda2);

				controlPoints_tmp.push_back(lambdaP1P2);
				controlPoints_tmp.push_back(startControlePoint_tmp);

				BezierCurve bezier_tmp = computeBezier(controlPoints_tmp);
				mBezierCurves.push_back(bezier_tmp);

				controlePoint_tmp = lambdaP2P3;
			}

			else if (i == nbPoints - 3)
			{
				controlPoints_tmp.clear();
				controlPoints_tmp.push_back(startBezier);
				controlPoints_tmp.push_back(controlePoint_tmp);
				controlPoints_tmp.push_back(p2);
				controlPoints_tmp.push_back(p3);

				BezierCurve bezier_tmp = computeBezier(controlPoints_tmp);
				mBezierCurves.push_back(bezier_tmp);
			}
		/**********************************************************************\
										FIN
		\**********************************************************************/

}
