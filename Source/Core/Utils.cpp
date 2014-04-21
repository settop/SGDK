#include "Utils.h"

StaticInitableBase *StaticInitableBase::s_layerStart[eStaticInitLayer_Num] = {nullptr, nullptr, nullptr};

void StaticInitableBase::StaticInit
(
)
{
	for(uint32 i = 0; i < eStaticInitLayer_Num; ++i)
	{
		StaticInitableBase *next = s_layerStart[i];
		while(next)
		{
			next->_StaticInit();
			next = next->m_next;
		}
	}
}
void StaticInitableBase::StaticShutdown
(
)
{
	for( uint32 i = eStaticInitLayer_Num; i > 0; --i )
	{
		StaticInitableBase *next = s_layerStart[i - 1];
		while(next)
		{
			next->_StaticShutdown();
			next = next->m_next;
		}
	}
}

StaticInitableBase::StaticInitableBase
(
	uint32 _layer
)
{
	m_next = s_layerStart[_layer];
	s_layerStart[_layer] = this;
}