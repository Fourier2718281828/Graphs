#include "GraphAlgorithm.h"
#include "GraphFunction.h"
#include "SearchIterator.h"
#include <cmath>

#include <iostream>

bool is_peakless(const GraphFunction& f)
{
	auto graph = f.domain();
	for (Graph::_Vertex_t i = 0u; i < graph.vertex_count(); ++i)
	{
		for (auto&& u : graph[i])
		{
			for (auto&& v : graph[u])
			{
				//std::cout << i << ' ' << u << ' ' << v << std::endl;

				try
				{
					if (!is_peakless_on_induced_pathL2(f, i, u, v))
					{
						std::cout << i << ' ' << u << ' ' << v << " is bad" << std:: endl;
						return false;
					}
					else
					{
						std::cout << i << ' ' << u << ' ' << v << " is good" << std::endl;
					}
				}
				catch(const NonExistentVertexException&){}
			}
		}
	}

	return true;
}

bool is_peakless_on_induced_pathL2
(
	const GraphFunction& f,
	const Graph::_Vertex_t v1,
	const Graph::_Vertex_t v2,
	const Graph::_Vertex_t v3
)
{
	auto graph = f.domain();
	if (!graph.has_induced_path(v1, v2, v3))
		throw NonExistentVertexException("No induced path v1, v2, v3");

	auto max = std::max(f(v1), f(v3));
	return	f(v2) < max || (f(v2) == max && f(v1) == f(v3));
}