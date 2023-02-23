#include "Graph.h"
#include "NonExistentVertexException.h"
#include <vector>

using std::vector;
using std::unordered_set;

class Graph::Implementation
{
private:
	size_t _edgeCount;
	vector<unordered_set<_Vertex_t>> _adjList;
public:
	Implementation(const size_t);
	Implementation(const Implementation&) = default;
	~Implementation() = default;
public:
	Implementation& operator=(const Implementation&) = default;
public:
	inline void add_vertex();
	inline void add_edge(const _Vertex_t, const _Vertex_t);
	inline size_t deg(const _Vertex_t)														const;
	inline size_t vertex_count()															const;
	inline size_t edge_count()																const;
	inline bool has_vertex(const _Vertex_t)													const;
	inline bool has_edge(const _Vertex_t, const _Vertex_t)									const;
	inline const _Iterable& get_adjecent(const _Vertex_t)									const;
	inline const _Iterable  sphere_r2(const _Vertex_t)										const;
	inline bool has_induced_path(const _Vertex_t a, const _Vertex_t b, const _Vertex_t c)	const;
};

Graph::Implementation::Implementation(const size_t vertex_count)
	: _adjList(vertex_count), _edgeCount(0)
{
}

inline void Graph::Implementation::add_vertex()
{
	_adjList.push_back(unordered_set<_Vertex_t>());
}

inline void Graph::Implementation::add_edge(const _Vertex_t u, const _Vertex_t v)
{
	if (!has_vertex(u))
		throw NonExistentVertexException("Non-existent vertex : ");
	if (!has_vertex(v))
		throw NonExistentVertexException("Non-existent vertex : ");

	_adjList[u].insert(v);
	_adjList[v].insert(u);
	++_edgeCount;
}

inline size_t Graph::Implementation::deg(const _Vertex_t u) const
{
	if (!has_vertex(u))
		throw NonExistentVertexException("Non-existent vertex : ");
	return _adjList[u].size();
}

inline size_t Graph::Implementation::vertex_count() const
{
	return _adjList.size();
}

inline size_t Graph::Implementation::edge_count() const
{
	return _edgeCount;
}

inline bool Graph::Implementation::has_vertex(const _Vertex_t u) const
{
	return u < vertex_count();
}

inline bool Graph::Implementation::has_edge(const _Vertex_t u, const _Vertex_t v) const
{
	return get_adjecent(u).find(v) != get_adjecent(u).cend();
}

inline const Graph::_Iterable& Graph::Implementation::get_adjecent(const _Vertex_t u) const
{
	return _adjList[u];
}

inline const Graph::_Iterable Graph::Implementation::sphere_r2(const _Vertex_t u) const
{
	if (!has_vertex(u))
		throw NonExistentVertexException("Non-existent vertex : ");

	Graph::_Iterable result;
	for (auto&& i : get_adjecent(u))
	{
		for (auto&& j : get_adjecent(i))
		{
			if (j != u && !has_edge(u, j))
			{
				result.insert(j);
			}
		}
	}

	return result;
}

inline bool Graph::Implementation::has_induced_path
(
	const _Vertex_t a,
	const _Vertex_t b, 
	const _Vertex_t c
) const
{
	return	has_vertex(a)	&&
			has_vertex(b)	&&
			has_vertex(c)	&&
			!has_edge(a, c) &&
			a != c;
}

Graph::Graph(const size_t vertex_count)
	:	_impl(new Implementation(vertex_count))
{
}

Graph::Graph(const Graph& g)
	:	_impl(new Implementation(*g._impl))
{
}

Graph::Graph(Graph&& g) noexcept
	: _impl(g._impl)
{
	g._impl = nullptr;
}

Graph::~Graph()
{
	delete _impl;
	_impl = nullptr;
}

Graph& Graph::operator=(const Graph& g)
{
	*_impl = *g._impl;
	return *this;
}

Graph& Graph::operator=(Graph&& g) noexcept
{
	_impl = g._impl;
	g._impl = nullptr;
	return *this;
}

void Graph::add_vertex()
{
	_impl->add_vertex();
}

void Graph::add_edge(const _Vertex_t u, const _Vertex_t v)
{
	_impl->add_edge(u, v);
}

size_t Graph::deg(const _Vertex_t vertex) const
{
	return _impl->deg(vertex);
}

size_t Graph::vertex_count() const
{
	return _impl->vertex_count();
}

size_t Graph::edge_count() const
{
	return _impl->edge_count();
}

bool Graph::has_vertex(const _Vertex_t u) const
{
	return _impl->has_vertex(u);
}

bool Graph::has_edge(const _Vertex_t u, const _Vertex_t v) const
{
	return _impl->has_edge(u, v);
}

bool Graph::has_induced_path(const _Vertex_t a, const _Vertex_t b, const _Vertex_t c) const
{
	return _impl->has_induced_path(a, b, c);
}

const Graph::_Iterable& Graph::operator[](const _Vertex_t vertex) const
{
	return _impl->get_adjecent(vertex);
}

const Graph::_Iterable Graph::sphere_r2(const _Vertex_t u) const
{
	return _impl->sphere_r2(u);
}

const Graph Graph::path_l(const size_t length)
{
	Graph path(length);
	for (size_t i = 0u; i < length - 1; ++i)
	{
		path.add_edge(i, i + 1);
	}

	return path;
}
