/**
 * ITI_ClockInference.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef CLOCKINFERENCE_H
#define CLOCKINFERENCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ITI_Types.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ITI_real
#define ITI_real	double
#endif
#ifndef ITI_int
#define ITI_int		int
#endif
#ifndef ITI_char
#define ITI_char	char
#endif

#ifndef MAX_ERROR_LENGTH
#define MAX_ERROR_LENGTH 1000
#endif

#define ERROR_LENGTH_LEFT max(MAX_ERROR_LENGTH - (int)strlen(graph->m_Error) - 1, 0)

	struct graphEdge;
	struct graphPath;

	 
	enum ClockType {
		subClock,
		eventClock,
		rationalClock,
		realClock
	};

	 
	enum edgeType {
		subSample,
		superSample,
		shiftSample,
		backSample,
		solverMethod,
		noClock
	};

	



	struct graphStatistics {
		ITI_int m_NumNodes;
		ITI_int	m_NumBaseClocks;
		ITI_int	m_NumRootClocks;
		ITI_int	m_NumEdges;

		ITI_int	m_NumChildren;
		ITI_int	m_NumPathes;
		ITI_int	m_NumSteps;

		const ITI_int* m_Children;
		const ITI_int* m_StepsInPath;

		const ITI_int* m_BaseClocks;
		const ITI_int* m_RootClocks;

		enum ClockType m_ClockType;
		ITI_real m_BaseInterval;
	};

	

	struct graphNode {
		ITI_int		m_Index;				
		ITI_int		m_FirstChild;			
		ITI_int		m_NumberOfChildren;		

		ITI_real	m_Interval;				
		ITI_int		m_Resolution;			

		ITI_int		m_Nominator;			
		ITI_int		m_Denominator;			

		ITI_int		m_ShiftTicks;			
		ITI_int		m_Ticks;				
		ITI_int		m_MaxTicks;				

		ITI_int		m_Visited;				
		const ITI_char*	m_Constructor;		

		ITI_bool	m_IsBaseClock;			
	};

	

	struct graphEdge {
		ITI_int		m_NodeFrom;				
		ITI_int		m_NodeTo;				

		ITI_int		m_Alias;				

		ITI_int		m_Factor;				
		ITI_int		m_Shift;				
		enum edgeType	m_EdgeType;				

		ITI_bool	m_HasPath;				

		const ITI_char*	m_Constructor;		
	};

	

	struct graphStep {
		ITI_int		m_Index;				
		ITI_int		m_PathIndex;			

		ITI_int		m_NodeFrom;				
		ITI_int		m_NodeTo;				

		ITI_int		m_Path;					
		ITI_int		m_OtherStep;			

		ITI_int		m_Edge;					
		ITI_int		m_DenominatorBefore;	
		ITI_int		m_DenominatorAfter;		
		ITI_int		m_NominatorBefore;		
		ITI_int		m_NominatorAfter;		
		ITI_bool	m_FactorKnown;			
		ITI_bool	m_ActsOnNominator;		
	};

	

	struct graphPath {
		ITI_int		m_FirstStep;			
		ITI_int		m_NumSteps;				

		ITI_int		m_FirstNode;			
		ITI_int		m_LastNode;				

		ITI_int		m_FirstDenominator;		
		ITI_int		m_FirstNominator;		
		ITI_int		m_LastDenominator;		
		ITI_int		m_LastNominator;		


		ITI_int		m_UnknownFactors;		

		ITI_bool	m_IsCycle;				
		ITI_bool	m_ConsistenceChecked;	
	};

	

	struct inferenceGraph {
		ITI_int		m_NumClocks;			
		ITI_int		m_NumBaseClocks;		
		ITI_int		m_NumEdges;				

		ITI_int		m_Root;					
		ITI_int*    m_Roots;				
		ITI_int		m_NumRoots;				

		ITI_int		m_NumPaths;				
		ITI_int		m_NumSteps;				

		ITI_char*	m_Error;				

		struct graphNode*	m_Nodes;		
		struct graphEdge*	m_Edges;		

		ITI_int*	m_Children;				
		ITI_int*	m_ChildEdges;			

		ITI_int*	m_BaseClocks;			
		
		enum ClockType	m_ClockType;		

		struct graphPath*	m_Paths;		
	    struct graphStep*	m_Steps;		

		ITI_int		m_CurrentVisit;			
		ITI_int		m_BaseDenominator;		
		ITI_int		m_BaseNominator;		
		ITI_real	m_BaseInterval;			

		ITI_ClockInferenceState	m_Status;	
	};

	















	void initEdge(
		struct inferenceGraph* graph,
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
		ITI_AllocateMemory allocateMemory
	);

	










	void initNode(
		struct inferenceGraph* graph,
		ITI_int nodeIndex,
		ITI_int firstChild,
		ITI_int	numberOfChildren,
		ITI_real interval,
		ITI_int resolution,
		ITI_bool isBaseClock,
		ITI_char* constructor,
		ITI_AllocateMemory allocateMemory
	);
				
	







	void updateIGNode(struct inferenceGraph* graph, const ITI_int nodeIndex, ITI_real interval, ITI_int resolution, ITI_int ticks, ITI_int maxTicks);

	




	void updateNodeInterval(struct inferenceGraph* graph, const ITI_int nodeIndex, ITI_real interval);


	





	void updateIGEdge(struct inferenceGraph* graph, const ITI_int edgeIndex, ITI_int factor, ITI_int shift);

	



	void loadResult_BaseInterval(struct inferenceGraph* graph, ITI_real* bpinterval);

	







	void loadResult_ClockInference(struct inferenceGraph* graph, const ITI_int nodeIndex, ITI_real* interval, ITI_int* maxTicks, ITI_int* ticks, ITI_int* activated);

	




	void addPath(struct inferenceGraph* graph, const ITI_int pathIndex, struct graphPath* newPath);

	




	void addStep(struct inferenceGraph* graph, const ITI_int stepIndex, struct graphStep* newStep);

	


	void freeInferenceGraph(struct inferenceGraph* graph);

	



	void initInferenceGraph(struct inferenceGraph* graph, ITI_int clockType, ITI_real baseInterval);

	



	void allocInferenceGraph(struct inferenceGraph* graph, const struct graphStatistics* stat);

	


	const ITI_char* getError(struct inferenceGraph* graph);

	


	ITI_ClockInferenceState performClockInference(struct inferenceGraph* graph);

	


	ITI_ClockInferenceState performIntervalUpdate(struct inferenceGraph* graph);

#ifdef __cplusplus
} 
#endif

#endif  
