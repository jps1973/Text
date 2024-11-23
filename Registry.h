// Registry.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

DWORD RegistryGetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKeyPath, LPCTSTR lpszValueName, DWORD dwDefaultValue );

BOOL RegistrySetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKeyPath, LPCTSTR lpszValueName, DWORD dwValue );
