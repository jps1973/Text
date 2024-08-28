// TOOL_BARWindow.h
//
// Note that the following text must be added to the end of the g++ command:
//
// -lcomctl32

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#include "Resource.h"

#define TOOL_BAR_WINDOW_CLASS_NAME												TOOLBARCLASSNAME

#define TOOL_BAR_WINDOW_EXTENDED_STYLE											0
#define TOOL_BAR_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT )
#define TOOL_BAR_WINDOW_TEXT													NULL

#define TOOL_BAR_WINDOW_BUTTON_STATE											TBSTATE_ENABLED
#define TOOL_BAR_WINDOW_BUTTON_STYLE											BTNS_AUTOSIZE
#define TOOL_BAR_WINDOW_BUTTON_WIDTH											16
#define TOOL_BAR_WINDOW_BUTTON_HEIGHT											16

typedef enum ToolBarButtons
{
	TOOL_BAR_WINDOW_UNDO_BUTTON = 0,
	TOOL_BAR_WINDOW_REDO_BUTTON,
	TOOL_BAR_WINDOW_CUT_BUTTON,
	TOOL_BAR_WINDOW_COPY_BUTTON,
	TOOL_BAR_WINDOW_PASTE_BUTTON,
	TOOL_BAR_WINDOW_DELETE_BUTTON,
	TOOL_BAR_WINDOW_ABOUT_BUTTON,

	TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS,

} TOOL_BAR_WINDOW_BUTTONS;

BOOL IsToolBarWindow( HWND hWnd );

void ToolBarWindowAutoSize();

BOOL ToolBarWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL ToolBarWindowEnableButton( int nCommandID, BOOL bEnable );

BOOL ToolBarWindowGetRect( LPRECT lpRect );

void ToolBarWindowInitButton( int nWhichButton, int nImage, int nCommandID );

BOOL ToolBarWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

HWND ToolBarWindowSetFocus();

void ToolBarWindowSetFont( HFONT hFont );
