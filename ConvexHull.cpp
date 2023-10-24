#include "pch.h"
#include "Graph.h"
#include "GraphApplicationDlg.h"
#include <set>



// =============================================================================
// CONVEX HULL =================================================================
// =============================================================================

// QuickHull ===================================================================

CConvexHull QuickHull(CGraph& graph)
{
	CConvexHull hull(&graph);

	double max = DBL_MIN, min = DBL_MAX;
	CVertex vMax(graph.m_Vertices.front()), vMin(graph.m_Vertices.front());

	for (CVertex v : graph.m_Vertices) {
		if (v.m_Point.m_X > max) 
	}



	return CConvexHull(&graph);
}