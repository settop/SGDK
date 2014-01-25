#pragma once

template <typename T, uint32 Layer>
StaticInitableClass<T, Layer>::StaticInitableClass
(
) : StaticInitableBase(_layer)
{
}

template <typename T, uint32 Layer>
void StaticInitableClass<T, Layer>::_StaticInit
(
)
{
	T:StaticInit();
}

template <typename T, uint32 Layer>
void StaticInitableClass<T, Layer>::_StaticShutdown
(
)
{
	T::StaticShutdown();
}


template <typename T, uint32 Layer>
StaticInitableClass<T, Layer> StaticInitable<T, Layer>::s_staticInitable;