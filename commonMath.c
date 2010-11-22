/*
 *  commonMath.c
 *  iGLView
 *
 *  Created by David Petrie on 6/11/10.
 *  Copyright 2010 n/a. All rights reserved.
 *
 */

#include "commonMath.h"

void Cross3(vec3_t vOut, const vec3_t a, const vec3_t b)
{
	vec3Set(vOut,
			(a[1] * b[2]) - (a[2] * b[1]),
			(a[2] * b[0]) - (a[0] * b[2]),
			(a[0] * b[1]) - (a[1] * b[0]));
}


void Normalize3(vec3_t vOut, const vec3_t vec)
{
	float f;
	double temp;
	
	temp = (double)(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	temp = 1.0 / sqrt(temp);
	f = (float)temp;
	vec3Set(vOut, vec[0] * f, vec[1] * f, vec[2] * f);
}


void MatrixTranslation(float *mOut, const float x, const float y, const float z)
{
	mOut[__11] = 1;	mOut[__12] = 0;	mOut[__13] = 0;	mOut[__14] = 0;
	mOut[__21] = 0;	mOut[__22] = 1;	mOut[__23] = 0;	mOut[__24] = 0;
	mOut[__31] = 0;	mOut[__32] = 0;	mOut[__33] = 1;	mOut[__34] = 0;
	mOut[__41] = x;	mOut[__42] = y;	mOut[__43] = z; mOut[__44] = 1;
}


void MatrixRotationZ(float *mOut, const float angle)
{
	float fsin = sinf(angle);
	float fcos = cosf(angle);
	
	mOut[__11] = fcos;	mOut[__12] = fsin;	mOut[__13] = 0;	mOut[__14] = 0;
	mOut[__21] = -fsin;	mOut[__22] = fcos;	mOut[__23] = 0;	mOut[__24] = 0;
	mOut[__31] = 0;		mOut[__32] = 0;		mOut[__33] = 1;	mOut[__34] = 0;
	mOut[__41] = 0;		mOut[__42] = 0;	mOut[__43] = 0;	mOut[__44] = 1;
}


void MatrixMultiply(float *mOut, const float *mA, const float *mB)
{
	mOut[__11] = mA[__11]*mB[__11] + mA[__12]*mB[__21] + mA[__13]*mB[__31] + mA[__14]*mB[__41];	
	mOut[__12] = mA[__11]*mB[__12] + mA[__12]*mB[__22] + mA[__13]*mB[__32] + mA[__14]*mB[__42];	
	mOut[__13] = mA[__11]*mB[__13] + mA[__12]*mB[__23] + mA[__13]*mB[__33] + mA[__14]*mB[__43];	
	mOut[__14] = mA[__11]*mB[__14] + mA[__12]*mB[__24] + mA[__13]*mB[__34] + mA[__14]*mB[__44];
	
	mOut[__21] = mA[__21]*mB[__11] + mA[__22]*mB[__21] + mA[__23]*mB[__31] + mA[__24]*mB[__41];	
	mOut[__22] = mA[__21]*mB[__12] + mA[__22]*mB[__22] + mA[__23]*mB[__32] + mA[__24]*mB[__42];	
	mOut[__23] = mA[__21]*mB[__13] + mA[__22]*mB[__23] + mA[__23]*mB[__33] + mA[__24]*mB[__43];	
	mOut[__24] = mA[__21]*mB[__14] + mA[__22]*mB[__24] + mA[__23]*mB[__34] + mA[__24]*mB[__44];
	
	mOut[__31] = mA[__31]*mB[__11] + mA[__32]*mB[__21] + mA[__33]*mB[__31] + mA[__34]*mB[__41];	
	mOut[__32] = mA[__31]*mB[__12] + mA[__32]*mB[__22] + mA[__33]*mB[__32] + mA[__34]*mB[__42];	
	mOut[__33] = mA[__31]*mB[__13] + mA[__32]*mB[__23] + mA[__33]*mB[__33] + mA[__34]*mB[__43];	
	mOut[__34] = mA[__31]*mB[__14] + mA[__32]*mB[__24] + mA[__33]*mB[__34] + mA[__34]*mB[__44];
	
	mOut[__41] = mA[__41]*mB[__11] + mA[__42]*mB[__21] + mA[__43]*mB[__31] + mA[__44]*mB[__41];
	mOut[__42] = mA[__41]*mB[__12] + mA[__42]*mB[__22] + mA[__43]*mB[__32] + mA[__44]*mB[__42];
	mOut[__43] = mA[__41]*mB[__13] + mA[__42]*mB[__23] + mA[__43]*mB[__33] + mA[__44]*mB[__43];
	mOut[__44] = mA[__41]*mB[__14] + mA[__42]*mB[__24] + mA[__43]*mB[__34] + mA[__44]*mB[__44];
}


void MatrixPerspectiveFovRH(float *mOut, const float FOVy, const float aspect, const float near, const float far)
{
	float f, n, realAspect;
	
	realAspect = aspect;
	
	// cotangent(a) == 1.0f / tan(a);
	f = 1.0f / (float)tan(FOVy * 0.5f);
	n = 1.0f / (near - far);
	
	mOut[ 0] = f / realAspect;
	mOut[ 1] = 0;
	mOut[ 2] = 0;
	mOut[ 3] = 0;
	
	mOut[ 4] = 0;
	mOut[ 5] = f;
	mOut[ 6] = 0;
	mOut[ 7] = 0;
	
	mOut[ 8] = 0;
	mOut[ 9] = 0;
	mOut[10] = (far + near) * n;
	mOut[11] = -1;
	
	mOut[12] = 0;
	mOut[13] = 0;
	mOut[14] = (2 * far * near) * n;
	mOut[15] = 0;
}


void MatrixLookAtRH(float *mOut, const vec3_t vEye, const vec3_t vAt, const vec3_t vUp)
{
	vec3_t f, vUpActual, s, u;
	float	t[16];
	
	f[0] = vAt[0] - vEye[0];
	f[1] = vAt[1] - vEye[1];
	f[2] = vAt[2] - vEye[2];
	
	Normalize3(f, f);
	Normalize3(vUpActual, vUp);
	Cross3(s, f, vUpActual);
	Cross3(u, s, f);
	
	mOut[ 0] = s[0];
	mOut[ 1] = u[0];
	mOut[ 2] = -f[0];
	mOut[ 3] = 0;
	
	mOut[ 4] = s[1];
	mOut[ 5] = u[1];
	mOut[ 6] = -f[1];
	mOut[ 7] = 0;
	
	mOut[ 8] = s[2];
	mOut[ 9] = u[2];
	mOut[10] = -f[2];
	mOut[11] = 0;
	
	mOut[12] = 0;
	mOut[13] = 0;
	mOut[14] = 0;
	mOut[15] = 1;
	
	MatrixTranslation(t, -vEye[0], -vEye[1], -vEye[2]);
	MatrixMultiply(mOut, t, mOut);
}
