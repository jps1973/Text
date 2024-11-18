// RichEditWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>
#include <richedit.h>

#include "Ascii.h"
#include "Common.h"

#define RICH_EDIT_WINDOW_CLASS_NAME												RICHEDIT_CLASS

#define RICH_EDIT_WINDOW_EXTENDED_STYLE											0
#define RICH_EDIT_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | WS_HSCROLL | ES_MULTILINE )
#define RICH_EDIT_WINDOW_TEXT													NULL

#define RICH_EDIT_WINDOW_LIBRARY_NAME											"Riched20.dll"

#define RICH_EDIT_WINDOW_EVENT_MASK												
#define RICH_EDIT_WINDOW_TEXT_MODE												( TM_PLAINTEXT | TM_MULTILEVELUNDO )

#define RICH_EDIT_WINDOW_UNABLE_TO_LOAD_RICH_EDIT_LIBRARY_ERROR_MESSAGE			"Unable to load rich edit library"

#define RICH_EDIT_WINDOW_UNABLE_TO_SAVE_WARNING_MESSAGE							"Unable to save text.\r\n\r\nAre you sure that you want to close?"

#define RICH_EDIT_WINDOW_UNABLE_TO_GET_CLIPBOARD_TEXT_ERROR_MESSAGE				"Unable to get clipboard text"
#define RICH_EDIT_WINDOW_UNABLE_TO_GET_CLIPBOARD_DATA_ERROR_MESSAGE				"Unable to get clipboard data"
#define RICH_EDIT_WINDOW_UNABLE_TO_OPEN_CLIPBOARD_ERROR_MESSAGE					"Unable to open clipboard"

BOOL IsRichEditWindow( HWND hWnd );

BOOL RichEditWindowChangeToLowerCase( BOOL bCanUndo = TRUE );

BOOL RichEditWindowChangeToTitleCase( BOOL bCanUndo = TRUE );

BOOL RichEditWindowChangeToUpperCase( BOOL bCanUndo = TRUE );

BOOL RichEditWindowCopy();

BOOL RichEditWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL RichEditWindowCut();

BOOL RichEditWindowGetRect( LPRECT lpRect );

BOOL RichEditWindowHandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM, void( *lpUpdateFunction )( HWND hWndMain, BOOL bCanUndo, BOOL bCanRedo ) );

BOOL RichEditWindowHandleNotifyMessage( HWND hWndMain, WPARAM, LPARAM lParam, void( *lpSelectionChangeFunction )( HWND hWndMain, int nLength ) );

BOOL RichEditWindowLoad( LPCTSTR lpszFileName );

BOOL RichEditWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

BOOL RichEditWindowPaste();

BOOL RichEditWindowRedo();

void RichEditWindowReplaceSelected( LPCTSTR lpszReplacement, BOOL bCanUndo = TRUE );

BOOL RichEditWindowSave( LPCTSTR lpszFileName );

void RichEditWindowSelect( int nStart = 0, int nEnd = -1 );

HWND RichEditWindowSetFocus();

void RichEditWindowSetFont( HFONT hFont );

BOOL RichEditWindowUndo();
