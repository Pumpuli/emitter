#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include "global.h"
#include <windows.h>

namespace ui
{
	class dialog_t
	{
	public:
		dialog_t(WORD resource_id, HWND parent = NULL);
		virtual ~dialog_t();

		virtual INT_PTR CALLBACK dialog_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;

	protected:
		HWND m_hwnd;

		void create(WORD resource_id, HWND parent = NULL);
	};

	bool process_dialog_message(MSG& msg);
}

#endif
