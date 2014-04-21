#pragma once

#include <new>
#include <Core/TypeTraits.h>
#include <Core/Utils.h>

#include <Mem/Allocator/Allocator.h>
#include <Mem/AllocationParams.h>

//allocation policies
#include <Mem/Allocator/GlobalAllocationPolicy.h>

//inlcude thread policies
#include <Mem/Allocator/NoThreadPolicy.h>

//inlcude bounds checking policies
#include <Mem/Allocator/SimpleBoundsCheckingPolicy.h>

//inlcude memory tracking policies
#include <Mem/Allocator/NoMemoryTrackingPolicy.h>

//inlcude memory tagging policies
#include <Mem/Allocator/SimpleMemoryTaggingPolicy.h>

#define NEW(_Allocator, _Type) new(_Allocator.Allocate(sizeof(_Type), std::alignment_of<_Type>::value, 0u, CreateAllocParams(_Type))) _Type
#define DELETE(_Allocator, _Ptr) _Private_Mem::Delete(_Allocator, _Ptr); _Ptr = nullptr

#define ARRAY_NEW(_Allocator, _TypeAndCount) _Private_Mem::NewArray<std::remove_extent<_TypeAndCount>::type>(_Allocator, std::extent<_TypeAndCount>::value, std::alignment_of<std::remove_extent<_TypeAndCount>::type>::value, CreateAllocParams(std::remove_extent<_TypeAndCount>::type))
#define ARRAY_DELETE(_Allocator, _Ptr) _Private_Mem::DeleteArray(_Allocator, _Ptr); _Ptr = nullptr

namespace _Private_Mem
{
	typedef std::true_type PODType;
	typedef std::false_type NonPODType;

	template <typename T, class ALLOCATOR>
	inline void Delete(ALLOCATOR &_allocator, T* _ptr)
	{
		Delete(_allocator, _ptr, std::is_pod<T>());
	}

	template <typename T, class ALLOCATOR>
	inline void Delete(ALLOCATOR &_allocator, T* _ptr, PODType)
	{
		_allocator.Free(_ptr);
	}

	template <typename T, class ALLOCATOR>
	inline void Delete(ALLOCATOR &_allocator, T* _ptr, NonPODType)
	{
		_ptr->~T();
		_allocator.Free(_ptr);
	}

	template <typename T, class ALLOCATOR>
	inline void* NewArray(ALLOCATOR &_allocator, size_t _count, size_t _alignment, AllocationParams _allocationParams)
	{
		return NewArray(_allocator, _count, _alignment, _allocationParams, std::is_pod<T>());
	}

	template <typename T, class ALLOCATOR>
	inline void DeleteArray(ALLOCATOR &_allocator, T *_ptr)
	{
		DeleteArray(_allocator, _ptr, std::is_pod<T>());
	}

	template <typename T, class ALLOCATOR>
	void* NewArray(ALLOCATOR &_allocator, size_t _count, size_t _alignment, AllocationParams _allocationParams, PODType)
	{
		void* memBlock = _allocator.Allocate(sizeof(T) * _count + sizeof(size_t), _alignment, sizeof(size_t), _allocationParams);

		size_t* count = (size_t*)memBlock;
		*count = _count;

		T* typeArray = (T*)(memBlock + sizeof(size_t));

		for (size_t i = 0u; i < _count; ++i)
		{
			new (&typeArray[i]) T;
		}
		return typeArray;
	}

	template <typename T, class ALLOCATOR>
	void DeleteArray(ALLOCATOR &_allocator, T *_ptr, PODType)
	{
		size_t count = ((size_t*)_ptr)[-1];
		T* typeArray = (T*)_ptr;

		for (size_t i = count; i > 0; --i)
		{
			typeArray[i - 1].~T();
		}
		_allocator.Free(_ptr - sizeof(size_t));
	}

	template <typename T, class ALLOCATOR>
	void* NewArray(ALLOCATOR &_allocator, size_t _count, size_t _alignment, AllocationParams _allocationParams, NonPODType)
	{
		void* memBlock = _allocator.Allocate(sizeof(T)* _count, _alignment, 0u, _allocationParams);

		T* typeArray = (T*)(memBlock);
		return typeArray;
	}

	template <typename T, class ALLOCATOR>
	void DeleteArray(ALLOCATOR &_allocator, T *_ptr, NonPODType)
	{
		_allocator.Free(_ptr);
	}
};

typedef Allocator<GlobalAllocationPolicy, NoThreadPolicy, SimpleBoundsCheckingPolicy, NoMemoryTrackingPolicy, SimpleMemoryTaggingPolicy> GlobalAllocatorType;

class Mem :
	StaticInitable<Mem, eStaticInitLayer_Heap>
{
public:
	static void StaticInit();
	static void StaticShutdown();

	inline static GlobalAllocatorType& GetGlobalAllocator(){ Assert(s_initalised); return *s_allocator; }
private:
	Mem();
	Mem(Mem const&);

	static bool s_initalised;
	static GlobalAllocatorType *s_allocator;
};

inline GlobalAllocatorType& GlobalAllocator() { return Mem::GetGlobalAllocator(); }