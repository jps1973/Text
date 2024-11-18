// Text.cpp

#include "Text.h"

// Global variables
static HMENU g_hMenuContext;

BOOL UpdatePasteButtons( HWND hWndMain )
{
	BOOL bResult = FALSE;

	HMENU hMenuMain;

	// Get main menu
	hMenuMain = GetMenu( hWndMain );

	// See if clipboard contains text
	if( IsClipboardFormatAvailable( CF_TEXT ) )
	{
		// Clipboard contains text

	} // End of clipboard contains text
	else
	{
		// Clipboard does not contain text

	} // End of clipboard does not contain text

	return bResult;

} // End of function UpdatePasteButtons

void RichEditWindowUpdateFunction( HWND hWndMain, BOOL bCanUndo, BOOL bCanRedo )
{
	HMENU hMenuMain;

	// Get main menu
	hMenuMain = GetMenu( hWndMain );

	// See if undo is possible
	if( bCanUndo )
	{
		// Undo is possible

	} // End of undo is possible
	else
	{
		// Undo is not possible

	} // End of undo is not possible

	// See if redo is possible
	if( bCanRedo )
	{
		// Redo is possible

	} // End of redo is possible
	else
	{
		// Redo is not possible

	} // End of redo is not possible

} // End of function RichEditWindowUpdateFunction

void RichEditWindowSelectionChangeFunction( HWND hWndMain, int nLengthOfSelection )
{
	HMENU hMenuMain;

	// Get main menu
	hMenuMain = GetMenu( hWndMain );

	// See if any text is selected
	if( nLengthOfSelection > 0 )
	{
		// Some text is selected

	} // End of some text is selected
	else
	{
		// No text is selected

	} // End of no text is selected

} // End of function RichEditWindowSelectionChangeFunction

int ShowAboutMessage( HWND hWndParent )
{
	int nResult = 0;

	MSGBOXPARAMS mbp;

	// Clear message box parameter structure
	ZeroMemory( &mbp, sizeof( mbp ) );

	// Initialise message box parameter structure
	mbp.cbSize		= sizeof( MSGBOXPARAMS );
	mbp.hwndOwner	= hWndParent;
	mbp.hInstance	= NULL;
	mbp.lpszText	= ABOUT_MESSAGE_TEXT;
	mbp.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	mbp.dwStyle		= ( MB_OK | MB_USERICON );
	mbp.lpszIcon	= MAIN_WINDOW_CLASS_ICON_NAME;

	// Show message box
	nResult = MessageBoxIndirect( &mbp );

	return nResult;

} // End of function ShowAboutMessage

LRESULT CALLBACK MainWindowProcedure( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;

			// Get instance
			hInstance = GetModuleHandle( NULL );

			// Create rich edit window
			if( RichEditWindowCreate( hWndMain, hInstance ) )
			{
				// Successfully created rich edit window
				HFONT hFont;

				// Get rich edit window font
				hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

				// Set rich edit window font
				RichEditWindowSetFont( hFont );

				// Create status bar window
				if( StatusBarWindowCreate( hWndMain, hInstance ) )
				{
					// Successfully created status bar window

					// Get status bar window font
					hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

					// Set status bar window font
					StatusBarWindowSetFont( hFont );

					// Load context menu
					g_hMenuContext = LoadMenu( NULL, MAKEINTRESOURCE( IDR_CONTEXT_MENU ) );

				} // End of successfully created status bar window

			} // End of successfully created rich edit window

			// Break out of switch
			break;

		} // End of a create message
		case WM_SIZE:
		{
			// A size message
			int nClientWidth;
			int nClientHeight;
			RECT rcStatusBar;
			int nStatusBarWindowHeight;
			int nRichEditWindowHeight;

			// Get client size
			nClientWidth	= LOWORD( lParam );
			nClientHeight	= HIWORD( lParam );

			// Size status bar window
			StatusBarWindowSize();

			// Get status bar window size
			StatusBarWindowGetRect( &rcStatusBar );

			// Calculate window sizes
			nStatusBarWindowHeight	= ( rcStatusBar.bottom - rcStatusBar.top );
			nRichEditWindowHeight	= ( nClientHeight - nStatusBarWindowHeight );

			// Move control windows
			RichEditWindowMove( 0, 0, nClientWidth, nRichEditWindowHeight, TRUE );

			// Break out of switch
			break;

		} // End of a size message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on rich edit window
			RichEditWindowSetFocus();

			// Break out of switch
			break;

		} // End of an activate message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO *lpMinMaxInfo = ( MINMAXINFO * )lParam;

			// Update minimum size
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case IDM_HELP_ABOUT:
				{
					// A help about command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about command
				case IDM_FILE_EXIT:
				{
					// A file exit command

					// Destroy main window
					DestroyWindow( hWndMain );

					// Break out of switch
					break;

				} // End of a file exit command
				default:
				{
					// Default command


					// See if command is from rich edit window
					if( IsRichEditWindow( ( HWND )lParam ) )
					{
						// Command is from rich edit window

						// Handle command from rich edit window
						if( !( RichEditWindowHandleCommandMessage( hWndMain, wParam, lParam, &RichEditWindowUpdateFunction ) ) )
						{
							// Command was not handled from rich edit window

							// Call default procedure
							lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

						} // End of command was not handled from rich edit window

					} // End of command is from rich edit window
					else
					{
						// Command is not from rich edit window

						// Call default procedure
						lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					} // End of command is not from rich edit window

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_SYSCOMMAND:
		{
			// A system command message

			// Select system command 
			switch( LOWORD( wParam ) )
			{
				case IDM_HELP_ABOUT:
				{
					// A help about system command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about system command
				default:
				{
					// Default system command

					// Call default window procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_CONTEXTMENU:
		{
			// A context menu message

			// Show context menu
			TrackPopupMenu( GetSubMenu( g_hMenuContext, 0 ), ( TPM_LEFTALIGN | TPM_LEFTBUTTON ), LOWORD( lParam ), HIWORD( lParam ), 0, hWndMain, NULL );

			// Break out of switch
			break;

		} // End of a context menu message
		case WM_CLOSE:
		{
			// A close message

			// Save rich edit window text
			if( RichEditWindowSave( TEXT_FILE_NAME ) )
			{
				// Successfully saved rich edit window text

				// Destroy main window
				DestroyWindow( hWndMain );

			} // End of successfully saved rich edit window text
			else
			{
				// Unable to save rich edit window text

				// Ensure that user is happy to continue
				if( MessageBox( hWndMain, RICH_EDIT_WINDOW_UNABLE_TO_SAVE_WARNING_MESSAGE, WARNING_MESSAGE_CAPTION, ( MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 ) ) == IDYES )
				{
					// User is happy to continue

					// Destroy main window
					DestroyWindow( hWndMain );

				} // End of user is happy to continue

			} // End of unable to save rich edit window text

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function MainWindowProcedure

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE,  LPSTR, int nCmdShow )
{
	MSG msg;

	HWND hWndRunning;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Attempt to find running instance of window
	hWndRunning = FindWindow( MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT );

	// See if running instance of window was found
	if( hWndRunning )
	{
		// Successfully found running instance of window

		// Set running instance as foreground window
		SetForegroundWindow( hWndRunning );

	} // End of successfully found running instance of window
	else
	{
		// Unable to find running instance of window
		HMODULE hModuleRichEdit;

		// Load rich edit library module
		hModuleRichEdit = LoadLibrary( RICH_EDIT_WINDOW_LIBRARY_NAME );

		// Ensure that rich edit library module was loaded
		if( hModuleRichEdit )
		{
			// Successfully loaded rich edit library module
			WNDCLASSEX wcMain;

			// Clear main window class structure
			ZeroMemory( &wcMain, sizeof( wcMain ) );

			// Initialise main window class structure
			wcMain.cbSize			= sizeof( WNDCLASSEX );
			wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
			wcMain.lpfnWndProc		= MainWindowProcedure;
			wcMain.hInstance		= hInstance;
			wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
			wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
			wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
			wcMain.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
			wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
			wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON;

			// Register main window class
			if( RegisterClassEx( &wcMain ) )
			{
				// Successfully registered main window class
				HWND hWndMain;

				// Create main window
				hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT, MAIN_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL );

				// Ensure that main window was created
				if( hWndMain )
				{
					// Successfully created main window
					HMENU hMenuSystem;

					// Allocate string memory
					LPTSTR lpszStatusMessage = new char[ STRING_LENGTH ];

					// Get system menu
					hMenuSystem = GetSystemMenu( hWndMain, FALSE );

					// Add separator to system menu
					InsertMenu( hMenuSystem, SYSTEM_MENU_SEPARATOR_ITEM_POSITION, ( MF_BYPOSITION | MF_SEPARATOR ), 0, NULL );

					// Add about item to system menu
					InsertMenu( hMenuSystem, SYSTEM_MENU_ABOUT_ITEM_POSITION, MF_BYPOSITION, IDM_HELP_ABOUT, SYSTEM_MENU_ABOUT_ITEM_TEXT );

					// Show main window
					ShowWindow( hWndMain, nCmdShow );

					// Update main window
					UpdateWindow( hWndMain );

					// Load text into rich edit window
					if( RichEditWindowLoad( TEXT_FILE_NAME ) )
					{
						// Successfully loaded text into rich edit window

						// Select rich edit window text
						RichEditWindowSelect();

					} // End of successfully loaded text into rich edit window

					// Main message loop
					while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
					{
						// Translate message
						TranslateMessage( &msg );

						// Dispatch message
						DispatchMessage( &msg );

					}; // End of main message loop

					// Free string memory
					delete [] lpszStatusMessage;

				} // End of successfully created main window
				else
				{
					// Unable to create main window

					// Display error message
					MessageBox( NULL, UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

				} // End of unable to create main window

			} // End of successfully registered main window class
			else
			{
				// Unable to register main window class

				// Display error message
				MessageBox( NULL, UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

			} // End of unable to register main window class

			// Free rich edit library module
			FreeLibrary( hModuleRichEdit );

		} // End of successfully loaded rich edit library module
		else
		{
			// Unable to load rich edit library module

			// Display error message
			MessageBox( NULL, RICH_EDIT_WINDOW_UNABLE_TO_LOAD_RICH_EDIT_LIBRARY_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to load rich edit library module

	} // End of unable to find running instance of window

	return msg.wParam;

} // End of function WinMain