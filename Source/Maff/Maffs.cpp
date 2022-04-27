// Fill out your copyright notice in the Description page of Project Settings.


#include "Maffs.h"

int64 UMaffs::Square(int64 value)
{
	return value * value;
}

int64 UMaffs::SquareRoot(int64 value)
{
	//todo impliment actual rool pls
	return sqrt(value);
}

int64 UMaffs::Magnitude(FVector vector)
{
	return SquareRoot(Square(vector.X) + Square(vector.Y) + Square(vector.Z));
}

int64 UMaffs::Distance(FVector vector1, FVector vector2)
{
	return SquareRoot(Square(vector1.X - vector2.X) + Square(vector1.Y - vector2.Y) +
		Square(vector1.Z - vector2.Z));
}

int64 UMaffs::Dot(FVector vector1, FVector vector2)
{
	return vector1.X * vector2.X + vector1.Y * vector2.Y;
}

FVector UMaffs::Normalize(FVector vector)
{
	int64 mag = Magnitude(vector);
	vector.X /= mag;
	vector.Y /= mag;
	vector.Z /= mag;
	return vector;
}

int64 UMaffs::AngleRad(FVector vector1, FVector vector2)
{
	return acos(Dot(vector1, vector2) / Magnitude(vector1) * Magnitude(vector2));
}

int64 UMaffs::RadToDeg(int64 value)
{
	return value *= 180 / PI;
}

int64 UMaffs::DegToRad(int64 value)
{
	return value *= PI / 180;
}

FVector UMaffs::RotateX(FVector vector, float angle, bool clockwise)
{
	if (clockwise)
	{
		angle = 2 * PI - angle;
	}
	vector.Z = vector.Z * cos(angle) - vector.Y * sin(angle);
	vector.Y = vector.Z * sin(angle) + vector.Y * cos(angle);
	return vector;
}

FVector UMaffs::RotateY(FVector vector, float angle, bool clockwise)
{
	if (clockwise)
	{
		angle = 2 * PI - angle;
	}
	vector.X = vector.X * cos(angle) - vector.Z * sin(angle);
	vector.Z = vector.X * sin(angle) + vector.Z * cos(angle);
	return vector;
}

FVector UMaffs::RotateZ(FVector vector, float angle, bool clockwise)
{
	if (clockwise)
	{
		angle = 2 * PI - angle;
	}
	vector.X = vector.X * cos(angle) - vector.Y * sin(angle);
	vector.Y = vector.X * sin(angle) + vector.Y * cos(angle);
	return vector;
}

