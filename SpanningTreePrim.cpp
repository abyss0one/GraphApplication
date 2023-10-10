#include "pch.h"
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

// =============================================================================
// SpanningTreePrim ============================================================
// =============================================================================


CSpanningTree SpanningTreePrim(CGraph & graph)
{
    CSpanningTree tree(&graph);
    if (graph.GetNEdges() == 0) return tree;
	    std::priority_queue<std::pair<double, CEdge*>, std::vector<pair<double, CEdge*>>, std::greater<pair<double, CEdge*>>> pq;
        int n = graph.GetNVertices();
        for (CVertex& v : graph.m_Vertices)
        {
            v.m_JaHePassat = false;
        }
        for (CEdge* edge : graph.m_Vertices.front().m_Edges) {
            pq.push({ edge->m_Length, edge });
        }
        graph.m_Vertices.front().m_JaHePassat = true;
        int vCount = 1;
        while (!pq.empty()) {
            CEdge* e = pq.top().second;
            pq.pop();
            e->m_pDestination->m_JaHePassat = true;
            tree.Add(e);
            vCount++;
            if (vCount == n) break;
            for (CEdge* edge : e->m_pDestination->m_Edges) {
                if (!edge->m_pDestination->m_JaHePassat)
                    pq.push({ edge->m_Length, edge });
            }
            while (pq.top().second->m_pDestination->m_JaHePassat) {
                pq.pop();
                if (pq.empty()) break;
            }
        }
	return tree;
}
