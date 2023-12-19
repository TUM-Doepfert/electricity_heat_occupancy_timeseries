/**
 * ITI_AllocClockInference.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_AllocClockInference.h"
#include "ITI_ClockInference.h"

int AllocIGData(ITI_Partition* pPart, ITI_AllocateMemory allocateMemory) {
	int i;
	int igCount = pPart->curr->size.iig;
	if (igCount == 0) {
		pPart->curr->partitionIG = NULL;
		return 1;
		 
	}

	 
	pPart->curr->partitionIG = (struct inferenceGraph*)allocateMemory(igCount, sizeof(struct inferenceGraph));

	 
	for (i = 0; i < igCount; i++)
	{
		int nodeCnt = pPart->curr->size.iig_nodes[i];
		int edgeCnt = pPart->curr->size.iig_edges[i];
		int baseclkCnt = pPart->curr->size.iig_baseclocks[i];
		int rootCnt = pPart->curr->size.iig_roots[i];
		int solverCnt = pPart->curr->size.iig_solverclocks[i];
		int solverNeed = pPart->curr->size.iig_solverneeded[i];
		int pathCnt = pPart->curr->size.iig_paths[i];
		int stepCnt = pPart->curr->size.iig_steps[i];
		int childCnt = pPart->curr->size.iig_children[i];

		pPart->curr->partitionIG[i].m_NumClocks = nodeCnt;
		pPart->curr->partitionIG[i].m_NumEdges = edgeCnt;
		pPart->curr->partitionIG[i].m_NumBaseClocks = baseclkCnt;
		pPart->curr->partitionIG[i].m_NumRoots = rootCnt;
		pPart->curr->partitionIG[i].m_NumPaths = pathCnt;
		pPart->curr->partitionIG[i].m_NumSteps = stepCnt;

		pPart->curr->partitionIG[i].m_Error = (ITI_char*)allocateMemory(MAX_ERROR_LENGTH + 1, sizeof(ITI_char));

		if (nodeCnt)
			pPart->curr->partitionIG[i].m_Nodes = (struct graphNode*)allocateMemory(nodeCnt, sizeof(struct graphNode));
		else
			pPart->curr->partitionIG[i].m_Nodes = NULL;
		if (edgeCnt)
			pPart->curr->partitionIG[i].m_Edges = (struct graphEdge*)allocateMemory(edgeCnt, sizeof(struct graphEdge));
		else
			pPart->curr->partitionIG[i].m_Edges = NULL;
		if (baseclkCnt)
			pPart->curr->partitionIG[i].m_BaseClocks = (ITI_int*)allocateMemory(baseclkCnt, sizeof(ITI_int));
		else
			pPart->curr->partitionIG[i].m_BaseClocks = NULL;
		if (rootCnt)
			pPart->curr->partitionIG[i].m_Roots = (ITI_int*)allocateMemory(rootCnt+1, sizeof(ITI_int));
		else
			pPart->curr->partitionIG[i].m_Roots = NULL;
		if (pathCnt)
			pPart->curr->partitionIG[i].m_Paths = (struct graphPath*)allocateMemory(pathCnt, sizeof(struct graphPath));
		else
			pPart->curr->partitionIG[i].m_Paths = NULL;
		if (stepCnt)
			pPart->curr->partitionIG[i].m_Steps = (struct graphStep*)allocateMemory(stepCnt, sizeof(struct graphStep));
		else
			pPart->curr->partitionIG[i].m_Steps = NULL;
		if (childCnt)
		{
			pPart->curr->partitionIG[i].m_Children = (ITI_int*)allocateMemory(childCnt, sizeof(ITI_int));
			pPart->curr->partitionIG[i].m_ChildEdges = (ITI_int*)allocateMemory(childCnt, sizeof(ITI_int));
		}
		else
		{
			pPart->curr->partitionIG[i].m_Children = NULL;
			pPart->curr->partitionIG[i].m_ChildEdges = NULL;
		}
	}
	return 1;
}

int FreeIGData(ITI_Partition* pPart, ITI_FreeMemory freeMemory) {
	int i;
	int igCount = pPart->curr->size.iig;

	 
	if (igCount > 0) {
		freeMemory(pPart->curr->size.iig_nodes);	pPart->curr->size.iig_nodes = NULL;
		freeMemory(pPart->curr->size.iig_edges);	pPart->curr->size.iig_edges = NULL;
		freeMemory(pPart->curr->size.iig_children);	pPart->curr->size.iig_children = NULL;
		freeMemory(pPart->curr->size.iig_roots);	pPart->curr->size.iig_roots = NULL;
		freeMemory(pPart->curr->size.iig_baseclocks);	pPart->curr->size.iig_baseclocks = NULL;
		freeMemory(pPart->curr->size.iig_solverclocks);	pPart->curr->size.iig_solverclocks = NULL;
		freeMemory(pPart->curr->size.iig_solverneeded);	pPart->curr->size.iig_solverneeded = NULL;
		freeMemory(pPart->curr->size.iig_paths);	pPart->curr->size.iig_paths = NULL;
		freeMemory(pPart->curr->size.iig_steps);	pPart->curr->size.iig_steps = NULL;

		for (i = 0; i < igCount; i++)
		{
			freeInferenceGraph(&pPart->curr->partitionIG[i]);
		}

		freeMemory(pPart->curr->partitionIG);
		pPart->curr->partitionIG = NULL;
		pPart->curr->size.iig = 0;
	}
	return 1;
}
