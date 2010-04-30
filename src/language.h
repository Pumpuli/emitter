#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "global.h"
#include <string>

namespace text
{
	enum text_id_t
	{
		EMITTER,
		EXIT,
		SPLASH_BUSY,
		SPLASH_RECENT,
		SPLASH_NEW
	};

	const wchar_t* ui(text_id_t id);
}

#endif
