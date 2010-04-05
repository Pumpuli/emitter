#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "global.h"
#include <string>

namespace text
{
	enum text_id_t
	{
		SPLASH_BUSY,
		SPLASH_NEW,
		SPLASH_EXIT
	};

	const wchar_t* ui(text_id_t id, const std::string& fallback);
}

#endif
