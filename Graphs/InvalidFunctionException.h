#ifndef _INVALID_FUNCTION_EXCEPTION_
#define _INVALID_FUNCTION_EXCEPTION_

class InvalidFunctionException : std::exception
{
public:
	InvalidFunctionException(const char* message) : std::exception(message) {}
};
#endif // !_INVALID_FUNCTION_EXCEPTION_
