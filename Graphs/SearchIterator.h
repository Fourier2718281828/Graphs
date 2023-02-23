#ifndef _SEARCH_ITERATOR_
#define _SEARCH_ITERATOR_
#include "NonExistentVertexException.h"
#include "StoppedIteratorException.h"
#include <vector>
#include <stack>
#include <queue>
#include <list>

template
<
	template<typename> typename Container, 
	typename Graph
>
class SearchIterator
{ 
public:
	using _Vertex_t = size_t;
private:
	const Graph&					_graph;
	mutable Container<_Vertex_t>	_buffer;
	mutable std::vector<bool>		_visitedVertices;
	mutable _Vertex_t				_current;
	_Vertex_t						_start;
public:
	SearchIterator(const Graph&, const _Vertex_t);
	~SearchIterator() = default;
public:
	inline void start(const _Vertex_t = _start);
	inline bool is_stopped()						const;
	inline const SearchIterator& operator++()		const;
	inline const SearchIterator operator++(int)		const;
	inline const _Vertex_t& operator*()				const;
};

template<template<typename> typename Container, typename Graph>
inline SearchIterator<Container, Graph>::SearchIterator(const Graph& g, const _Vertex_t u)
	: _graph(g),
	_buffer(),
	_visitedVertices(_graph.vertex_count()),
	_current(u),
	_start(u)
{
	if (!_graph.has_vertex(u))
		throw NonExistentVertexException("Non-existent vertex : ");
	_visitedVertices[u] = true;
	_buffer.push(u);
}

template<template<typename> typename Container, typename Graph>
inline void SearchIterator<Container, Graph>::start(const _Vertex_t u)
{
	_buffer.clear();
	_buffer.push(u);
	_visitedVertices.resize(_graph.vertex_count(), false);
	_visitedVertices[u] = true;
	_start = _current = u;
}

template<template<typename> typename Container, typename Graph>
inline bool SearchIterator<Container, Graph>::is_stopped() const
{
	return _buffer.empty();
}

template<template<typename> typename Container, typename Graph>
inline const SearchIterator<Container, Graph>& SearchIterator<Container, Graph>::operator++() const
{
	if (_buffer.empty())
		throw StoppedIteratorException("Cannot increament a stopped iterator");

	_buffer.pop();

	for (auto&& neighbour : _graph[_current])
	{
		if (!_visitedVertices[neighbour])
		{
			_buffer.push(neighbour);
			_visitedVertices[neighbour] = true;
		}
	}

	if (!is_stopped()) 
		_current = _buffer.top();

	return *this;
}

template<template<typename> typename Container, typename Graph>
inline const SearchIterator<Container, Graph> SearchIterator<Container, Graph>::operator++(int) const
{
	const auto prev_iterator = *this;
	++(*this);
	return prev_iterator;
}

template<template<typename> typename Container, typename Graph>
inline const typename SearchIterator<Container, Graph>::_Vertex_t& 
	SearchIterator<Container, Graph>::operator*() const
{
	if (is_stopped())
		throw StoppedIteratorException("Cannot operator* on a stopped iterator");
	return _current;
}

template<typename T>
class SearchContainer
{
public:
	SearchContainer() = default;
	virtual ~SearchContainer() = default;
public:
	virtual void push(const T& value)	= 0;
	virtual void clear()				= 0;
	virtual void pop()					= 0;
	virtual const T& top() const		= 0;
	virtual bool empty() const			= 0;
};

template<typename T>
class BFSContainer : SearchContainer<T>
{
private:
	std::list<T> _queue;
public:
	BFSContainer() = default;
	virtual ~BFSContainer() = default;
public:
	virtual inline void push(const T& value)	override { _queue.push_back(value);		}
	virtual inline void clear()					override { _queue = std::list<T>();		}
	virtual inline void pop()					override { _queue.pop_front();			}
	virtual inline const T& top() const			override { return _queue.front();		}
	virtual inline bool empty() const			override { return _queue.empty();		}
};

template<typename T>
class DFSContainer : SearchContainer<T>
{
private:
	std::stack<T> _stack;
public:
	DFSContainer() = default;
	virtual ~DFSContainer() = default;
public:
	virtual inline void push(const T& value)	override { _stack.push(value);			}
	virtual inline void clear()					override { _stack = std::stack<T>();	}
	virtual inline void pop()					override { _stack.pop();				}
	virtual inline const T& top() const			override { return _stack.top();			}
	virtual inline bool empty() const			override { return _stack.empty();		}
};

template<typename Graph>
using BFSIterator = SearchIterator<BFSContainer, Graph>;

template<typename Graph>
using DFSIterator = SearchIterator<DFSContainer, Graph>;

template<typename Graph>
using ConstBFSIterator = SearchIterator<BFSContainer, Graph>;

template<typename Graph>
using ConstDFSIterator = SearchIterator<DFSContainer, Graph>;

#endif // !_SEARCH_ITERATOR_
