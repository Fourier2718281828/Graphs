#include "GraphFunction.h"
#include "Graph.h"
#include "NonExistentVertexException.h"
#include "InvalidFunctionException.h"

GraphFunction::GraphFunction(const Graph& g, const std::initializer_list<GraphFunction::_ReturnType> init_list)
	:	_domain(g), _image(init_list)
{
	if (_domain.vertex_count() != _image.size())
		throw InvalidFunctionException("Cannot initialize function with initializer_list of size " + _image.size());
}


const GraphFunction::_ReturnType GraphFunction::operator()(const Graph::_Vertex_t u) const
{
	if (!_domain.has_vertex(u))
		throw NonExistentVertexException("No vertex in the domain : " + u);
	return _image[u];
}

const Graph& GraphFunction::domain() const
{
	return _domain;
}
