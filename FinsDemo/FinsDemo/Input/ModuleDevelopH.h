#ifndef __MODULE_DEVELOP_HEADER_H__
#define __MODULE_DEVELOP_HEADER_H__
#include <string>
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
//函数返回值见标准软件开发返回值规范
//////////////////////////////////////////////////////////////////////////


//CMgrDllDelegate方便调用者编写显示调用动态库函数
class CMgrDllDelegate
{
public:
	CMgrDllDelegate(std::string pDllPathFullName)
	{
		m_hLib=NULL;
		m_bFuncLoaded=FALSE;

		////
		SetLibName(pDllPathFullName);
	}
	virtual ~CMgrDllDelegate()
	{				
		ReleaseLib();
	}

	//设置动态库完整路径名称
	void SetLibName(std::string pDllPathFullName)
	{		
		m_pDllPathFullName = pDllPathFullName;		
	}

	//释放动态库
	void ReleaseLib()
	{
		if( NULL!=m_hLib )
		{
			::FreeLibrary(m_hLib);
			m_hLib=NULL;
		}
		m_bFuncLoaded=FALSE;
	}
		
	//创建接口指针
	DWORD DllCreateInterface(void** ppInterface, long nInterfaceNo = 0)
	{
		DWORD rlt = 0x00;
		if( !_LoadFunc() )
		{
			rlt = _HandleErrInLoadFunc();
		}
		else
		{
			rlt = ((DWORD (__stdcall*)(void**, long)) m_pfnCreateInterface)(ppInterface, nInterfaceNo);
		}
		////
		return rlt;
	}


protected:
	virtual void _DoLoadFunc()
	{		
		m_pfnCreateInterface = (void*) ::GetProcAddress((HMODULE) m_hLib, (LPCSTR) "DllCreateInterface");
		
	}
		
	virtual void _DoCorrectFuncLoadedFlag()
	{
		m_bFuncLoaded = (NULL != m_pfnCreateInterface);

	}

	DWORD _HandleErrInLoadFunc()
	{
		DWORD rlt=0x00;
		if( NULL==_GetLibModule() )
		{//动态库载入失败
			rlt = 0x80000004;
		}
		else
		{
			rlt = 0x80000005;
		}
		return rlt;
	}


	BOOL _LoadFunc()
	{
		if( !_IsFuncLoaded() )
		{
			if( !__LoadLib() )
				return FALSE;
			////
			_DoLoadFunc();
			
			////
			_DoCorrectFuncLoadedFlag();
			return _IsFuncLoaded();
		}
		////
		return TRUE;
	}

	BOOL _IsFuncLoaded() const{
		return m_bFuncLoaded;
	}

	HMODULE _GetLibModule() const{
		return m_hLib;
	}

private:
	BOOL __LoadLib()
	{
		if( NULL==m_hLib )
		{
			m_hLib = ::LoadLibrary(m_pDllPathFullName.c_str());
		}
		return (NULL!=m_hLib);
	}

protected:
	BOOL m_bFuncLoaded;
	std::string m_pDllPathFullName;
	HMODULE m_hLib;

	////
	void* m_pfnCreateInterface;
};

#endif









