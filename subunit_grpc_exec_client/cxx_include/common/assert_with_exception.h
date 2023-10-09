#pragma once
#include <exception>

namespace ext::assert
{
	using AssertExceptionNullPointer = std::exception;
	template<typename T>
	static void Assert_With_Exception_Is_Not_Null(T&);
}

template<typename T>
static void ext::assert::Assert_With_Exception_Is_Not_Null(T& t)
{
	if(t == nullptr)
	{
		throw AssertExceptionNullPointer();
	}
}
