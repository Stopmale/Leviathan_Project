#pragma once

#include <Windows.h>
#include <DbgHelp.h>

namespace Leviathan
{
#define USER_DATA_BUFFER_SIZE (4096)

typedef bool (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE dumpType, 
											CONST PMINIDUMP_EXCEPTION_INFORMATION exceptionParam,
											CONST PMINIDUMP_USER_STREAM_INFORMATION userStreamparam,
											CONST PMINIDUMP_CALLBACK_INFORMATION callbackParam);

class cMinidump
{
public:
	cMinidump();

public:
	static cMinidump* dumper;

private:
	_EXCEPTION_POINTERS* exceptionInfo;
	TCHAR dumpPath[MAX_PATH];
	TCHAR appPath[MAX_PATH];
	TCHAR appBaseName[MAX_PATH];

private:
	static LONG WINAPI Handler(struct _EXCEPTION_POINTERS* _exceptionInfo);
	LONG WriteMiniDump(_EXCEPTION_POINTERS* _exceptionInfo);

protected:
	virtual void VSetDumpFileName();
	virtual MINIDUMP_USER_STREAM_INFORMATION* VGetUserStreamArray() { return NULL; }
	virtual const TCHAR* VGetUserMessage() { return NULL; }
};

}