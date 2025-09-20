// ToolBarWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define TOOL_BAR_WINDOW_CLASS_NAME												TOOLBARCLASSNAME

#define TOOL_BAR_WINDOW_EXTENDED_STYLE											0
#define TOOL_BAR_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | TBSTYLE_WRAPABLE | TBSTYLE_FLAT )
#define TOOL_BAR_WINDOW_TEXT													NULL

#define TOOL_BAR_WINDOW_IMAGE_LIST_ID											0
#define TOOL_BAR_WINDOW_IMAGE_LIST_SIZE											16
#define TOOL_BAR_WINDOW_IMAGE_LIST_FLAGS										( ILC_COLOR16 | ILC_MASK )
#define TOOL_BAR_WINDOW_IMAGE_LIST_GROW											0

typedef enum
{
	TOOL_BAR_WINDOW_UNDO_BUTTON_ID = 0,
	TOOL_BAR_WINDOW_REDO_BUTTON_ID,
	TOOL_BAR_WINDOW_CUT_BUTTON_ID,
	TOOL_BAR_WINDOW_COPY_BUTTON_ID,
	TOOL_BAR_WINDOW_PASTE_BUTTON_ID,
	TOOL_BAR_WINDOW_DELETE_BUTTON_ID,
	TOOL_BAR_WINDOW_ABOUT_BUTTON_ID,
	TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS

} TOOL_BAR_WINDOW_BUTTONS;

void ToolBarWindowAddButton( WORD wBitmap, int nCommand );

BOOL ToolBarWindowAddButtons();

void ToolBarWindowAutoSize();

BOOL ToolBarWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL ToolBarWindowGetRect( LPRECT lpRect );
