// RichEditWindow.cpp

#include "RichEditWindow.h"

// Global variables
static HWND g_hWndRichEdit;

BOOL IsRichEditWindow( HWND hWnd )
{
	// See if supplied window is rich edit window
	return( hWnd == g_hWndRichEdit );

} // End of function IsRichEditWindow

BOOL RichEditWindowChangeToLowerCase( BOOL bCanUndo )
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;
	DWORD dwBufferSize;
	LPTSTR lpszSelectedText;

	// Get start and end of selection
	SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	// Ensure that some text is selected
	if( dwEnd <= dwStart )
	{
		// No text is selected

		// Select all text
		SendMessage( g_hWndRichEdit, EM_SETSEL, ( WPARAM )0, ( LPARAM )-1 );

		// Get start and end of selection
		SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	} // End of no text is selected

	// Calculate buffer size
	dwBufferSize = ( ( dwEnd - dwStart ) + sizeof( char ) );

	// Allocate string memory
	lpszSelectedText = new char[ dwBufferSize ];

	// Get selected text
	if( SendMessage( g_hWndRichEdit, EM_GETSELTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelectedText ) )
	{
		// Successfully got selected text
		DWORD dwWhichCharacter;

		// Loop through characters in selected text
		for( dwWhichCharacter = 0; dwWhichCharacter < dwBufferSize; dwWhichCharacter ++ )
		{
			// Set current character to lower case
			lpszSelectedText[ dwWhichCharacter ] = tolower( lpszSelectedText[ dwWhichCharacter ] );

		} // End of loop through characters in selected text

		// Replace selected text
		SendMessage( g_hWndRichEdit, EM_REPLACESEL, ( WPARAM )bCanUndo, ( LPARAM )lpszSelectedText );

	} // End of successfully got selected text

	// Free string memory
	delete [] lpszSelectedText;

	return bResult;

} // End of function RichEditWindowChangeToLowerCase

BOOL RichEditWindowChangeToTitleCase( BOOL bCanUndo )
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;
	DWORD dwBufferSize;
	LPTSTR lpszSelectedText;

	// Get start and end of selection
	SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	// Ensure that some text is selected
	if( dwEnd <= dwStart )
	{
		// No text is selected

		// Select all text
		SendMessage( g_hWndRichEdit, EM_SETSEL, ( WPARAM )0, ( LPARAM )-1 );

		// Get start and end of selection
		SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	} // End of no text is selected

	// Calculate buffer size
	dwBufferSize = ( ( dwEnd - dwStart ) + sizeof( char ) );

	// Allocate string memory
	lpszSelectedText = new char[ dwBufferSize ];

	// Get selected text
	if( SendMessage( g_hWndRichEdit, EM_GETSELTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelectedText ) )
	{
		// Successfully got selected text
		DWORD dwWhichCharacter;

		// Set first character to upper case
		lpszSelectedText[ 0 ] = toupper( lpszSelectedText[ 0 ] );

		// Loop through remaining characters in selected text
		for( dwWhichCharacter = 1; dwWhichCharacter < dwBufferSize; dwWhichCharacter ++ )
		{
			// See if previous character is a space
			if( lpszSelectedText[ dwWhichCharacter - sizeof( char ) ] == ASCII_SPACE_CHARACTER )
			{
				// Previous character is a space

				// Set current character to upper case
				lpszSelectedText[ dwWhichCharacter ] = toupper( lpszSelectedText[ dwWhichCharacter ] );

			} // End of previous character is a space
			else
			{
				// Previous character is not a space

				// Set current character to lower case
				lpszSelectedText[ dwWhichCharacter ] = tolower( lpszSelectedText[ dwWhichCharacter ] );

			} // End of previous character is not a space

		} // End of loop through remaining characters in selected text

		// Replace selected text
		SendMessage( g_hWndRichEdit, EM_REPLACESEL, ( WPARAM )bCanUndo, ( LPARAM )lpszSelectedText );

	} // End of successfully got selected text

	// Free string memory
	delete [] lpszSelectedText;

	return bResult;

} // End of function RichEditWindowChangeToTitleCase

BOOL RichEditWindowChangeToUpperCase( BOOL bCanUndo )
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;
	DWORD dwBufferSize;
	LPTSTR lpszSelectedText;

	// Get start and end of selection
	SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	// Ensure that some text is selected
	if( dwEnd <= dwStart )
	{
		// No text is selected

		// Select all text
		SendMessage( g_hWndRichEdit, EM_SETSEL, ( WPARAM )0, ( LPARAM )-1 );

		// Get start and end of selection
		SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	} // End of no text is selected

	// Calculate buffer size
	dwBufferSize = ( ( dwEnd - dwStart ) + sizeof( char ) );

	// Allocate string memory
	lpszSelectedText = new char[ dwBufferSize ];

	// Get selected text
	if( SendMessage( g_hWndRichEdit, EM_GETSELTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelectedText ) )
	{
		// Successfully got selected text
		DWORD dwWhichCharacter;

		// Loop through characters in selected text
		for( dwWhichCharacter = 0; dwWhichCharacter < dwBufferSize; dwWhichCharacter ++ )
		{
			// Set current character to upper case
			lpszSelectedText[ dwWhichCharacter ] = toupper( lpszSelectedText[ dwWhichCharacter ] );

		} // End of loop through characters in selected text

		// Replace selected text
		SendMessage( g_hWndRichEdit, EM_REPLACESEL, ( WPARAM )bCanUndo, ( LPARAM )lpszSelectedText );

	} // End of successfully got selected text

	// Free string memory
	delete [] lpszSelectedText;

	return bResult;

} // End of function RichEditWindowChangeToUpperCase

BOOL RichEditWindowCopy()
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;

	// Get start and end of selection
	SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	// Ensure that some text is selected
	if( dwEnd > dwStart )
	{
		// Some text is selected
		DWORD dwBufferSize;
		LPTSTR lpszSelectedText;

		// Calculate buffer size
		dwBufferSize = ( ( dwEnd - dwStart ) + sizeof( char ) );

		// Allocate string memory
		lpszSelectedText = new char[ dwBufferSize ];

		// Get selected text
		if( SendMessage( g_hWndRichEdit, EM_GETSELTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelectedText ) )
		{
			// Successfully got selected text

			// Open clipboard
			if( OpenClipboard( NULL ) )
			{
				// Successfully opened clipboard
				HGLOBAL hGlobal;

				// Empty clipboard
				EmptyClipboard();

				// Allocate global memory
				hGlobal = GlobalAlloc( GMEM_MOVEABLE, dwBufferSize );

				// Ensure that global memory was allocated
				if( hGlobal )
				{
					// Successfully allocated global memory

					// Copy selected text into global memory
					memcpy( GlobalLock( hGlobal ), lpszSelectedText, dwBufferSize );

					// Unlock global memory
					GlobalUnlock( hGlobal );

					// Update clipboard
					if( SetClipboardData( CF_TEXT, hGlobal ) )
					{
						// Successfully updated clipboard

						// Update return value
						bResult = TRUE;

					} // End of successfully updated clipboard

					// Free global memory
					GlobalFree( hGlobal );

				} // End of successfully allocated global memory

				// Close clipboard
				CloseClipboard();

			} // End of successfully opened clipboard

		} // End fo successfully got selected text

		// Free string memory
		delete [] lpszSelectedText;

	} // End of some text is selected

	return bResult;

} // End of function RichEditWindowCopy

BOOL RichEditWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Create rich edit window
	g_hWndRichEdit = CreateWindowEx( RICH_EDIT_WINDOW_EXTENDED_STYLE, RICH_EDIT_WINDOW_CLASS_NAME, RICH_EDIT_WINDOW_TEXT, RICH_EDIT_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that rich edit window was created
	if( g_hWndRichEdit )
	{
		// Successfully created rich edit window

		// Set rich edit window text mode
		SendMessage( g_hWndRichEdit, EM_SETTEXTMODE, ( WPARAM )RICH_EDIT_WINDOW_TEXT_MODE, ( LPARAM )NULL );

		// Set rich edit window event mask
		SendMessage( g_hWndRichEdit, EM_SETEVENTMASK, ( WPARAM )NULL, ( LPARAM )ENM_SELCHANGE );

		// Update return value
		bResult = TRUE;

	} // End of successfully created rich edit window

	return bResult;

} // End of function RichEditWindowCreate

BOOL RichEditWindowCut()
{
	BOOL bResult = FALSE;

	// Copy selected text
	if( RichEditWindowCopy() )
	{
		// Successfully copied selected text

		// Delete selected text
		RichEditWindowReplaceSelected( NULL );

		// Update return value
		bResult = TRUE;

	} // End of successfully copied selected text

	return bResult;

} // End of function RichEditWindowCut

BOOL RichEditWindowGetRect( LPRECT lpRect )
{
	// Get rich edit window rect
	return GetWindowRect( g_hWndRichEdit, lpRect );

} // End of function RichEditWindowGetRect

BOOL RichEditWindowHandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM, void( *lpUpdateFunction )( HWND hWndMain, BOOL bCanUndo, BOOL bCanRedo ) )
{
	BOOL bResult = FALSE;

	// Select command notification code
	switch( HIWORD( wParam ) )
	{
		case EN_UPDATE:
		{
			// An edit window update notification code
			BOOL bCanUndo;
			BOOL bCanRedo;

			// Initialise undo and redo values
			bCanUndo = SendMessage( g_hWndRichEdit, EM_CANUNDO, ( WPARAM )NULL, ( LPARAM )NULL );
			bCanRedo = SendMessage( g_hWndRichEdit, EM_CANREDO, ( WPARAM )NULL, ( LPARAM )NULL );

			// Call update function
			( *lpUpdateFunction )( hWndMain, bCanUndo, bCanRedo );

			// Update return value
			bResult = TRUE;

			// Break out of switch
			break;

		} // End of an edit window update notification code

	} // End of selection for command notification code

	return bResult;

} // End of function RichEditWindowHandleCommandMessage

BOOL RichEditWindowHandleNotifyMessage( HWND hWndMain, WPARAM, LPARAM lParam, void( *lpSelectionChangeFunction )( HWND hWndMain, int nLength ) )
{
	BOOL bResult = FALSE;

	LPNMHDR lpNmHdr;

	// Store notify message handler
	lpNmHdr = ( LPNMHDR )lParam;

	// Select notify message
	switch( lpNmHdr->code )
	{
		case EN_SELCHANGE:
		{
			// An edit selection change notification message
			//
			// Note that for this to work, the rich edit window event mask must include ENM_SELCHANGE
			SELCHANGE *lpSelChange;
			int nSelectionLength;

			// Get selection change item
			lpSelChange = ( SELCHANGE * )lParam;

			// Calculate selection length
			nSelectionLength = ( lpSelChange->chrg.cpMax - lpSelChange->chrg.cpMin );

			// Call selection change function
			( *lpSelectionChangeFunction )( hWndMain, nSelectionLength );

			// Update return value
			bResult = TRUE;

			// Break out of switch
			break;

		} // End of an edit selection change notification message

	}; // End of selection for notify message

	return bResult;

} // End of function RichEditWindowHandleNotifyMessage

BOOL RichEditWindowLoad( LPCTSTR lpszFileName )
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
			LPTSTR lpszFileText = new char[ dwFileSize + sizeof( char ) ];

			// Read file text
			if( ReadFile( hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Update rich edit window
				if( SetWindowText( g_hWndRichEdit, lpszFileText ) )
				{
					// Successfully updated rich edit window

					// Update return value
					bResult = TRUE;

				} // End of successfully updated rich edit window

			} // End of successfully read file text

			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function RichEditWindowLoad

BOOL RichEditWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move rich edit window
	return MoveWindow( g_hWndRichEdit, nX, nY, nWidth, nHeight, bRepaint );

} // End of function RichEditWindowMove

BOOL RichEditWindowPaste()
{
	BOOL bResult = FALSE;

	// Open clipboard
	if( OpenClipboard( NULL ) )
	{
		// Successfully opened clipboard
		HANDLE hClipboard;

		// Get clipboard data
		hClipboard = GetClipboardData( CF_TEXT );

		// Ensure that clipboard data was got
		if( hClipboard )
		{
			// Successfully got clipboard data

			// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
			LPTSTR lpszClipboard;

			// Get clipboard text
			lpszClipboard = static_cast<LPTSTR>( GlobalLock( hClipboard ) );

			// Ensure that clipboard text was got
			if( lpszClipboard )
			{
				// Successfully got clipboard text

				// Replace current selection with clipboard text
				SendMessage( g_hWndRichEdit, EM_REPLACESEL, ( WPARAM )TRUE, ( LPARAM )lpszClipboard );

				// Update return value
				bResult = TRUE;

			} // End of successfully got clipboard text
			else
			{
				// Unable to get clipboard text

				// Display error message
				MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_GET_CLIPBOARD_TEXT_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

			} // End of unable to get clipboard text

		} // End of successfully got clipboard data
		else
		{
			// Unable to get clipboard data

			// Display error message
			MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_GET_CLIPBOARD_DATA_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to get clipboard data

		// Close clipboard
		CloseClipboard();

	} // End of successfully opened clipboard
	else
	{
		// Unable to open clipboard

		// Display error message
		MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_OPEN_CLIPBOARD_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to open clipboard

	return bResult;

} // End of function RichEditWindowPaste

BOOL RichEditWindowRedo()
{
	// Redo
	return SendMessage( g_hWndRichEdit, EM_REDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichEditWindowRedo

void RichEditWindowReplaceSelected( LPCTSTR lpszReplacement, BOOL bCanUndo )
{
	// Replace selected text
	SendMessage( g_hWndRichEdit, EM_REPLACESEL, ( WPARAM )bCanUndo, ( LPARAM )lpszReplacement );

} // End of function RichEditWindowReplaceSelected

BOOL RichEditWindowSave( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Create file
	hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was created
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file
		DWORD dwTextLength;

		// Get rich edit window text length
		dwTextLength = GetWindowTextLength( g_hWndRichEdit );

		// Ensure that rich edit window is not empty
		if( dwTextLength > 0 )
		{
			// Rich edit window is not empty
			DWORD dwBufferSize;
			LPTSTR lpszWindowText;

			// Calculate buffer size
			dwBufferSize = ( dwTextLength + sizeof( char ) );

			// Allocate string memory
			lpszWindowText = new char[ dwBufferSize ];

			// Get rich edit window text
			if( GetWindowText( g_hWndRichEdit, lpszWindowText, dwBufferSize ) )
			{
				// Successfully got rich edit window text

				// Write rich edit window text to file
				if( WriteFile( hFile, lpszWindowText, dwTextLength, NULL, NULL ) )
				{
					// Successfully wrote rich edit window text to file

					// Update return value
					bResult = TRUE;

				} // End of successfully wrote rich edit window text to file

			} // End of successfully got rich edit window text

			// Free string memory
			delete [] lpszWindowText;

		} // End of rich edit window is not empty
		else
		{
			// Rich edit window is empty

			// Update return value
			bResult = TRUE;

		} // End of rich edit window is empty

		// Close file
		CloseHandle( hFile );

	} // End of successfully created file

	return bResult;

} // End of function RichEditWindowSave

void RichEditWindowSelect( int nStart, int nEnd )
{
	// Select rich edit window text
	SendMessage( g_hWndRichEdit, EM_SETSEL, ( WPARAM )nStart, ( LPARAM )nEnd );

} // End of function RichEditWindowSelect

HWND RichEditWindowSetFocus()
{
	// Focus on rich edit window
	return SetFocus( g_hWndRichEdit );

} // End of function RichEditWindowSetFocus

void RichEditWindowSetFont( HFONT hFont )
{
	// Set rich edit window font
	SendMessage( g_hWndRichEdit, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function RichEditWindowSetFont

BOOL RichEditWindowUndo()
{
	// Undo
	return SendMessage( g_hWndRichEdit, EM_UNDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichEditWindowUndo

