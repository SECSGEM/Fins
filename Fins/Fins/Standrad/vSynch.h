#ifndef __VSYNCH_H__
#define __VSYNCH_H__


#include <windows.h>

///////////////抽象基类，不能实例化
class vLockObject
{
public:
	vLockObject(){}
	virtual ~vLockObject(){}
	virtual void Lock(int nType=0)=0;//0==vLocker::eLocker
	virtual void UnLock(int nType=0)=0;//0==vLocker::eLocker
};

/////////////////锁辅助类
class vLocker
{
public:
	enum
	{
		eLocker=0,
		eLockerRead,
		eLockerChange,
	};
public:
	vLocker(vLockObject* pLock=NULL,int nType=vLocker::eLocker)
	{
		m_nLockType=nType;
		m_pLock=pLock;
		if( m_pLock!=NULL )
			m_pLock->Lock(m_nLockType);
	}
	~vLocker()
	{
		if( m_pLock!=NULL )
			m_pLock->UnLock(m_nLockType);
	}

private:
	int m_nLockType;
	vLockObject* m_pLock;
};

////////////////目前做了两个简易同步类
////临界区
class vCritical : public vLockObject
{
public:
	vCritical()
	{
		::InitializeCriticalSection(&m_criticalSection);
	}
	virtual ~vCritical()
	{
		::DeleteCriticalSection(&m_criticalSection);
	}
	void Lock(int nType=vLocker::eLocker)
	{
		::EnterCriticalSection(&m_criticalSection);
	}
	void UnLock(int nType=vLocker::eLocker)
	{
		::LeaveCriticalSection(&m_criticalSection);
	}

private:
	CRITICAL_SECTION m_criticalSection;
};

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
#endif
