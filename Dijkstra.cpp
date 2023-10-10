#include "pch.h"
#include "Graph.h"
#include <queue>

// =============================================================================
// Dijkstra ====================================================================
// =============================================================================

void Dijkstra(CGraph& graph, CVertex* pStart) {
	for (CVertex& vertex : graph.m_Vertices) {
		vertex.m_DijkstraDistance = DBL_MAX;
		vertex.m_DijkstraVisit = false;
	}
	graph.FindVertex(pStart->m_Name.c_str())->m_DijkstraDistance = 0.0;

	CVertex* pActual = pStart;

	while (pActual != nullptr) {
		pActual->m_DijkstraVisit = true;
		for (CEdge* e : pActual->m_Edges) {
			CVertex* pNeighbour = e->m_pDestination;
			double neighbourDist = e->m_Length;

			if (!pNeighbour->m_DijkstraVisit) {
				double newDist = pActual->m_DijkstraDistance + neighbourDist;
				if (newDist < pNeighbour->m_DijkstraDistance) {
					pNeighbour->m_DijkstraDistance = newDist;
				}
			}
		}
		pActual = nullptr;
		double minDistance = DBL_MAX;
		for (CVertex& vertex : graph.m_Vertices) {
			if (!vertex.m_DijkstraVisit && vertex.m_DijkstraDistance < minDistance) {
				pActual = &vertex;
				minDistance = vertex.m_DijkstraDistance;
			}
		}
	}
}
// =============================================================================
// DijkstraQueue ===============================================================
// =============================================================================

void DijkstraQueue(CGraph & graph, CVertex * pStart) {

	for (CVertex& vertex : graph.m_Vertices) {
		vertex.m_DijkstraDistance = DBL_MAX;
		vertex.m_DijkstraVisit = false;
	}
	graph.FindVertex(pStart->m_Name.c_str())->m_DijkstraDistance = 0.0;

	std::priority_queue<std::pair<double, CVertex*>, std::vector<pair<double, CVertex*>>, std::greater<pair<double, CVertex*>>> pq;
	pq.push({ 0.0, pStart });

	while (!pq.empty()) {
		CVertex* pActual = pq.top().second;
		double dist = pq.top().first;

		pq.pop();

		if (!pActual->m_DijkstraVisit) {
			pActual->m_DijkstraVisit = true;

			for (CEdge* e : pActual->m_Edges) {
				CVertex* pNeighbour = e->m_pDestination;
				double neighbourDist = e->m_Length;

				double newDist = pActual->m_DijkstraDistance + neighbourDist;
				if (newDist < pNeighbour->m_DijkstraDistance) {
					pNeighbour->m_DijkstraDistance = newDist;
					pq.push({ newDist, pNeighbour });
				}
			}
		}
	}
}
