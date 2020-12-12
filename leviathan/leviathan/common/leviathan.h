#pragma once

// system header file include
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>
//

// utility header file include
#include "logger.h"
#include "singleton.h"
#include "random.h"
//

// common header file include
#include "minidump.h"

// control header file include
#include "server_control.h"
//

namespace Leviathan
{

class cScopeReadLock
{
public:
	cScopeReadLock() {}
	cScopeReadLock(SRWLOCK* _lock) { lock = _lock; AcquireSRWLockShared(lock); }
	~cScopeReadLock() { if (lock) ReleaseSRWLockShared(lock); }

private:
	SRWLOCK* lock;
};

class cScopeWriteLock
{
public:
	cScopeWriteLock() {}
	cScopeWriteLock(SRWLOCK* _lock) { lock = _lock; AcquireSRWLockExclusive(lock); }
	~cScopeWriteLock() { if (lock) ReleaseSRWLockExclusive(lock); }

private:
	SRWLOCK* lock;
};

class cLeviathan : public cServerControl, public cSingleton<cLeviathan>
{
public:
	cLeviathan() {}
	virtual ~cLeviathan() {}

private:

public:
	bool Booting(std::string config);
};

char* WideCharToMultiByte(const wchar_t* wstr);
std::string WideCharToMultiByte(const std::wstring& wstr);

wchar_t* MultiByteToWideChar(const char* str);
std::wstring MultiByteToWideChar(const std::string& str);
}