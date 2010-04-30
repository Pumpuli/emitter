#include "global.h"
#include "ui_splash.h"
#include "ui_dialog.h"
#include "ui.h"
#include "resource.h"
#include "language.h"

ui::splash_dialog_t::splash_dialog_t():
	m_quitting(true)
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
			m_quitting = false;
			::DestroyWindow(hwnd);
			return TRUE;

		case IDCANCEL:
			::DestroyWindow(hwnd);
			return TRUE;
		}
		return FALSE;

	case WM_INITDIALOG:
		{
			RECT pos;
			::GetWindowRect(hwnd, &pos);

			::SetWindowPos(hwnd, NULL, (::GetSystemMetrics(SM_CXSCREEN) / 2) - ((pos.right - pos.left) / 2), (::GetSystemMetrics(SM_CYSCREEN) / 2) - ((pos.bottom - pos.top) / 2), 0, 0, SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOSENDCHANGING | SWP_NOSIZE | SWP_NOZORDER);

			::SetWindowText(hwnd, text::ui(text::EMITTER));
			::SetDlgItemText(hwnd, IDC_SPLASH_BUSY, text::ui(text::SPLASH_BUSY));
			::SetDlgItemText(hwnd, IDC_SPLASH_NEW, text::ui(text::SPLASH_NEW));
			::SetDlgItemText(hwnd, IDC_SPLASH_RECENT, text::ui(text::SPLASH_RECENT));
			::SetDlgItemText(hwnd, IDCANCEL, text::ui(text::EXIT));

			HICON icon = ::LoadIcon(g_instance, MAKEINTRESOURCE(IDI_MAIN));
			::SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon));
			::SendMessage(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon));
		}
		return TRUE;

	case WM_CLOSE:
		::DestroyWindow(hwnd);
		return TRUE;

	case WM_DESTROY:
		if (!m_quitting)
			create_main_window();
		else
			::PostQuitMessage(0);

		delete this;

		return TRUE;
	}

	return FALSE;
}
