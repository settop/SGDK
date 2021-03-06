#pragma once

#include <Core\TypeDefs.h>
#include <Windows.h>
#include <stdio.h>

#define Bit( _bit ) ( 1 << (_bit) )
#define IsBitSet( _value, _bit ) (((_value) & (Bit(_bit))) != 0)
#define SetBit( _value, _bit ) ((_value) |= Bit(_bit))
#define ClearBit( _value, _bit ) ((_value) &= ~Bit(_bit))

//---------------------------------------------------------------------------------

#ifdef S_DEBUGGING
	#define AssertMessage( _msg ) \
	{\
		static bool assertIgnored = false;\
		if(!assertIgnored)\
		{\
			int msgboxID = MessageBoxA\
			(\
				nullptr,\
				_msg,\
				"Runtime Assert",\
				MB_ICONWARNING | MB_ABORTRETRYIGNORE | MB_DEFBUTTON1\
			);\
			switch(msgboxID)\
			{\
			case IDABORT:\
				DebugBreak();\
				break;\
			case IDRETRY:\
				break;\
			case IDIGNORE:\
				assertIgnored = true;\
				break;\
			}\
		}\
	}

	#define Assert( _cond ) if(!(_cond)) AssertMessage( "Assert failed: " #_cond );
	#define Verify( _cond, _msg ) if(!(_cond)) AssertMessage( "Assert failed: " #_cond "\n" _msg );
	#define Error( _msg ) AssertMessage( _msg )
	#define VerifyF( _cond, _msgFormat, ... ) \
	{\
		if(!(_cond))\
		{\
			char messageBuffer[2048];\
			sprintf_s(messageBuffer, "Assert failed: %s\n" _msgFormat, #_cond, __VA_ARGS__);\
			AssertMessage(messageBuffer);\
		}\
	}
	#define ErrorF( _msgFormat, ...  )\
	{\
		char messageBuffer[2048];\
		sprintf_s(messageBuffer, _msgFormat, __VA__ARGS__);\
		AssertMessage(messageBuffer);\
	}
#else
	#define Assert( _cond )
	#define Verify( _cond, _msg )
	#define VerifyF( _cond, _msg )
	#define Error( _msg )
	#define ErrorF( _msg )
#endif

//---------------------------------------------------------------------------------

enum eStaticInitLayer
{
	eStaticInitLayer_Heap,
	eStaticInitLayer_Core,
	eStaticInitLayer_Other,

	eStaticInitLayer_Num
};

class StaticInitableBase
{
public:
	static void StaticInit();
	static void StaticShutdown();
protected:
	StaticInitableBase(uint32 _layer);

	virtual void _StaticInit() = 0;
	virtual void _StaticShutdown() = 0;
private:
	static StaticInitableBase *s_layerStart[eStaticInitLayer_Num];

	StaticInitableBase *m_next;
};

template <typename T, uint32 Layer>
class StaticInitableClass
{
public:
	StaticInitableClass();
private:	
	virtual void _StaticInit();
	virtual void _StaticShutdown();
};

template <typename T, uint32 Layer = StaticInitableBase::eStaticInitLayer_Other>
class StaticInitable
{
private:
	static StaticInitableClass<T, Layer> s_staticInitable;
};

#include "Utils.inl"