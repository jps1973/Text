// RichTextWindow.cpp

#include "RichTextWindow.h"

// Global variables
static HWND g_hWndRichText;

BOOL IsRichTextWindow( HWND hWnd )
{
	// See if supplied window is rich text window
	return( hWnd == g_hWndRichText );

} // End of function IsRichTextWindow

BOOL RichTextWindowCopy()
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;
	DWORD dwSelectedTextLength;

	// Get start and end of selection
	SendMessage( g_hWndRichText, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	// Calculate selected text length
	dwSelectedTextLength = ( dwEnd - dwStart );

	// Ensure that some text is selected
	if( dwSelectedTextLength > 0 )
	{
		// Some text is selected
		DWORD dwBufferLength;

		// Calculate buffer length
		dwBufferLength = ( dwSelectedTextLength + sizeof( char ) );

		// Allocate string memory
		LPTSTR lpszSelectedText = new char[ dwBufferLength ];

		// Get selected text
		if( SendMessage( g_hWndRichText, EM_GETSELTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelectedText ) )
		{
			// Successfully got selected text

			// Open clipboard
			if( OpenClipboard( NULL ) )
			{
				// Successfully opened clipboard
				HGLOBAL hClipboard;

				// Allocate global memory
				hClipboard = GlobalAlloc( GMEM_MOVEABLE, dwBufferLength );

				// Ensure that global memory was allocated
				if( hClipboard )
				{
					// Successfully allocated global memory

					// Copy selected text into global memory
					memcpy( GlobalLock( hClipboard ), lpszSelectedText, dwBufferLength );

					// Unlock global memory
					GlobalUnlock( hClipboard );

					// Update clipboard
					SetClipboardData( CF_TEXT, hClipboard );

					// Update return value
					bResult = TRUE;

					// Free global memory
					GlobalFree( hClipboard );

				} // End of successfully allocated global memory

				// Close clipboard
				CloseClipboard();

			} // End of successfully opened clipboard

		} // End of successfully got window text

		// Free string memory
		delete [] lpszSelectedText;

	} // End of some text is selected

	return bResult;

} // End of function RichTextWindowCopy

BOOL RichTextWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Load rich edit library
	LoadLibrary( RICH_EDIT_CLASS_NAME );

	// Create rich text window
	g_hWndRichText = CreateWindowEx( RICH_TEXT_WINDOW_EXTENDED_STYLE, RICH_TEXT_WINDOW_CLASS_NAME, RICH_TEXT_WINDOW_TEXT, RICH_TEXT_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that rich text window was created
	if( g_hWndRichText )
	{
		// Successfully created rich text window

		// Set rich text window text mode
		SendMessage( g_hWndRichText, EM_SETTEXTMODE, ( WPARAM )RICH_TEXT_WINDOW_TEXT_MODE, ( LPARAM )NULL );

		// Update return value
		bResult = TRUE;

	} // End of successfully created rich text window

	return bResult;

} // End of function RichTextWindowCreate

BOOL RichTextWindowCut( BOOL bCanUndo )
{
	BOOL bResult = FALSE;

	// Copy selected text
	if( RichTextWindowCopy() )
	{
		// Successfully copied selected text

		// Delete selected text
		bResult = RichTextWindowDelete( bCanUndo );

	} // End of successfully copied selected text

	return bResult;

} // End of function RichTextWindowCopy

BOOL RichTextWindowDelete( BOOL bCanUndo )
{
	// Delete selected text
	return SendMessage( g_hWndRichText, EM_REPLACESEL, ( WPARAM )bCanUndo, ( LPARAM )EMPTY_STRING );

} // End of function RichTextWindowDelete

BOOL RichTextWindowGetRect( LPRECT lpRect )
{
	// Get rich text window rect
	return GetWindowRect( g_hWndRichText, lpRect );

} // End of function RichTextWindowGetRect

BOOL RichTextWindowHandleCommandMessage( WPARAM wParam, LPARAM, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	// Select rich text window notification code
	switch( HIWORD( wParam ) )
	{
		case LBN_DBLCLK:
		{
			// A rich text window double click notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get selected item
			nSelectedItem = SendMessage( g_hWndRichText, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( SendMessage( g_hWndRichText, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Display selected item text
				MessageBox( NULL, lpszSelected, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a rich text window double click notification code
		case LBN_SELCHANGE:
		{
			// A rich text window selection change notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get selected item
			nSelectedItem = SendMessage( g_hWndRichText, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( SendMessage( g_hWndRichText, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Show selected item text on status bar window
				( *lpStatusFunction )( lpszSelected );

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a rich text window selection change notification code
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for rich text window notification code

	return bResult;

} // End of function RichTextWindowHandleCommandMessage

BOOL RichTextWindowHandleNotifyMessage( WPARAM, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	LPNMHDR lpNmhdr;

	// Get notify message handler
	lpNmhdr = ( ( LPNMHDR )lParam );

	// Select rich text window notification code
	switch( lpNmhdr->code )
	{
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for rich text window notification code

	return bResult;

} // End of function RichTextWindowHandleNotifyMessage

BOOL RichTextWindowLoad( LPCTSTR lpszFileName )
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

				// Copy file text to window
				SetWindowText( g_hWndRichText, lpszFileText );

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

} // End of function RichTextWindowLoad

BOOL RichTextWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move rich text window
	return MoveWindow( g_hWndRichText, nX, nY, nWidth, nHeight, bRepaint );

} // End of function RichTextWindowMove

BOOL RichTextWindowPaste( BOOL bCanUndo )
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
			LPTSTR lpszClipboardText;

			// Get clipboard text
			lpszClipboardText = static_cast<LPTSTR>( GlobalLock( hClipboard ) );

			// Ensure that clipboard text was got
			if( lpszClipboardText )
			{
				// Successfully got clipboard text

				// Replace selected text
				bResult = SendMessage( g_hWndRichText, EM_REPLACESEL, ( WPARAM )bCanUndo, ( LPARAM )lpszClipboardText );

			} // End of successfully got clipboard text

		} // End of successfully got clipboard data

		// Close clipboard
		CloseClipboard();

	} // End of successfully opened clipboard

	return bResult;

} // End of function RichTextWindowPaste

BOOL RichTextWindowPopulate( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	// Clear rich text window
	SendMessage( g_hWndRichText, LB_RESETCONTENT, ( WPARAM )NULL, ( LPARAM )NULL );

	// Load file
	if( RichTextWindowLoad( lpszFileName ) )
	{
		// Successfully loaded file

		// Select text
		RichTextWindowSelect();

		// Update return value
		bResult = TRUE;

	} // End of successfully loaded file

	return bResult;

} // End of function RichTextWindowPopulate

BOOL RichTextWindowRedo()
{
	// Undo
	return SendMessage( g_hWndRichText, EM_REDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichTextWindowRedo

BOOL RichTextWindowSave( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Create file
	hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was created
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file
		DWORD dwWindowTextLength;

		// Get window text length
		dwWindowTextLength = GetWindowTextLength( g_hWndRichText );

		// Ensure that window contains text
		if( dwWindowTextLength > 0 )
		{
			// Window contains text
			DWORD dwBuffferLength = ( dwWindowTextLength + sizeof( char ) );

			// Allocate string memory
			LPTSTR lpszWindowText = new char[ dwBuffferLength ];

			// Get window text
			if( GetWindowText( g_hWndRichText, lpszWindowText, dwBuffferLength ) )
			{
				// Successfully got window text

				// Write window text to file
				if( WriteFile( hFile, lpszWindowText, dwWindowTextLength, NULL, NULL ) )
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
			// Window is empty

			// Update return value
			bResult = TRUE;

		} // End of window is empty

		// Close file
		CloseHandle( hFile );

	} // End of successfully created file

	return bResult;

} // End of function RichTextWindowSave

void RichTextWindowSelect( int nStart, int nEnd )
{
	// Select rich text window text
	SendMessage( g_hWndRichText, EM_SETSEL, ( WPARAM )nStart, ( LPARAM )nEnd );

} // End of function RichTextWindowSetFont

HWND RichTextWindowSetFocus()
{
	// Focus on rich text window
	return SetFocus( g_hWndRichText );

} // End of function RichTextWindowSetFocus

void RichTextWindowSetFont( HFONT hFont )
{
	// Set rich text window font
	SendMessage( g_hWndRichText, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function RichTextWindowSetFont

BOOL RichTextWindowUndo()
{
	// Redo
	return SendMessage( g_hWndRichText, EM_UNDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichTextWindowUndo

