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

BOOL RichEditWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move rich edit window
	return ::MoveWindow( g_hWndRichEdit, nX, nY, nWidth, nHeight, bRepaint );

} // End of function RichEditWindowMove

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
