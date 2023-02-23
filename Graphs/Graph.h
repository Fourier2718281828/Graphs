#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <unordered_set>

class Graph
{
public:
	using _Iterable = std::unordered_set<size_t>;
	using _Vertex_t = size_t;
private:
	class Implementation;
	Implementation* _impl;
public:
	Graph(const size_t);
	Graph(const Graph&);
	Graph(Graph&&) noexcept;
	~Graph();
public:
	Graph& operator=(const Graph&);
	Graph& operator=(Graph&&)  noexcept;
public:
	void add_vertex();
	void add_edge(const _Vertex_t, const _Vertex_t);
	size_t deg(const _Vertex_t)													const;
	size_t vertex_count()														const;
	size_t edge_count()															const;
	bool has_vertex(const _Vertex_t)											const;
	bool has_edge(const _Vertex_t, const _Vertex_t)								const;
	bool has_induced_path(const _Vertex_t, const _Vertex_t, const _Vertex_t)	const;
	const _Iterable& operator[](const _Vertex_t)								const;
	const _Iterable  sphere_r2(const _Vertex_t)									const;
public:
	static const Graph path_l(const size_t);
};
#endif // !_GRAPH_H_
