// RichTextWindow.h

#pragma once

#include <windows.h>
#include <richedit.h>

#include "Ascii.h"
#include "Common.h"

#define RICH_EDIT_LIBRARY_NAME													"RICHED20.DLL"

#define RICH_TEXT_WINDOW_CLASS_NAME												RICHEDIT_CLASS

#define RICH_TEXT_WINDOW_EXTENDED_STYLE											0
#define RICH_TEXT_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | /*WS_BORDER |*/ ES_MULTILINE )
#define RICH_TEXT_WINDOW_TEXT													NULL

#define RICH_TEXT_WINDOW_EVENT_MASK												ENM_NONE
#define RICH_TEXT_WINDOW_TEXT_MODE												( TM_PLAINTEXT | TM_MULTILEVELUNDO | TM_MULTICODEPAGE )

BOOL RichTextWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

BOOL RichTextWindowFreeMemory();

BOOL RichTextWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRedraw );

HWND RichTextWindowSetFocus();
