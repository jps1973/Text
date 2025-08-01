// RichTextWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>
#include <richedit.h>

#include "Ascii.h"
#include "Common.h"

#define RICH_EDIT_CLASS_NAME													"riched32.dll"

#define RICH_TEXT_WINDOW_CLASS_NAME												RICHEDIT_CLASS

#define RICH_TEXT_WINDOW_EXTENDED_STYLE											0
#define RICH_TEXT_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_MULTILINE )
#define RICH_TEXT_WINDOW_TEXT													NULL

#define RICH_TEXT_WINDOW_POPULATE_STATUS_MESSAGE_FORMAT_STRING					"%s (%d items )"

#define RICH_TEXT_WINDOW_UNABLE_TO_SAVE_WARNING_MESSAGE							"Unable to save.\r\n\r\nDo you want to close?"

BOOL IsRichTextWindow( HWND hWnd );

BOOL RichTextWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL RichTextWindowGetRect( LPRECT lpRect );

BOOL RichTextWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

BOOL RichTextWindowHandleNotifyMessage( WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

BOOL RichTextWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

BOOL RichTextWindowLoad( LPCTSTR lpszFileName );

BOOL RichTextWindowPopulate( LPCTSTR lpszFileName );

void RichTextWindowSelect( int nStart = 0, int nEnd = -1 );

BOOL RichTextWindowSave( LPCTSTR lpszFileName );

HWND RichTextWindowSetFocus();

void RichTextWindowSetFont( HFONT hFont );
