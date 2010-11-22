#include <stdio.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

#include "diag.h"

void DoDiagnostics(int val);


int main (int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: diag <val>, where val is one of four diagnostics programs numbered 0 to 3");
		return;
	}
	
	int val = (int)strtol(argv[1], NULL, 0);
	
	DoDiagnostics(val);
	
	
	return 0;
}


static uint32	startTime = 0.0f;
static uint32	stopTime = 0.0f;

void DoDiagnostics(int val)
{
	switch (val) {
		case 0:
			startTime = mach_absolute_time();
			MatrixVecMultGCC();
			stopTime = mach_absolute_time();
			
			snprintf(tmp, 128, "GCC Vec Mult: %d ticks", (stopTime - startTime));
			m_fontTestResult->SetText(tmp);					
			
			
			/*
			 startTime = mach_absolute_time();
			 GCCDotProductTest();
			 stopTime = mach_absolute_time();
			 
			 snprintf(tmp, 128, "GCC Dot Prod: %d ticks", (stopTime - startTime));
			 m_fontTestResult->SetText(tmp);
			 */
			break;
		case 1:
			startTime = mach_absolute_time();
			MatrixVecMultVFP();
			
			stopTime = mach_absolute_time();
			
			snprintf(tmp, 128, "VFP Vec Mult: %d ticks", (stopTime - startTime));
			m_fontTestResult->SetText(tmp);
			
			
			/*
			 startTime = mach_absolute_time();
			 ARMDotProductTest();
			 
			 stopTime = mach_absolute_time();
			 
			 snprintf(tmp, 128, "(BROKEN) ARM Dot Prod: %d ticks", (stopTime - startTime));
			 m_fontTestResult->SetText(tmp);
			 */
			break;
		case 2:
			startTime = mach_absolute_time();
			MatrixVFPTest();
			
			stopTime = mach_absolute_time();
			
			snprintf(tmp, 128, "Normal VFP Matrix Mult: %d ticks", (stopTime - startTime));
			m_fontTestResult->SetText(tmp);					
			
			
			break;
		case 3:
			startTime = mach_absolute_time();
			MatrixVFPAltTest();
			
			stopTime = mach_absolute_time();
			
			snprintf(tmp, 128, "Alternative VFP Matrix Mult: %d ticks", (stopTime - startTime));
			m_fontTestResult->SetText(tmp);	
			
			break;
		default:
			break;
	}
}