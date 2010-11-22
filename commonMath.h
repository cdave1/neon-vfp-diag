/*
 *  commonMath.h
 *  glCommon
 *
 *  Created by David Petrie on 6/11/10.
 *  Copyright 2010 n/a. All rights reserved.
 *
 */

#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include <math.h>

#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec4_t color4_t;

typedef float matrix_t[16]; // CMO

#define vec2Set(__v, __x, __y) { __v[0] = __x; __v[1] = __y; }
#define vec3Set(__v, __x, __y, __z) { __v[0] = __x; __v[1] = __y; __v[2] = __z; }
#define vec4Set(__v, __x, __y, __z, __u) { __v[0] = __x; __v[1] = __y; __v[2] = __z; __v[3] = __u; }
#define color4Set(__c, __r, __g, __b, __a) { vec4Set(__c, __r, __g, __b, __a) }
#define color4SetC(__cDst, __cSrc) { color4Set(__cDst, __cSrc[0], __cSrc[1], __cSrc[2], __cSrc[3]); }

typedef struct gVertex 
{
	vec3_t xyz;
	vec2_t st;
	color4_t rgba;
} gVertex_t;


#define __11 0
#define __21 1
#define __31 2
#define __41 3
#define __12 4
#define __22 5
#define __32 6
#define __42 7
#define __13 8
#define __23 9
#define __33 10
#define __43 11
#define __14 12
#define __24 13
#define __34 14
#define __44 15

#ifdef __cplusplus
extern "C" {
#endif

void Cross3(vec3_t vOut, const vec3_t a, const vec3_t b);

void Normalize3(vec3_t vOut, const vec3_t vec);

void MatrixMultiply(float *mOut, const float *mA, const float *mB);

void MatrixTranslation(float *mOut, const float x, const float y, const float z);

void MatrixRotationZ(float *mOut, const float angle);

void MatrixPerspectiveFovRH(float *mOut, const float FOVy, const float aspect, const float near, const float far);

void MatrixLookAtRH(float *mOut, const vec3_t vEye, const vec3_t vAt, const vec3_t vUp);
	
#ifdef __cplusplus
}
#endif

#endif