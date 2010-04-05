#include "global.h"
#include "ui_dialog.h"
#include <list>
#include <stdexcept>
#include <iostream>
#include <windows.h>
#include "ui.h"

static std::list<HWND> g_dialogs;

static INT_PTR CALLBACK generic_dialog_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	ui::dialog_t* instance;

	if (msg == WM_INITDIALOG)
	{
		instance = reinterpret_cast<ui::dialog_t*>(lparam);
		::SetWindowLongPtr(hwnd, DWLP_USER, reinterpret_cast<LONG_PTR>(instance));
	}
	else
		instance = reinterpret_cast<ui::dialog_t*>(::GetWindowLongPtr(hwnd, DWLP_USER));

	if (!instance)
		return FALSE;

	return instance->dialog_procedure(hwnd, msg, wparam, lparam);
}

ui::dialog_t::dialog_t(WORD resource_id, HWND parent):
	m_hwnd(NULL)
{
}

ui::dialog_t::~dialog_t()
{
	g_dialogs.remove(m_hwnd);
}

void ui::dialog_t::create(WORD resource_id, HWND parent)
{
	m_hwnd = ::CreateDialogParam(g_instance, MAKEINTRESOURCE(resource_id), parent, generic_dialog_procedure, reinterpret_cast<LPARAM>(this));

	if (!m_hwnd)
		throw std::runtime_error("Creating window failed.");

	g_dialogs.push_back(m_hwnd);
}

bool ui::process_dialog_message(MSG& msg)
{
	for (std::list<HWND>::const_iterator dialog = g_dialogs.begin(); dialog != g_dialogs.end(); ++dialog)
	{
		if (::IsDialogMessage(*dialog, &msg))
			return true;
	}

	return false;
}
