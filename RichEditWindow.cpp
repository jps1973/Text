// RichEditWindow.cpp

#include "RichEditWindow.h"

// Global variables
HWND g_hWndRichEdit;

BOOL IsRichEditWindow( HWND hWnd )
{
	// See if supplied window is rich edit window
	return( hWnd == g_hWndRichEdit );

} // End of function IsRichEditWindow

BOOL RichEditWindowCanPaste()
{
	// See if clipboard contains text
	return IsClipboardFormatAvailable( CF_TEXT );

} // End of function RichEditWindowCanPaste

BOOL RichEditWindowCanRedo()
{
	// See if redo is possible
	return SendMessage( g_hWndRichEdit, EM_CANREDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichEditWindowCanRedo

BOOL RichEditWindowCanUndo()
{
	// See if undo is possible
	return SendMessage( g_hWndRichEdit, EM_CANUNDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichEditWindowCanUndo

BOOL RichEditWindowCopy()
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;

	// Get selection
	if( SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd ) )
	{
		// Successfully got selection
		DWORD dwSelectedTextLength;

		// Get selected text length
		dwSelectedTextLength = ( dwEnd - dwStart );

		// Ensure that selection is not empty
		if( dwSelectedTextLength )
		{
			// Selection is not empty
			DWORD dwBufferLength;
			LPTSTR lpszSelectedText;

			// Calculate buffer length
			dwBufferLength = ( dwSelectedTextLength + sizeof( char ) );

			// Allocate string memory
			lpszSelectedText = new char[ dwBufferLength ];

			// Get selected text
			if( SendMessage( g_hWndRichEdit, EM_GETSELTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelectedText ) )
			{
				// Successfully got selected text

				// Open clipboard
				if( OpenClipboard( NULL ) )
				{
					// Successfully opened clipboard

					// Enpty clipboard
					if( EmptyClipboard() )
					{
						// Successfully emptied clipboard
						HGLOBAL hGlobal;

						// Allocate global memory
						hGlobal = GlobalAlloc( GMEM_MOVEABLE, dwBufferLength );

						// Ensure that global memory was allocated
						if( hGlobal )
						{
							// Successfully allocated global memory

							// Copy clipboard into global memory
							memcpy( GlobalLock( hGlobal ), lpszSelectedText, dwBufferLength );

							// Unlock global memory
							GlobalUnlock( hGlobal );

							// Update clipboard
							if( SetClipboardData( CF_TEXT, hGlobal ) )
							{
								// Successfully updated clipboard

								// Update return value
								bResult = TRUE;

							} // End of successfully updated clipboard
							else
							{
								// Unable to update clipboard

								// Display error message
								MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_UPDATE_CLIPBOARD_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

							} // End of unable to update clipboard

							// Free global memory
							GlobalFree( hGlobal );

						} // End of successfully allocated global memory
						else
						{
							// Unable to allocate global memory

							// Display error message
							MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_ALLOCATE_GLOBAL_MEMORY_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

						} // End of unable to allocate global memory

					} // End of successfully emptied clipboard
					else
					{
						// Unable to empty clipboard

						// Display error message
						MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_EMPTY_CLIPBOARD_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

					} // End of unable to empty clipboard

					// Close clipboard
					CloseClipboard();

				} // End of successfully opened clipboard
				else
				{
					// Unable to open clipboard

					// Display error message
					MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_OPEN_CLIPBOARD_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

				} // End of unable to open clipboard

			} // End of successfully got selected text
			else
			{
				// Unable to get selected text

				// Display error message
				MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_GET_SELECTED_TEXT_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

			} // End of unable to get selected text

		} // End of selection is not empty
		else
		{
			// Selection is empty

			// Display error message
			MessageBox( NULL, RICH_EDIT_WINDOW_SELECTION_IS_EMPTY_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of selection is empty

	} // End of successfully got selection
	else
	{
		// Unable to get selection

		// Display error message
		MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_GET_SELECTION_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to get selection

	return bResult;

} // End of function RichEditWindowCopy

BOOL RichEditWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Load rich edit library
	if( LoadLibrary( RICH_EDIT_LIBRARY_NAME ) )
	{
		// Successfully loaded rich edit library

		// Create rich edit window
		g_hWndRichEdit = CreateWindowEx( RICH_EDIT_WINDOW_EXTENDED_STYLE, RICH_EDIT_WINDOW_CLASS_NAME, RICH_EDIT_WINDOW_TEXT, RICH_EDIT_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

		// Ensure that rich edit window was created
		if( g_hWndRichEdit )
		{
			// Successfully created rich edit window

			// Set text mode
			SendMessage( g_hWndRichEdit, EM_SETTEXTMODE, ( WPARAM )RICH_EDIT_WINDOW_TEXT_MODE, ( LPARAM )NULL );

			// Set event mask
			SendMessage( g_hWndRichEdit, EM_SETEVENTMASK, ( WPARAM )NULL, ( LPARAM )RICH_EDIT_WINDOW_EVENT_MASK );

			// Update return value
			bResult = TRUE;

		} // End of successfully created rich edit window

	} // End of successfully loaded rich edit library

	return bResult;

} // End of function RichEditWindowCreate

BOOL RichEditWindowCut()
{
	BOOL bResult = FALSE;

	// Copy text
	if( RichEditWindowCopy() )
	{
		// Successfully copied text

		// Delete text
		if( RichEditWindowDelete() )
		{
			// Successfully deleted text

			// Update return value
			bResult = TRUE;

		} // End of successfully deleted text

	} // End of successfully copied text

	return bResult;

} // End of function RichEditWindowCut

BOOL RichEditWindowDelete()
{
	// Delete rich edit window text
	return SendMessage( g_hWndRichEdit, EM_REPLACESEL, ( WPARAM )TRUE, ( LPARAM )NULL );

} // End of function RichEditWindowDelete

BOOL RichEditWindowGetRect( LPRECT lpRect )
{
	// Get rich edit window rect
	return GetWindowRect( g_hWndRichEdit, lpRect );

} // End of function RichEditWindowGetRect

BOOL RichEditWindowHandleCommandMessage( WPARAM wParam, LPARAM, void( *lpUpdateFunction )() )
{
	BOOL bResult = FALSE;

	// Select command notification code
	switch( HIWORD( wParam ) )
	{
		case EN_UPDATE:
		{
			// An edit window update notification code

			// Call update function
			( *lpUpdateFunction )();

			// Update return value
			bResult = TRUE;

			// Break out of switch
			break;

		} // End of an edit window update notification code

	} // End of selection for command notification code

	return bResult;

} // End of function RichEditWindowHandleCommandMessage

BOOL RichEditWindowHandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangeFunction )( int nLength ) )
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
			( *lpSelectionChangeFunction )( nSelectionLength );

			// Update return value
			bResult = TRUE;

			// Break out of switch
			break;

		} // End of an edit selection change notification message

	}; // End of selection for notify message

	return bResult;

} // End of function RichEditWindowHandleNotifyMessage

BOOL RichEditWindowIsTextSelected()
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;

	// Get selection
	if( SendMessage( g_hWndRichEdit, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd ) )
	{
		// Successfully got selection

		// See if any text is selected
		if( dwStart != dwEnd )
		{
			// Some text is selected

			// Update return value
			bResult = TRUE;

		} // End of some text is selected

	} // End of successfully got selection

	return bResult;

} // End of function RichEditWindowIsTextSelected

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

void RichEditWindowReplaceSelection( LPCTSTR lpszReplacementText )
{
	// Replace selected text
	SendMessage( g_hWndRichEdit, EM_REPLACESEL, ( WPARAM )TRUE, ( LPARAM )lpszReplacementText );

} // End of function RichEditWindowReplaceSelection

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
