#include "pch.h"
#include "Graph.h"
#include "GraphApplicationDlg.h"
#include <set>
#include <cmath>



// =============================================================================
// CONVEX HULL =================================================================
// =============================================================================

// QuickHull ===================================================================
double areaT(CGPoint& A, CGPoint& B, CGPoint& C) {
	double a = 0.5 * abs(A.m_X * (B.m_Y - C.m_Y) + B.m_X * (C.m_Y - A.m_Y) + C.m_X * (A.m_Y - B.m_Y));
	return a;
}

double aboveOrBelow(CGPoint& A, CGPoint& B, CGPoint& C) {
	double aux = (B.m_X - A.m_X) * (C.m_Y - A.m_Y) - (B.m_Y - A.m_Y) * (C.m_X - A.m_X);
	return -aux;
}

list<CVertex> ConvexHull(CVertex A, CVertex B, list<CVertex> Punts, bool up) {
	if (!Punts.empty()) {
		double max = 0.0;
		double area = 0.0;
		CVertex maxA(Punts.front());
		for (CVertex v : Punts) {
			area = areaT(A.m_Point, B.m_Point, v.m_Point);
			if (area > max) {
				max = area;
				maxA = v;
			}
		}

		list<CVertex> edgeAC, edgeBC;
		for (CVertex vp : Punts) {
			double lineEqAC = aboveOrBelow(A.m_Point, maxA.m_Point, vp.m_Point);
			double lineEqBC = aboveOrBelow(B.m_Point, maxA.m_Point, vp.m_Point);
			if (up)
			{
				if (lineEqAC > 0) {
					edgeAC.push_back(vp);
				}else if (lineEqBC < 0) {
					edgeBC.push_back(vp);
				}
			}
			else {
				if (lineEqAC > 0) {
					edgeAC.push_back(vp);
				}
				else if (lineEqBC < 0) {
					edgeBC.push_back(vp);
				}
			}
		}
		list<CVertex> CHRight = ConvexHull(maxA, B, edgeBC, up);
		list<CVertex> CHLeft = ConvexHull(A, maxA, edgeAC, up);
		CHRight.insert(CHRight.end(), CHLeft.begin(), CHLeft.end());
		return CHRight;
	}
	list<CVertex> l;
	l.push_back(B);
	return l;
}

CConvexHull QuickHull(CGraph& graph){
	CConvexHull hull(&graph);
	if (graph.m_Vertices.size() <= 2) {
		if (graph.GetNVertices() == 0) {
			return hull;
		}
		else if (graph.m_Vertices.front().m_Point == graph.m_Vertices.back().m_Point) {
			CVertex* ptrV = new CVertex(graph.m_Vertices.front().m_Name.c_str(), graph.m_Vertices.front().m_Point.m_X, graph.m_Vertices.front().m_Point.m_Y);
			hull.m_Vertices.push_back(ptrV);
			return hull;
		}
		else {
			for (CVertex v : graph.m_Vertices) {
				CVertex* ptrV = new CVertex(v.m_Name.c_str(), v.m_Point.m_X, v.m_Point.m_Y);
				hull.m_Vertices.push_back(ptrV);
			}
			return hull;
		}
	}

	double max = DBL_MIN, min = graph.m_Vertices.front().m_Point.m_X;
	CVertex A(graph.m_Vertices.front()), B(graph.m_Vertices.front());

	for (CVertex pVertex : graph.m_Vertices) {
		if (pVertex.m_Point.m_X < A.m_Point.m_X) {
			A = pVertex;
		}

		if (pVertex.m_Point.m_X > B.m_Point.m_X) {
			B = pVertex;
		}
	}

	if (A.m_Point == B.m_Point) {
		CVertex* ptrV = new CVertex(A.m_Name.c_str(), A.m_Point.m_X, A.m_Point.m_Y);
		hull.m_Vertices.push_back(ptrV);
		return hull;
	}

	list<CVertex> above, below;

	for (CVertex v : graph.m_Vertices) {
		if (v.m_Point != A.m_Point && v.m_Point != B.m_Point) {
			double lineEq = aboveOrBelow(A.m_Point, B.m_Point, v.m_Point);
			if (lineEq > 0) {
				above.push_back(v);
			}
			else if (lineEq < 0) {
				below.push_back(v);
			}
		}
	}
	
	list<CVertex> CHUp = ConvexHull(A, B, above, true), CHDown = ConvexHull(B, A, below, false);
	CHUp.insert(CHUp.end(), CHDown.begin(), CHDown.end());

	for (CVertex v : CHUp) {
		CVertex* ptrV = new CVertex(v.m_Name.c_str(), v.m_Point.m_X, v.m_Point.m_Y);
		hull.m_Vertices.push_back(ptrV);
	}
	return hull;
}