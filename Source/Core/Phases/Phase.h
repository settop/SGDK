#pragma once

#include <Core\TypeDefs.h>
#include <Core\Utils.h>
#include <boost\atomic.hpp>

namespace _PrivatePhase
{
	template<bool UseMultithreading>
	struct MultithreadingPolicy
	{
		static bool const Value = UseMultithreading;
	};

	template<typename _P1 = Null, typename _P2 = Null, typename _P3 = Null>
	struct FunctionParams
	{
		template<typename C>
		struct ClassFunc
		{
			typedef bool (*Value)(_P1, _P2, _P3);
		};
		static uint32 const NumArgs = 3;
		typedef _P1 P1;
		typedef _P2 P2;
		typedef _P3 P3;
	};

	template<typename _P1>
	struct FunctionParams<_P1, Null, Null>
	{
		template<typename C>
		struct ClassFunc
		{
			typedef bool (*Value)(_P1);
		};
		static uint32 const NumArgs = 1;
		typedef _P1 P1;
	};

	template<typename _P1, typename _P2>
	struct FunctionParams<_P1, _P2, Null>
	{
		template<typename C>
		struct ClassFunc
		{
			typedef bool (*Value)(_P1, _P2);
		};
		static uint32 const NumArgs = 2;
		typedef _P1 P1;
		typedef _P2 P2;
	};

	template<>
	struct FunctionParams<Null, Null, Null>
	{
		template<typename C>
		struct ClassFunc
		{
			typedef bool (*Value)();
		};
		static uint32 const NumArgs = 0;
	};

	template<typename Policy, uint32 _numArgs> struct PhaseBase;
	
	template<typename Policy>
	class PhaseAdvancerBase0
	{
		typedef PhaseAdvancerBase0<Policy> SELF;
	public:		
		virtual void ExecutePhase() = 0;
		bool IsActive() const;
		void Activate();
		void Deactivate();
		//void SetLayer(uint32 _layer);
	protected:	
		PhaseAdvancerBase0(uint32 _layer);
	private:
		friend struct PhaseBase<Policy, 0>;
		uint32 m_layer;
		boost::atomic<SELF*> m_next;
		boost::atomic<bool> m_active;

		static boost::atomic<uint32> s_currentLayer;
		static boost::atomic<SELF*> s_layers[2][Policy::MaxLayers];
	};

	template<typename Policy, typename C, bool (C::*Function)()>
	class PhaseAdvancer0 
		: public PhaseAdvancerBase0<Policy>
	{
		typedef PhaseAdvancerBase0<Policy> SUPER;
		typedef PhaseAdvancer0<Policy, C, Function> SELF;
		//static_assert(IsDerivedFrom<C, SELF>::Value, "Class must derive from PhaseAdvancer");
	public:
		PhaseAdvancer0(C *_owningClass, uint32 _layer = 0);
	private:
		virtual void ExecutePhase();
		C *m_owningClass;
	};
	
	template<typename Policy, uint32 _numArgs>
	struct PhaseBase
	{		
		static_assert(_numArgs <= 0, "Not implemented for this number of arguments");
	};

	template<typename Policy>
	struct PhaseBase<Policy, 0>
	{		
		template<typename C, bool (C::*Function)()>
		struct Advancer
		{
			typedef _PrivatePhase::PhaseAdvancer0<Policy, C, Function> Base;
		};
		void AdvanceAll();
	};
};


struct DefaultPolicy
{
	typedef _PrivatePhase::MultithreadingPolicy<true> MultiThreadingPolicy;
	typedef _PrivatePhase::FunctionParams<> FunctionParamsPolicy;
	static uint32 const MaxLayers = 10;
};

template<typename Policy>
struct Phase
	: public _PrivatePhase::PhaseBase<Policy, Policy::FunctionParamsPolicy::NumArgs>
{
};



#include "Phase.inl"