// Menu.cpp

#include "Menu.h"

BOOL MenuEnableItem( HMENU hMenu, UINT uWhichItem, BOOL bEnableOrDisable )
{
	BOOL bResult = FALSE;

	// See if menu is to be enabled
	if( bEnableOrDisable == TRUE )
	{
		// Menu is to be enabled

		// Enable menu item
		bResult = EnableMenuItem( hMenu, uWhichItem, MF_ENABLED );

	} // End of menu is to be enabled
	else
	{
		// Menu is to be disabled

		// Disable menu item
		bResult = EnableMenuItem( hMenu, uWhichItem, MF_DISABLED );

	} // End of menu is to be disabled

	return bResult;

} // End of function MenuEnableItem

BOOL MenuEnableItem( HWND hWnd, UINT uWhichItem, BOOL bEnableOrDisable )
{
	BOOL bResult = FALSE;

	HMENU hMenu;

	// Get menu
	hMenu = GetMenu( hWnd );

	// Ensure that menu was got
	if( hMenu )
	{
		// Successfully got menu

		// Enable menu item
		bResult = MenuEnableItem( hMenu, uWhichItem, bEnableOrDisable );

	} // End of successfully got menu

	return bResult;

} // End of function MenuEnableItem
