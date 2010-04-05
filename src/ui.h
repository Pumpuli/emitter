#ifndef UI_H
#define UI_H

#include "global.h"
#include <list>
#include <windows.h>

namespace ui
{
	extern const wchar_t g_window_class_name[];
	extern HINSTANCE g_instance;
	extern std::list<HWND> g_dialogs;

	void initialize(HINSTANCE instance);
	void create_splash_dialog();

	LRESULT CALLBACK main_window_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
}

#endif
