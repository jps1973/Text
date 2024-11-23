// ToolBarWindow.cpp

#include "ToolBarWindow.h"

// Global variables
static HWND g_hWndToolBar;
static HIMAGELIST g_hImageList;
static TBBUTTON g_tbButton[ TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS ];

BOOL IsToolBarWindow( HWND hWnd )
{
	// See if supplied window is tool bar window
	return( hWnd == g_hWndToolBar );

} // End of function IsToolBarWindow

void ToolBarWindowAutoSize()
{
	// Auto-size tool bar window
	SendMessage( g_hWndToolBar, TB_AUTOSIZE, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function ToolBarWindowAutoSize

BOOL ToolBarWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Create tool bar window
	g_hWndToolBar = CreateWindowEx( TOOLBAR_WINDOW_EXTENDED_STYLE, TOOLBAR_WINDOW_CLASS_NAME, TOOLBAR_WINDOW_TEXT, TOOLBAR_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that tool bar window was created
	if( g_hWndToolBar )
	{
		// Successfully created tool bar window

		// Create image list
		g_hImageList = ImageList_Create( TOOL_BAR_WINDOW_BUTTON_SIZE, TOOL_BAR_WINDOW_BUTTON_SIZE, ILC_COLOR16 | ILC_MASK, TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS, 0);

		// Assign image list to toop bar window
		SendMessage( g_hWndToolBar, TB_SETIMAGELIST, ( WPARAM )TOOL_BAR_WINDOW_IMAGE_LIST_INDEX, ( LPARAM )g_hImageList );

		// Load button images
		SendMessage( g_hWndToolBar, TB_LOADIMAGES, ( WPARAM )IDB_STD_SMALL_COLOR, ( LPARAM )HINST_COMMCTRL );

		// Initialise toolbar buttons
		ToolBarWindowInitButton( TOOL_BAR_WINDOW_UNDO_BUTTON,	STD_UNDO,	IDM_EDIT_UNDO );
		ToolBarWindowInitButton( TOOL_BAR_WINDOW_REDO_BUTTON,	STD_REDOW,	IDM_EDIT_REDO );
		ToolBarWindowInitButton( TOOL_BAR_WINDOW_CUT_BUTTON,	STD_CUT,	IDM_EDIT_CUT );
		ToolBarWindowInitButton( TOOL_BAR_WINDOW_COPY_BUTTON,	STD_COPY,	IDM_EDIT_COPY );
		ToolBarWindowInitButton( TOOL_BAR_WINDOW_PASTE_BUTTON,	STD_PASTE,	IDM_EDIT_PASTE );
		ToolBarWindowInitButton( TOOL_BAR_WINDOW_DELETE_BUTTON,	STD_DELETE,	IDM_EDIT_DELETE );
		ToolBarWindowInitButton( TOOL_BAR_WINDOW_ABOUT_BUTTON,	STD_HELP,	IDM_HELP_ABOUT );

		// Specify size of toolbar button structure
		SendMessage( g_hWndToolBar, TB_BUTTONSTRUCTSIZE, ( WPARAM )sizeof( TBBUTTON ), ( LPARAM )0 );

		// Add buttons to toolbar
		SendMessage( g_hWndToolBar, TB_ADDBUTTONS, ( WPARAM )TOOL_BAR_WINDOW_NUMBER_OF_BUTTONS, ( LPARAM )&g_tbButton );

		// Resize toolbar
		SendMessage( g_hWndToolBar, TB_AUTOSIZE, ( WPARAM )NULL, ( LPARAM )NULL ); 

		// Show toolbar window
		ShowWindow( g_hWndToolBar,  TRUE);

		// Update return value
		bResult = TRUE;

	} // End of successfully created tool bar window
	return bResult;

} // End of function ToolBarWindowCreate

BOOL ToolBarWindowEnableButton( int nCommandID, BOOL bEnable )
{
	// Enable toolbar window button
	return SendMessage( g_hWndToolBar, TB_ENABLEBUTTON, ( WPARAM )nCommandID, ( LPARAM )bEnable );

} // End of function ToolBarWindowEnableButton

BOOL ToolBarWindowGetRect( LPRECT lpRect )
{
	// Get tool bar window rect
	return GetWindowRect( g_hWndToolBar, lpRect );

} // End of function ToolBarWindowGetRect

void ToolBarWindowInitButton( int nWhichButton, int nImage, int nCommandID )
{
	// Clear toolbar button structure
	ZeroMemory( &( g_tbButton[ nWhichButton ] ), sizeof( TBBUTTON ) );

	// Initialise toolbar button structure
	g_tbButton[ nWhichButton ].iBitmap		= nImage;
	g_tbButton[ nWhichButton ].idCommand	= nCommandID;
	g_tbButton[ nWhichButton ].fsState		= TOOL_BAR_WINDOW_BUTTON_STATE;
	g_tbButton[ nWhichButton ].fsStyle		= TOOL_BAR_WINDOW_BUTTON_STYLE;

} // End of function ToolBarWindowInitButton

BOOL ToolBarWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move tool bar window
	return MoveWindow( g_hWndToolBar, nX, nY, nWidth, nHeight, bRepaint );

} // End of function ToolBarWindowMove

HWND ToolBarWindowSetFocus()
{
	// Focus on tool bar window
	return SetFocus( g_hWndToolBar );

} // End of function ToolBarWindowSetFocus

void ToolBarWindowSetFont( HFONT hFont )
{
	// Set tool bar window font
	SendMessage( g_hWndToolBar, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function ToolBarWindowSetFont
