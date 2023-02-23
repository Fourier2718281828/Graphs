#include <iostream>
#include <algorithm>
#include "Graph.h"
#include "GraphAlgorithm.h"
#include "GraphFunction.h"

using std::cout;
using std::ostream;
using std::endl;

inline ostream& operator<<(ostream& o, const Graph& graph)
{
	auto ver_count = graph.vertex_count();
	for (auto i = 0u; i < ver_count; ++i)
	{
		for (auto j = 0u; j < ver_count; ++j)
		{
			o << (graph.has_edge(i, j) ? 1 : 0) << ", ";
			//if (j == ver_count - 1) o << endl;
		}
		o << endl;
	}

	return o;
}


int main()
{
	auto g = Graph::path_l(4);
	GraphFunction f(g, {2, 1, 0, 2});
	cout << is_peakless(f);
	
	//Graph g(7);
	//g.add_edge(0, 5);
	//g.add_edge(1, 5);
	//g.add_edge(1, 2);
	//g.add_edge(0, 6);
	//cout << g;
	////cout << (g.has_edge(0, 5)) << ' ' << (g.has_edge(1, 5)) << ' ' << (g.has_edge(0, 4));
	////cout << g;
	//for (auto&& v : g.sphere_r2(5))
	//{
	//	cout << v << ' ';
	//}

	/*Graph g(4);
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(1, 2);
	g.add_edge(2, 0);
	g.add_edge(2, 3);
	g.add_edge(3, 3);

	cout << g;

	cout << "Following is Breadth First Traversal "
		<< "(starting from vertex 2) \n";
	for (auto i = DFSIterator<Graph>(g, 2); !i.is_stopped(); ++i)
	{
		cout << *i << ' ';
	}*/
	return 0;
}