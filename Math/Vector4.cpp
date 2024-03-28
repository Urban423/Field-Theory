#include "Vector4.h"

Vector4::Vector4()
{
	
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//Vector4::~Vector4(){}

Vector4 Vector4::cross(
	const Vector4& v1,
	const Vector4& v2,
	const Vector4& v3)
{
	Vector4 out;
	
	out.x = 
	  v1.y * (v2.z * v3.w - v3.z * v2.w)
	- v1.z * (v2.y * v3.w - v3.y * v2.w) 
	+ v1.w * (v2.y * v3.z - v3.y * v2.z);
	
	out.y = 
	- v1.x * (v2.z * v3.w - v3.z * v2.w)
	+ v1.z * (v2.x * v3.w - v3.x * v2.w) 
	- v1.w * (v2.x * v3.z - v3.x * v2.z);
	
	out.z = 
	  v1.x * (v2.y * v3.w - v3.y * v2.w)
	- v1.y * (v2.x * v3.w - v3.x * v2.w) 
	+ v1.w * (v2.x * v3.y - v3.x * v2.y);
	
	out.w = 
	- v1.x * (v2.y * v3.z - v3.y * v2.z)
	+ v1.y * (v2.x * v3.z - v3.x * v2.z) 
	- v1.z * (v2.x * v3.y - v3.x * v2.y);
	
	return out;
}