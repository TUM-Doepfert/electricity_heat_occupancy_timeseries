/**
 * ITI_SolverHelpers.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_SolverHelpers)
#define _ITI_SolverHelpers

#include "ITI_crt.h"

#include <time.h>

typedef struct ITI_ExecModel_Data {
	SetInputsFunc pSetInputFunc;
	char *outputFileName;
	FILE* outputs;
	int iVariant;
	int iPlaces;
	clock_t cLast;
} ITI_ExecModel_Data;

ITI_FUNCTIONS_API int str_case_cmp(const char* str1, const char* str2);
ITI_FUNCTIONS_API void FillSolverSettings(ITI_SolverSettings* pSS);
#if !defined(ITI_DSPACE)
ITI_FUNCTIONS_API int ReadSolverSettingsFromFile(FILE* file, ITI_SolverSettings* pSS);
ITI_FUNCTIONS_API int ReadVariationNumberFromStream(FILE* file);
ITI_FUNCTIONS_API int ReadParametersFromStream(char** buf, int* bufLen, FILE* fp, double **p, unsigned int* isCommented);
ITI_FUNCTIONS_API int ReadLine(char** buf, int* bufLen, FILE* fp);
#endif
ITI_FUNCTIONS_API void Write2Stream(FILE* stream, double* val1, double* val2, double* val3, int c1, int c2, int c3, int i1, int i2, int i3);
 
ITI_FUNCTIONS_API void WriteOutput2Stream(FILE* stream, ITI_outputData* outputData, ITI_PartitionVar* pData, int ySize, int prec_t, int prec_y);
ITI_FUNCTIONS_API void WriteStreamHeader(FILE* stream, const char* str1, const char* str2, const char* str3, int c1, int c2, int c3);
ITI_FUNCTIONS_API void WriteOutputStreamHeader(FILE* stream, ITI_outputData* outputs, int iy);
ITI_FUNCTIONS_API int GetNumberOfDecimalPlaces(const double dblVal);
ITI_FUNCTIONS_API void ShowActTime(clock_t* cLast, ITI_real t, ITI_real tStop, ITI_int iStart);
ITI_FUNCTIONS_API void WriteRootCounter(const char* strFile, int* rootctr, int iSize);
ITI_FUNCTIONS_API int FindMax(int* iData, int iSize);
ITI_FUNCTIONS_API int Check_z_data_trDiscrVar(ITI_PartitionVar* pData, ITI_int intSize, ITI_int realSize, FILE* file, ITI_uint k);
ITI_FUNCTIONS_API int Check_Update_oldsign_zf_trEvent(ITI_real* zf,ITI_real* old_sign_zf, ITI_int iSize, FILE* file, ITI_uint k);
ITI_FUNCTIONS_API void GetOutputFileName(char *fileNameOut, char *fileNameIn, int iVariation);

#ifdef DSD_LENZE
#include <windows.h>
void GetITITempFileName(LPSTR lpTempFileName);
#endif

#ifdef ITI_COMP_SIM
ITI_FUNCTIONS_API void UpdateStates(ITI_xData* dataX, ITI_int size, ITI_WorkSpace ws, ITI_real* x);

ITI_FUNCTIONS_API void RememberVarData(ITI_PartitionVar pData, ITI_WorkSpace ws);
ITI_FUNCTIONS_API void RestoreVarData(ITI_PartitionVar pData, ITI_WorkSpace ws);

ITI_FUNCTIONS_API void InitSynchStrsData(ITI_SynchStrsDataItem* strData, ITI_int size, ITI_uint forParameters);
ITI_FUNCTIONS_API void FreeSynchStrsData(ITI_SynchStrsDataItem* strData);
#endif

#endif

ITI_FUNCTIONS_API void SetContainerData(void* pData, void* pContainer);
ITI_FUNCTIONS_API void* GetContainerData(void* pData);