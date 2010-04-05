#include "global.h"
#include "main.h"
#include <iostream>
#include <windows.h>
#include "ui.h"
#include "ui_dialog.h"
#include "ui_splash.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance, LPSTR cmd_line, int cmd_show)
{
	try
	{
		ui::initialize(instance);

		// Splash dialog takes care of creating main window.
		ui::create_splash_dialog();

		MSG msg;
		while (::GetMessage(&msg, NULL, 0, 0) > 0)
		{
			if (!ui::process_dialog_message(msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}

		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "ERROR!?!?!?" << std::endl << e.what();
		return 2;
	}
}
