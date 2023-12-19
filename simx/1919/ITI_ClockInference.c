/**
 * ITI_ClockInference.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_ClockInference.h"
#include <string.h>

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif





static ITI_int gcd(ITI_int a, ITI_int b) {
	ITI_int c;
	while (a != 0) {
		c = a;
		a = b%a;
		b = c;
	}
	return b;
}





static ITI_int lcm(ITI_int a, ITI_int b) {
	return (a / gcd(a, b)) * b;
}





static void reduceFraction(ITI_int* nominator, ITI_int* denominator) {
	const ITI_int greatesCommonDivisor = gcd(*nominator, *denominator);
	*nominator	 /= greatesCommonDivisor;
	*denominator /= greatesCommonDivisor;
}

#pragma region Graph Construction
void initEdge(struct inferenceGraph* graph,
			  ITI_int nodeFrom,
			  ITI_int nodeTo,
			  ITI_int edgeIndex,
			  ITI_int neighborFrom,
			  ITI_int neighborTo,
			  enum edgeType edgeType,
			  ITI_int factor,
			  ITI_int shift,
			  ITI_bool isAlias,
			  ITI_int aliasFrom,
			  ITI_bool hasPath,
			  ITI_char* constructor,
			  ITI_AllocateMemory allocateMemory)
{
	struct graphEdge* currentEdge = &graph->m_Edges[edgeIndex];
	char *tmpstr = (ITI_char*)allocateMemory((strlen(constructor) + 1), sizeof(ITI_char));

	currentEdge->m_NodeFrom		= nodeFrom;
	currentEdge->m_NodeTo		= nodeTo;
	currentEdge->m_Alias		= -1;
	currentEdge->m_Factor		= factor;				
	currentEdge->m_Shift		= shift;				
	currentEdge->m_EdgeType		= edgeType;
	currentEdge->m_HasPath		= hasPath;
	strcat(tmpstr, constructor);
	currentEdge->m_Constructor = tmpstr;

	if (isAlias) {
		graph->m_Edges[aliasFrom].m_Alias = edgeIndex;
		
		if (aliasFrom == edgeIndex) {
			graph->m_Children[graph->m_Nodes[nodeFrom].m_FirstChild + neighborFrom] = nodeTo;
			graph->m_ChildEdges[graph->m_Nodes[nodeFrom].m_FirstChild + neighborFrom] = edgeIndex;
		}
	}
	else {
		
		graph->m_Children[graph->m_Nodes[nodeFrom].m_FirstChild + neighborFrom] = nodeTo;
		graph->m_ChildEdges[graph->m_Nodes[nodeFrom].m_FirstChild + neighborFrom] = edgeIndex;

		
		graph->m_Children[graph->m_Nodes[nodeTo].m_FirstChild + neighborTo] = nodeFrom;
		graph->m_ChildEdges[graph->m_Nodes[nodeTo].m_FirstChild + neighborTo] = edgeIndex;
	}
}

void initNode(struct inferenceGraph* graph,
			ITI_int nodeIndex,
			ITI_int firstChild,
			ITI_int numberOfChildren,
			ITI_real interval,
			ITI_int resolution,
			ITI_bool isBaseClock,
			ITI_char* constructor,
			ITI_AllocateMemory allocateMemory)
{
	struct graphNode* currentNode	= &graph->m_Nodes[nodeIndex];
	char* tmpstr = (ITI_char*)allocateMemory((strlen(constructor) + 1), sizeof(ITI_char));
	currentNode->m_Index			= nodeIndex;
	currentNode->m_FirstChild		= firstChild;
	currentNode->m_NumberOfChildren	= numberOfChildren;
	currentNode->m_Interval			= interval;				
	currentNode->m_Resolution		= resolution;			
	currentNode->m_Nominator		= 0;
	currentNode->m_Denominator		= 0;
	currentNode->m_ShiftTicks		= 0;
	currentNode->m_Ticks			= 0;
	currentNode->m_MaxTicks			= 0;
	currentNode->m_Visited			= -1;
	currentNode->m_IsBaseClock		= isBaseClock;
	strcat(tmpstr, constructor);
	currentNode->m_Constructor = tmpstr;
}

void initPath(struct inferenceGraph* graph,
	ITI_int pathIndex,
	ITI_int firstStep,
	ITI_int numSteps,
	ITI_int firstNode,
	ITI_int lastNode,
	ITI_char isCycle)
{
	struct graphPath* currentPath = &graph->m_Paths[pathIndex];
	currentPath->m_FirstStep = firstStep;
	currentPath->m_NumSteps = numSteps;
	currentPath->m_FirstNode = firstNode;
	currentPath->m_LastNode = lastNode;
	currentPath->m_FirstDenominator = -1;
	currentPath->m_FirstNominator = -1;
	currentPath->m_LastDenominator = -1;
	currentPath->m_LastNominator = -1;
	currentPath->m_UnknownFactors = 0;
	currentPath->m_IsCycle = isCycle;
	currentPath->m_ConsistenceChecked = ITI_false;
}

void initStep(struct inferenceGraph* graph,
	ITI_int stepIndex,
	ITI_int stepInPath,
	ITI_int nodeFrom,
	ITI_int nodeTo,
	ITI_int pathIndex,
	ITI_int otherStep,
	ITI_int edgeIndex,
	ITI_char actsOnNominator)
{
	struct graphStep* currentStep = &graph->m_Steps[stepIndex];
	currentStep->m_Index = stepIndex;
	currentStep->m_PathIndex = stepInPath;
	currentStep->m_NodeFrom = nodeFrom;
	currentStep->m_NodeTo = nodeTo;
	currentStep->m_Path = pathIndex;
	currentStep->m_OtherStep = otherStep;
	currentStep->m_Edge = edgeIndex;
	currentStep->m_DenominatorBefore = -1;
	currentStep->m_DenominatorAfter  = -1;
	currentStep->m_NominatorBefore	 = -1;
	currentStep->m_NominatorAfter	 = -1;
	currentStep->m_FactorKnown		 = ITI_false;
	currentStep->m_ActsOnNominator = actsOnNominator;
}

void updateNodeInterval(struct inferenceGraph* graph, const ITI_int nodeIndex, ITI_real interval) {
	assert(nodeIndex < graph->m_NumClocks);
	graph->m_Nodes[nodeIndex].m_Interval = interval;
	graph->m_Nodes[nodeIndex].m_Nominator = 0;
}

void updateIGNode(struct inferenceGraph* graph, const ITI_int nodeIndex, ITI_real interval, ITI_int resolution, ITI_int ticks, ITI_int maxTicks) {
	assert(nodeIndex < graph->m_NumClocks);
	graph->m_Nodes[nodeIndex].m_Interval = interval;
	graph->m_Nodes[nodeIndex].m_Resolution = resolution;
	graph->m_Nodes[nodeIndex].m_Ticks = ticks;
	graph->m_Nodes[nodeIndex].m_MaxTicks = maxTicks;
}

void updateIGEdge(struct inferenceGraph* graph, const ITI_int edgeIndex, ITI_int factor, ITI_int shift) {
	assert(edgeIndex < graph->m_NumEdges);
	graph->m_Edges[edgeIndex].m_Factor = factor;
	graph->m_Edges[edgeIndex].m_Shift = shift;
}

void loadResult_BaseInterval(struct inferenceGraph* graph, ITI_real* bpinterval) {
	*bpinterval = graph->m_BaseInterval;
}

void loadResult_ClockInference(struct inferenceGraph* graph, const ITI_int nodeIndex, ITI_real* interval, ITI_int* maxTicks, ITI_int* ticks, ITI_int* activated) {
	*interval = graph->m_Nodes[nodeIndex].m_MaxTicks * graph->m_BaseInterval;
	*maxTicks = graph->m_Nodes[nodeIndex].m_MaxTicks;
	*ticks = graph->m_Nodes[nodeIndex].m_Ticks;
	*activated = (graph->m_Nodes[nodeIndex].m_MaxTicks == graph->m_Nodes[nodeIndex].m_Ticks);
}

void addPath(struct inferenceGraph* graph, const ITI_int pathIndex, struct graphPath* newPath) {
	assert(pathIndex < graph->m_NumPaths);
	memcpy(&graph->m_Paths[pathIndex], newPath, sizeof(struct graphPath));
}

void addStep(struct inferenceGraph* graph, const ITI_int stepIndex, struct graphStep* newStep) {
	assert(stepIndex < graph->m_NumSteps);
	memcpy(&graph->m_Steps[stepIndex], newStep, sizeof(struct graphStep));
}

void allocInferenceGraph(struct inferenceGraph* graph, const struct graphStatistics* stat) {
	graph->m_NumClocks = stat->m_NumNodes;
	graph->m_NumBaseClocks = stat->m_NumBaseClocks;
	graph->m_NumRoots = stat->m_NumRootClocks;
	graph->m_NumEdges = stat->m_NumEdges;
	graph->m_NumPaths = stat->m_NumPathes;
	graph->m_NumSteps = stat->m_NumSteps;

	
	graph->m_Error = (ITI_char*)malloc((MAX_ERROR_LENGTH + 1) * sizeof(ITI_char));

	
	if ((graph->m_Nodes = (struct graphNode*)malloc(graph->m_NumClocks * sizeof(struct graphNode))) == NULL) {
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for nodes failed.\n");
		graph->m_Status = errorNoMemory;
	}

	if ((graph->m_Edges = (struct graphEdge*)malloc(graph->m_NumEdges * sizeof(struct graphEdge))) == NULL) {
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for edges failed.\n");
		graph->m_Status = errorNoMemory;
	}

	if ((graph->m_Children = (ITI_int*)malloc(stat->m_NumChildren * sizeof(ITI_int))) == NULL) {
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for child nodes failed.\n");
		graph->m_Status = errorNoMemory;
	}
	if ((graph->m_ChildEdges = (ITI_int*)malloc(stat->m_NumChildren * sizeof(ITI_int))) == NULL) {
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for child edges failed.\n");
		graph->m_Status = errorNoMemory;
	}

	if ((graph->m_BaseClocks = (ITI_int*)malloc(graph->m_NumBaseClocks * sizeof(ITI_int))) == NULL) {
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for base clocks failed.\n");
		graph->m_Status = errorNoMemory;
	}
	memcpy(graph->m_BaseClocks, stat->m_BaseClocks, graph->m_NumBaseClocks * sizeof(ITI_int));

	if ((graph->m_Roots = (ITI_int*)malloc((graph->m_NumRoots + 1) * sizeof(ITI_int))) == NULL) {	
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for root clocks failed.\n");
		graph->m_Status = errorNoMemory;
	}
	memcpy(graph->m_Roots, stat->m_RootClocks, (graph->m_NumRoots + 1) * sizeof(ITI_int));

	if ((graph->m_Paths = (struct graphPath*)malloc(graph->m_NumPaths * sizeof(struct graphPath))) == NULL) {
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for cycles failed.\n");
		graph->m_Status = errorNoMemory;
	}

	if ((graph->m_Steps = (struct graphStep*)malloc(graph->m_NumSteps * sizeof(struct graphStep))) == NULL) {
		strcpy(graph->m_Error, "ERROR [ClockInference]: memory allocation for steps failed.\n");
		graph->m_Status = errorNoMemory;
	}
}

void freeInferenceGraph(struct inferenceGraph* graph) {
	ITI_int index;

	for (index = 0; index < graph->m_NumClocks; ++index) {
		free((ITI_char*)graph->m_Nodes[index].m_Constructor);
	}
	free(graph->m_Nodes);
	for (index = 0; index < graph->m_NumEdges; ++index) {
		free((ITI_char*)graph->m_Edges[index].m_Constructor);
	}
	free(graph->m_Edges);
	free(graph->m_BaseClocks);
	free(graph->m_Roots);
	free(graph->m_Paths);
	free(graph->m_Children);
	free(graph->m_ChildEdges);
	free(graph->m_Steps);
	free(graph->m_Error);
}

void initInferenceGraph(struct inferenceGraph* graph, ITI_int clockType, ITI_real baseInterval) {
	graph->m_BaseDenominator = 1;
	graph->m_BaseNominator = -1;
	graph->m_CurrentVisit = 0;
	graph->m_ClockType = (enum ClockType) clockType;
	graph->m_Status = noError;
	graph->m_BaseInterval = baseInterval;
}
#pragma endregion

#pragma region Select base clock





static void selectBaseClockIdx(struct inferenceGraph* graph, const ITI_int rootIndex) {
	ITI_int index;
	ITI_int temp;
	ITI_int rootClock = -1;

	if (graph->m_Status > warningBaseClock) {
		return;
	}

	
	for (index = graph->m_Roots[rootIndex]; index < graph->m_Roots[rootIndex+1]; ++index) { 
		if (graph->m_ClockType == eventClock || graph->m_Nodes[graph->m_BaseClocks[index]].m_Interval != 0.0) {
			if (rootClock == -1) {
				rootClock = index;
			}
			graph->m_Nodes[graph->m_BaseClocks[index]].m_Nominator = (graph->m_ClockType == rationalClock) ? (ITI_int)graph->m_Nodes[graph->m_BaseClocks[index]].m_Interval : 1;
			graph->m_Nodes[graph->m_BaseClocks[index]].m_Denominator = (graph->m_ClockType == rationalClock) ? graph->m_Nodes[graph->m_BaseClocks[index]].m_Resolution : 1;
		}
	}

	
	if (rootClock == -1) {
		graph->m_Status = warningBaseClock;
		if (graph->m_NumBaseClocks == 0) {
			strcpy(graph->m_Error, "No base clock found! Using default clock with intervalCounter = 1.0.");
		}
		else {
			strcpy(graph->m_Error, "No base clock with intervalCounter != 0 found! Using default clock with intervalCounter = 1.0.");
			if (graph->m_ClockType != eventClock) {
				graph->m_Nodes[graph->m_Roots[rootIndex]].m_Interval = 1.0;
			}
		}
		graph->m_Nodes[graph->m_Roots[rootIndex]].m_Nominator = 1;
		graph->m_Nodes[graph->m_Roots[rootIndex]].m_Denominator = 1;
	}
	else {
		temp = graph->m_BaseClocks[graph->m_Roots[rootIndex]];
		graph->m_BaseClocks[graph->m_Roots[rootIndex]] = graph->m_BaseClocks[rootClock];
		graph->m_BaseClocks[rootClock] = temp;
	}
}






static void selectBaseClock(struct inferenceGraph* graph) {
	ITI_int rootIndex;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		selectBaseClockIdx(graph, rootIndex);
	}
}
#pragma endregion

#pragma region Factor Inference

#pragma region Equivalent Edges














static ITI_bool actsOnNominator(struct inferenceGraph* graph, const ITI_int nodeTo, const ITI_int edge) {
	return ((graph->m_Edges[edge].m_EdgeType == subSample) == (graph->m_Edges[edge].m_NodeTo == nodeTo));
}








static ITI_int getFactor(struct inferenceGraph* graph, const ITI_int edge) {
	if (graph->m_Edges[edge].m_EdgeType == subSample || graph->m_Edges[edge].m_EdgeType == superSample) {
		return graph->m_Edges[edge].m_Factor;
	}
	else { 
		return 1;
	}
}








static void setFactor(struct inferenceGraph* graph, const ITI_int edge, const ITI_int newFactor) {
	if (graph->m_Edges[edge].m_EdgeType == subSample || graph->m_Edges[edge].m_EdgeType == superSample) {
		graph->m_Edges[edge].m_Factor = newFactor;
	}
	else {
		assert(0);
	}
}






static ITI_int getShift(struct inferenceGraph* graph, const ITI_int edge) {
	if (graph->m_Edges[edge].m_EdgeType == backSample || graph->m_Edges[edge].m_EdgeType == shiftSample) {
		return graph->m_Edges[edge].m_Shift;
	}
	else { 
		assert(0);
		return 0;
	}
}







static ITI_int getResolution(struct inferenceGraph* graph, const ITI_int edge) {
	if (graph->m_Edges[edge].m_EdgeType == backSample || graph->m_Edges[edge].m_EdgeType == shiftSample) {
		return graph->m_Edges[edge].m_Factor;
	}
	else { 
		assert(0);
		return 1;
	}
}








static void getEquivalentEdgeFactors(struct inferenceGraph* graph, const ITI_int nodeTo, const ITI_int edge, ITI_int* factorNominator, ITI_int* factorDenominator) {
	if (*factorNominator <= 0 && actsOnNominator(graph, nodeTo, edge)) {
		*factorNominator = getFactor(graph, edge);
	}
	else if (*factorDenominator <= 0 && !actsOnNominator(graph, nodeTo, edge)) {
		*factorDenominator = getFactor(graph, edge);
	}
	if (graph->m_Edges[edge].m_Alias != -1) {
		getEquivalentEdgeFactors(graph, nodeTo, graph->m_Edges[edge].m_Alias, factorNominator, factorDenominator);
	}
}








static void setEquivalentEdgeFactors(struct inferenceGraph* graph, const ITI_int nodeTo, const ITI_int edge, const ITI_int factorNominator, const ITI_int factorDenominator) {
	if (getFactor(graph, edge) == 0) {
		setFactor(graph, edge, actsOnNominator(graph, nodeTo, edge) ? factorNominator : factorDenominator);
	}
	else {
		if (getFactor(graph, edge) != (actsOnNominator(graph, nodeTo, edge) ? factorNominator : factorDenominator)) {
			ITI_char firstFactor[10];
			ITI_char secondFactor[10];
			sprintf(firstFactor,  "%d", getFactor(graph, edge));
			sprintf(secondFactor, "%d", actsOnNominator(graph, nodeTo, edge) ? factorNominator : factorDenominator);
			graph->m_Status = errorMissmatchFactors;
			strcpy(graph->m_Error, "Conflicting Sub-clock conversion operators found:\n The operator ");
			strncat(graph->m_Error, graph->m_Edges[edge].m_Constructor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, " has a factor of ", ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, firstFactor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, ". Expected was ", ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, secondFactor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, "!", ERROR_LENGTH_LEFT);
		}
	}
	if (graph->m_Edges[edge].m_Alias != -1) {
		setEquivalentEdgeFactors(graph, nodeTo, graph->m_Edges[edge].m_Alias, factorNominator, factorDenominator);
	}
}









void setEquivalentEdges(struct inferenceGraph* graph, const ITI_int nodeTo, const ITI_int edge) {
	ITI_int factorNominator = -1;
	ITI_int factorDenominator = -1;

	
	getEquivalentEdgeFactors(graph, nodeTo, edge, &factorNominator, &factorDenominator);

	
	
	
	if (factorNominator == 0 && factorDenominator >= 0) {
		factorNominator = 1;
	}
	if (factorDenominator == 0 && factorNominator >= 0) {
		factorDenominator = 1;
	}

	
	if ((factorNominator <= 0 && factorDenominator <= 0 && !graph->m_Edges[edge].m_HasPath) ||
		(factorNominator > 0 && factorDenominator > 0)) {
		factorNominator = 1;
		factorDenominator = 1;
	}

	
	if (factorNominator != -1 || factorDenominator != -1) {
		setEquivalentEdgeFactors(graph, nodeTo, edge, factorNominator, factorDenominator);
	}
}






static void infereEquivalentEdgesIdx(struct inferenceGraph* graph, const ITI_int node, const ITI_int edge) {
	ITI_int index;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit || graph->m_Status > warningBaseClock) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	
	if (edge != -1) {
		setEquivalentEdges(graph, node, edge);
	}

	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		infereEquivalentEdgesIdx(graph, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index], graph->m_ChildEdges[graph->m_Nodes[node].m_FirstChild + index]);
	}
}




static void infereEquivalentEdges(struct inferenceGraph* graph) {
	ITI_int rootIndex;
	if (graph->m_Status > warningBaseClock) {
		return;
	}
	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		infereEquivalentEdgesIdx(graph, graph->m_BaseClocks[graph->m_Roots[rootIndex]], -1);
	}
}
#pragma endregion

#pragma region Infere Cycles









static void checkConsistence(struct inferenceGraph* graph, const ITI_int pathIndex) {
	ITI_int index;
	ITI_int currentDenominator = graph->m_Paths[pathIndex].m_FirstDenominator;
	ITI_int currentNominator = graph->m_Paths[pathIndex].m_FirstNominator;
	if (graph->m_Paths[pathIndex].m_ConsistenceChecked) {
		return;
	}
	for (index = 0; index < graph->m_Paths[pathIndex].m_NumSteps; ++index) {
		if (graph->m_Steps[graph->m_Paths[pathIndex].m_FirstStep + index].m_ActsOnNominator) {
			currentNominator *= getFactor(graph, graph->m_Steps[graph->m_Paths[pathIndex].m_FirstStep + index].m_Edge);
		}
		else {
			currentDenominator *= getFactor(graph, graph->m_Steps[graph->m_Paths[pathIndex].m_FirstStep + index].m_Edge);
		}
		reduceFraction(&currentNominator, &currentDenominator);
	}
	if (currentNominator != graph->m_Paths[pathIndex].m_LastNominator || currentDenominator != graph->m_Paths[pathIndex].m_LastDenominator) {
		if (graph->m_Paths[pathIndex].m_IsCycle) {
			graph->m_Status = errorCycleInconsistent;
			strcpy(graph->m_Error, "There is an inconsistent cycle starting at: \n");
			strncat(graph->m_Error, graph->m_Nodes[graph->m_Paths[pathIndex].m_FirstNode].m_Constructor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, "\n", ERROR_LENGTH_LEFT);
		}
		else {
			graph->m_Status = errorMissmatchBaseClocks;
			strcpy(graph->m_Error, "The two base clocks:\n");
			strncat(graph->m_Error, graph->m_Nodes[graph->m_Paths[pathIndex].m_FirstNode].m_Constructor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, "\n", ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, graph->m_Nodes[graph->m_Paths[pathIndex].m_LastNode].m_Constructor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, "\nare inconsistent!\n", ERROR_LENGTH_LEFT);

		}			
		strncat(graph->m_Error, "The connecting Sub-clock conversion operators are:\n", ERROR_LENGTH_LEFT);
		for (index = 0; index < graph->m_Paths[pathIndex].m_NumSteps; ++index) {
			strncat(graph->m_Error, graph->m_Edges[graph->m_Steps[graph->m_Paths[pathIndex].m_FirstStep + index].m_Edge].m_Constructor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, "\n", ERROR_LENGTH_LEFT);
		}
	}
	graph->m_Paths[pathIndex].m_ConsistenceChecked = ITI_true;
}





static void updateBaseClock(struct inferenceGraph* graph, const ITI_int pathIndex) {
	ITI_int index;
	ITI_int stepIndex;
	ITI_int currentDenominator;
	ITI_int currentNominator;
	ITI_bool forward;
	if ((graph->m_Paths[pathIndex].m_FirstNominator		!= 0 &&			
		 graph->m_Paths[pathIndex].m_FirstDenominator	!= 0 &&
		 graph->m_Paths[pathIndex].m_LastNominator		!= 0 &&
		 graph->m_Paths[pathIndex].m_LastDenominator	!= 0) ||
		(graph->m_Paths[pathIndex].m_FirstNominator		== 0 &&			
	 	 graph->m_Paths[pathIndex].m_FirstDenominator	== 0 &&
		 graph->m_Paths[pathIndex].m_LastNominator		== 0 &&
		 graph->m_Paths[pathIndex].m_LastDenominator	== 0)) {
		return;
	}

	
	forward = graph->m_Paths[pathIndex].m_FirstNominator != 0;

	
	currentDenominator = forward ? graph->m_Paths[pathIndex].m_FirstDenominator : graph->m_Paths[pathIndex].m_LastDenominator;
	currentNominator   = forward ? graph->m_Paths[pathIndex].m_FirstNominator   : graph->m_Paths[pathIndex].m_LastNominator;

	for (index = 0; index < graph->m_Paths[pathIndex].m_NumSteps; ++index) {
		stepIndex = forward ? graph->m_Paths[pathIndex].m_FirstStep + index
								     : graph->m_Paths[pathIndex].m_FirstStep - index + graph->m_Paths[pathIndex].m_NumSteps - 1;
		if (graph->m_Steps[stepIndex].m_ActsOnNominator) {
			currentNominator *= getFactor(graph, graph->m_Steps[stepIndex].m_Edge);
		}
		else {
			currentDenominator *= getFactor(graph, graph->m_Steps[stepIndex].m_Edge);
		}
		reduceFraction(&currentNominator, &currentDenominator);
	}

	if (forward) {
		graph->m_Nodes[graph->m_Paths[pathIndex].m_LastNode].m_Nominator = currentNominator;
		graph->m_Nodes[graph->m_Paths[pathIndex].m_LastNode].m_Denominator = currentDenominator;
		graph->m_Paths[pathIndex].m_LastNominator = currentNominator;
		graph->m_Paths[pathIndex].m_LastDenominator = currentDenominator;
	}
	else {
		graph->m_Nodes[graph->m_Paths[pathIndex].m_FirstNode].m_Nominator = currentNominator;
		graph->m_Nodes[graph->m_Paths[pathIndex].m_FirstNode].m_Denominator = currentDenominator;
		graph->m_Paths[pathIndex].m_FirstNominator = currentNominator;
		graph->m_Paths[pathIndex].m_FirstDenominator = currentDenominator;
	}
}





static void checkPath(struct inferenceGraph* graph, const ITI_int pathIndex) {
	if (graph->m_Paths[pathIndex].m_UnknownFactors == 0) {
		if (!graph->m_Paths[pathIndex].m_IsCycle) {
			updateBaseClock(graph, pathIndex);
		}
		checkConsistence(graph, pathIndex);
	}
}









static ITI_bool updateStep(struct inferenceGraph* graph, const ITI_int stepIndex, ITI_int* currentDenominator, ITI_int* currentNominator, ITI_bool isForward) {
	if (isForward) {
		graph->m_Steps[stepIndex].m_DenominatorBefore = *currentDenominator;
		graph->m_Steps[stepIndex].m_NominatorBefore = *currentNominator;
	}
	else {
		graph->m_Steps[stepIndex].m_DenominatorAfter = *currentDenominator;
		graph->m_Steps[stepIndex].m_NominatorAfter = *currentNominator;
	}
	if (graph->m_Steps[stepIndex].m_ActsOnNominator == isForward) {
		*currentNominator *= getFactor(graph, graph->m_Steps[stepIndex].m_Edge);
	}
	else {
		*currentDenominator *= getFactor(graph, graph->m_Steps[stepIndex].m_Edge);
	}

	if (*currentNominator != 0 && *currentDenominator != 0) {
		reduceFraction(currentNominator, currentDenominator);
	}

	graph->m_Steps[stepIndex].m_FactorKnown = (getFactor(graph, graph->m_Steps[stepIndex].m_Edge) != 0);
	return graph->m_Steps[stepIndex].m_FactorKnown;
}





static void initializePath(struct inferenceGraph* graph, const ITI_int pathIndex) {
	ITI_int denominatorBackward;
	ITI_int denominatorForward;
	ITI_int nominatorBackward;
	ITI_int nominatorForward;

	ITI_int forwardIndex;
	ITI_int backwardIndex = graph->m_Paths[pathIndex].m_NumSteps - 1;

	
	if (graph->m_Paths[pathIndex].m_IsCycle) {
		graph->m_Paths[pathIndex].m_FirstNominator = 1;
		graph->m_Paths[pathIndex].m_FirstDenominator = 1;
		graph->m_Paths[pathIndex].m_LastNominator = 1;
		graph->m_Paths[pathIndex].m_LastDenominator = 1;
	}
	else {
		graph->m_Paths[pathIndex].m_FirstNominator = (ITI_int)graph->m_Nodes[graph->m_Paths[pathIndex].m_FirstNode].m_Interval;
		graph->m_Paths[pathIndex].m_FirstDenominator = graph->m_Nodes[graph->m_Paths[pathIndex].m_FirstNode].m_Resolution;
		graph->m_Paths[pathIndex].m_LastNominator = (ITI_int)graph->m_Nodes[graph->m_Paths[pathIndex].m_LastNode].m_Interval;
		graph->m_Paths[pathIndex].m_LastDenominator = graph->m_Nodes[graph->m_Paths[pathIndex].m_LastNode].m_Resolution;
	}
	reduceFraction(&graph->m_Paths[pathIndex].m_FirstNominator, &graph->m_Paths[pathIndex].m_FirstDenominator);
	reduceFraction(&graph->m_Paths[pathIndex].m_LastNominator, &graph->m_Paths[pathIndex].m_LastDenominator);

	denominatorBackward	= graph->m_Paths[pathIndex].m_LastDenominator;
	denominatorForward	= graph->m_Paths[pathIndex].m_FirstDenominator;
	nominatorBackward	= graph->m_Paths[pathIndex].m_LastNominator;
	nominatorForward	= graph->m_Paths[pathIndex].m_FirstNominator;
	for (forwardIndex = 0; forwardIndex < graph->m_Paths[pathIndex].m_NumSteps; ++forwardIndex, --backwardIndex) {
		if (!updateStep(graph, graph->m_Paths[pathIndex].m_FirstStep + backwardIndex, &denominatorBackward, &nominatorBackward, ITI_false)) {
			++graph->m_Paths[pathIndex].m_UnknownFactors;
		}
		updateStep(graph, graph->m_Paths[pathIndex].m_FirstStep + forwardIndex, &denominatorForward, &nominatorForward, ITI_true);
	}
}






static void propagateFactor(struct inferenceGraph* graph, const ITI_int pathIndex, const ITI_int stepIndex) {
	ITI_int subIndex;
	ITI_int denominatorBackward = graph->m_Steps[stepIndex].m_DenominatorAfter;
	ITI_int denominatorForward  = graph->m_Steps[stepIndex].m_DenominatorBefore;
	ITI_int nominatorBackward   = graph->m_Steps[stepIndex].m_NominatorAfter;
	ITI_int nominatorForward    = graph->m_Steps[stepIndex].m_NominatorBefore;

	--graph->m_Paths[pathIndex].m_UnknownFactors;
	for (subIndex = graph->m_Steps[stepIndex].m_PathIndex; subIndex < graph->m_Paths[pathIndex].m_NumSteps; ++subIndex) {
		updateStep(graph, graph->m_Paths[pathIndex].m_FirstStep + subIndex, &denominatorForward, &nominatorForward, ITI_true);
	}
	for (subIndex = graph->m_Steps[stepIndex].m_PathIndex + 1; subIndex > 0; --subIndex) {
		updateStep(graph, graph->m_Paths[pathIndex].m_FirstStep + subIndex - 1, &denominatorBackward, &nominatorBackward, ITI_false);
	}
}






static void setEdgeFactor(struct inferenceGraph* graph, const ITI_int edge, const ITI_int newFactor) {
	ITI_int alias;

	setFactor(graph, edge, newFactor);
	alias = graph->m_Edges[edge].m_Alias;
	while (alias != -1) {
		setFactor(graph, alias, newFactor);
		alias = graph->m_Edges[alias].m_Alias;
	}
}






static ITI_bool setFactorInPath(struct inferenceGraph* graph, const ITI_int stepIndex) {
	ITI_int leastCommonMultiple;
	ITI_int newFactor;
	ITI_int newNominatorAfter;
	ITI_int newNominatorBefore;
	ITI_bool wrongDirection;
	ITI_bool notDivisible;

	if (graph->m_Steps[stepIndex].m_FactorKnown ||
		graph->m_Steps[stepIndex].m_NominatorAfter == 0 ||
		graph->m_Steps[stepIndex].m_NominatorBefore == 0 ||
		graph->m_Steps[stepIndex].m_DenominatorAfter == 0 ||
		graph->m_Steps[stepIndex].m_DenominatorBefore == 0) {
		return ITI_false;
	}

	
	leastCommonMultiple = lcm(graph->m_Steps[stepIndex].m_DenominatorAfter, graph->m_Steps[stepIndex].m_DenominatorBefore);
	newNominatorAfter  = graph->m_Steps[stepIndex].m_NominatorAfter  * leastCommonMultiple / graph->m_Steps[stepIndex].m_DenominatorAfter;
	newNominatorBefore = graph->m_Steps[stepIndex].m_NominatorBefore * leastCommonMultiple / graph->m_Steps[stepIndex].m_DenominatorBefore;

	if (graph->m_Steps[stepIndex].m_ActsOnNominator)
		wrongDirection = newNominatorBefore > newNominatorAfter;
	else
		wrongDirection = newNominatorBefore < newNominatorAfter;

	if (wrongDirection) {
		graph->m_Status = errorWrongDirection;
		strcpy(graph->m_Error, "Conflicting Sub-clock conversion operators found:\n The operator");
		strncat(graph->m_Error, graph->m_Edges[graph->m_Steps[stepIndex].m_Edge].m_Constructor, ERROR_LENGTH_LEFT);
		strncat(graph->m_Error, " seems inverted. Try to replace the Sub-clock conversion operator with ", ERROR_LENGTH_LEFT);
		strncat(graph->m_Error, graph->m_Edges[graph->m_Steps[stepIndex].m_Edge].m_EdgeType == subSample ? "superSample!" : "subSample!", ERROR_LENGTH_LEFT);
		return ITI_false;
	}

	if (graph->m_Steps[stepIndex].m_ActsOnNominator)
		notDivisible = (newNominatorAfter  % newNominatorBefore) != 0;
	else
		notDivisible = (newNominatorBefore % newNominatorAfter) != 0;

	if (notDivisible) {
		ITI_char firstFactor[10];
		ITI_char secondFactor[10];
		sprintf(firstFactor,  "%d", graph->m_Steps[stepIndex].m_ActsOnNominator ? newNominatorAfter : newNominatorBefore);
		sprintf(secondFactor, "%d", graph->m_Steps[stepIndex].m_ActsOnNominator ? newNominatorBefore : newNominatorAfter);
		graph->m_Status = errorNotDivisible;
		strcpy(graph->m_Error, "Conflicting Sub-clock conversion operators found:\n The operator");
		strncat(graph->m_Error, graph->m_Edges[graph->m_Steps[stepIndex].m_Edge].m_Constructor, ERROR_LENGTH_LEFT);
		strncat(graph->m_Error, " requires a noninteger factor of ", ERROR_LENGTH_LEFT);
		strncat(graph->m_Error, firstFactor, ERROR_LENGTH_LEFT);
		strncat(graph->m_Error, "/", ERROR_LENGTH_LEFT);
		strncat(graph->m_Error, secondFactor, ERROR_LENGTH_LEFT);
		return ITI_false;
	}

	
	if (graph->m_Steps[stepIndex].m_ActsOnNominator)
		newFactor = newNominatorAfter / newNominatorBefore;
	else
		newFactor = newNominatorBefore / newNominatorAfter;

	setEdgeFactor(graph, graph->m_Steps[stepIndex].m_Edge, newFactor);
	graph->m_Steps[stepIndex].m_FactorKnown = ITI_true;
	return ITI_true;
}






static void updateFactors(struct inferenceGraph* graph, const ITI_int pathIndex, ITI_bool* pathUpdated) {
	ITI_int index;
	ITI_int otherStep;

	
	if (graph->m_Paths[pathIndex].m_UnknownFactors != 1) {
		return;
	}

	
	for (index = 0; index < graph->m_Paths[pathIndex].m_NumSteps; ++index) {
		if (setFactorInPath(graph, graph->m_Paths[pathIndex].m_FirstStep + index)) {
			propagateFactor(graph, pathIndex, graph->m_Paths[pathIndex].m_FirstStep + index);

			
			otherStep = graph->m_Steps[graph->m_Paths[pathIndex].m_FirstStep + index].m_OtherStep;
			while (otherStep != graph->m_Paths[pathIndex].m_FirstStep + index) {
				propagateFactor(graph, graph->m_Steps[otherStep].m_Path, otherStep);
				otherStep = graph->m_Steps[otherStep].m_OtherStep;
			}
			*pathUpdated = ITI_true;
		}
	}
}




static void infereFactors(struct inferenceGraph* graph) {
	ITI_int pathIndex;
	ITI_bool pathUpdated = ITI_true;

	if (graph->m_Status > warningBaseClock) {
		return;
	}

	
	for (pathIndex = 0; pathIndex < graph->m_NumPaths; ++pathIndex) {
		initializePath(graph, pathIndex);
		checkPath(graph, pathIndex);
		if (graph->m_Status > warningBaseClock) {
			return;
		}
	}

	
	
	while (pathUpdated) {
		pathUpdated = ITI_false;
		for (pathIndex = 0; pathIndex < graph->m_NumPaths; ++pathIndex) {
			updateFactors(graph, pathIndex, &pathUpdated);
			
			if (graph->m_Status > warningBaseClock) {
				return;
			}
		}
	}

	for (pathIndex = 0; pathIndex < graph->m_NumPaths; ++pathIndex) {
		if (graph->m_Paths[pathIndex].m_UnknownFactors != 0) {
			graph->m_Status = errorUnknownFactor;
			strcpy(graph->m_Error, "Unknown factor. Clock inference was unable to infer all factors, as the system is underdetermined!\n");
			return;
		}
	}
}
#pragma endregion

#pragma endregion

#pragma region Set Nominator/Denominator








static ITI_int getDenominatorFromEdge(struct inferenceGraph* graph, const ITI_int node, const ITI_int edge) {
	if (graph->m_Edges[edge].m_EdgeType == backSample || graph->m_Edges[edge].m_EdgeType == shiftSample) {
		if (getShift(graph, edge) % getResolution(graph, edge) != 0) {
			return graph->m_Nodes[node].m_Denominator * getResolution(graph, edge);
		}
	}
	return graph->m_Nodes[node].m_Denominator;
}









static ITI_int getNominatorFromEdge(struct inferenceGraph* graph, const ITI_int node, const ITI_int edge) {
	ITI_int shift;
	ITI_int resolution;

	if (graph->m_Edges[edge].m_EdgeType == backSample || graph->m_Edges[edge].m_EdgeType == shiftSample) {
		if (getShift(graph, edge) % getResolution(graph, edge) != 0) {
			shift = getShift(graph, edge);
			resolution = getResolution(graph, edge);
			reduceFraction(&shift, &resolution);
			return shift % resolution;
		}
	}
	return graph->m_Nodes[node].m_Nominator;
}






static void getBaseDenominator(struct inferenceGraph* graph, const ITI_int node, const ITI_int edge) {
	ITI_int index;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	
	if (edge == -1) {
		graph->m_BaseDenominator = lcm(graph->m_BaseDenominator, graph->m_Nodes[node].m_Denominator);
	}
	else {
		if (graph->m_Edges[edge].m_EdgeType == backSample || graph->m_Edges[edge].m_EdgeType == shiftSample) {
			reduceFraction(&graph->m_Edges[edge].m_Shift, &graph->m_Edges[edge].m_Factor);
		}
		graph->m_BaseDenominator = lcm(graph->m_BaseDenominator, getDenominatorFromEdge(graph, node, edge));
	}
	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		getBaseDenominator(graph, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index], graph->m_ChildEdges[graph->m_Nodes[node].m_FirstChild + index]);
	}
}






static void getBaseNominator(struct inferenceGraph* graph, const ITI_int node, const ITI_int edge) {
	ITI_int index;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	if (edge == -1) {
		if (graph->m_BaseNominator == -1) {	
			graph->m_BaseNominator = graph->m_Nodes[node].m_Nominator;
		}
		else {
			graph->m_BaseNominator = gcd(graph->m_BaseNominator, graph->m_Nodes[node].m_Nominator);
		}
	}
	else {
		graph->m_BaseNominator = gcd(graph->m_BaseNominator, getNominatorFromEdge(graph, node, edge));
	}
	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		getBaseNominator(graph, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index], graph->m_ChildEdges[graph->m_Nodes[node].m_FirstChild + index]);
	}
}







static void setNominatorDenominator2(struct inferenceGraph* graph, const ITI_int parent, const ITI_int node, const ITI_int edge) {
	ITI_int index;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	
	if (edge != -1 && parent != -1 && !graph->m_Nodes[node].m_IsBaseClock) {
		graph->m_Nodes[node].m_Nominator   = graph->m_Nodes[parent].m_Nominator   * (actsOnNominator(graph, node, edge) ? getFactor(graph, edge) : 1);
		graph->m_Nodes[node].m_Denominator = graph->m_Nodes[parent].m_Denominator * (actsOnNominator(graph, node, edge) ? 1 : getFactor(graph, edge));
		reduceFraction(&graph->m_Nodes[node].m_Nominator, &graph->m_Nodes[node].m_Denominator);
	}

	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		setNominatorDenominator2(graph, node, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index], graph->m_ChildEdges[graph->m_Nodes[node].m_FirstChild + index]);
	}
}






static void propagateBaseDenominator(struct inferenceGraph* graph, const ITI_int node, const ITI_int edge) {
	ITI_int index;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	
	graph->m_Nodes[node].m_Nominator  *= graph->m_BaseDenominator / graph->m_Nodes[node].m_Denominator;
	if (edge != -1 && (graph->m_Edges[edge].m_EdgeType == backSample || graph->m_Edges[edge].m_EdgeType == shiftSample)) {
		graph->m_Edges[edge].m_Shift  *= graph->m_BaseDenominator / graph->m_Nodes[node].m_Denominator;
		graph->m_Edges[edge].m_Factor *= graph->m_BaseDenominator / graph->m_Nodes[node].m_Denominator;
	}
	graph->m_Nodes[node].m_Denominator = graph->m_BaseDenominator;

	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		propagateBaseDenominator(graph, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index], graph->m_ChildEdges[graph->m_Nodes[node].m_FirstChild + index]);
	}
}




static void setNominatorDenominator(struct inferenceGraph* graph) {
	ITI_int rootIndex;
	if (graph->m_Status > warningBaseClock) {
		return;
	}

	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		setNominatorDenominator2(graph, -1, graph->m_BaseClocks[graph->m_Roots[rootIndex]], -1);
	}

	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		getBaseDenominator(graph, graph->m_BaseClocks[graph->m_Roots[rootIndex]], -1);
	}

	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		propagateBaseDenominator(graph, graph->m_BaseClocks[graph->m_Roots[rootIndex]], -1);
	}

	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		getBaseNominator(graph, graph->m_BaseClocks[graph->m_Roots[rootIndex]], -1);
	}

	
	if (graph->m_ClockType == rationalClock) {
		graph->m_BaseInterval = (double)graph->m_BaseNominator / graph->m_BaseDenominator;
	}
	else if (graph->m_ClockType == realClock) {
		graph->m_BaseInterval = (double)graph->m_BaseNominator / graph->m_BaseDenominator * (graph->m_Nodes[graph->m_BaseClocks[0]].m_Interval);
	}
}

#pragma endregion

#pragma region Set MaxTicks





static void setMaxTicksOnNode(struct inferenceGraph* graph, const ITI_int node) {
	ITI_int index;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	
	graph->m_Nodes[node].m_MaxTicks = graph->m_Nodes[node].m_Nominator / graph->m_BaseNominator;

	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		setMaxTicksOnNode(graph, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index]);
	}
}




static void setMaxTicks(struct inferenceGraph* graph) {
	ITI_int rootIndex;
	if (graph->m_Status > warningBaseClock) {
		return;
	}
	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		setMaxTicksOnNode(graph, graph->m_BaseClocks[graph->m_Roots[rootIndex]]);
	}
}

#pragma endregion

#pragma region Set shiftTicks







static void setShiftTicksOnNode(struct inferenceGraph* graph, const ITI_int parent, const ITI_int node, const ITI_int edge) {
	ITI_int index;
	ITI_bool isPositive;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit || graph->m_Status > warningBaseClock) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	
	if (edge != -1 && parent != -1) {
		if (graph->m_Edges[edge].m_EdgeType == backSample || graph->m_Edges[edge].m_EdgeType == shiftSample) {
			if (graph->m_Edges[edge].m_EdgeType == shiftSample)
				isPositive = graph->m_Edges[edge].m_NodeFrom == parent;
			else
				isPositive = graph->m_Edges[edge].m_NodeFrom == node;
			graph->m_Nodes[node].m_ShiftTicks = isPositive ? graph->m_Nodes[parent].m_ShiftTicks + (graph->m_Nodes[node].m_MaxTicks) * getShift(graph, edge) / getResolution(graph, edge)
														   : graph->m_Nodes[parent].m_ShiftTicks - (graph->m_Nodes[node].m_MaxTicks) * getShift(graph, edge) / getResolution(graph, edge);
		}
		else {
			graph->m_Nodes[node].m_ShiftTicks = graph->m_Nodes[parent].m_ShiftTicks;
		}
		if (graph->m_Nodes[node].m_ShiftTicks < 0) {
			graph->m_Status = errorNegativeShift;
			strcpy(graph->m_Error, "Invalid backShift operator:\n The operator");
			strncat(graph->m_Error, graph->m_Edges[edge].m_Constructor, ERROR_LENGTH_LEFT);
			strncat(graph->m_Error, " would create a Sub-clock partition that ticks before the first tick of the base partition.", ERROR_LENGTH_LEFT);
		}
	}

	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		setShiftTicksOnNode(graph, node, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index], graph->m_ChildEdges[graph->m_Nodes[node].m_FirstChild + index]);
	}
}




static void setShiftTicks(struct inferenceGraph* graph) {
	ITI_int rootIndex;
	if (graph->m_Status > warningBaseClock) {
		return;
	}
	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		setShiftTicksOnNode(graph, -1, graph->m_BaseClocks[graph->m_Roots[rootIndex]], -1);
	}
}
#pragma endregion

#pragma region Set ticks





static void setTicksOnNode(struct inferenceGraph* graph, const ITI_int node) {
	ITI_int index;
	
	if (node == -1 || graph->m_Nodes[node].m_Visited == graph->m_CurrentVisit) {
		return;
	}
	graph->m_Nodes[node].m_Visited = graph->m_CurrentVisit;

	
	graph->m_Nodes[node].m_Ticks = graph->m_Nodes[node].m_MaxTicks - graph->m_Nodes[node].m_ShiftTicks;

	
	for (index = 0; index < graph->m_Nodes[node].m_NumberOfChildren; ++index) {
		setTicksOnNode(graph, graph->m_Children[graph->m_Nodes[node].m_FirstChild + index]);
	}
}




static void setTicks(struct inferenceGraph* graph) {
	ITI_int rootIndex;
	if (graph->m_Status > warningBaseClock) {
		return;
	}
	++graph->m_CurrentVisit;
	for (rootIndex = 0; rootIndex < graph->m_NumRoots; ++rootIndex) {
		setTicksOnNode(graph, graph->m_BaseClocks[graph->m_Roots[rootIndex]]);
	}
}
#pragma endregion

#pragma region Inference

const ITI_char* getError(struct inferenceGraph* graph){
	return graph->m_Error;
}

ITI_ClockInferenceState performClockInference(struct inferenceGraph* graph) {
	
	initInferenceGraph(graph, graph->m_ClockType, graph->m_BaseInterval);

	
	selectBaseClock(graph);

	
	infereEquivalentEdges(graph);

	
	infereFactors(graph);

	
	setNominatorDenominator(graph);

	
	setMaxTicks(graph);

	
	setShiftTicks(graph);

	
	setTicks(graph);
	
	return graph->m_Status;
}

ITI_ClockInferenceState performIntervalUpdate(struct inferenceGraph* graph) {
	ITI_int pathIndex;
	
	graph->m_BaseDenominator = -1;
	graph->m_BaseNominator = -1;

	
	selectBaseClock(graph);

	
	for (pathIndex = 0; pathIndex < graph->m_NumPaths; ++pathIndex) {
		if (graph->m_Paths[pathIndex].m_IsCycle == ITI_false) {
			graph->m_Paths[pathIndex].m_ConsistenceChecked = ITI_false;
			initializePath(graph, pathIndex);
			checkPath(graph, pathIndex);
		}
	}

	
	setNominatorDenominator(graph);
	
	return graph->m_Status;
}
#pragma endregion
