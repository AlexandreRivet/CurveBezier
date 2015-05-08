#include "Matrix3x3.h"

Matrix3x3::Matrix3x3()
{
	memset(m, 0.0f, 9 * sizeof(float));
}

Matrix3x3::Matrix3x3(const float arr[3][3])
{
	memcpy(m, arr, 9 * sizeof(float));
}

Matrix3x3::Matrix3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	m[0][0] = a;
	m[0][1] = b;
	m[0][2] = c;
	m[1][0] = d;
	m[1][1] = e;
	m[1][2] = f;
	m[2][0] = g;
	m[2][1] = h;
	m[2][2] = i;
}

Matrix3x3::Matrix3x3(const Matrix3x3& other)
{
	memcpy(m, other.m, 9 * sizeof(float));
}

Matrix3x3::~Matrix3x3()
{

}

float* Matrix3x3::operator[] (uint index) const
{
	return (float*)m[index];
}

bool Matrix3x3::operator== (const Matrix3x3& other) const
{
	for (uint i = 0; i < 3; ++i)
	{
		for (uint j = 0; j < 3; ++j)
		{
			if (m[i][j] != other[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix3x3::operator!= (const Matrix3x3& other) const
{
	return !operator==(other);
}

Matrix3x3 Matrix3x3::operator + (const Matrix3x3& other) const
{
	Matrix3x3 res;
	for (uint i = 0; i < 3; ++i)
	{
		for (uint j = 0; j < 3; ++j)
		{
			res.m[i][j] = m[i][j] + other.m[i][j];
		}
	}
	return res;
}

Matrix3x3 Matrix3x3::operator - (const Matrix3x3& other) const
{
	Matrix3x3 res;
	for (uint i = 0; i < 3; ++i)
	{
		for (uint j = 0; j < 3; ++j)
		{
			res.m[i][j] = m[i][j] - other.m[i][j];
		}
	}
	return res;
}

Matrix3x3 Matrix3x3::operator* (const Matrix3x3& other) const
{
	Matrix3x3 res;
	for (uint i = 0; i < 3; ++i)
	{
		for (uint j = 0; j < 3; ++j)
		{
			res.m[i][j] =
				m[i][0] * other.m[0][j] +
				m[i][1] * other.m[1][j] +
				m[i][2] * other.m[2][j];
		}
	}
	return res;
}

Vector3 Matrix3x3::operator* (const Vector3& v) const
{
	Vector3 res;
	for (uint i = 0; i < 3; ++i)
	{
		res[i] =
			m[i][0] * v[0] +
			m[i][1] * v[1] +
			m[i][2] * v[2];
	}
	return res;
}

Matrix3x3 Matrix3x3::transpose() const
{
	Matrix3x3 res;
	for (uint i = 0; i < 3; ++i)
	{
		for (uint j = 0; j < 3; ++j)
		{
			res.m[i][j] = m[j][i];
		}
	}
	return res;
}

Matrix3x3 Matrix3x3::inverse() const
{
	Matrix3x3 res;

	res[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
	res[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
	res[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
	
	res[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
	res[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
	res[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];
	
	res[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
	res[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
	res[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

	float det =
		m[0][0] * res[0][0] +
		m[0][1] * res[1][0] +
		m[0][2] * res[2][0];

	if (det == 0.0f)
		return *this;

	float invDet = 1.0f / det;
	for (uint i = 0; i < 3; ++i)
	{
		for (uint j = 0; j < 3; ++j)
		{
			res[i][j] *= invDet;
		}
	}
	return res;
}