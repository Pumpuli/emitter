#include "global.h"
#include "ui.h"
#include <stdexcept>
#include <windows.h>
#include <commctrl.h>
#include "ui_splash.h"
#include "resource.h"
#include "language.h"

const wchar_t ui::g_window_class_name[] = L"emitter-window-class";
HINSTANCE ui::g_instance = NULL;
std::list<HWND> ui::g_dialogs;
HWND ui::g_main_window = NULL;
HFONT ui::g_main_font = NULL;
HWND ui::g_main_tabs = NULL;

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

void ui::create_splash_dialog()
{
	// splash_dialog_t deletes itself.
	splash_dialog_t* splash = new splash_dialog_t;
}

void ui::create_main_window()
{
	g_main_window = ::CreateWindow(
		g_window_class_name,
		L"Main window",
		WS_POPUP | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		0, 0,
		512, 256,
		NULL, // parent
		NULL, // menu
		g_instance,
		NULL // lpCreateParams
	);

	if (!g_main_window)
		throw std::runtime_error("Creating window failed.");

	::UpdateWindow(g_main_window);
	::ShowWindow(g_main_window, SW_SHOW);
}

LRESULT CALLBACK ui::main_window_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
		{
			g_main_font = ::CreateFont(
				14, // height
				0, // width
				0, // angle of escapement
				0, // orientation
				FW_NORMAL, // weight
				FALSE, // italic
				FALSE, // underline
				FALSE, // strike
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, // output precision
				CLIP_DEFAULT_PRECIS, // clip precision
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				L"MS Shell Dlg"
			);

			if (g_main_font)
				::SendMessage(hwnd, WM_SETFONT, reinterpret_cast<WPARAM>(g_main_font), MAKELPARAM(FALSE, 0));
		}

		{
			RECT pos;
			::GetWindowRect(hwnd, &pos);
			::SetWindowPos(hwnd, NULL, (::GetSystemMetrics(SM_CXSCREEN) / 2) - ((pos.right - pos.left) / 2), (::GetSystemMetrics(SM_CYSCREEN) / 2) - ((pos.bottom - pos.top) / 2), 0, 0, SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOSENDCHANGING | SWP_NOSIZE | SWP_NOZORDER);

			::SetWindowText(hwnd, text::ui(text::EMITTER));

			HICON icon = ::LoadIcon(g_instance, MAKEINTRESOURCE(IDI_MAIN));
			::SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon));
			::SendMessage(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon));
		}

		{
			RECT pos;
			::GetClientRect(hwnd, &pos);

			g_main_tabs = ::CreateWindowEx(
				WS_EX_CLIENTEDGE,
				WC_TABCONTROL,
				NULL,
				TCS_HOTTRACK | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
				0, 0,
				pos.right, pos.bottom,
				hwnd,
				NULL,
				g_instance,
				NULL
			);

			if (g_main_tabs)
			{
				if (g_main_font)
					::SendMessage(g_main_tabs, WM_SETFONT, reinterpret_cast<WPARAM>(g_main_font), MAKELPARAM(FALSE, 0));

				TC_ITEM tab = {0};
				tab.mask = TCIF_TEXT;
				tab.pszText = const_cast<wchar_t*>(text::ui(text::EMITTER));
				::SendMessage(g_main_tabs, TCM_INSERTITEM, 1, reinterpret_cast<LPARAM>(&tab));
				::SendMessage(g_main_tabs, TCM_INSERTITEM, 2, reinterpret_cast<LPARAM>(&tab));
				::SendMessage(g_main_tabs, TCM_INSERTITEM, 2, reinterpret_cast<LPARAM>(&tab));
				::SendMessage(g_main_tabs, TCM_INSERTITEM, 2, reinterpret_cast<LPARAM>(&tab));
			}
		}
		return 0;

	case WM_NCDESTROY:
		if (g_main_font)
			::DeleteObject(g_main_font);
		::PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}
