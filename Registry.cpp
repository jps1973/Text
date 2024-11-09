// Registry.cpp

#include "Registry.h"

DWORD RegistryGetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, LPCTSTR lpszValueName )
{
	DWORD dwResult = 0;

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
