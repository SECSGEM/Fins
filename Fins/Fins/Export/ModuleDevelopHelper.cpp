#include "stdafx.h"
#include <tchar.h>
#include "Handle/FinsReadWrite.h"


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) DWORD __stdcall DllCreateInterface(void** ppInterface, long nInterfaceNo)
{	
	if( NULL==ppInterface )
	{
		return 1;
	}
	*ppInterface = NULL;
	////	
	////�˴���ӽӿڴ�������	
	try
	{
			CInterfaceExport* pObject = new CFinsReadWrite;		
			*ppInterface = (void*) (static_cast<CInterfaceExport*>(pObject));
	}
	catch (...)
	{
		*ppInterface = NULL;
	}
	////
	return 0x00;
}
