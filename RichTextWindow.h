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

#define RICH_TEXT_WINDOW_FILTER													"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
#define RICH_TEXT_WINDOW_DEFAULT_EXTENSION										"txt"

#define RICH_TEXT_WINDOW_CHECK_MODOFIED_MESSAGE_TEXT							"Text has been modified.\r\n\r\nAre you sure that you want to continue?"

BOOL RichTextWindowCheckModified( HWND hWndParent );

BOOL RichTextWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

BOOL RichTextWindowFreeMemory();

BOOL RichTextWindowIsFilePathValid();

BOOL RichTextWindowIsModified();

BOOL RichTextWindowLoad( HWND hWndParent );

BOOL RichTextWindowLoad( LPCTSTR lpszFilePath );

BOOL RichTextWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRedraw );

BOOL RichTextWindowNew();

BOOL RichTextWindowSave( HWND hWndParent );

BOOL RichTextWindowSave( HWND hWndParent, LPCTSTR lpszFilePath );

BOOL RichTextWindowSaveAs( HWND hWndParent );

HWND RichTextWindowSetFocus();
