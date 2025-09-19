// ControlWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>
#include <richedit.h>

#include "Ascii.h"
#include "Common.h"

#define RICH_EDIT_LIBRARY_NAME													"Riched20.dll"

#define CONTROL_WINDOW_CLASS_NAME												RICHEDIT_CLASS

#define CONTROL_WINDOW_EXTENDED_STYLE											0
#define CONTROL_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_MULTILINE )
#define CONTROL_WINDOW_TEXT														NULL

BOOL IsControlWindow( HWND hWnd );

BOOL ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL ControlWindowGetRect( LPRECT lpRect );

BOOL ControlWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam );

BOOL ControlWindowHandleNotifyMessage( WPARAM wParam, LPARAM lParam );

BOOL ControlWindowMove( DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, BOOL bRepaint = TRUE );

BOOL ControlWindowLoad( LPCTSTR lpszFileName );

BOOL ControlWindowSave( LPCTSTR lpszFileName );

void ControlWindowSelectText( int nStart = 0, int nEnd = -1 );

HWND ControlWindowSetFocus();
