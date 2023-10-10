#include "pch.h"
#include "Graph.h"
#include <queue>
// SalesmanTrackGreedy =========================================================

CTrack GetShortestPath(CGraph& graph, CVertex* startVertex, CVertex* endVertex) {
    CTrack track(&graph);

    CVertex* currentVertex = endVertex;

    while (currentVertex != startVertex) {
        for (CEdge* edge : currentVertex->m_Edges) {
            CVertex* neighbor = edge->m_pDestination;
            double neighborDistance = neighbor->m_DijkstraDistance;

            if (neighborDistance + edge->m_Length == currentVertex->m_DijkstraDistance) {
                track.AddFirst(edge->m_pReverseEdge);
                currentVertex = neighbor;
                break;
            }
        }
    }
    return track;
}

CTrack SalesmanTrackGreedy(CGraph& graph, CVisits &visits){
	CTrack track(&graph);

	list<CVertex*> candidats(++visits.m_Vertices.begin(), --visits.m_Vertices.end());
	CVertex* currentVertex = visits.m_Vertices.front();

	while (!candidats.empty()) {
        DijkstraQueue(graph, currentVertex);
		CVertex* closestVisit = nullptr;
		double minDist = DBL_MAX;

		for (CVertex* v : candidats) {
			if (v->m_DijkstraDistance < minDist) {
				closestVisit = v;
				minDist = v->m_DijkstraDistance;
			}
		}
        CTrack tempTrack = GetShortestPath(graph, currentVertex, closestVisit);
        track.Append(tempTrack);

        currentVertex = closestVisit;

        candidats.remove(closestVisit);
    }

    CVertex* lastVertex = visits.m_Vertices.back();
    DijkstraQueue(graph, currentVertex);
    CTrack tempTrack = GetShortestPath(graph, currentVertex, lastVertex);
    track.Append(tempTrack);

    return track;
}
