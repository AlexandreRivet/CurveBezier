#ifndef _MATRIX3x3_H_
#define _MATRIX3x3_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "type.h"
#include "Vector3.h"

class Matrix3x3
{
public:
	Matrix3x3();
	Matrix3x3(const float arr[3][3]);
	Matrix3x3(float, float, float, float, float, float, float, float, float);
	Matrix3x3(const Matrix3x3&);
	~Matrix3x3();

	float* operator[] (uint index) const;
	bool operator== (const Matrix3x3&) const;
	bool operator!= (const Matrix3x3&) const;

	Matrix3x3 operator+ (const Matrix3x3&) const;
	Matrix3x3 operator- (const Matrix3x3&) const;
	Matrix3x3 operator* (const Matrix3x3&) const;
	Vector3 operator* (const Vector3&) const;

	Matrix3x3 transpose() const;
	Matrix3x3 inverse() const;


private:	
	float m[3][3];

};


#endif