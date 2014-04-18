#pragma once

#include <Core/TypeTraits.h>

#ifdef S_DEBUGGING
#define AllocationTracking (1)
#else
#define AllocationTracking (0)
#endif

#if AllocationTracking
	#define CreateAllocParams(_Type) , AllocationParams(__FILE__, __LINE__, __FUNCTION__, TypeName(_Type))
	#define AllocParam ,_params	
#else
	#define CreateAllocParams(_Type)
	#define AllocParam _params	
#endif

struct AllocationParams
{
#if AllocationTracking
	inline AllocationParams(char const *_file, int _line, char const *_function, char const *_type):
	m_file(_file),
	m_line(_line),
	m_function(_function),
	m_type(_type)
	{}

	char const * const m_file;
	int const m_line;
	char const * const m_function;
	char const * const m_type;
#else
	inline AllocationParams(char const *_file, int _line, char const *_function, char const *_type){}
#endif
};