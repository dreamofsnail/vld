////////////////////////////////////////////////////////////////////////////////
//  $Id: utility.h,v 1.4 2006/01/22 04:27:01 db Exp $
//
//  Visual Leak Detector (Version 1.0)
//  Copyright (c) 2005 Dan Moulding
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation; either version 2.1 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  See COPYING.txt for the full terms of the GNU Lesser General Public License.
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef VLDBUILD
#error "This header should only be included by Visual Leak Detector when building it from source. Applications should never include this header."
#endif

#include <cstdio>
#include <windows.h>

#ifdef _WIN64
#define ADDRESSFORMAT   L"0x%.16X" // Format string for 64-bit addresses
#else
#define ADDRESSFORMAT   L"0x%.8X"  // Format string for 32-bit addresses
#endif // _WIN64
#define BOM             0xFEFF     // Unicode byte-order mark.
#define MAXREPORTLENGTH 511        // Maximum length, in characters, of "report" messages.

// Architecture-specific definitions for x86 and x64
#if defined(_M_IX86)
#define SIZEOFPTR 4
#define X86X64ARCHITECTURE IMAGE_FILE_MACHINE_I386
#define AXREG Eax
#define BPREG Ebp
#define IPREG Eip
#define SPREG Esp
#elif defined(_M_X64)
#define SIZEOFPTR 8
#define X86X64ARCHITECTURE IMAGE_FILE_MACHINE_AMD64
#define AXREG Rax
#define BPREG Rbp
#define IPREG Rip
#define SPREG Rsp
#endif // _M_IX86

// Relative Virtual Address to Virtual Address conversion.
#define R2VA(modulebase, rva) (((PBYTE)modulebase) + rva)

// Reports can be encoded as either ASCII or Unicode (UTF-16).
enum encoding_e {
    ascii,
    unicode
};

// Utility functions. See function definitions for details.
LPCWSTR booltostr (BOOL b);
VOID dumpmemorya (LPCVOID address, SIZE_T length);
VOID dumpmemoryw (LPCVOID address, SIZE_T length);
#if defined(_M_IX86) || defined(_M_X64)
SIZE_T getprogramcounterx86x64 ();
#endif // _M_IX86 || _M_X64
VOID patchimport (HMODULE importmodule, LPCSTR exportmodulename, LPCSTR importname, LPCVOID replacement);
VOID report (LPCWSTR format, ...);
VOID restoreimport (HMODULE importmodule, LPCSTR exportmodulename, LPCSTR importname, LPCVOID replacement);
VOID setreportencoding (encoding_e encoding);
VOID setreportfile (FILE *file, BOOL copydebugger);
VOID strapp (LPWSTR *dest, LPCWSTR source);
BOOL strtobool (LPCWSTR s);
