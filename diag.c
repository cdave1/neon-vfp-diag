/*
 *  DiagnosticsFunctions.cpp
 *  TotemGame
 *
 *  Created by david on 9/07/09.
 *  Copyright 2009 n/a. All rights reserved.
 *
 */

#include "diag.h"
#include "vfp/common_macros.h"
#include "vfp/matrix_impl.h"
#include "vfp/vfp_clobbers.h"


const int kIterations = 1000000;

void MatrixVecMultGCC()
{
	int i = 0;
	
	matrix_t matA;
	vec3_t vec(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f));
	vec3_t res;
	
	MatrixIdentity(matA);
	MatrixRotationXYZAxis(matA, hdRandom(0.0f, 10.0f), vec3_t(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f)));
	
	while(i++ < kIterations)
	{
		//void MatrixVec4Multiply(vec3_t &vOut, const vec3_t &vIn, const matrix_t &mIn)
		MatrixVec4Multiply(res, vec, matA);
		
		//Matrix4Vector4Mul(&res.x, &vec.x, res);
	}
}



void MatrixVecMultVFP()
{
	int i = 0;
	
	matrix_t matA;
	vec3_t vec(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f));
	vec3_t res;
	
	MatrixIdentity(matA);
	MatrixRotationXYZAxis(matA, hdRandom(0.0f, 10.0f), vec3_t(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f)));
	
	while(i++ < kIterations)
	{
		//void MatrixVec4Multiply(vec3_t &vOut, const vec3_t &vIn, const matrix_t &mIn)
		//MatrixVec4Multiply(res, vec, matA);
		//Matrix4Vector4Mul(const float* src_mat, const float* src_vec, float* dst_vec)Matrix4Vector4Mul(const float* src_mat, const float* src_vec, float* dst_vec);
		Matrix4Vector3Mul(matA.f, &(vec.x), &(res.x));
	}
}


void MatrixVFPTest()
{
	int i = 0;
	
	matrix_t matA;
	matrix_t matB;
	matrix_t res;
	
	MatrixIdentity(matA);
	MatrixIdentity(matB);
	MatrixIdentity(res);
	
	MatrixRotationXYZAxis(matA, hdRandom(0.0f, 10.0f), vec3_t(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f)));
	MatrixRotationXYZAxis(matB, hdRandom(0.0f, 10.0f), vec3_t(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f)));
	
	while(i++ < kIterations)
	{
		Matrix4Mul(matA.f,
				   matB.f,
				   res.f);
	}
}


void MatrixVFPAltTest()
{
	int i = 0;
	
	matrix_t matA;
	matrix_t matB;
	matrix_t res;
	
	MatrixIdentity(matA);
	MatrixIdentity(matB);
	MatrixIdentity(res);
	
	MatrixRotationXYZAxis(matA, hdRandom(0.0f, 10.0f), vec3_t(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f)));
	MatrixRotationXYZAxis(matB, hdRandom(0.0f, 10.0f), vec3_t(hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f), hdRandom(0.0f, 3.0f)));
	
	while(i++ < kIterations)
	{
		Matrix4Mul_Test(matA.f,
						matB.f,
						res.f);	
	}
}


void ARMDotProductTest()
{
	int i = 0;

	
	

	
	
	while (i++ < kIterations) 
	{
		//res[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
		
		/*
		 "fldmias %1!, {s0-s7} \n\t"
		 // Load the whole matrix into memory.
		 "fldmias %2, {s16-s31} \n\t"
		 
		 // First column times matrix.
		 "fmuls s8, s16, s0 \n\t"
		 "fmuls s12, s16, s4 \n\t"
		 "fmacs s8, s20, s1 \n\t"
		 "fmacs s12, s20, s5 \n\t"
		 "fmacs s8, s24, s2 \n\t"
		 "fmacs s12, s24, s6 \n\t"
		 */
		
		ARMDotProduct(); //res, a, b);
		/*
		asm volatile (
					  
					  
					  
					  
						  "flds	s14, [%[fA], #4] \n\t"
						  "flds	s15, [%[fB], #4] \n\t"
						  "flds	s12, [%[fB], #0] \n\t"
						  "flds	s13, [%[fA], #0] \n\t"
						  
						  "fmuls	s15, s14, s15  \n\t"
						  "flds	s14, [%[fA], #8] \n\t"
						  "fmacs	s15, s12, s13  \n\t"
						  "fcpys	s13, s15		\n\t"
						  "flds	s15, [%[fB], #8]	\n\t"
						  "fmacs	s13, s14, s15	\n\t"
						  "fsts	s13, [%0, #0] \n\t"
						  : "=r" (res)
						  :  
						  [fA] "r" (a),
							"0" (res),
						  [fB] "r" (b)
						  : "r0", "cc", "memory", VFP_CLOBBER_S12_S15
						  );//"s13", "cc"
		
		*/
		
		//assert(res[0] == 9000.0f); // 9000.0f); // || res < 0.0f);
	}
	//delete [] src;
}



//"fstmias  %0, {s8-s10}   \n\t" 
volatile void ARMDotProduct() //float* fOut, const float* fA, const float* fB)
{
	// [rOut] "=r" (fOut) 
	const float a[3] = {100.0f, 100.0f, 100.0f }; 
	const float b[3] = {20.0f, 30.0f, 40.0f }; 
	float res[2] = {0.0f,0.0f}; // = 0.0f; //[3] = {0.0f, 0.0f, 0.0f };
	
	
	__asm__ volatile (VFP_SWITCH_TO_ARM 
				  "nop \n\t"
				  VFP_SWITCH_TO_THUMB 
		//"flds	s14, [%[fA], #4] \n\t"
		//"flds	s15, [%[fB], #4] \n\t"
		//"flds	s13, [%[fB], #0] \n\t"
		//"flds	s12, [%[fA], #0] \n\t"

		//"fmuls	s15, s14, s15  \n\t"
		//"flds	s14, [%[fA], #8] \n\t"
		//"fmacs	s15, s12, s13  \n\t"
		//"fcpys	s13, s15		\n\t"
		//"flds	s15, [%[fB], #8]	\n\t"
		//"fmacs	s13, s14, s15	\n\t"
		//"fsts	s13, [%0, #0]	\n\t"
					  : //"=r" (res)
					  : 
					 // [fA] "r" (a), 
					  //"0" (res),
					 // [fB] "r" (b)
					  : //"r0" , "cc", "memory", VFP_CLOBBER_S12_S15
					  );
	//assert(res[0] == 9000.0f);
	/*
	__asm__ volatile (
					  //VFP_SWITCH_TO_ARM 
					  //"mov r1, %[a1] \n\t"
					  //"mov r2, %[b1] \n\t"
					  
					  "mul r0, %[a1], %[b1] \n\t" 
					  "mul r1, %[a2], %[b2] \n\t"
					  "mul r2, %[a3], %[b3] \n\t"
					  
					  "add r1, r1, r2 \n\t"
					  "add r0, r1, r0 \n\t"
					  "mov %[result], r0 \n\t"
				
					  //VFP_SWITCH_TO_THUMB 
					  : [result] "=r" (fOut) 
					  : [a1] "r" (fA[0]), 
					  [a2] "r" (fA[1]), 
					  [a3] "r" (fA[2]), 
					  [b1] "r" (fB[0]), 
					  [b2] "r" (fB[1]), 
					  [b3] "r" (fB[2]) 
					  : "r0" , "cc"
					  );*/
		
	
	/*
	__asm__ volatile (
					  //VFP_SWITCH_TO_ARM 
					  "mov r1, %[a1] \n\t"
					  "mov r2, %[b1] \n\t"
					  "mul r3, r1, r2 \n\t" 
					  
					  "mov r4, %[a2] \n\t"
					  "mov r5, %[b2] \n\t"
					  "mul r6, r4, r5 \n\t" 
					  
					  "add r4, r3, r6 \n\t"
					  
					  "mov r1, %[a3] \n\t"
					  "mov r2, %[b3] \n\t"
					  "mul r3, r1, r2 \n\t" 
					  
					  "add r1, r3, r4 \n\t"
					  "mov %[result], r0 \n\t"
					  
					  
					  //VFP_SWITCH_TO_THUMB 
					  : [result] "=r" (fOut) 
					  : [a1] "r" (fA[1]), 
					  [a2] "r" (fA[2]), 
					  [a3] "r" (fA[3]), 
					  [b1] "r" (fB[1]), 
					  [b2] "r" (fB[2]), 
					  [b3] "r" (fB[3]) 
					  : "r0" , "cc"
					  );
	*/
	
	
	/*
	__asm__ volatile (
					  "fmuls %[result], %[a1], %[b1] \n\t"
  					  "fmacs %[result], %[a2], %[b2] \n\t"
					  "fmacs %[result], %[a3], %[b3] \n\t"					  
					  : [result] "=w" (fOut) 
					  : [a1] "w" (fA[1]), 
					  [a2] "w" (fA[2]), 
					  [a3] "w" (fA[3]), 
					  [b1] "w" (fB[1]), 
					  [b2] "w" (fB[2]), 
					  [b3] "w" (fB[3]) 
					  : "r0" 
					  );
	
	*/
	/*
	__asm__ volatile (
					  //VFP_SWITCH_TO_ARM 
					  
					  //"fmuls %[result], %[a1], %[b1] \n\t"
  					  //"fmacs %[result], %[a2], %[b2] \n\t"
					  //"fmacs %[result], %[a3], %[b3] \n\t"					  
					  
					  "mov %[result], %[a1] \n\t"
					  //"mul s3, s0, %[a2] \n\t"
					  //"add 
					  
					  
					  
					  //VFP_SWITCH_TO_THUMB 
					  : [result] "=r" (fOut) 
					  : [a1] "r" (fA[1]), 
					  [a2] "r" (fA[2]), 
					  [a3] "r" (fA[3]), 
					  [b1] "r" (fB[1]), 
					  [b2] "r" (fB[2]), 
					  [b3] "r" (fB[3]) 
					  : "r0" 
					  );
	*/
	
	
	//float res = 0.0f;
	/*
	__asm__ volatile (
					  VFP_SWITCH_TO_ARM 

					  "fmuls %[result], %[a1], %[b1] \n\t"
  					  "fmacs %[result], %[a2], %[b2] \n\t"
					  "fmacs %[result], %[a3], %[b3] \n\t"					  

					  VFP_SWITCH_TO_THUMB 
					  : [result] "=w" (fOut) 
					  : [a1] "w" (fA[1]), 
						[a2] "w" (fA[2]), 
						[a3] "w" (fA[3]), 
						[b1] "w" (fB[1]), 
						[b2] "w" (fB[2]), 
						[b3] "w" (fB[3]) 
					  : "r0" 
					  );
	*/
	
	
	/*
	__asm__ volatile (
				  VFP_SWITCH_TO_ARM 
				  
				  "fldmias  %[vector1], {s8-s10}  \n\t"
				  "fldmias  %[vector2], {s12-s14} \n\t" 
				  
				  VFP_VECTOR_LENGTH(1) 
				  
				  "fmacs s8, s8, s16   \n\t" 
				  "fmacs s8, s9, s17   \n\t" 
				  "fmacs s8, s10, s18 \n\t" 
				  //"fadds s8, s8, s9   \n\t" 
				  //"fadds s8, s8, s10   \n\t" 
				  "fstmias %[result], {s8} \n\t" 
				  //"fsts {%[result]}, {s8} \n\t"
				  
				  VFP_VECTOR_LENGTH_ZERO 
				 
				  VFP_SWITCH_TO_THUMB 
				  : [result] "=r" (fOut) 
				  : [vector1] "r" (fA), [vector2] "r" (fB) 
				  : "r0", "cc" 
				  );
	*/
	//(*fOut) = res;
}




void GCCDotProductTest()
{

	int i = 0;
	
	while (i++ < kIterations) 
	{
		
		
		GCCDotProduct(); //&res, a, b);
		
		
	}
}





void GCCDotProduct() //float* fOut, const float* fA, const float* fB)
{
	
	const float a[3] = {100.0f, 100.0f, 100.0f }; 
	const float b[3] = {20.0f, 30.0f, 40.0f }; 
	float res = 0.0f;
	
	res = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
	assert(res == 9000.0f);
	//(*fOut) = fA[0]*fB[0] + fA[1]*fB[1] + fA[2]*fB[2];
	
//	return x*a.x + y*a.y + z*a.z;
}