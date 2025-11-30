// Menu.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

BOOL MenuEnableItem( HMENU hMenu, UINT uWhichItem, BOOL bEnableOrDisable );

BOOL MenuEnableItem( HWND hWnd, UINT uWhichItem, BOOL bEnableOrDisable );
