#ifndef UI_SPLASH_H
#define UI_SPLASH_H

#include "global.h"
#include <windows.h>
#include "ui_dialog.h"

namespace ui
{
	class splash_dialog_t: public ui::dialog_t
	{
	public:
		splash_dialog_t();
		~splash_dialog_t();

		INT_PTR CALLBACK dialog_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		void destroy();
	private:
		HWND m_hwnd;
	};
}

#endif
