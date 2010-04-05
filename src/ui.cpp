#include "global.h"
#include "ui.h"
#include <stdexcept>
#include <windows.h>
#include <commctrl.h>

const wchar_t ui::g_window_class_name[] = L"emitter-window-class";
HINSTANCE ui::g_instance = NULL;
std::list<HWND> ui::g_dialogs;

void ui::initialize(HINSTANCE instance)
{
	g_instance = instance;

	::InitCommonControls();

	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = main_window_procedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hIcon = NULL;
	wc.hCursor = ::LoadIcon(g_instance, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_3DFACE + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_window_class_name;

	if (!::RegisterClass(&wc))
		throw std::runtime_error("Registering window class failed.");
}

LRESULT CALLBACK ui::main_window_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}
