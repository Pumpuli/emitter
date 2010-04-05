#include "global.h"
#include "ui_splash.h"
#include "ui_dialog.h"
#include "ui.h"
#include "resource.h"
#include "language.h"

ui::splash_dialog_t::splash_dialog_t()
{
	create(IDD_SPLASH);
}

ui::splash_dialog_t::~splash_dialog_t()
{
}

INT_PTR CALLBACK ui::splash_dialog_t::dialog_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case IDC_SPLASH_NEW:
			::DestroyWindow(hwnd);
			return TRUE;

		case IDCANCEL:
			::DestroyWindow(hwnd);
			return TRUE;
		}
		return FALSE;

	case WM_INITDIALOG:
		{
			::SetDlgItemText(hwnd, IDC_SPLASH_BUSY, text::ui(text::SPLASH_BUSY, "Etsitään..."));
			::SetDlgItemText(hwnd, IDC_SPLASH_NEW, text::ui(text::SPLASH_NEW, "Uusi"));
			::SetDlgItemText(hwnd, IDCANCEL, text::ui(text::SPLASH_EXIT, "Lopeta"));

			HICON icon = ::LoadIcon(g_instance, MAKEINTRESOURCE(IDI_MAIN));
			::SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon));
			::SendMessage(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon));
		}
		return TRUE;

	case WM_CLOSE:
		::DestroyWindow(hwnd);
		return TRUE;

	case WM_DESTROY:
		::PostQuitMessage(0);
		return TRUE;
	}

	return FALSE;
}

void ui::splash_dialog_t::destroy()
{
	::PostQuitMessage(0);
	delete this;
}
