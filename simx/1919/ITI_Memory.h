/**
 * ITI_Memory.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef ITI_MEMORY_H
#define ITI_MEMORY_H

#ifndef ITI_MEMORY_API
#define ITI_MEMORY_API
#endif

ITI_int Align(ITI_int n, ITI_int a);

ITI_MEMORY_API void InitMemory(ITI_MemoryObject* currMem, ITI_AllocateMemory allocateMemory, ITI_FreeMemory freeMemory);
ITI_int GetTypeLength(enum MemoryType memType);

ITI_MemoryBlock* GetCurrentBlock(ITI_MemoryObject* currMem, enum MemoryType memType);
ITI_MemoryBlock* GetFirstBlock(ITI_MemoryObject* currMem, enum MemoryType memType);
void SetCurrentBlock(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_MemoryBlock* currentBlock);
void SetFirstBlock(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_MemoryBlock* firstBlock);

ITI_int* GetIntMemory(ITI_MemoryObject* currMem, ITI_int nInt);
ITI_real* GetRealMemory(ITI_MemoryObject* currMem, ITI_int nReal);
ITI_MEMORY_API ITI_char* GetStringMemory(ITI_MemoryObject* currMem, ITI_int nChar);
char** GetStringPtrMemory(ITI_MemoryObject* currMem, int nChar);

ITI_char* GetMemory(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_int bSize);
ITI_char* GetCachedMemory(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_int bSize);

void SaveCurrentBuffer(ITI_MemoryObject* currMem, enum MemoryType memType);
void RestoreSavedBuffer(ITI_MemoryObject* currMem, enum MemoryType memType);

ITI_MEMORY_API void FreeAllMemory(ITI_MemoryObject* currMem);
ITI_MEMORY_API void  ReleaseAllMemory(ITI_MemoryObject* currMem);

ITI_uint IsInMemoryBlock(ITI_char* mem, ITI_MemoryObject* currMem, enum MemoryType memType);

void CopyToFlatMemory(ITI_MemoryObject* currMem, ITI_MemoryBlock* block);
void FreeFlatMemory(ITI_MemoryObject* currMem);

#endif  
