#pragma once

#include <Core/TypeDefs.h>
#include <Core/Utils.h>
#include <Core/TypeTraits.h>

struct DeleteOnDestruction;

template <typename DestructionPolicy = DeleteOnDestruction>
class SmartPointerTarget
{
public:
	inline SmartPointerTarget();
	virtual ~SmartPointerTarget();

	inline void Claim();
	inline void Release();
private:
	uint32 m_refCount;
};

template <typename T>
class SmartPointer
{
public:
	inline SmartPointer();
	inline SmartPointer(T *_ptr);
	//copy constructors
	inline SmartPointer(SmartPointer<T> const &_other);
	template <typename O>
	inline SmartPointer(SmartPointer<O> const &_other);
	//move constructors
	inline SmartPointer( SmartPointer<T> &&_other );
	template <typename O>
	inline SmartPointer( SmartPointer<O> &&_other );
	 
	inline ~SmartPointer();

	inline SmartPointer<T>& operator=(SmartPointer<T> const &_other);
	template <typename O>
	inline SmartPointer<T>& operator=(SmartPointer<O> const &_other);

	inline operator T*();
	inline T* operator->();
	inline T& operator*();
private:
	inline void Claim(T *_ptr);
	inline void Release(T *_ptr);
	T* m_ptr;
};

struct DeleteOnDestruction
{
	inline static void Destroy(SmartPointerTarget<DeleteOnDestruction> *_todestroy);
};

#include "SmartPointer.inl"