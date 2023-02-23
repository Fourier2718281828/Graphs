#ifndef _GRAPH_FUNCTION_
#define _GRAPH_FUNCTION_

#include "Graph.h"
#include <initializer_list>
#include <vector>

class GraphFunction
{
public:
	using _ReturnType = float;
private:
	const Graph& _domain;
	const std::vector<_ReturnType> _image;
public:
	GraphFunction(const Graph&, const std::initializer_list<_ReturnType>);
	~GraphFunction() = default;
public:
	const _ReturnType operator() (const Graph::_Vertex_t) const;
public:
	bool is_peakless() const;
	bool is_peekless_on_walk(const Graph::_Iterable&) const;
	const Graph& domain() const;
};
#endif // !_GRAPH_FUNCTION_
