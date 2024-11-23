// Registry.cpp

#include "Registry.h"

DWORD RegistryGetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKeyPath, LPCTSTR lpszValueName, DWORD dwDefaultValue )
{
	DWORD dwResult = dwDefaultValue;

	HKEY hKey;

	// Open registry key
	if( RegOpenKeyEx( hKeyTopLevel, lpszSubKeyPath, 0, KEY_QUERY_VALUE, &hKey ) == ERROR_SUCCESS )
	{
		// Successfully opened registry key
		DWORD dwSize;

		// Initialise size value
		dwSize = sizeof( DWORD );

		// Get registry value
		if( RegQueryValueEx( hKey, lpszValueName, NULL, NULL, reinterpret_cast<BYTE *>( &dwResult ), &dwSize ) != ERROR_SUCCESS )
		{
			// Unable to get registry value

			// Set result to default
			dwResult = dwDefaultValue;

		} // End of unable to get registry value

		// Close registry key
		RegCloseKey( hKey );

	} // End of successfully opened registry key

	return dwResult;

} // End of function RegistryGetValue

BOOL RegistrySetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKeyPath, LPCTSTR lpszValueName, DWORD dwValue )
{
	BOOL bResult = FALSE;

	HKEY hKey;

	// Create registry key
	if( RegCreateKeyEx( hKeyTopLevel, lpszSubKeyPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL ) == ERROR_SUCCESS )
	{
		// Successfully created registry key
		DWORD dwSize;

		// Initialise size value
		dwSize = sizeof( DWORD );

		// Set registry value
		if( RegSetValueEx( hKey, lpszValueName, 0, REG_DWORD, reinterpret_cast<BYTE *>( &( dwValue ) ), dwSize ) == ERROR_SUCCESS )
		{
			// Successfully got registry value

			// Update return value
			bResult = TRUE;

		} // End of successfully got registry value

		// Close registry key
		RegCloseKey( hKey );

	} // End of successfully created registry key

	return bResult;

} // End of function RegistrySetValue
