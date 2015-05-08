/*
Fichier :							Vector3
*/

#include <cmath>
#include "Vector3.h"

#define PI 3.14159f

Vector3::Vector3()
{
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
}

Vector3::Vector3(const float x, const float y, const float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

Vector3::Vector3(const Vector3& v)
{
	mX = v.mX;
	mY = v.mY;
	mZ = v.mZ;
}

Vector3::~Vector3(void) {}

float Vector3::getX() const
{
	return mX;
}

float Vector3::getY() const
{
	return mY;
}

float Vector3::getZ() const
{
	return mZ;
}

void Vector3::setX(const float x)
{
	mX = x;
}

void Vector3::setY(const float y)
{
	mY = y;
}

void Vector3::setZ(const float z)
{
	mZ = z;
}

float Vector3::operator[] (uint i) const
{
	return *(&mX + i);
}

float& Vector3::operator[] (uint i)
{
	return *(&mX + i);
}

Vector3 Vector3::operator + (const Vector3& v) const
{
	return Vector3(
		mX + v.mX,
		mY + v.mY,
		mZ + v.mZ);
}

Vector3 Vector3::operator + (const float s) const
{
	return Vector3(
		mY + s,
		mY + s,
		mZ + s);
}

Vector3 Vector3::operator - (const Vector3& v) const
{
	return Vector3(
		mX - v.mX,
		mY - v.mY,
		mZ - v.mZ);
}

Vector3 Vector3::operator - (const float s) const
{
	return Vector3(
		mX - s,
		mY - s,
		mZ - s);
}

Vector3 Vector3::operator * (const Vector3& v) const
{
	return Vector3(
		mX * v.mX,
		mY * v.mY,
		mZ * v.mZ);
}

Vector3 Vector3::operator * (const float s) const
{
	return Vector3(
		mX * s,
		mY * s,
		mZ * s);
}

Vector3 Vector3::operator / (const Vector3& v) const
{
	if (v.mX == 0 && v.mY == 0) return Vector3::ZERO;
	return Vector3(
		mX / v.mX,
		mY / v.mY,
		mZ / v.mZ);
}

Vector3 Vector3::operator / (const float s) const
{
	if (s == 0) return Vector3::ZERO;
	return Vector3(
		mX / s,
		mY / s,
		mZ / s);
}

Vector3& Vector3::operator += (const Vector3& v)
{
	mX += v.mX;
	mY += v.mY;
	mZ += v.mZ;
	return *this;
}

Vector3& Vector3::operator += (const float s)
{
	mX += s;
	mY += s;
	mZ += s;
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& v)
{
	mX -= v.mX;
	mY -= v.mY;
	mZ -= v.mZ;
	return *this;
}

Vector3& Vector3::operator -= (const float s)
{
	mX -= s;
	mY -= s;
	mZ -= s;
	return *this;
}

Vector3& Vector3::operator *= (const Vector3& v)
{
	mX *= v.mX;
	mY *= v.mY;
	mZ *= v.mZ;
	return *this;
}

Vector3& Vector3::operator *= (const float s)
{
	mX *= s;
	mY *= s;
	mZ *= s;
	return *this;
}

Vector3& Vector3::operator /= (const Vector3& v)
{
	if (v.mX == 0 || v.mY == 0 || v.mZ == 0) return *this;
	mX /= v.mX;
	mY /= v.mY;
	mZ /= v.mZ;
	return *this;
}

Vector3& Vector3::operator /= (const float s)
{
	if (s == 0) return *this;
	mX /= s;
	mY /= s;
	mZ /= s;
	return *this;
}

Vector3& Vector3::operator = (const Vector3& v)
{
	mX = v.mX;
	mY = v.mY;
	mZ = v.mZ;
	return *this;
}

bool Vector3::operator == (const Vector3& v) const
{
	return ((mX == v.mX) && (mY == v.mY) && (mZ == v.mZ));
}

bool Vector3::operator != (const Vector3& v)const
{
	return !operator==(v);
}

bool Vector3::operator < (const Vector3& v) const
{
	return ((mX < v.mX) && (mY < v.mY) && (mZ < v.mZ));
}

bool Vector3::operator >(const Vector3& v) const
{
	return ((mX > v.mX) && (mY > v.mY) && (mZ > v.mZ));
}

std::ostream& operator << (std::ostream& os, const Vector3& v)
{
	os << "Vector3(" << v.mX << "," << v.mY << "," << v.mY << ")";
	return os;
}

float Vector3::length() const
{
	return sqrt(mX * mX + mY * mY + mZ * mZ);
}

float Vector3::squaredLength() const
{
	return mX * mX + mY * mY + mZ * mZ;
}

float Vector3::distance(const Vector3& v) const
{
	return (*this - v).length();
}

float Vector3::squaredDistance(const Vector3& v) const
{
	return (*this - v).squaredLength();
}

float Vector3::dotProduct(const Vector3& v) const
{
	return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

float Vector3::normalise()
{
	float len = length();

	if (len > 0.0f)
	{
		mX /= len;
		mY /= len;
		mZ /= len;
	}
	return len;
}

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::UNIT_SCALE(1.0f, 1.0f, 0.0f);