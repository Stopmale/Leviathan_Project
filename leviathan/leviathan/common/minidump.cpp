#include "minidump.h"
#include <time.h>
#include <iostream>

Leviathan::cMinidump *Leviathan::cMinidump::dumper = NULL;

Leviathan::cMinidump::cMinidump()
{
	if (!dumper)
	{
		SetUnhandledExceptionFilter(Handler);
		dumper = this;
	}
}

LONG __stdcall Leviathan::cMinidump::Handler(_EXCEPTION_POINTERS* _exceptionInfo)
{
	LONG retvel = EXCEPTION_CONTINUE_SEARCH;
	if (!dumper)
		return retvel;

	return dumper->WriteMiniDump(_exceptionInfo);
}

LONG Leviathan::cMinidump::WriteMiniDump(_EXCEPTION_POINTERS* _exceptionInfo)
{
	LONG retvel = EXCEPTION_CONTINUE_SEARCH;

	exceptionInfo = _exceptionInfo;
	
	HMODULE dll = NULL;
	TCHAR dbgPath[_MAX_PATH];
	if (GetModuleFileName(NULL, appPath, _MAX_PATH))
	{
		TCHAR* slash = wcsrchr(appPath, '\\');
		if (slash)
		{
			wcscpy_s(appBaseName, slash + 1);
			*(slash + 1) = 0;
		}
		
		wcscpy_s(dbgPath, appPath);
		wcscat_s(dbgPath, L"DBGHELP.DLL");
		dll = ::LoadLibrary(dbgPath);
	}

	if (dll == NULL)
		dll = ::LoadLibrary(L"DBGHELP.DLL");

	LPCTSTR szResult;
	if (dll)
	{
		MINIDUMPWRITEDUMP pMiniDupmWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(dll, "MiniDumpWriteDump");
		if (pMiniDupmWriteDump)
		{
			TCHAR szScratch[USER_DATA_BUFFER_SIZE];
			VSetDumpFileName();

			HANDLE hFile = ::CreateFile(dumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				_MINIDUMP_EXCEPTION_INFORMATION exInfo;
				exInfo.ThreadId = ::GetCurrentThreadId();
				exInfo.ExceptionPointers = exceptionInfo;
				exInfo.ClientPointers = NULL;

				MINIDUMP_TYPE dumpType;
				dumpType = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory | MiniDumpWithDataSegs | MiniDumpWithHandleData |
					MiniDumpWithFullMemoryInfo | MiniDumpWithThreadInfo | MiniDumpWithUnloadedModules);

				bool bOK = pMiniDupmWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, dumpType, &exInfo, VGetUserStreamArray(), NULL);
				if (bOK)
				{
					szResult = NULL;
					retvel = EXCEPTION_EXECUTE_HANDLER;
				}
				else
				{
					wsprintf(szScratch, L"Failed to save dump file to '%s' (error %d)", dumpPath, GetLastError());
					szResult = szScratch;
				}
				::CloseHandle(hFile);
			}
			else
			{
				wsprintf(szScratch, L"Failed to create dump file '%s' (error %d)", dumpPath, GetLastError());
				szResult = szScratch;
			}
		}
		else
		{
			szResult = L"DBGHLEP.DLL too old";
		}
	}
	else
	{
		szResult = L"DBGHELP.DLL not found";
	}


	if (szResult)
		::MessageBox(NULL, szResult, NULL, MB_OK);

	TerminateProcess(GetCurrentProcess(), 0);
	return retvel;
}

void Leviathan::cMinidump::VSetDumpFileName()
{
	time_t curTime;
	time(&curTime);

	std::basic_string<TCHAR> path;
	path = appBaseName;
	path += L'.';
	path += _wctime(&curTime);
	path += L".dump";

	// "\n\0" 문자 삭제
	{
		std::basic_string<TCHAR>::size_type pos = path.find(L"\n\0");
		path.erase(pos, 1);
	}

	// : 문자 _로 변경
	while (true)
	{
		std::basic_string<TCHAR>::size_type pos = path.find(L":");
		if (pos != std::basic_string<TCHAR>::npos)
			path.replace(pos, 1, L"_");
		else
			break;
	}

	path = appPath + path;
	wsprintf(dumpPath, L"%s", path.c_str());

	wprintf(L"%s", dumpPath);
}
