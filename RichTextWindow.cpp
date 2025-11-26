// RichTextWindow.cpp

#include "RichTextWindow.h"

// Global variables
HMODULE g_hModuleRichEdit;
HWND g_hWndRichEdit;

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

	return bResult;

} // End of function RichTextWindowFreeMemory

BOOL RichTextWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRedraw )
{
	// Move rich edit window
	return MoveWindow( g_hWndRichEdit, nLeft, nTop, nWidth, nHeight, bRedraw );

} // End of function RichTextWindowMove

HWND RichTextWindowSetFocus()
{
	// Focus on rich text window
	return SetFocus( g_hWndRichEdit );

} // End of function RichTextWindowSetFocus
