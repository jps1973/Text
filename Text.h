// Text.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"
#include "Resource.h"

#include "Registry.h"

#include "ListBoxWindow.h"
#include "StatusBarWindow.h"

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

#define REGISTRY_TOP_LEVEL_KEY													HKEY_CURRENT_USER
#define REGISTRY_SUB_KEY														"SOFTWARE\\Jim Smith\\Text"

#define ABOUT_MESSAGE_TEXT														"Text\r\n"							\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"November 2024"

#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to create main window"
#define UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE						"Unable to register main window class"
