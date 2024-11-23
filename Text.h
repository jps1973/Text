// Text.h

#define WINVER																	_WIN32_WINNT_WIN10
#define _WIN32_WINNT															_WIN32_WINNT_WIN10

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"
#include "Resource.h"

#include "Registry.h"

#include "RichEditWindow.h"
#include "StatusBarWindow.h"
#include "ToolBarWindow.h"

#define MAIN_WINDOW_CLASS_NAME													"Main Text Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON_NAME												IDI_APPLICATION
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_MENU_NAME												MAKEINTRESOURCE( IDR_MAIN_MENU )

#define MAIN_WINDOW_EXTENDED_STYLE												( WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES )
#define MAIN_WINDOW_STYLE														WS_OVERLAPPEDWINDOW
#define MAIN_WINDOW_TEXT														"Text"

#define MAIN_WINDOW_MINIMUM_WIDTH												320
#define MAIN_WINDOW_MINIMUM_HEIGHT												200

#define SYSTEM_MENU_SEPARATOR_ITEM_POSITION										5
#define SYSTEM_MENU_ABOUT_ITEM_POSITION											6
#define SYSTEM_MENU_ABOUT_ITEM_TEXT												"About"

#define ABOUT_MESSAGE_TEXT														"Text\r\n"							\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"November 2024"

#define REGISTRY_TOP_LEVEL_KEY													HKEY_CURRENT_USER
#define REGISTRY_SUB_KEY_PATH													"SOFTWARE\\Jim Smith\\Text"
#define REGISTRY_LEFT_VALUE_NAME												"left"
#define REGISTRY_TOP_VALUE_NAME													"top"
#define REGISTRY_WIDTH_VALUE_NAME												"width"
#define REGISTRY_HEIGHT_VALUE_NAME												"height"

#define TEXT_FILE_NAME															"Text.txt"

#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to create main window"
#define UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE						"Unable to register main window class"
