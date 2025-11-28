// RichTextWindow.cpp

#include "RichTextWindow.h"

// Global variables
HMODULE g_hModuleRichEdit;
HWND g_hWndRichEdit;
LPTSTR g_lpszFilePath;

BOOL RichTextWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont )
{
	BOOL bResult = FALSE;

	// Load rich edit library
	g_hModuleRichEdit = LoadLibrary( RICH_EDIT_LIBRARY_NAME );

	// Ensure that rich edit library was loaded
	if( g_hModuleRichEdit )
	{
		// Successfully loaded rich edit library

		// Create rich edit window
		g_hWndRichEdit = CreateWindowEx( RICH_TEXT_WINDOW_EXTENDED_STYLE, RICH_TEXT_WINDOW_CLASS_NAME, RICH_TEXT_WINDOW_TEXT, RICH_TEXT_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

		// Ensure that rich edit window was created
		if( g_hWndRichEdit )
		{
			// Successfully created rich edit window

			// Set rich edit window font
			SendMessage( g_hWndRichEdit, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

			// Set rich edit window text mode
			SendMessage( g_hWndRichEdit, EM_SETTEXTMODE, ( WPARAM )RICH_TEXT_WINDOW_TEXT_MODE, ( LPARAM )NULL );

			// Set rich edit window event mask
			SendMessage( g_hWndRichEdit, EM_SETEVENTMASK, ( WPARAM )NULL, ( LPARAM )RICH_TEXT_WINDOW_EVENT_MASK );

			// Allocate global string memory
			g_lpszFilePath = new char[ STRING_LENGTH + sizeof( char ) ];

			// Clear global file path
			g_lpszFilePath[ 0 ] = ( char )NULL;

		} // End of successfully created rich edit window

	} // End of successfully loaded rich edit library

	return bResult;

} // End of function RichTextWindowCreate

BOOL RichTextWindowFreeMemory()
{
	BOOL bResult = FALSE;

	// Ensure that rich edit library is valid
	if( g_hModuleRichEdit )
	{
		// Rich edit library is valid

		// Free memory
		bResult = FreeLibrary( g_hModuleRichEdit );

	} // End of rich edit library is valid

	// Free global string memory
	delete [] g_lpszFilePath;

	return bResult;

} // End of function RichTextWindowFreeMemory

BOOL RichTextWindowLoad( HWND hWndParent )
{
	BOOL bResult = FALSE;

	OPENFILENAME ofn;

	// Allocate string memory
	LPTSTR lpszFilePath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear file path
	lpszFilePath[ 0 ] = ( char )NULL;

	// Clear open file name structure
	ZeroMemory( &ofn, sizeof( ofn ) );

	// Initialise open file name structure
	ofn.lStructSize		= sizeof( ofn );
	ofn.hwndOwner		= hWndParent;
	ofn.lpstrFilter		= RICH_TEXT_WINDOW_FILTER;
	ofn.lpstrFile		= lpszFilePath;
	ofn.nMaxFile		= STRING_LENGTH;
	ofn.Flags			= ( OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY );
	ofn.lpstrDefExt		= RICH_TEXT_WINDOW_DEFAULT_EXTENSION;

	// Get open file name
	if( GetOpenFileName( &ofn ) )
	{
		// Successfully got open file name

		// Load file
		bResult = RichTextWindowLoad( lpszFilePath );

	} // End of successfully got open file name

	return bResult;

} // End of function RichTextWindowLoad

BOOL RichTextWindowLoad( LPCTSTR lpszFilePath )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Open file
	hFile = CreateFile( lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

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
			LPSTR lpszFileText = new char[ dwFileSize + sizeof( char ) ];

			// Read file text
			if( ReadFile( hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Update window text
				if( SetWindowText( g_hWndRichEdit, lpszFileText ) )
				{
					// Successfully updated window text

					// Update global file path
					lstrcpy( g_lpszFilePath, lpszFilePath );

					// Update return value
					bResult = TRUE;

				} // End of successfully updated window text

			} // End of successfully read file text

			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function RichTextWindowLoad

BOOL RichTextWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRedraw )
{
	// Move rich edit window
	return MoveWindow( g_hWndRichEdit, nLeft, nTop, nWidth, nHeight, bRedraw );

} // End of function RichTextWindowMove

BOOL RichTextWindowNew()
{
	BOOL bResult = FALSE;

	// Clear window text
	SetWindowText( g_hWndRichEdit, NULL );

	// Clear global file path
	g_lpszFilePath[ 0 ] = ( char )NULL;

	return bResult;

} // End of function RichTextWindowNew

BOOL RichTextWindowSave( HWND hWndParent )
{
	// Save to global file path
	return RichTextWindowSave( hWndParent, g_lpszFilePath );

} // End of function RichTextWindowSave

BOOL RichTextWindowSave( HWND hWndParent, LPCTSTR lpszFilePath )
{
	BOOL bResult = FALSE;

	// Ensure that file path is not empty
	if( lpszFilePath[ 0 ] )
	{
		// File path is not empty
		HANDLE hFile;

		// Create file
		hFile = CreateFile( lpszFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

		// Ensure that file was created
		if( hFile != INVALID_HANDLE_VALUE )
		{
			// Successfully created file
			DWORD dwWindowTextLength;

			// Get window text length
			dwWindowTextLength = GetWindowTextLength( g_hWndRichEdit );

			// Ensure that window contains text
			if( dwWindowTextLength > 0 )
			{
				// Window contains text
				DWORD dwBufferSize;
				LPSTR lpszWindowText;

				// Calculate buffer size
				dwBufferSize = ( dwWindowTextLength + sizeof( char ) );

				// Allocate string memory
				lpszWindowText = new char[ dwBufferSize ];

				// Get window text
				if( GetWindowText( g_hWndRichEdit, lpszWindowText, dwBufferSize ) )
				{
					// Successfully got window text

					// Write window text to file
					if( WriteFile( hFile, lpszWindowText, dwWindowTextLength, NULL, NULL ) )
					{
						// Successfully wrote window text to file

						// Update global file path
						lstrcpy( g_lpszFilePath, lpszFilePath );

						// Update return value
						bResult = TRUE;

					} // End of successfully wrote window text to file

				} // End of successfully got window text

				// Free string memory
				delete [] lpszWindowText;

			} // End of window contains text
			else
			{
				// Window is empty

				// Update global file path
				lstrcpy( g_lpszFilePath, lpszFilePath );

				// Update return value
				bResult = TRUE;

			} // End of window is empty

			// Close file
			CloseHandle( hFile );

		} // End of successfully created file

	} // End of file path is not empty
	else
	{
		// File path is empty

		// Save file as
		RichTextWindowSaveAs( hWndParent );

	} // End of file path is empty

	return bResult;

} // End of function RichTextWindowSave

BOOL RichTextWindowSaveAs( HWND hWndParent )
{
	BOOL bResult = FALSE;

	OPENFILENAME ofn;

	// Allocate string memory
	LPTSTR lpszFilePath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear file path
	lpszFilePath[ 0 ] = ( char )NULL;

	// Clear open file name structure
	ZeroMemory( &ofn, sizeof( ofn ) );

	// Initialise open file name structure
	ofn.lStructSize		= sizeof( ofn );
	ofn.hwndOwner		= hWndParent;
	ofn.lpstrFilter		= RICH_TEXT_WINDOW_FILTER;
	ofn.lpstrFile		= lpszFilePath;
	ofn.nMaxFile		= STRING_LENGTH;
	ofn.Flags			= ( OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT );
	ofn.lpstrDefExt		= RICH_TEXT_WINDOW_DEFAULT_EXTENSION;

	// Get save file name
	if( GetSaveFileName( &ofn ) )
	{
		// Successfully got save file name

		// Save file
		bResult = RichTextWindowSave( hWndParent, lpszFilePath );

	} // End of successfully got save file name

	return bResult;

} // End of function RichTextWindowSave

HWND RichTextWindowSetFocus()
{
	// Focus on rich text window
	return SetFocus( g_hWndRichEdit );

} // End of function RichTextWindowSetFocus
