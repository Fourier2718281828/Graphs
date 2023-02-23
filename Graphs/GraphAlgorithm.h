#ifndef _GRAPH_ALHORITHM_
#define _GRAPH_ALHORITHM_
#include "Graph.h"

class GraphFunction;

bool is_peakless(const GraphFunction&);
bool is_peakless_on_induced_pathL2
(
	const GraphFunction& f,
	const Graph::_Vertex_t v1,
	const Graph::_Vertex_t v2,
	const Graph::_Vertex_t v3
);

#endif // !_GRAPH_ALHORITHM_
