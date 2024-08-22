// RichEditWindow.cpp

#include "RichEditWindow.h"

// Global variables
HWND g_hWndRichEdit;

BOOL IsRichEditWindow( HWND hWnd )
{
	// See if supplied window is rich edit window
	return( hWnd == g_hWndRichEdit );

} // End of function IsRichEditWindow

BOOL RichEditWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Load rich edit library
	if( LoadLibrary( RICH_EDIT_LIBRARY_NAME ) )
	{
		// Successfully loaded rich edit library

		// Create rich edit window
		g_hWndRichEdit = ::CreateWindowEx( RICH_EDIT_WINDOW_EXTENDED_STYLE, RICH_EDIT_WINDOW_CLASS_NAME, RICH_EDIT_WINDOW_TEXT, RICH_EDIT_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

		// Ensure that rich edit window was created
		if( g_hWndRichEdit )
		{
			// Successfully created rich edit window

			// Set text mode
			SendMessage( g_hWndRichEdit, EM_SETTEXTMODE, ( WPARAM )RICH_EDIT_WINDOW_TEXT_MODE, ( LPARAM )NULL );

			// Update return value
			bResult = TRUE;

		} // End of successfully created rich edit window

	} // End of successfully loaded rich edit library

	return bResult;

} // End of function RichEditWindowCreate

BOOL RichEditWindowGetRect( LPRECT lpRect )
{
	// Get rich edit window rect
	return ::GetWindowRect( g_hWndRichEdit, lpRect );

} // End of function RichEditWindowGetRect

BOOL RichEditWindowHandleCommandMessage( WPARAM wParam, LPARAM, void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	// Select rich edit window notification code
	switch( HIWORD( wParam ) )
	{
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for rich edit window notification code

	return bResult;

} // End of function RichEditWindowHandleCommandMessage

BOOL RichEditWindowLoadText( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

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
			LPTSTR lpszFileText = new char[ STRING_LENGTH + sizeof( char ) ];

			// Read file text
			if( ReadFile (hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Set rich edit window text
				if( SendMessage( g_hWndRichEdit, WM_SETTEXT, ( WPARAM )NULL, ( LPARAM )lpszFileText ) )
				{
					// Successfully set rich edit window text

					// Update return value
					bResult = TRUE;

				} // End of successfully set rich edit window text

			} // End of successfully read file text

			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function RichEditWindowLoadText

BOOL RichEditWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move rich edit window
	return ::MoveWindow( g_hWndRichEdit, nX, nY, nWidth, nHeight, bRepaint );

} // End of function RichEditWindowMove

BOOL RichEditWindowSaveText( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Open file
	hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file
		DWORD dwTextLength;

		// Get rich edit window text length
		dwTextLength = SendMessage( g_hWndRichEdit, WM_GETTEXTLENGTH, ( WPARAM )NULL, ( LPARAM )NULL );

		// Ensure that window is not empty
		if( dwTextLength )
		{
			// Window is not empty
			DWORD dwBufferLength;
			LPCTSTR lpszFileText;

			// Calculate buffer length
			dwBufferLength = ( dwTextLength + sizeof( char ) );

			// Allocate string memory
			lpszFileText = new char[ dwBufferLength ];

			// Get rich edit window text
			if( SendMessage( g_hWndRichEdit, WM_GETTEXT, ( WPARAM )dwBufferLength, ( LPARAM )lpszFileText ) )
			{
				// Successfully got rich edit window text

				// Write text to file
				if( WriteFile( hFile, lpszFileText, lstrlen( lpszFileText ), NULL, NULL ) )
				{
					// Successfully wrote text to file

					// Update return value
					bResult = TRUE;

				} // End of successfully wrote text to file

			} // End of successfully got rich edit window text

			// Free string memory
			delete [] lpszFileText;

		} // End of window is not empty

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function RichEditWindowSaveText

void RichEditWindowSelect( int nStart, int nEnd )
{
	// Select rich edit window text
	::SendMessage( g_hWndRichEdit, EM_SETSEL, ( WPARAM )nStart, ( LPARAM )nEnd );

} // End of function RichEditWindowSelect

HWND RichEditWindowSetFocus()
{
	// Focus on rich edit window
	return ::SetFocus( g_hWndRichEdit );

} // End of function RichEditWindowSetFocus

void RichEditWindowSetFont( HFONT hFont )
{
	// Set rich edit window font
	::SendMessage( g_hWndRichEdit, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function RichEditWindowSetFont
