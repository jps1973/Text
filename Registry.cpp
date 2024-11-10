// Registry.cpp

#include "Registry.h"

DWORD RegistryGetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, LPCTSTR lpszValueName, DWORD dwDefaultValue )
{
	DWORD dwResult = dwDefaultValue;

	HKEY hKey;

	// Open registry key
	if( RegOpenKeyEx( hKeyTopLevel, lpszSubKey, 0, KEY_READ, &hKey ) == ERROR_SUCCESS )
	{
		// Successfully opened registry key
		DWORD dwDataSize = sizeof( DWORD );

		// Get registry value
		RegQueryValueEx( hKey, lpszValueName, 0, NULL, ( LPBYTE )&dwResult, &dwDataSize );

		// Close registry key
		RegCloseKey( hKey );

	} // End of successfully opened registry key

	return dwResult;

} // End of function RegistryGetValue

BOOL RegistrySaveWindowPosition( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, HWND hWnd )
{
	BOOL bResult = FALSE;

	DWORD dwLeft;
	DWORD dwTop;
	DWORD dwWidth;
	DWORD dwHeight;
	RECT rcWindow;

	// Get window rect
	if( GetWindowRect( hWnd, &rcWindow ) )
	{
		// Successfully got window rect

		// Store window position
		dwLeft	= rcWindow.left;
		dwTop	= rcWindow.top;

		// Calculate window size
		dwWidth		= ( rcWindow.right - rcWindow.left );
		dwHeight	= ( rcWindow.bottom - rcWindow.top );

		// Stave window position on registry
		RegistrySetValue( hKeyTopLevel, lpszSubKey, REGISTRY_LEFT_VALUE_NAME,	dwLeft );
		RegistrySetValue( hKeyTopLevel, lpszSubKey, REGISTRY_TOP_VALUE_NAME,	dwTop );
		RegistrySetValue( hKeyTopLevel, lpszSubKey, REGISTRY_WIDTH_VALUE_NAME,	dwWidth );
		RegistrySetValue( hKeyTopLevel, lpszSubKey, REGISTRY_HEIGHT_VALUE_NAME,	dwHeight );

		// Update return value
		bResult = TRUE;

	} // End of successfully got window rect

	return bResult;

} // End of function RegistrySaveWindowPosition

DWORD RegistrySetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, LPCTSTR lpszValueName, DWORD dwValue )
{
	DWORD dwResult = 0;

	HKEY hKey;

	// Open registry key
	if( RegOpenKeyEx( hKeyTopLevel, lpszSubKey, 0, KEY_ALL_ACCESS, &hKey ) == ERROR_SUCCESS )
	{
		// Successfully opened registry key

		// Get registry value
		RegSetValueEx( hKey, lpszValueName, 0, REG_DWORD, ( LPBYTE )&dwValue,  sizeof( DWORD ) );

		// Close registry key
		RegCloseKey( hKey );

	} // End of successfully opened registry key

	return dwResult;

} // End of function RegistrySetValue

/*
https://stackoverflow.com/questions/5437800/setting-a-dword-value-in-the-registry

RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\pager", 0, KEY_ALL_ACCESS, &hKey);
DWORD value=0;
RegSetValueEx(hKey, TEXT("Save"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
RegCloseKey(hKey);
*/