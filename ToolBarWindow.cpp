// ToolBarWindow.cpp

#include "ToolBarWindow.h"

// Global variables
static HWND g_hWndToolBar;
static HIMAGELIST g_hImageList;
static TBBUTTON g_tbButtons[ TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS ];
static int g_nNextButtonID = 0;

void ToolBarWindowAddButton( WORD wBitmap, int nCommand )
{
	int nBitmap;

	// Clear tool bar button structure
	ZeroMemory( &( g_tbButtons[ g_nNextButtonID ] ), sizeof( TBBUTTON) );

	// Get bitmap integer
	nBitmap = MAKELONG( wBitmap, TOOL_BAR_WINDOW_IMAGE_LIST_ID );

	// Update tool bar button structure
	g_tbButtons[ g_nNextButtonID ].iBitmap		= nBitmap;
	g_tbButtons[ g_nNextButtonID ].idCommand	= nCommand;
	g_tbButtons[ g_nNextButtonID ].fsState		= TBSTATE_ENABLED;
	g_tbButtons[ g_nNextButtonID ].fsStyle		= BTNS_AUTOSIZE;
	g_tbButtons[ g_nNextButtonID ].iString		= 0;

	// Advance to next button
	g_nNextButtonID ++;

} // End of function ToolBarWindowAddButton

BOOL ToolBarWindowAddButtons()
{
	BOOL bResult;

	// Set tool bar button structure size
	SendMessage( g_hWndToolBar, TB_BUTTONSTRUCTSIZE, ( WPARAM )sizeof( TBBUTTON ), ( LPARAM )0 );

	// Add buttons to tool bar window
	bResult = SendMessage( g_hWndToolBar, TB_ADDBUTTONS, ( WPARAM )TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS, ( LPARAM )&g_tbButtons );

	return bResult;

} // End of function ToolBarWindowAddButtons

void ToolBarWindowAddSeparator()
{
	// Clear tool bar button structure
	ZeroMemory( &( g_tbButtons[ g_nNextButtonID ] ), sizeof( TBBUTTON) );

	// Update tool bar button structure
	g_tbButtons[ g_nNextButtonID ].fsStyle		= BTNS_SEP;

	// Advance to next button
	g_nNextButtonID ++;

} // End of function ToolBarWindowAddButton

void ToolBarWindowAutoSize()
{
	// Auto-size tool bar window
	SendMessage( g_hWndToolBar, TB_AUTOSIZE, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function ToolBarWindowAutoSize

BOOL ToolBarWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Create tool bar window
	g_hWndToolBar = CreateWindowEx( TOOL_BAR_WINDOW_EXTENDED_STYLE, TOOL_BAR_WINDOW_CLASS_NAME, TOOL_BAR_WINDOW_TEXT, TOOL_BAR_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, NULL, hInstance, NULL );

	// Ensure that tool bar window was created
	if( g_hWndToolBar )
	{
		// Successfully created tool bar window

		// Create image list
		g_hImageList = ImageList_Create( TOOL_BAR_WINDOW_IMAGE_LIST_SIZE, TOOL_BAR_WINDOW_IMAGE_LIST_SIZE, TOOL_BAR_WINDOW_IMAGE_LIST_FLAGS, TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS, TOOL_BAR_WINDOW_IMAGE_LIST_GROW );

		// Assign image list to toolbar
		SendMessage( g_hWndToolBar, TB_SETIMAGELIST, ( WPARAM )TOOL_BAR_WINDOW_IMAGE_LIST_ID, ( LPARAM )g_hImageList );

		// Load images into tool bar
		SendMessage( g_hWndToolBar, TB_LOADIMAGES, ( WPARAM )IDB_STD_SMALL_COLOR, ( LPARAM )HINST_COMMCTRL );

		// Update return value
		bResult = TRUE;

	} // End of successfully created tool bar window

	return bResult;

} // End of function ToolBarWindowCreate

BOOL ToolBarWindowGetRect( LPRECT lpRect )
{
	// Get tool bar window rect
	return GetWindowRect( g_hWndToolBar, lpRect );

} // End of function ControlWindowGetRect
