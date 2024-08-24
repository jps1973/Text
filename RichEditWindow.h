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

#define RICH_EDIT_WINDOW_SUCCESSFULLY_CUT_TEXT_STATUS_MESSAGE					"Cut text to clipboard"
#define RICH_EDIT_WINDOW_SUCCESSFULLY_COPIED_TEXT_STATUS_MESSAGE				"Copied text to clipboard"

#define RICH_EDIT_WINDOW_UNABLE_TO_UPDATE_CLIPBOARD_ERROR_MESSAGE				"Unable to update clipboard"
#define RICH_EDIT_WINDOW_UNABLE_TO_ALLOCATE_GLOBAL_MEMORY_ERROR_MESSAGE			"Unable to allocate global memory"
#define RICH_EDIT_WINDOW_UNABLE_TO_EMPTY_CLIPBOARD_ERROR_MESSAGE				"Unable to empty clipboard"
#define RICH_EDIT_WINDOW_UNABLE_TO_OPEN_CLIPBOARD_ERROR_MESSAGE					"Unable to open clipboard"
#define RICH_EDIT_WINDOW_UNABLE_TO_GET_SELECTED_TEXT_ERROR_MESSAGE				"Unable to get selected text"
#define RICH_EDIT_WINDOW_SELECTION_IS_EMPTY_ERROR_MESSAGE						"No text selected"
#define RICH_EDIT_WINDOW_UNABLE_TO_GET_SELECTION_ERROR_MESSAGE					"Unable to get selection"
#define RICH_EDIT_WINDOW_UNABLE_TO_GET_CLIPBOARD_TEXT_ERROR_MESSAGE				"Unable to get clipboard text"
#define RICH_EDIT_WINDOW_UNABLE_TO_GET_CLIPBOARD_DATA_ERROR_MESSAGE				"Unable to get clipboard data"

#define RICH_EDIT_WINDOW_UNABLE_TO_SAVE_WARNING_MESSAGE							"Unable to save text.\r\n\r\nAre you sure that you want to close?"

BOOL IsRichEditWindow( HWND hWnd );

BOOL RichEditWindowCanPaste();

BOOL RichEditWindowCanRedo();

BOOL RichEditWindowCanUndo();

BOOL RichEditWindowCopy();

BOOL RichEditWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL RichEditWindowCut();

BOOL RichEditWindowDelete();

BOOL RichEditWindowGetRect( LPRECT lpRect );

BOOL RichEditWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam, void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ) );

BOOL RichEditWindowIsTextSelected();

BOOL RichEditWindowLoadText( LPCTSTR lpszFileName );

BOOL RichEditWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

BOOL RichEditWindowPaste();

BOOL RichEditWindowRedo();

BOOL RichEditWindowSaveText( LPCTSTR lpszFileName );

void RichEditWindowSelect( int nStart = 0, int nEnd = -1 );

HWND RichEditWindowSetFocus();

void RichEditWindowSetFont( HFONT hFont );

BOOL RichEditWindowUndo();