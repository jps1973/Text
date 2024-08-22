// RichEditWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>
#include <richedit.h>

#include "Ascii.h"
#include "Common.h"

#define RICH_EDIT_WINDOW_CLASS_NAME												RICHEDIT_CLASS

#define RICH_EDIT_WINDOW_EXTENDED_STYLE											0
#define RICH_EDIT_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE )
#define RICH_EDIT_WINDOW_TEXT													NULL

#define RICH_EDIT_WINDOW_TEXT_MODE												( TM_PLAINTEXT | TM_MULTILEVELUNDO | TM_MULTICODEPAGE )

#define RICH_EDIT_LIBRARY_NAME													"Riched32.dll"

BOOL IsRichEditWindow( HWND hWnd );

BOOL RichEditWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL RichEditWindowGetRect( LPRECT lpRect );

BOOL RichEditWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam, void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ) );

BOOL RichEditWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

HWND RichEditWindowSetFocus();

void RichEditWindowSetFont( HFONT hFont );
