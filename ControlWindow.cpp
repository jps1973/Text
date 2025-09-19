// ControlWindow.cpp

#include "ControlWindow.h"

// Global variables
static HWND g_hWndControl;

BOOL IsControlWindow( HWND hWnd )
{
	// See if supplied window is control window
	return( hWnd == g_hWndControl );

} // End of function IsControlWindow

BOOL ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Load rich edit library
	if( LoadLibrary( RICH_EDIT_LIBRARY_NAME ) )
	{
		// Successfully loaded rich edit library

		// Create control window
		g_hWndControl = CreateWindowEx( CONTROL_WINDOW_EXTENDED_STYLE, CONTROL_WINDOW_CLASS_NAME, CONTROL_WINDOW_TEXT, CONTROL_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

		// Ensure that control window was created
		if( g_hWndControl )
		{
			// Successfully created control window
			HFONT hFont;

			// Get default fixed font
			hFont = ( HFONT )GetStockObject( ANSI_FIXED_FONT );

			// Set control window font
			SendMessage( g_hWndControl, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

			// Update return value
			bResult = TRUE;

		} // End of successfully created control window

	} // End of successfully loaded rich edit library

	return bResult;

} // End of function ControlWindowCreate

BOOL ControlWindowGetRect( LPRECT lpRect )
{
	// Get control window rect
	return GetWindowRect( g_hWndControl, lpRect );

} // End of function ControlWindowGetRect

BOOL ControlWindowHandleCommandMessage( WPARAM wParam, LPARAM )
{
	BOOL bResult = FALSE;

	// Select control window notification code
	switch( HIWORD( wParam ) )
	{
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for control window notification code

	return bResult;

} // End of function ControlWindowHandleCommandMessage

BOOL ControlWindowHandleNotifyMessage( WPARAM, LPARAM lParam )
{
	BOOL bResult = FALSE;

	LPNMHDR lpNmhdr;

	// Get notify message handler
	lpNmhdr = ( ( LPNMHDR )lParam );

	// Select control window notification code
	switch( lpNmhdr->code )
	{
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for control window notification code

	return bResult;

} // End of function ControlWindowHandleNotifyMessage

BOOL ControlWindowMove( DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, BOOL bRepaint )
{
	// Move control window
	return MoveWindow( g_hWndControl, dwX, dwY, dwWidth, dwHeight, bRepaint );

} // End of function ControlWindowMove

BOOL ControlWindowLoad( LPCTSTR lpszFileName )
{
	BOOL bResult = 0;

	HANDLE hFile;

	// Open file
	hFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that file was opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file
		DWORD dwFileSize;

		// Get file size
		dwFileSize = GetFileSize( hFile, NULL );

		// Ensure that file size was got
		if( dwFileSize != INVALID_FILE_SIZE )
		{
			// Successfully got file size

			// Allocate string memory
			LPTSTR lpszFileText = new char[ dwFileSize + sizeof( char ) ];

			// Read file text
			if( ReadFile( hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Use file text as window text
				SendMessage( g_hWndControl, WM_SETTEXT, ( WPARAM )NULL, ( LPARAM )lpszFileText );

				// Update return value
				bResult = TRUE;

			} // End of successfully read file text

			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function ControlWindowLoad

BOOL ControlWindowSave( LPCTSTR lpszFileName )
{
	BOOL bResult = 0;

	HANDLE hFile;

	// Create file
	hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was created
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file
		DWORD dwWindowTextLength;

		// Get window text length
		dwWindowTextLength = SendMessage( g_hWndControl, WM_GETTEXTLENGTH, ( WPARAM )NULL, ( LPARAM )NULL );

		// Ensure that window contains text
		if( dwWindowTextLength > 0 )
		{
			// Window contains text
			DWORD dwBufferLength = ( dwWindowTextLength + sizeof( char ) );

			// Allocate string memory
			LPTSTR lpszWindowText = new char[ dwBufferLength ];

			// Get window text
			if( SendMessage( g_hWndControl, WM_GETTEXT, ( WPARAM )dwBufferLength, ( LPARAM )lpszWindowText ) )
			{
				// Successfully got window text

				// Write window text to file
				if( WriteFile( hFile, lpszWindowText, dwBufferLength, NULL, NULL ) )
				{
					// Successfully wrote window text to file

					// Update return value
					bResult = TRUE;

				} // End of successfully wrote window text to file

			} // End of successfully got window text

			// Free string memory
			delete [] lpszWindowText;

		} // End of window contains text
		else
		{
			// Window contains no text

			// Update return value
			bResult = TRUE;

		} // End of window contains no text

		// Close file
		CloseHandle( hFile );

	} // End of successfully created file

	return bResult;

} // End of function ControlWindowSave

void ControlWindowSelectText( int nStart, int nEnd )
{
	// Select text
	SendMessage( g_hWndControl, EM_SETSEL, ( WPARAM )nStart, ( LPARAM )nEnd );

} // End of function ControlWindowSelectText

HWND ControlWindowSetFocus()
{
	// Focus on control window
	return SetFocus( g_hWndControl );

} // End of function ControlWindowSetFocus
