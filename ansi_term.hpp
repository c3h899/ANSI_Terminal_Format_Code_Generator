#ifndef _ANSI_TERM_H
#define _ANSI_TERM_H

#include<string>

namespace ctrm{		
	enum format_code : unsigned char{
		// Text Formatting
		blink = '%',
		bold = '#',
		dim = '$',
		hidden = '*',
		inverted = '!',
		light = '^',
		underlined = '_',
		
		// Background Color
		bg_black = 'K',
		bg_blue = 'B',
		bg_cyan = 'C',
		bg_green = 'G',
		bg_grey_dark = 'D',
		bg_grey_light = 'L',
		bg_magenta = 'M',
		bg_red = 'R',
		bg_white = 'W',
		bg_yellow = 'Y',
		
		// Foreground Color
		fg_black = 'k',
		fg_blue = 'b',
		fg_cyan = 'c',
		fg_green = 'g',
		fg_grey_dark = 'd',
		fg_grey_light = 'l',
		fg_magenta = 'm',
		fg_red = 'r',
		fg_white = 'w',
		fg_yellow = 'y'
	};
	std::string reset(unsigned char c = '\0');
	std::string tformat(std::string s);
}

#endif
