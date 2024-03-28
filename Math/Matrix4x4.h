#pragma once
#include "Vector3.h"

class Matrix4x4
{
public:
	Matrix4x4();
	//~Matrix4x4();

	void setIdentity();
	float getDeterminant();
	void inverse();
	
	void setScale(const Vector3& scale);
	void setTranslation(const Vector3& translation);
	void setRotationX(const float x);
	void setRotationY(const float y);
	void setRotationZ(const float z);

	void setOrthoLH(float width, float height, float nearPlane, float farPlane);
	void setPerspectiveFovLH(float fov, float aspect, float nearPlane, float farPlane);
	
	Vector3 getXDirection();
	Vector3 getYDirection();
	Vector3 getZDirection();

	float* getPtr();
public:
	void operator *=(const Matrix4x4& matrix);
private:
	float mat[4][4] = {0};
};