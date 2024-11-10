// Registry.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define REGISTRY_LEFT_VALUE_NAME												"Left"
#define REGISTRY_TOP_VALUE_NAME													"Top"
#define REGISTRY_WIDTH_VALUE_NAME												"Width"
#define REGISTRY_HEIGHT_VALUE_NAME												"Height"

DWORD RegistryGetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, LPCTSTR lpszValueName, DWORD dwDefaultValue );

BOOL RegistrySaveWindowPosition( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, HWND hWnd );

DWORD RegistrySetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, LPCTSTR lpszValueName, DWORD dwValue );
