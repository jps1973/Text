// Text.cpp

#include "Text.h"

BOOL UpdateMenuTtem( HMENU hMenu, int nItemID, BOOL bEnable )
{
	BOOL bResult;

	// See if menu item is to be enabled
	if( bEnable )
	{
		// Menu item is to be enabled

		// Enable menu item
		bResult = EnableMenuItem( hMenu, nItemID, MF_ENABLED );

	} // End of menu item is to be enabled
	else
	{
		// Menu item is to be disabled

		// Disable menu item
		bResult = EnableMenuItem( hMenu, nItemID, MF_DISABLED );

	} // End of menu item is to be disabled

	return bResult;

} // End of function UpdateMenuTtem

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

// Main window procedure
LRESULT CALLBACK MainWndProc( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
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
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Create rich edit window
			if( RichEditWindowCreate( hWndMain, hInstance ) )
			{
				// Successfully created rich edit window
				HFONT hFont;

				// Get (rich edit window font) font
				hFont = ( HFONT )GetStockObject( ANSI_FIXED_FONT );

				// Set rich edit window font
				RichEditWindowSetFont( hFont );

				// Create status bar window
				if( StatusBarWindowCreate( hWndMain, hInstance ) )
				{
					// Successfully created status bar window

					// Get (status bar window) font
					hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

					// Set status bar window font
					StatusBarWindowSetFont( hFont );

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
			RECT rcStatus;
			int nStatusWindowHeight;
			int nRichEditWindowHeight;

			// Store client width and height
			nClientWidth	= ( int )LOWORD( lParam );
			nClientHeight	= ( int )HIWORD( lParam );

			// Size status bar window
			StatusBarWindowSize();

			// Get status window size
			StatusBarWindowGetRect( &rcStatus );

			// Calculate window sizes
			nStatusWindowHeight		= ( rcStatus.bottom - rcStatus.top );
			nRichEditWindowHeight	= ( nClientHeight - nStatusWindowHeight );

			// Move rich edit window
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
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_DROPFILES:
		{
			// A drop files message
			UINT uFileCount;
			HDROP hDrop;
			UINT uWhichFile;
			UINT uFileSize;

			// Allocate string memory
			LPTSTR lpszFilePath = new char[ STRING_LENGTH ];

			// Get drop handle
			hDrop = ( HDROP )wParam;

			// Count dropped files
			uFileCount = DragQueryFile( hDrop, ( UINT )-1, NULL, 0 );

			// Loop through dropped files
			for( uWhichFile = 0; uWhichFile < uFileCount; uWhichFile ++ )
			{
				// Get size of dropped file
				uFileSize = DragQueryFile( hDrop, uWhichFile, NULL, 0 );

				// Ensure that file size is valid
				if( uFileSize != 0 )
				{
					// File size is valid

					// Get file path
					if( DragQueryFile( hDrop, uWhichFile, lpszFilePath, ( uFileSize + sizeof( char ) ) ) )
					{
						// Successfully got file path

						// Display file path
						MessageBox( hWndMain, lpszFilePath, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					} // End of successfully got file path

				} // End of file size is valid

			}; // End of loop through dropped files

			// Free string memory
			delete [] lpszFilePath;

			// Break out of switch
			break;

		} // End of a drop files message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case IDM_EDIT_UNDO:
				{
					// An edit undo command

					// Undo
					RichEditWindowUndo();

					// Clear status bar window
					StatusBarWindowSetText( NULL );

					// Break out of switch
					break;

				} // End of an edit undo command
				case IDM_EDIT_REDO:
				{
					// An edit redo command

					// Redo
					RichEditWindowRedo();

					// Clear status bar window
					StatusBarWindowSetText( NULL );

					// Break out of switch
					break;

				} // End of an edit redo command
				case IDM_EDIT_CUT:
				{
					// An edit cut command

					// Cut text
					if( RichEditWindowCut() )
					{
						// Successfully cut text

						// Show message on status bar window
						StatusBarWindowSetText( RICH_EDIT_WINDOW_SUCCESSFULLY_CUT_TEXT_STATUS_MESSAGE );

					} // End of successfully cut text

					// Break out of switch
					break;

				} // End of an edit cut command
				case IDM_EDIT_COPY:
				{
					// An edit copy command

					// Copy text
					if( RichEditWindowCopy() )
					{
						// Successfully copied text

						// Show message on status bar window
						StatusBarWindowSetText( RICH_EDIT_WINDOW_SUCCESSFULLY_COPIED_TEXT_STATUS_MESSAGE );

					} // End of successfully copied text

					// Break out of switch
					break;

				} // End of an edit copy command
				case IDM_EDIT_PASTE:
				{
					// An edit paste command

					// Show message
					RichEditWindowPaste();

					// Clear status bar window
					StatusBarWindowSetText( NULL );

					// Break out of switch
					break;

				} // End of an edit paste command
				case IDM_EDIT_DELETE:
				{
					// An edit delete command

					// Show message
					RichEditWindowDelete();

					// Clear status bar window
					StatusBarWindowSetText( NULL );

					// Break out of switch
					break;

				} // End of an edit delete command
				case IDM_EDIT_SELECT_ALL:
				{
					// An edit select all command

					// Select all text on rich edit window
					RichEditWindowSelect();

					// Clear status bar window
					StatusBarWindowSetText( NULL );

					// Break out of switch
					break;

				} // End of an edit select all command
				case IDM_HELP_ABOUT:
				{
					// A help about command

					// Clear status bar window
					StatusBarWindowSetText( NULL );

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about command
				default:
				{
					// Default command

					// Source window is ( HWND )lParam

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

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
					// A help about command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about command
				default:
				{
					// Default system command

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_NOTIFY:
		{
			// A notify message

			// Call default procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of a notify message
		case WM_CONTEXTMENU:
		{
			// A context menu message
			HMENU hMenuContext;
			BOOL bIsTextSelected;

			// See if any text is selected on rich edit window
			bIsTextSelected = RichEditWindowIsTextSelected();

			// Load context menu
			hMenuContext = LoadMenu( NULL, MAKEINTRESOURCE( IDR_CONTEXT_MENU ) );

			// Update context menu items
			UpdateMenuTtem( hMenuContext, IDM_EDIT_UNDO,	RichEditWindowCanUndo() );
			UpdateMenuTtem( hMenuContext, IDM_EDIT_REDO,	RichEditWindowCanRedo() );
			UpdateMenuTtem( hMenuContext, IDM_EDIT_CUT,		bIsTextSelected );
			UpdateMenuTtem( hMenuContext, IDM_EDIT_COPY,	bIsTextSelected );
			UpdateMenuTtem( hMenuContext, IDM_EDIT_PASTE,	RichEditWindowCanPaste() );
			UpdateMenuTtem( hMenuContext, IDM_EDIT_DELETE,	bIsTextSelected );

			// Show context menu
			TrackPopupMenu( GetSubMenu( hMenuContext, 0 ), ( TPM_LEFTALIGN | TPM_LEFTBUTTON ), LOWORD( lParam ), HIWORD( lParam ), 0, hWndMain, NULL );

			// Break out of switch
			break;

		} // End of a context menu message
		case WM_CLOSE:
		{
			// A close message

			// Save rich edit window text
			if( RichEditWindowSaveText( TEXT_FILE_NAME ) )
			{
				// Successfully saved rich edit window text

				// Destroy main window
				DestroyWindow( hWndMain );

			} // End of successfully saved rich edit window text
			else
			{
				// Unable to save rich edit window text

				// Ensure that user is ok to close
				if( MessageBox( hWndMain, RICH_EDIT_WINDOW_UNABLE_TO_SAVE_WARNING_MESSAGE, WARNING_MESSAGE_CAPTION, ( MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 ) ) == IDYES )
				{
					// User is ok to close

					// Destroy main window
					DestroyWindow( hWndMain );

				} // End of user is ok to close

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

			// Call default window procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function MainWndProc

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow )
{
	MSG msg;

	HWND hWndRunning;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Attempt to find running instance of window
	hWndRunning = FindWindow( MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE );

	// See if running instance of window was found
	if( hWndRunning )
	{
		// Running instance of window was found

		// Set running instance as foreground window
		SetForegroundWindow( hWndRunning );

	} // End of running instance of window was found
	else
	{
		// Running instance of window was not found
		WNDCLASSEX wcMain;

		// Clear main window class structure
		ZeroMemory( &wcMain, sizeof( wcMain ) );

		// Initialise main window class structure
		wcMain.cbSize			= sizeof( WNDCLASSEX );
		wcMain.lpfnWndProc		= MainWndProc;
		wcMain.hInstance		= hInstance;
		wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
		wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
		wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
		wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
		wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
		wcMain.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
		wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON;

		// Register main window class
		if( RegisterClassEx( &wcMain ) )
		{
			// Successfully registered main window class
			HWND hWndMain;

			// Create main window
			hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE, MAIN_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT,  CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL );

			// Ensure that main window was created
			if( hWndMain )
			{
				// Successfully created main window
				HMENU hMenuSystem;
				LPWSTR *lpszArgumentList;
				int nArgumentCount;

				// Get system menu
				hMenuSystem = GetSystemMenu( hWndMain, FALSE );

				// Add separator to system menu
				InsertMenu( hMenuSystem, SYSTEM_MENU_SEPARATOR_ITEM_POSITION, ( MF_BYPOSITION | MF_SEPARATOR ), 0, NULL );

				// Add about item to system menu
				InsertMenu( hMenuSystem, SYSTEM_MENU_ABOUT_ITEM_POSITION, MF_BYPOSITION, IDM_HELP_ABOUT, SYSTEM_MENU_ABOUT_ITEM_TEXT );

				// Get argument list
				lpszArgumentList = CommandLineToArgvW( GetCommandLineW(), &nArgumentCount );

				// Ensure that argument list was got
				if( lpszArgumentList )
				{
					// Successfully got argument list
					int nWhichArgument;
					int nSizeNeeded;
					int nWideArgumentLength;

					// Allocate string memory
					LPTSTR lpszArgument = new char[ STRING_LENGTH ];

					// Loop through arguments
					for( nWhichArgument = 1; nWhichArgument < nArgumentCount; nWhichArgument ++ )
					{
						// Get wide argument length
						nWideArgumentLength = lstrlenW( lpszArgumentList[ nWhichArgument ] );

						// Get size required for argument
						nSizeNeeded = WideCharToMultiByte( CP_UTF8, 0, lpszArgumentList[ nWhichArgument ], nWideArgumentLength, NULL, 0, NULL, NULL );

						// Convert argument to ansi
						WideCharToMultiByte( CP_UTF8, 0, lpszArgumentList[ nWhichArgument ], nWideArgumentLength, lpszArgument, nSizeNeeded, NULL, NULL );

						// Terminate argument
						lpszArgument[ nSizeNeeded ] = ( char )NULL;

						// Display argument
						MessageBox( hWndMain, lpszArgument, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					}; // End of loop through arguments

					// Free string memory
					delete [] lpszArgument;

				} // End of successfully got argument list

				// Show main window
				ShowWindow( hWndMain, nCmdShow );

				// Update main window
				UpdateWindow( hWndMain );

				// Load rich edit window text
				if( RichEditWindowLoadText( TEXT_FILE_NAME ) )
				{
					// Successfully loaded rich edit window text

					// Select rich edit window text
					RichEditWindowSelect();

				} // End of successfully loaded rich edit window text

				// Message loop
				while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
				{
					// Translate message
					TranslateMessage( &msg );

					// Dispatch message
					DispatchMessage( &msg );

				}; // End of message loop

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

	} // End of running instance of window was not found

	return msg.wParam;

} // End of function WinMain
