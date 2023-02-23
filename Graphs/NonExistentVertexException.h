#ifndef _NON_EXISTANT_VERTEX_EXCEPTION_
#define _NON_EXISTANT_VERTEX_EXCEPTION_

#include <exception>

class NonExistentVertexException : std::exception 
{
public:
	NonExistentVertexException(const char* message) : std::exception(message) {}
};

#endif // !_NON_EXISTANT_VERTEX_EXCEPTION_