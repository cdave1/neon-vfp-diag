/*
 NEON math library for the iPhone / iPod touch
 
 Copyright (c) 2009 Justin Saunders
 
 This software is provided 'as-is', without any express or implied warranty.
 In no event will the authors be held liable for any damages arising
 from the use of this software.
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must
 not claim that you wrote the original software. If you use this
 software in a product, an acknowledgment in the product documentation
 would be appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must
 not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source distribution.
*/

#include "hdMath/neon/neon_matrix_impl.h"

#ifdef __thumb__
#error "This file should be compiled in ARM mode only."
// Note in Xcode, right click file, Get Info->Build, Other compiler flags = "-marm"
#endif

//#ifdef _ARM_ARCH_7
#ifdef __ARM_NEON__
#warning "NEON Matrix functions are included." 

// Note asm is taken from reader "Jeff" post Wolfgang's blog:
// https://www.blogger.com/comment.g?blogID=398682525365778708&postID=7527893703750196380&page=1
void NEON_Matrix4Mul(const float* a, const float* b, float* output )
{
	_asm volatile
	(
	 // Store A & B leaving room at top of registers for result (q0-q3)
	 "vldmia %1, { q0-q3 }	\n\t"
	 "vldmia %2, { q8-q11 }	\n\t"
	 
	 // result = first column of B x first row of A
	 "vmul.f32 q12, q8, d0[0]\n\t"
	 "vmul.f32 q13, q8, d2[0]\n\t"
	 "vmul.f32 q14, q8, d4[0]\n\t"
	 "vmul.f32 q15, q8, d6[0]\n\t"
	 
	 // result += second column of B x second row of A
	 "vmla.f32 q12, q9, d0[1]\n\t"
	 "vmla.f32 q13, q9, d2[1]\n\t"
	 "vmla.f32 q14, q9, d4[1]\n\t"
	 "vmla.f32 q15, q9, d6[1]\n\t"
	 
	 // result += third column of B x third row of A
	 "vmla.f32 q12, q10, d1[0]\n\t"
	 "vmla.f32 q13, q10, d3[0]\n\t"
	 "vmla.f32 q14, q10, d5[0]\n\t"
	 "vmla.f32 q15, q10, d7[0]\n\t"
	 
	 // result += last column of B x last row of A
	 "vmla.f32 q12, q11, d1[1]\n\t"
	 "vmla.f32 q13, q11, d3[1]\n\t"
	 "vmla.f32 q14, q11, d5[1]\n\t"
	 "vmla.f32 q15, q11, d7[1]\n\t"
	 
	 // output = result registers
	 "vstmia %0, { q12-q15 }"
	 : // no output
	 : "r" (output), "r" (a), "r" (b) 	// input - note *value* of pointer doesn't change
	 : "memory", "q0", "q1", "q2", "q3", "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15" //clobber
	 );
}
	 
void NEON_Matrix4Vector4Mul(const float* m, const float* v, float* output)
{
	 _asm volatile
	 (
	 // Store m & v leaving room at top of registers for result (q0)
	 "vldmia %1, {q1-q4 }	\n\t"	// q2-q5 = m
	 "vldmia %2, {q5}		\n\t"	// q1    = v
	 
	 // result = first column of A x V.x
	 "vmul.f32 q0, q1, d10[0]\n\t"
	 
	 // result += second column of A x V.y
	 "vmla.f32 q0, q2, d10[1]\n\t"
	 
	 // result += third column of A x V.z
	 "vmla.f32 q0, q3, d11[0]\n\t"
	 
	 // result += last column of A x V.w
	 "vmla.f32 q0, q4, d11[1]\n\t"
	 
	 // output = result registers
	 "vstmia %0, {q0}"
	 
	 : // no output
	 : "r" (output), "r" (m), "r" (v) 	// input - note *value* of pointer doesn't change
	 : "memory", "q0", "q1", "q2", "q3", "q4", "q5" //clobber
	 );
}


void NEON_Matrix4Vector3Mul(const float* m, const float* v, float* output)
{
	_asm volatile
	(
	 // Store m & v leaving room at top of registers for result (q0)
	 "vldmia %1, {q8-q10 }	\n\t"	// q2-q5 = m
	 "vldmia %2, {q1}		\n\t"	// q1    = v
	 
	 // result = first column of A x V.x
	 "vmul.f32 q0, q8, d2[0]\n\t"
	 
	 // result += second column of A x V.y
	 "vmla.f32 q0, q9, d2[1]\n\t"
	 
	 // result += third column of A x V.z
	 "vmla.f32 q0, q10, d3[0]\n\t"
	 
	 // result += last column of A x V.w
	 "vmla.f32 q0, q11, d3[1]\n\t"
	 
	 // output = result registers
	 "vstmia %0, {q0}"
	 
	 : // no output
	 : "r" (output), "r" (m), "r" (v) 	// input - note *value* of pointer doesn't change
	 : "memory", "q0", "q1", "q8", "q9", "q10" //clobber
	 );
}

#endif