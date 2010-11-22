/*
 *  DiagnosticsFunctions.h
 *  TotemGame
 *
 *  Created by david on 9/07/09.
 *  Copyright 2009 n/a. All rights reserved.
 *
 */

#ifndef _DIAGNOSTIC_FUNCTIONS_
#define _DIAGNOSTIC_FUNCTIONS_

#include "commonMath.h"


#ifdef __cplusplus
extern "C" {
#endif

void MatrixVFPTest();
	
void MatrixVFPAltTest();

	void MatrixVecMultGCC();	
	
	void MatrixVecMultVFP();
	
	
void ARMDotProductTest();

void GCCDotProductTest();

	volatile void ARMDotProduct(); //float* fOut, const float* fA, const float* fB);

	void GCCDotProduct(); //float* fOut, const float* fA, const float* fB);

#ifdef __cplusplus
}
#endif
	
#endif