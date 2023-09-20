#include "allegro5/color.h"

//ALLEGRO_COLOR get_color(const char* hexcode)
//{
//	if (strlen(hexcode) != 6)
//		return al_map_rgb(255, 255, 255);
//
//	const int code = strtol(hexcode, NULL, 16);
//
//	const int red = (code >> 16) & 0xFF;
//	const int green = (code >> 8) & 0xFF;
//	const int blue = (code) & 0xFF;
//
//	return al_map_rgb(red, green, blue);
//}

ALLEGRO_COLOR get_color(const unsigned int hexcode)
{
	unsigned int red = 0xFF, green = 0xFF, blue = 0xFF, alpha = 0xFF;

	char length[_MAX_U64TOSTR_BASE16_COUNT];
	_itoa_s(hexcode, length, _countof(length), 16);

	if(strlen(length) == 6)
	{
		red = (hexcode >> 16) & 0xFF;
		green = (hexcode >> 8) & 0xFF;
		blue = (hexcode) & 0xFF;
	}

	if(strlen(length) == 8)
	{
		red = (hexcode >> 24) & 0xFF;
		green = (hexcode >> 16) & 0xFF;
		blue = (hexcode >> 8) & 0xFF;
		alpha = (hexcode) & 0xFF;
	}

	

	return al_map_rgba(red, green, blue, alpha);
}