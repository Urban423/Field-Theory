#include "Matrix4x4.h"
#include "Vector4.h"
#include <math.h>

Matrix4x4::Matrix4x4()
{
	
}

//Matrix4x4::~Matrix4x4() {}

void Matrix4x4::setIdentity()
{
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			mat[y][x] = 0;
		}
	}
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
}

float Matrix4x4::getDeterminant()
{
	Vector4 v1 = Vector4(mat[0][0], mat[1][0], mat[2][0], mat[3][0]);
	Vector4 v2 = Vector4(mat[0][1], mat[1][1], mat[2][1], mat[3][1]);
	Vector4 v3 = Vector4(mat[0][2], mat[1][2], mat[2][2], mat[3][2]);
	
	Vector4 v4  = Vector4::cross(v1, v2, v3);
	
	return 
	 -(mat[0][3] * v4.x +
	   mat[1][3] * v4.y +
	   mat[2][3] * v4.z + 
	   mat[3][3] * v4.w);
}

void Matrix4x4::inverse()
{
	Matrix4x4 out;
	float determinant = getDeterminant();
	
	Vector4 vectors[3];
	Vector4 v;
	unsigned int index;
	unsigned int index_to_ignore = 0;
	
	
	for(unsigned int i = 0; i < 4; i++)
	{
		index_to_ignore = i;
		index = 0;
		for(unsigned int j = 0; j < 4; j++)
		{
			if(j != index_to_ignore)
			{
				vectors[index] = Vector4(mat[j][0], mat[j][1], mat[j][2], mat[j][3]);
				index++;
			}
		}
		
		v  = Vector4::cross(vectors[0], vectors[1], vectors[2]);
	
		out.mat[0][i] = (float)pow(-1, i) * v.x / determinant;
		out.mat[1][i] = (float)pow(-1, i) * v.y / determinant;
		out.mat[2][i] = (float)pow(-1, i) * v.z / determinant;
		out.mat[3][i] = (float)pow(-1, i) * v.w / determinant;
	}
	
	
	*this = out;
}


void Matrix4x4::setScale(const float x, const float y, const float z)
{
	mat[0][0] = x;
	mat[1][1] = y;
	mat[2][2] = z;
}


void Matrix4x4::setTranslation(const float x, const float y, const float z)
{
	mat[3][0] = x;
	mat[3][1] = y;
	mat[3][2] = z;
}

void Matrix4x4::setRotationX(const float x)
{
	mat[1][1] = cos(x);
	mat[1][2] = sin(x);
	mat[2][1] = -mat[1][2];
	mat[2][2] = mat[1][1];
}

void Matrix4x4::setRotationY(const float y)
{
	mat[0][0] = cos(y);
	mat[0][2] = sin(y);
	mat[2][0] = -mat[0][2];
	mat[2][2] = mat[0][0];
}

void Matrix4x4::setRotationZ(const float z)
{
	mat[0][0] = cos(z);
	mat[0][1] = sin(z);
	mat[1][0] = -mat[0][1];
	mat[1][1] = mat[0][0];
}
	
float* Matrix4x4::getPtr()
{
	return &mat[0][0];
}


void Matrix4x4::operator *=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for(unsigned int i = 0; i < 4; i++)
	{
		for(unsigned int j = 0; j < 4; j++)
		{
			out.mat[i][j] = \
			mat[i][0] * matrix.mat[0][j] +
			mat[i][1] * matrix.mat[1][j] +
			mat[i][2] * matrix.mat[2][j] +
			mat[i][3] * matrix.mat[3][j];
		}
	}
	
	*this = out;
}

void Matrix4x4::setOrthoLH(
  float width, float height,
  float nearPlane, float farPlane)
{
	mat[0][0] = 2.0f / width;
	mat[1][1] = 2.0f / height;
	mat[2][2] = 1.0f / (farPlane - nearPlane);
	mat[3][2] = -(nearPlane / (farPlane - nearPlane));
}

void Matrix4x4::setPerspectiveFovLH(
	float fov, float aspect,
	float nearPlane, float farPlane)
{
	
	float yscale = 1.0f / tan(fov / 2.0f);
	float xscale = yscale / aspect;
	
	mat[0][0] = xscale;
	mat[1][1] = yscale;
	
	mat[2][2] = (nearPlane + farPlane) / (nearPlane - farPlane);
	mat[3][2] = (2 * nearPlane * farPlane) / (nearPlane - farPlane);
	mat[2][3] = -1;
	mat[3][3] = 0;
}