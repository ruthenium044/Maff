// Fill out your copyright notice in the Description page of Project Settings.


#include "Float3.h"
//
//Float3::Float3(float x, float y, float z)
//{
//	this->x = x;
//	this->y = y;
//	this->z = z;
//}
//
//float& Float3::operator[](int i)
//{
//	return (&x)[i];
//}
//
//const float& Float3::operator[](int i) const
//{
//	return (&x)[i];
//}
//
//Float3& Float3::operator*=(float s)
//{
//	x *= s;
//	y *= s;
//	z *= s;
//	return *this;
//}
//
//Float3& Float3::operator/=(float s)
//{
//	s = 1.0f / s;
//	x *= s;
//	y *= s;
//	z *= s;
//	return *this;
//}
//
//Float3 Float3::operator*(float s) const
//{
//	return Float3(this->x * s, this->y * s, this->z * s);
//}
//
//Float3 Float3::operator/(float s) const
//{
//	s = 1.0f / s;
//	return Float3(this->x * s, this->y * s, this->z * s);
//}
//
//Float3 Float3::operator-(const Float3& v) const
//{
//	return Float3(-this->x, -this->y, -this->z);
//}
//
//Float3& Float3::operator+=(const Float3& v)
//{
//	x += v.x;
//	y += v.y;
//	z += v.z;
//	return *this;
//}
//
//Float3& Float3::operator-=(const Float3& v)
//{
//	x -= v.x;
//	y -= v.y;
//	z -= v.z;
//	return *this;
//}
//
//Float3 Float3::operator+(const Float3& v) const
//{
//	return Float3(this->x + v.x, this->y + v.y, this->z + v.z);
//}
//
//Float3 Float3::operator-(const Float3& v)
//{
//	return Float3(this->x - v.x, this->y - v.y, this->z - v.z);
//}
//
//float Float3::Magnitude() const
//{
//	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
//}
//
//Float3 Float3::Normalize() const
//{
//	return *this / Magnitude();
//}
//
//
//