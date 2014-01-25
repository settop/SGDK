#pragma once

template <typename T, uint32 Layer>
class StaticInitableClass
{
public:
	StaticInitableClass();
private:	
	virtual void _StaticInit();
	virtual void _StaticShutdown();
};

template <typename T, uint32 Layer>
StaticInitableClass::StaticInitableClass
(
) : StaticInitableBase(_layer)
{
}

template <typename T, uint32 Layer>
void StaticInitableClass::_StaticInit
(
)
{
	T:StaticInit();
}

template <typename T, uint32 Layer>
void StaticInitableClass::_StaticShutdown
(
)
{
	T::StaticShutdown();
}


template <typename T, uint32 Layer>
static StaticInitableClass<T, Layer> StaticInitable::s_staticInitable;