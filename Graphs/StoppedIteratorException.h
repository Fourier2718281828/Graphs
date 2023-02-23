#ifndef _STOPPED_ITERATOR_EXCEPTION_
#define _STOPPED_ITERATOR_EXCEPTION_

#include <exception>

class StoppedIteratorException : std::exception
{
public:
	StoppedIteratorException(const char* message) : std::exception(message) {}
};

#endif // !_STOPPED_ITERATOR_EXCEPTION_
