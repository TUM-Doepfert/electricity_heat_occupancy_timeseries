/**
 * ITI_Memory.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_crt.h"
#include <stddef.h>

static void FreeMemory(ITI_MemoryObject* currMem, enum MemoryType memType);
static void ReleaseMemory(ITI_MemoryObject* currMem, enum MemoryType memType);

ITI_int Align(ITI_int n, ITI_int a)
{
	ITI_int d = n % a;
	if (d)
		n += a-d;
	return n;
}

void InitMemory(ITI_MemoryObject* currMem, ITI_AllocateMemory allocateMemory, ITI_FreeMemory freeMemory)
{
	if (allocateMemory==0)
		#ifdef ITI_SCALERT
		allocateMemory = calloc_SCALERT;
		#else
		allocateMemory = calloc;
		#endif
	currMem->allocateMemory = allocateMemory;

	if (freeMemory==0)
		#ifdef ITI_SCALERT
		freeMemory = free_SCALERT;
		#else
		freeMemory = free;
		#endif
	currMem->freeMemory = freeMemory;

	#ifdef REAL_TIME
	currMem->currentIntBlock = (ITI_MemoryBlock*)currMem->allocateMemory(1, sizeof(ITI_MemoryBlock));
	currMem->currentRealBlock = (ITI_MemoryBlock*)currMem->allocateMemory(1, sizeof(ITI_MemoryBlock));
	currMem->currentStringBlock = (ITI_MemoryBlock*)currMem->allocateMemory(1, sizeof(ITI_MemoryBlock));
	currMem->currentIntBlock->currBuffer = (ITI_char*)currMem->allocateMemory(ITI_BLOCK_SIZE, sizeof(ITI_int));
	currMem->currentRealBlock->currBuffer = (ITI_char*)currMem->allocateMemory(ITI_BLOCK_SIZE, sizeof(ITI_real));
	currMem->currentStringBlock->currBuffer = (ITI_char*)currMem->allocateMemory(ITI_BLOCK_SIZE, sizeof(ITI_char));

	currMem->currentIntBlock->startBuffer = currMem->currentIntBlock->currBuffer;
	currMem->currentIntBlock->nextBlock = 0;
	currMem->currentIntBlock->endBuffer = currMem->currentIntBlock->currBuffer + ITI_BLOCK_SIZE;
	currMem->firstIntBlock = currMem->currentIntBlock;

	currMem->currentRealBlock->startBuffer = currMem->currentRealBlock->currBuffer;
	currMem->currentRealBlock->nextBlock = 0;
	currMem->currentRealBlock->endBuffer = currMem->currentRealBlock->currBuffer + ITI_BLOCK_SIZE;
	currMem->firstRealBlock = currMem->currentRealBlock;

	currMem->currentStringBlock->startBuffer = currMem->currentStringBlock->currBuffer;
	currMem->currentStringBlock->nextBlock = 0;
	currMem->currentStringBlock->endBuffer = currMem->currentStringBlock->currBuffer + ITI_BLOCK_SIZE;
	currMem->firstStringBlock = currMem->currentStringBlock;
	#else
	currMem->currentIntBlock = 0;
	currMem->firstIntBlock = 0;

	currMem->currentRealBlock = 0;
	currMem->firstRealBlock = 0;

	currMem->currentStringBlock = 0;
	currMem->firstStringBlock = 0;
	#endif

	currMem->allocStrategy = UseFreeSpaceInOtherBlocks;
}

ITI_int GetTypeLength(enum MemoryType memType)
{
	ITI_int len = 0;
	switch (memType){
		case INT_TYPE :
			len = sizeof(ITI_int);
			break;
		case REAL_TYPE :
			len = sizeof(ITI_real);
			break;
		case STRING_TYPE :
			len = sizeof(ITI_char);
			break;
		case STRING_PTR_TYPE :
			len = sizeof(ITI_char*);
			break;
	}
	return len;
}

ITI_MemoryBlock* GetCurrentBlock(ITI_MemoryObject* currMem, enum MemoryType memType)
{
	ITI_MemoryBlock* memBlock = 0;
	switch (memType){
		case INT_TYPE :
			memBlock = currMem->currentIntBlock;
			break;
		case REAL_TYPE :
			memBlock = currMem->currentRealBlock;
			break;
		case STRING_TYPE :
		case STRING_PTR_TYPE :
			memBlock = currMem->currentStringBlock;
			break;
	}
	return memBlock;
}

void SetCurrentBlock(ITI_MemoryObject* currMem, enum MemoryType memType,
											ITI_MemoryBlock* currentBlock)
{
	switch (memType){
		case INT_TYPE :
			currMem->currentIntBlock = currentBlock;
			break;
		case REAL_TYPE :
			currMem->currentRealBlock = currentBlock;
			break;
		case STRING_TYPE :
		case STRING_PTR_TYPE :
			currMem->currentStringBlock = currentBlock;
			break;
	}
}

void SetFirstBlock(ITI_MemoryObject* currMem, enum MemoryType memType,
											ITI_MemoryBlock* firstBlock)
{
	switch (memType){
		case INT_TYPE :
			currMem->firstIntBlock = firstBlock;
			break;
		case REAL_TYPE :
			currMem->firstRealBlock = firstBlock;
			break;
		case STRING_TYPE :
			case STRING_PTR_TYPE :
			currMem->firstStringBlock = firstBlock;
			break;
	}
}

ITI_MemoryBlock* GetFirstBlock(ITI_MemoryObject* currMem, enum MemoryType memType)
{
	ITI_MemoryBlock* memBlock = 0;
	switch (memType){
		case INT_TYPE :
			memBlock = currMem->firstIntBlock;
			break;
		case REAL_TYPE :
			memBlock = currMem->firstRealBlock;
			break;
		case STRING_TYPE :
		case STRING_PTR_TYPE :
			memBlock = currMem->firstStringBlock;
			break;
	}
	return memBlock;
}

void CopyToFlatMemory(ITI_MemoryObject* currMem, ITI_MemoryBlock* block)
{
	ptrdiff_t offset = 0;
	ptrdiff_t memSize = 0;
	ITI_MemoryBlock* currBlock = block;

	while (currBlock){
		memSize += currBlock->currBuffer - currBlock->startBuffer;
		currBlock = currBlock->nextBlock;
	}

	memSize += 1;

	currMem->flatMemory = (ITI_char*)currMem->allocateMemory(memSize, 1);
	currBlock = block;

	while (currBlock){
		ptrdiff_t size = currBlock->currBuffer - currBlock->startBuffer;
		memcpy(currMem->flatMemory+offset, currBlock->startBuffer, size);
		offset += size;
		currBlock = currBlock->nextBlock;
	}
}

ITI_MemoryBlock* CreateMemoryBlock(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_int blockSize)
{
	ITI_MemoryBlock* newBlock = (ITI_MemoryBlock*)currMem->allocateMemory(1, sizeof(ITI_MemoryBlock));
	if (!newBlock)
		return NULL;
	newBlock->memType = memType;
	newBlock->currBuffer = (ITI_char*)currMem->allocateMemory(blockSize, 1);
	if (!newBlock->currBuffer) {
		currMem->freeMemory(newBlock);
		return NULL;
	}
	newBlock->startBuffer = newBlock->currBuffer;
	newBlock->endBuffer = newBlock->currBuffer + blockSize;
	newBlock->nextBlock = 0;
	return newBlock;
}




ITI_char* GetNextBlock(ITI_MemoryObject* currMem, enum MemoryType memType,
									ITI_int bSize, ITI_int blockSize)
{
	ITI_char* mem = 0;
	ITI_MemoryBlock* currentBlock = GetCurrentBlock(currMem, memType);

	if (currentBlock && currentBlock->nextBlock){
		if (currentBlock->nextBlock->currBuffer+bSize > currentBlock->nextBlock->endBuffer){
			 
			ITI_MemoryBlock* oldBlock = currentBlock;
			ITI_MemoryBlock* nextBlock = oldBlock->nextBlock;
			ITI_MemoryBlock* newBlock = CreateMemoryBlock(currMem, memType, blockSize);
			if (!newBlock)
				return NULL;
			newBlock->nextBlock = nextBlock;
			oldBlock->nextBlock = newBlock;
			currentBlock = newBlock;
			SetCurrentBlock(currMem, memType, newBlock);
		}
		else {
			currentBlock = currentBlock->nextBlock;
			SetCurrentBlock(currMem, memType, currentBlock);
		}
	}
	else {
		 
		ITI_MemoryBlock* newBlock = CreateMemoryBlock(currMem, memType, blockSize);
		if (!newBlock)
			return NULL;

		if (currentBlock)
			currentBlock->nextBlock = newBlock;

		currentBlock = newBlock;
		SetCurrentBlock(currMem, memType, currentBlock);
	}
	mem = currentBlock->currBuffer;
	currentBlock->currBuffer += bSize;
	return mem;
}




ITI_char* Overflow(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_int bSize)
{
	ITI_char* mem = 0;
	#ifdef REAL_TIME
	switch (memType){
		case INT_TYPE :
			assertFunction(0, "Out of memory (ITI_int)", 0);
			break;
		case REAL_TYPE :
			assertFunction(0, "Out of memory (ITI_real)", 0);
			break;
		case STRING_TYPE :
			assertFunction(0, "Out of memory (ITI_char)", 0);
			break;
		case STRING_PTR_TYPE :
			assertFunction(0, "Out of memory (ITI_char*)", 0);
			break;
	}
	

	#else
	ITI_MemoryBlock* firstBlock = GetFirstBlock(currMem, memType);
	ITI_MemoryBlock* currentBlock = GetCurrentBlock(currMem, memType);
	if (bSize < 0)
		return NULL;
	if (currentBlock){
		if (bSize < ITI_BLOCK_SIZE){
			ITI_MemoryBlock* res = 0;
			ITI_MemoryBlock* tempBlock = firstBlock;
			if(currMem->allocStrategy != DontUseSpaceInOtherBlocks){
				while (tempBlock) {
					if (tempBlock->currBuffer+bSize <= tempBlock->endBuffer){
						res = tempBlock;
						break;
					}
					tempBlock = tempBlock->nextBlock;
				}
			}
			if (res){
				mem = res->currBuffer;
				res->currBuffer += bSize;
			}
			else
				mem = GetNextBlock(currMem, memType, bSize, ITI_BLOCK_SIZE);
		}
		else
			mem = GetNextBlock(currMem, memType, bSize, bSize);
	}
	else {
		ITI_int blockSize = ITI_BLOCK_SIZE;
		if (bSize > ITI_BLOCK_SIZE)
			blockSize = bSize;

		mem = GetNextBlock(currMem, memType, bSize, blockSize);
		currentBlock = GetCurrentBlock(currMem, memType);
		SetFirstBlock(currMem, memType, currentBlock);
	}
	#endif
	return mem;
}

ITI_char* GetCachedMemory(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_int bSize)
{
	ITI_char* mem = NULL;
	ITI_MemoryBlock* currentBlock = GetCurrentBlock(currMem, memType);
	if (bSize < 0)
		return NULL;
	if (currentBlock && currentBlock->currBuffer+bSize <= currentBlock->endBuffer){
		mem = currentBlock->currBuffer;
		currentBlock->currBuffer += bSize;
	}
	return mem;
}




ITI_char* GetMemory(ITI_MemoryObject* currMem, enum MemoryType memType, ITI_int bSize)
{
	ITI_char* mem = GetCachedMemory(currMem, memType, bSize);
	if(!mem)
		mem = Overflow(currMem, memType, bSize);
	return mem;
}

void SaveCurrentBuffer(ITI_MemoryObject* currMem, enum MemoryType memType)
{
	ITI_MemoryBlock* currentBlock = GetCurrentBlock(currMem, memType);
	if (currentBlock && currentBlock->currBuffer)
		currentBlock->saveBuffer = currentBlock->currBuffer;
}

void RestoreSavedBuffer(ITI_MemoryObject* currMem, enum MemoryType memType)
{
	ITI_MemoryBlock* currentBlock = GetCurrentBlock(currMem, memType);
	if (currentBlock && currentBlock->saveBuffer){
		currentBlock->currBuffer = currentBlock->saveBuffer;
		currentBlock->saveBuffer = 0;
	}
}

int* GetIntMemory(ITI_MemoryObject* currMem, int nInt)
{
	int bSize = nInt * GetTypeLength(INT_TYPE);
	return (int*) GetMemory(currMem, INT_TYPE, bSize);
}

double* GetRealMemory(ITI_MemoryObject* currMem, int nReal)
{
	int bSize = nReal * GetTypeLength(REAL_TYPE);
	bSize = Align(bSize, 8);
	return (double*) GetMemory(currMem, REAL_TYPE, bSize);
}

char* GetStringMemory(ITI_MemoryObject* currMem, int nChar)
{
	int bSize = (nChar + 1) * GetTypeLength(STRING_TYPE);
	return GetMemory(currMem, STRING_TYPE, bSize);
}

char** GetStringPtrMemory(ITI_MemoryObject* currMem, int nChar)
{
	int bSize = nChar * GetTypeLength(STRING_PTR_TYPE);
	return (char**)GetMemory(currMem, STRING_PTR_TYPE, bSize+1);
}




static void ReleaseMemory(ITI_MemoryObject* currMem, enum MemoryType memType)
{
#ifdef REAL_TIME
	ITI_MemoryBlock* currBlock = GetCurrentBlock(currMem, memType);
	memset((void*)currBlock->startBuffer, 0, currBlock->currBuffer - currBlock->startBuffer);
	currBlock->currBuffer = currBlock->startBuffer;
#else
	ITI_MemoryBlock* firstBlock = GetFirstBlock(currMem, memType);
	if (firstBlock){
		ITI_MemoryBlock* currBlock = firstBlock;
		SetCurrentBlock(currMem, memType, firstBlock);
		while (currBlock){
			memset((void*)currBlock->startBuffer, 0, currBlock->currBuffer - currBlock->startBuffer);
			currBlock->currBuffer = currBlock->startBuffer;
			currBlock = currBlock->nextBlock;
		}
	}
#endif
}




static void FreeMemory(ITI_MemoryObject* currMem, enum MemoryType memType)
{
	#ifdef REAL_TIME
	ITI_MemoryBlock* firstBlock = GetFirstBlock(currMem, memType);
	currMem->freeMemory(firstBlock->startBuffer);
	currMem->freeMemory(firstBlock);
	#else
	ITI_MemoryBlock* firstBlock = GetFirstBlock(currMem, memType);
	if (firstBlock){
		ITI_MemoryBlock* currBlock = firstBlock;
		while (currBlock){
			ITI_MemoryBlock* temp = currBlock;
			currBlock = currBlock->nextBlock;
			currMem->freeMemory(temp->startBuffer);
			currMem->freeMemory(temp);
		}
	}
	#endif
}

void ReleaseAllMemory(ITI_MemoryObject* currMem)
{
	ReleaseMemory(currMem, INT_TYPE);
	ReleaseMemory(currMem, REAL_TYPE);
	ReleaseMemory(currMem, STRING_TYPE);
}

void FreeAllMemory(ITI_MemoryObject* currMem)
{
	FreeMemory(currMem, INT_TYPE);
	FreeMemory(currMem, REAL_TYPE);
	FreeMemory(currMem, STRING_TYPE);
}

void FreeFlatMemory(ITI_MemoryObject* currMem)
{
	if (currMem)
		currMem->freeMemory(currMem->flatMemory);
}

ITI_uint IsInMemoryBlock(ITI_char* mem, ITI_MemoryObject* currMem, enum MemoryType memType)
{
	ITI_uint res = 0;

	#ifdef REAL_TIME
		switch (memType){
			case INT_TYPE :
				if (mem >= currMem->currentIntBlock->startBuffer && mem <= currMem->currentIntBlock->endBuffer)
					res = 1;
				break;
			case REAL_TYPE :
				if (mem >= currMem->currentRealBlock->startBuffer && mem <= currMem->currentRealBlock->endBuffer)
					res = 1;
				break;
			case STRING_TYPE :
			case STRING_PTR_TYPE :
				if (mem >= currMem->currentStringBlock->startBuffer && mem <= currMem->currentStringBlock->endBuffer)
				break;
		}
	#else
		ITI_MemoryBlock* tempBlock = GetFirstBlock(currMem, memType);
		while (tempBlock){
			if (mem >= tempBlock->startBuffer && mem <= tempBlock->endBuffer){
				res = 1;
				break;
			}
			else
				tempBlock = tempBlock->nextBlock;
		}

	#endif

	return res;
}
