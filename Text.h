// Text.h

#pragma once

#include "Ascii.h"
#include "Common.h"

#include "Resource.h"

#include "ControlWindow.h"
#include "SplashScreenWindow.h"
#include "ToolBarWindow.h"

#include "RegistryKeyClass.h"

#define MAIN_WINDOW_CLASS_NAME													"Main Text Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON_NAME												IDI_APPLICATION
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_ICON_SMALL											LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )

#define MAIN_WINDOW_EXTENDED_STYLE												( WS_EX_TOOLWINDOW | WS_EX_TOPMOST )
#define MAIN_WINDOW_STYLE														( WS_OVERLAPPEDWINDOW | WS_BORDER )
#define MAIN_WINDOW_TEXT														"Text"

#define MAIN_WINDOW_MINIMUM_WIDTH												320
#define MAIN_WINDOW_MINIMUM_HEIGHT												200

#define REGISTRY_KEY															HKEY_CURRENT_USER
#define REGISTRY_SUB_KEY														"Software\\Jim Smith\\Text"

#define TEXT_FILE_NAME															"Text.txt"

#define ABOUT_MESSAGE_TEXT														"Text\r\n"							\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"September 2025"

#define UNABLE_TO_SAVE_TEXT_WARNING_MESSAGE										"Unable to save text.\r\n\r\nDo you still want to close?"

#define UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE						"Unable to Register Main Window Class"
#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to Create Main Window"
