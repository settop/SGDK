#pragma once

#include "Phase.h"

namespace _PrivatePhase
{	
	///-----------------------------------------------------------------------
	///Phase0
	///-----------------------------------------------------------------------
	template<typename Policy>
	PhaseAdvancerBase0<Policy>::PhaseAdvancerBase0
	(
		uint32 _layer
	) : m_layer(_layer),
		m_next(nullptr),
		m_active(false)
	{
	}

	template<typename Policy>
	bool PhaseAdvancerBase0<Policy>::IsActive
	(
	) const
	{
		return m_active.load();
	}

	template<typename Policy>
	void PhaseAdvancerBase0<Policy>::Activate
	(
	)
	{
		m_active.store(true);
		if(m_next.load())
		{
			//already in queue
			return;
		}



		SELF *target = s_layers[m_layer].load();
		do
		{
			SELF *expectedNext = nullptr;
			if(!m_next.compare_exchange_weak(expectedNext, target))
			{
				//another thread has activated this
				return;
			}
		} while(!s_layers[m_layer].compare_exchange_weak(target, this));
		//else it is already active
	}

	template<typename Policy>
	void PhaseAdvancerBase0<Policy>::Deactivate
	(
	)
	{
		m_active.store(false);
	}
	
	template<typename Policy>
	boost::atomic<typename PhaseAdvancerBase0<Policy>::SELF*> PhaseAdvancerBase0<Policy>::s_layers[Policy::MaxLayers];
	
	template<typename Policy>
	boost::atomic<uint32> PhaseAdvancerBase0<Policy>::s_currentLayer = 0u;

	template<typename Policy, typename C, bool (C::*Function)()>
	PhaseAdvancer0<Policy, C, Function>::PhaseAdvancer0
	(
		C *_owningClass, 
		uint32 _layer// = 0
	) : PhaseAdvancerBase0<Policy>(_layer),
		m_owningClass(_owningClass)
	{		
	}

	template<typename Policy, typename C, bool (C::*Function)()>
	void PhaseAdvancer0<Policy, C, Function>::ExecutePhase
	(
	)
	{
		bool active = m_active.load();
		if(active)
		{
			active = (m_owningClass->*Function)();
			if(!active)
			{
				m_active.store(false);
			}
			return active;
		}
		else
		{
			return false;
		}
	}


	template<typename Policy>
	void PhaseBase<Policy, 0>::AdvanceAll
	(
	)
	{
		typedef PhaseAdvancerBase0<Policy> Advancer;
		for(uint32 layer = 0; layer < Policy::MaxLayers; ++layer)
		{			
			Advancer *it = Advancer::s_layers[layer].load();
			while(it)
			{
				if(it->m_active)
				{
					it->m_active = it->ExecutePhase();
				}
				if(!it->m_active)
				{

				}
			}
		}
	}
};
