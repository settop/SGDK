#pragma once

template <bool DestroyOnZeroRef>
inline SmartPointerTarget<DestroyOnZeroRef>::SmartPointerTarget
(
) : m_refCount(0u)
{
}

template <bool DestroyOnZeroRef>
inline SmartPointerTarget<DestroyOnZeroRef>::~SmartPointerTarget
(
)
{
	Assert(m_refCount == 0);
}


template <bool DestroyOnZeroRef>
inline void SmartPointerTarget<DestroyOnZeroRef>::Claim
(
)
{
	++m_refCount;
}

template <bool DestroyOnZeroRef>
inline void SmartPointerTarget<DestroyOnZeroRef>::Release
(
)
{	
	Assert(m_refCount > 0);
	if(--m_refCount == 0);
	{
		delete this;
	}
}

template <>
inline void SmartPointerTarget<false>::Release
(
)
{	
	Assert(m_refCount > 0);
	--m_refCount;
}




template <typename T>
inline SmartPointer<T>::SmartPointer
(
) : m_ptr(nullptr)
{
}

template <typename T>
inline SmartPointer<T>::SmartPointer
(
	T *_ptr
) : m_ptr(_ptr)
{
	Claim(m_ptr);
}

template <typename T>
inline SmartPointer<T>::SmartPointer
(
	SmartPointer<T> const &_other
) : m_ptr(_other.m_ptr)
{
	Claim(m_ptr);
}

template <typename T>
template <typename O>
inline SmartPointer<T>::SmartPointer
(
	SmartPointer<O> const &_other
) : m_ptr(_other.m_ptr)
{
	static_assert(IsDerivedFrom<O, T>::Value, "Type O must derive from type T");
	Claim(m_ptr);
}


template <typename T>
inline SmartPointer<T>::~SmartPointer
(
)
{
	Release(m_ptr);
}

template <typename T>
inline SmartPointer<T>& SmartPointer<T>::operator=
(
	SmartPointer<T> const &_other
)
{
	Release(m_ptr);
	m_ptr = _other.m_ptr;
	Claim(m_ptr);
	return *this;
}

template <typename T>
template <typename O>
inline SmartPointer<T>& SmartPointer<T>::operator=
(
	SmartPointer<O> const &_other
)
{
	static_assert(IsDerivedFrom<O, T>::Value, "Type O must derive from type T");
	Release(m_ptr);
	m_ptr = _other.m_ptr;
	Claim(m_ptr);
	return *this;
}

template <typename T>
inline SmartPointer<T>::operator T*
(
)
{
	return m_ptr;
}

template <typename T>
inline T* SmartPointer<T>::operator->
(
)
{
	return m_ptr;
}

template <typename T>
inline T& SmartPointer<T>::operator*
(
)
{
	return *m_ptr;
}

template <typename T>
inline void SmartPointer<T>::Claim
(
	T *_ptr
)
{
	if(_ptr)
	{
		_ptr->Claim();
	}
}

template <typename T>
inline void SmartPointer<T>::Release
(
	T *_ptr
)
{
	if(_ptr)
	{
		_ptr->Release();
	}
}