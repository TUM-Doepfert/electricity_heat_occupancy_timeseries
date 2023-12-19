/**
 * ModelicaUtilities.c
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if defined(_MSC_VER)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <excpt.h>
#define STATUS_MODELICAERROR 0xE0000002
#endif

#include "ModelicaUtilities.h"
#include "ITI_Functions.h"
#include "ITI_Memory.h"

/* Define to 1 if you have a C99 compliant `vsnprintf' function. */
#if defined(STDC99)
#define HAVE_VSNPRINTF 1
#elif defined(__MINGW32__) || defined(__CYGWIN__)
#if __STDC_VERSION__ >= 199901L
#define HAVE_VSNPRINTF 1
#endif
#elif defined(__WATCOMC__)
#define HAVE_VSNPRINTF 1
#elif defined(__TURBOC__) && __TURBOC__ >= 0x550
#define HAVE_VSNPRINTF 1
#elif defined(MSDOS) && defined(__BORLANDC__) && (BORLANDC > 0x410)
#define HAVE_VSNPRINTF 1
#elif defined(_MSC_VER) && _MSC_VER >= 1900
#define HAVE_VSNPRINTF 1
#else
#undef HAVE_VSNPRINTF
#endif

#if !HAVE_VSNPRINTF
int rpl_vsnprintf(char *, size_t, const char *, va_list);
#define vsnprintf rpl_vsnprintf
#endif /* !HAVE_VSNPRINTF */

#if (defined(_OPENMP) )
/* Visual Studio breaks the openmp 2.0 rules, so it need an extra treatment: */
#if (defined(_MSC_VER) )
  extern _declspec(thread) ITI_SolverInfo* g_sInfo;
  extern _declspec(thread) ITI_MemoryObject* g_currMem;
  extern _declspec(thread) ITI_real g_tStart;
#else /* not defined _MSC_VER */
  extern ITI_SolverInfo* g_sInfo;
  extern ITI_MemoryObject* g_currMem;
  extern ITI_real g_tStart;
  #pragma omp threadprivate(g_currMem)
  #pragma omp threadprivate(g_sInfo)
  #pragma omp threadprivate(g_tStart)
#endif /* defined _MSC_VER */
#else /* not defined _OPENMP */
  extern ITI_SolverInfo* g_sInfo;
  extern ITI_MemoryObject* g_currMem;
  extern ITI_real g_tStart;
#endif

void ModelicaMessage(const char* string)
{
	ModelicaFormatMessage("%s", string);
}

void ModelicaFormatMessage(const char* string, ...)
{
	va_list argList;
	va_start(argList, string);
	ModelicaVFormatMessage(string, argList);
	va_end(argList);
}

void ModelicaVFormatMessage(const char* string, va_list argList)
{
	char msg[ITI_TRACE_STRING_SIZE];

	strcpy(msg, "Info: ");
	vsnprintf(msg + strlen(msg), sizeof(msg) - 7, string, argList);
	traceFunction(msg, g_sInfo);
}

void ModelicaWarning(const char* string)
{
	ModelicaFormatWarning("%s", string);
}

void ModelicaFormatWarning(const char* string, ...)
{
	va_list argList;
	va_start(argList, string);
	ModelicaVFormatWarning(string, argList);
	va_end(argList);
}

void ModelicaVFormatWarning(const char* string, va_list argList)
{
	char msg[ITI_TRACE_STRING_SIZE];

	strcpy(msg, "Warning: ");
	vsnprintf(msg + strlen(msg), sizeof(msg) - 10, string, argList);
	traceWarningImmediately("", msg, g_sInfo);
}

void ModelicaError(const char* string)
{
	ModelicaFormatError("%s", string);
}

void ModelicaFormatError(const char* string, ...)
{
	va_list argList;
	va_start(argList, string);
	ModelicaVFormatError(string, argList);
	va_end(argList);
}

void ModelicaVFormatError(const char* string, va_list argList)
{
	char msg[ITI_TRACE_STRING_SIZE];

	strcpy(msg, "Error: ");
	vsnprintf(msg + strlen(msg), sizeof(msg) - 8, string, argList);
	traceError(msg, g_sInfo);
	g_sInfo->MEcalled = ITI_true;
#if defined _MSC_VER && !defined ITI_TWINCAT
	RaiseException(STATUS_MODELICAERROR, 0, 0, 0);
#else
	longjmp(g_sInfo->buf, 1);
#endif
}

char* ModelicaAllocateString(size_t len)
{
	char *res = ModelicaAllocateStringWithErrorReturn(len);
	if (!res)
		ModelicaFormatError("ModelicaAllocateString failed\n");
	return res;
}

char* ModelicaAllocateStringWithErrorReturn(size_t len)
{
	#ifdef REAL_TIME
	char* res = GetCachedMemory(g_currMem, STRING_TYPE, (int)(len + 1));
	#else
	char* res = GetMemory(g_currMem, STRING_TYPE, (int)(len + 1));
	#endif
	if (res != NULL) {
		res[len] = '\0';
	}
	return res;
}

void SetTimeEvent(double t)
{
	/*TODO*/
	/*CSolutionClientSet* scc=GetCurrentModelForExternal();
	if(scc)
		scc->SetAbsEvent(t,NULL);*/
}

double GetStartTime(void)
{
	return g_tStart;
}

long IsModelicaEvent(void)
{
	return 1;
	/*
	if (g_sInfo)
		return (long)g_sInfo->isEvent;
	return 1;
	*/
}
