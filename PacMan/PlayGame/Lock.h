#pragma once

#include <Windows.h>

class Lock
{
public:
	Lock()
	{
		InitializeCriticalSection(&_cs);
	}

	~Lock()
	{
		DeleteCriticalSection(&_cs);
	}

	void Enter()
	{
		EnterCriticalSection(&_cs);
	}

	void Leave()
	{
		LeaveCriticalSection(&_cs);
	}

private:
	CRITICAL_SECTION _cs;
};

class LockGuard
{
public:
	LockGuard(Lock& lock) : _lock(lock)
	{
		_lock.Enter();
	}

	~LockGuard()
	{
		_lock.Leave();
	}
private:
	Lock& _lock;
};