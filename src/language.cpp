#include "global.h"
#include "language.h"
#include <string>
#include <windows.h>

#define CONVERSION_BUFFERS 4

const wchar_t* text::ui(text_id_t id, const std::string& fallback)
{
	static wchar_t* buffers[CONVERSION_BUFFERS] = {0};
	static int current = CONVERSION_BUFFERS - 1;

	current = (current + 1) % CONVERSION_BUFFERS;
	wchar_t* buffer = buffers[current];

	delete buffer;

	// Todo: get the text from language file.
	std::string text = fallback;

	int length = ::MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);

	if (!length)
		return NULL;

	buffer = new wchar_t[length];

	::MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, buffer, length);

	return buffer;
}
