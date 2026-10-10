/*
	tlhelp32.h - Include file for Tool help functions.

	Written by Mumit Khan <khan@nanotech.wisc.edu>

	This file is part of a free library for the Win32 API. 

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/
#ifndef _TLHELP32_H
#define _TLHELP32_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif
#define HF32_DEFAULT	1
#define HF32_SHARED	2
#define LF32_FIXED	0x1
#define LF32_FREE	0x2
#define LF32_MOVEABLE	0x4
#define MAX_MODULE_NAME32	255
#define TH32CS_SNAPHEAPLIST	0x1
#define TH32CS_SNAPPROCESS	0x2
#define TH32CS_SNAPTHREAD	0x4
#define TH32CS_SNAPMODULE	0x8
#define TH32CS_GETALLMODS      0x80000000
#define TH32CS_SNAPALL	(TH32CS_SNAPHEAPLIST|TH32CS_SNAPPROCESS|TH32CS_SNAPTHREAD|TH32CS_SNAPMODULE)
#define TH32CS_INHERIT	0x80000000
typedef struct tagHEAPLIST32 {
	DWORD dwSize;
	DWORD th32ProcessID;
	DWORD th32HeapID;
	DWORD dwFlags;
} HEAPLIST32,*PHEAPLIST32,*LPHEAPLIST32;
typedef struct tagHEAPENTRY32 {
	DWORD dwSize;
	HANDLE hHandle;
	DWORD dwAddress;
	DWORD dwBlockSize;
	DWORD dwFlags;
	DWORD dwLockCount;
	DWORD dwResvd;
	DWORD th32ProcessID;
	DWORD th32HeapID;
} HEAPENTRY32,*PHEAPENTRY32,*LPHEAPENTRY32;
typedef struct tagPROCESSENTRY32W {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
	WCHAR szExeFile[MAX_PATH];
} PROCESSENTRY32W,*PPROCESSENTRY32W,*LPPROCESSENTRY32W;
typedef struct tagPROCESSENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
#ifdef _WIN32_WCE
	WCHAR szExeFile[MAX_PATH];
	DWORD th32MemoryBase;
	DWORD th32AccessKey;
#else
	CHAR  szExeFile[MAX_PATH];
#endif
} PROCESSENTRY32,*PPROCESSENTRY32,*LPPROCESSENTRY32;
typedef struct tagTHREADENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ThreadID;
	DWORD th32OwnerProcessID;
	LONG tpBasePri;
	LONG tpDeltaPri;
	DWORD dwFlags;
#ifdef _WIN32_WCE
	DWORD th32AccessKey;
	DWORD th32CurrentProcessID;
#endif
} THREADENTRY32,*PTHREADENTRY32,*LPTHREADENTRY32;
typedef struct tagMODULEENTRY32W {
	DWORD dwSize;
	DWORD th32ModuleID;
	DWORD th32ProcessID;
	DWORD GlblcntUsage;
	DWORD ProccntUsage;
	BYTE *modBaseAddr;
	DWORD modBaseSize;
	HMODULE hModule; 
	WCHAR szModule[MAX_MODULE_NAME32 + 1];
	WCHAR szExePath[MAX_PATH];
} MODULEENTRY32W,*PMODULEENTRY32W,*LPMODULEENTRY32W;
typedef struct tagMODULEENTRY32 {
	DWORD dwSize;
	DWORD th32ModuleID;
	DWORD th32ProcessID;
	DWORD GlblcntUsage;
	DWORD ProccntUsage;
	BYTE *modBaseAddr;
	DWORD modBaseSize;
	HMODULE hModule;
#ifdef _WIN32_WCE
       WCHAR szModule[MAX_PATH];
	WCHAR szExePath[MAX_PATH];
	DWORD dwFlags;
#else
	CHAR szModule[MAX_MODULE_NAME32 + 1];
	CHAR szExePath[MAX_PATH];
#endif
} MODULEENTRY32,*PMODULEENTRY32,*LPMODULEENTRY32;
#ifdef _WIN32_WCE
/**
 * Retrieves the first block in a process heap.
 *
 * Set lphe->dwSize to the size of HEAPENTRY32 before calling. Use
 * Heap32Next to continue through the heap.
 *
 * @param hSnapshot Snapshot containing heap information.
 * @param lphe Receives the heap entry.
 * @param th32ProcessID Process that owns the heap.
 * @param th32HeapID Heap identifier.
 * @return TRUE when an entry is copied; FALSE on failure. GetLastError
 *         returns ERROR_NO_MORE_FILES for an invalid or empty heap.
 */
BOOL WINAPI Heap32First(HANDLE hSnapshot,LPHEAPENTRY32 lphe,DWORD th32ProcessID,DWORD th32HeapID);
#else
BOOL WINAPI Heap32First(LPHEAPENTRY32,DWORD,DWORD);
#endif
/**
 * Retrieves the first heap in a process heap list.
 *
 * Set lphl->dwSize to the size of HEAPLIST32 before calling. Use
 * Heap32ListNext to enumerate more heaps.
 *
 * @param hSnapshot Snapshot containing heap information.
 * @param lphl Receives the heap list entry.
 * @return TRUE when an entry is copied; FALSE on failure. GetLastError
 *         returns ERROR_NO_MORE_FILES if no list is available.
 */
BOOL WINAPI Heap32ListFirst(HANDLE hSnapshot,LPHEAPLIST32 lphl);
/**
 * Retrieves the next heap in a snapshot's heap list.
 *
 * Call Heap32ListFirst to retrieve the first entry.
 *
 * @param hSnapshot Snapshot containing the heap list.
 * @param lphl Receives the next heap entry.
 * @return TRUE when an entry is copied; FALSE when no more entries exist
 *         or an error occurs. GetLastError returns ERROR_NO_MORE_FILES at
 *         the end.
 */
BOOL WINAPI Heap32ListNext(HANDLE hSnapshot,LPHEAPLIST32 lphl);
#ifdef _WIN32_WCE
/**
 * Retrieves the next block in a heap.
 *
 * Call Heap32First to retrieve the first block.
 *
 * @param hSnapshot Snapshot containing the heap.
 * @param lphe Receives the next heap block.
 * @return TRUE when an entry is copied; FALSE when no more blocks exist
 *         or an error occurs. GetLastError returns ERROR_NO_MORE_FILES at
 *         the end and ERROR_INVALID_DATA if the heap walk cannot continue.
 */
BOOL WINAPI Heap32Next(HANDLE hSnapshot,LPHEAPENTRY32 lphe);
#else
BOOL WINAPI Heap32Next(LPHEAPENTRY32);
#endif
/**
 * Retrieves the first module recorded for a process in a snapshot.
 *
 * Set lpme->dwSize to the size of MODULEENTRY32 before calling. Use
 * Module32Next to continue the enumeration.
 *
 * @param hSnapshot Snapshot containing module information.
 * @param lpme Receives the module entry.
 * @return TRUE when an entry is copied; FALSE on failure. GetLastError
 *         returns ERROR_NO_MORE_FILES if the snapshot has no modules.
 */
BOOL WINAPI Module32First(HANDLE hSnapshot,LPMODULEENTRY32 lpme);
BOOL WINAPI Module32FirstW(HANDLE,LPMODULEENTRY32W);
/**
 * Retrieves the next module in a snapshot.
 *
 * Call Module32First to retrieve the first entry.
 *
 * @param hSnapshot Snapshot containing module information.
 * @param lpme Receives the next module entry.
 * @return TRUE when an entry is copied; FALSE when no more modules exist
 *         or an error occurs.
 */
BOOL WINAPI Module32Next(HANDLE hSnapshot,LPMODULEENTRY32 lpme);
BOOL WINAPI Module32NextW(HANDLE,LPMODULEENTRY32W);
/**
 * Retrieves the first process recorded in a system snapshot.
 *
 * Set lppe->dwSize to the size of PROCESSENTRY32 before calling. Use
 * Process32Next to continue the enumeration.
 *
 * @param hSnapshot Snapshot containing process information.
 * @param lppe Receives the process entry.
 * @return TRUE when an entry is copied; FALSE on failure. GetLastError
 *         returns ERROR_NO_MORE_FILES if the snapshot has no processes.
 */
BOOL WINAPI Process32First(HANDLE hSnapshot,LPPROCESSENTRY32 lppe);
BOOL WINAPI Process32FirstW(HANDLE,LPPROCESSENTRY32W);
/**
 * Retrieves the next process in a system snapshot.
 *
 * Call Process32First to retrieve the first entry.
 *
 * @param hSnapshot Snapshot containing process information.
 * @param lppe Receives the next process entry.
 * @return TRUE when an entry is copied; FALSE when no more processes exist
 *         or an error occurs.
 */
BOOL WINAPI Process32Next(HANDLE hSnapshot,LPPROCESSENTRY32 lppe);
BOOL WINAPI Process32NextW(HANDLE,LPPROCESSENTRY32W);
/**
 * Retrieves the first thread recorded in a system snapshot.
 *
 * Set lpte->dwSize to the size of THREADENTRY32 before calling. Use
 * Thread32Next to continue the enumeration.
 *
 * @param hSnapshot Snapshot containing thread information.
 * @param lpte Receives the thread entry.
 * @return TRUE when an entry is copied; FALSE on failure. GetLastError
 *         returns ERROR_NO_MORE_FILES if the snapshot has no threads.
 */
BOOL WINAPI Thread32First(HANDLE hSnapshot,LPTHREADENTRY32 lpte);
/**
 * Retrieves the next thread in a system snapshot.
 *
 * Call Thread32First to retrieve the first entry.
 *
 * @param hSnapshot Snapshot containing thread information.
 * @param lpte Receives the next thread entry.
 * @return TRUE when an entry is copied; FALSE when no more threads exist
 *         or an error occurs.
 */
BOOL WINAPI Thread32Next(HANDLE hSnapshot,LPTHREADENTRY32 lpte);
/**
 * Copies bytes from a process address space into the caller's buffer.
 *
 * The system verifies the entire requested range is readable before
 * copying. A process ID of zero selects the current process.
 *
 * @param th32ProcessID Process to read, or 0 for the current process.
 * @param lpBaseAddress Address in the target process.
 * @param lpBuffer Receives the copied bytes.
 * @param cbRead Number of bytes to read.
 * @param lpNumberOfBytesRead Receives the number copied, or NULL.
 * @return TRUE on success, FALSE on failure.
 */
BOOL WINAPI Toolhelp32ReadProcessMemory(DWORD th32ProcessID,LPCVOID lpBaseAddress,LPVOID lpBuffer,DWORD cbRead,LPDWORD lpNumberOfBytesRead);
/**
 * Captures a read-only snapshot of processes, threads, modules or heaps.
 *
 * Choose the included data with TH32CS_SNAP* flags. The process ID is
 * used for heap or module snapshots; zero selects the current process.
 * Close the result with CloseToolhelp32Snapshot, not CloseHandle.
 *
 * @param dwFlags Snapshot data to include.
 * @param th32ProcessID Process to snapshot for heap or module data, or 0
 *                       for the current process.
 * @return Snapshot handle, or INVALID_HANDLE_VALUE on failure. Use
 *         GetLastError for details.
 */
HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags,DWORD th32ProcessID);
#if (_WIN32_WCE >= 0x200)
/**
 * Closes a Tool Help snapshot and releases its system resources.
 *
 * @param hSnapshot Snapshot to close.
 * @return TRUE on success, FALSE on failure.
 */
BOOL WINAPI CloseToolhelp32Snapshot(HANDLE hSnapshot);
#endif
#if defined(UNICODE) && !defined(_WIN32_WCE)
#define LPMODULEENTRY32 LPMODULEENTRY32W
#define LPPROCESSENTRY32 LPPROCESSENTRY32W
#define MODULEENTRY32 MODULEENTRY32W
#define Module32First Module32FirstW
#define Module32Next Module32NextW
#define PMODULEENTRY32 PMODULEENTRY32W
#define PPROCESSENTRY32 PPROCESSENTRY32W
#define PROCESSENTRY32 PROCESSENTRY32W
#define Process32First Process32FirstW
#define Process32Next Process32NextW
#endif /* UNICODE && !_WIN32_WCE */
#ifdef __cplusplus
}
#endif
#endif /* _TLHELP32_H */

