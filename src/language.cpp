#include "global.h"
#include "language.h"
#include <string>
#include <windows.h>

#define CONVERSION_BUFFERS 4

static const wchar_t* get_default_text(text::text_id_t id)
{
	switch (id)
	{
	case text::EMITTER:
		return L"Emitter";

	case text::EXIT:
		return L"Exit";

	case text::SPLASH_BUSY:
		return L"Looking for server in local area network...";

	case text::SPLASH_RECENT:
		return L"Recent";

	case text::SPLASH_NEW:
		return L"Create event";
	}

	return L"[unknown]";
}

const wchar_t* text::ui(text_id_t id)
{
	static wchar_t* buffers[CONVERSION_BUFFERS] = {0};
	static int current = CONVERSION_BUFFERS - 1;

	return get_default_text(id);

	current = (current + 1) % CONVERSION_BUFFERS;
	wchar_t* buffer = buffers[current];

	delete buffer;

	// Todo: get the text from language file.
	std::string text = "[unknown]";

	int length = ::MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);

	if (!length)
		return NULL;

	buffer = new wchar_t[length];

	::MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, buffer, length);

	return buffer;
}
