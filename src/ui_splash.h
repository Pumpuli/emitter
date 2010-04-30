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

	private:
		HWND m_hwnd;
		int m_width;
		int m_height;
		int m_height_expanded;
		bool m_quitting;
		bool m_recent_visible;
	};
}

#endif
