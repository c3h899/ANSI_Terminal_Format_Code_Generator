#include<cstdint>

#include<iostream>

#include "ansi_term.hpp"

/* === ANSI DEFINED VALUES === */
// Escape Sequence
const std::string str_esc = "\033[";

// Typefaceing
const std::string str_bold = "1";
const std::string str_dim = "2";
const std::string str_underlined = "4";
const std::string str_blink = "5";
const std::string str_inverted = "7";
const std::string str_hidden = "8";

// Position Modifier (Position + Color)
const std::string str_fg = "3"; // Foreground
const std::string str_fg_light = "9"; // Light Foreground
const std::string str_bg = "4"; // Background
const std::string str_bg_light = "10"; // Light Background

// Colors
const std::string str_black = "0";
const std::string str_blue = "4";
const std::string str_cyan = "6";
const std::string str_green = "2";
const std::string str_grey = "7"; // Light Grey
const std::string str_magenta = "5";
const std::string str_red = "1";
const std::string str_yellow = "3";	
/* =========================== */

/* ====== MORE CONSTANTS ===== */
enum format : unsigned int{ // Bitwise operations will promote to int (or unsigned int) -Wconversion
	e_null = 0x00,
	e_blink = 0x01,
	e_bold = 0x02,
	e_dim = 0x04,
	e_hidden = 0x08,
	e_inverted = 0x10,
	e_light = 0x20,
	e_underlined = 0x40
};

enum colors {
	c_null = 0,
	e_black, e_blue, e_cyan, e_green,
	e_grey, e_magenta, e_red, e_yellow
};
/* =========================== */

/* Generate Appropriate reset code for single behavior */
std::string ctrm::reset(unsigned char c){
	std::string prefix = str_esc + "2";
	switch(c){
		case blink : prefix += str_blink + "m"; break;
		case bold : prefix += str_bold + "m"; break;
		case dim : prefix += str_dim + "m"; break;
		case hidden : prefix += str_hidden + "m"; break;
		case inverted : prefix += str_inverted + "m"; break;
		case underlined : prefix += str_underlined + "m"; break;
		default : prefix = str_esc + "0m"; break; // Reset All (Null Case)
	}
	return prefix;
}

/* Generate Appropriate format code for selected behavior */
std::string ctrm::tformat(std::string s){
	std::string format = str_esc;
	
	// Reduce format string to unique input
	unsigned int bg = e_null;
	unsigned int bg_format = 0;
	unsigned int fg = e_null;
	unsigned int fg_format = 0;
	
	auto ii = 0;
	while( (s[ii] != '\0') && (ii < 9) ){
		switch(s[ii]){
			// Background
			case bg_black : bg = e_black; break; // Black (K)
			case bg_blue : bg = e_blue; break; // Blue (B)
			case bg_cyan : bg = e_cyan; break; // Cyan (C)
			case bg_green : bg = e_green; break; // Green (G)
			case bg_grey_dark : bg = e_black;  // Grey, Dark (D)
				bg_format |= e_light;
				break;
			case bg_grey_light : bg = e_grey; break; // Grey, Light (L)
			case bg_magenta : bg = e_magenta; break; // Magenta (M)
			case bg_red : bg = e_red; break; // Red (R)
			case bg_white : bg = e_grey; // White (W)
				bg_format |= e_light;
				break;
			case bg_yellow : bg = e_yellow; break; // Yellow (Y)

			// Foreground
			case fg_black : fg = e_black; break; // Black (k)
			case fg_blue : fg = e_blue; break; // Blue (b)
			case fg_cyan : fg = e_cyan; break; // Cyan (c)
			case fg_green : fg = e_green; break; // Green (g)
			case fg_grey_dark : fg = e_black; // Grey, Dark (d)
				fg_format |= e_light;
				break;
			case fg_grey_light : fg = e_grey; break; // Grey, Light (l)
			case fg_magenta : fg = e_magenta; break; // Magenta (m)
			case fg_red : fg = e_red; break; // Red (r)
			case fg_white : fg = e_grey; // White (w)
				fg_format |= e_light;
				break;
			case fg_yellow : fg = e_yellow; break; // Yellow (y)
			
			// Foreground formatting
			case blink : fg_format |= e_blink; break; // Blink (%)
			case bold : fg_format |= e_bold; break; // Bold (#)
			case dim : fg_format |= e_dim; break; // Dim ($)
			case hidden : fg_format |= e_hidden; break; // Hidden (*)
			case inverted : fg_format |= e_inverted; break; // Inverted (!)
			case light : fg_format |= e_light; break; // Light (^)
			case underlined : fg_format |= e_underlined; break; // underlined (_)
			
			// Unhandled behavior
			default : break; // Do Nothing
		}
		++ii;
	}
	
	// Map Unique data to output_iterator
	if(fg != c_null){ // Specify Foreground color if any
		if(fg_format & e_light){ // Light-Color Prefix
			format += str_fg_light;
			fg_format &= ~e_light; // Clear format flag
		} else {
			format += str_fg;
		}
		switch(fg){
			case e_black : format += str_black; break;
			case e_blue : format += str_blue; break;
			case e_cyan : format += str_cyan; break;
			case e_green : format += str_green; break;
			case e_grey : format += str_grey; break;
			case e_magenta : format += str_magenta; break;
			case e_red : format += str_red; break;
			case e_yellow : format += str_yellow; break;
			default : break;
		}
		if((fg_format) || bg_format || (bg != c_null)){ // Has More?
			format += ";"; // Semi-colon delimited values
		}
	}
	if(fg_format){
		if(fg_format & e_blink){
			format += str_blink;
			fg_format &= ~e_blink;
			if((fg_format) || bg_format || (bg != e_null)){ // Has More?
				format += ";"; // Semi-colon delimited values
			}
		}
		if(fg_format & e_bold){
			format += str_bold;
			fg_format &= ~e_bold;
			if((fg_format) || bg_format || (bg != e_null)){ // Has More?
				format += ";"; // Semi-colon delimited values
			}
		}
		if(fg_format & e_dim){
			format += str_dim;
			fg_format &= ~e_dim;
			if((fg_format) || bg_format || (bg != e_null)){ // Has More?
				format += ";"; // Semi-colon delimited values
			}
		}
		if(fg_format & e_hidden){
			format += str_hidden;
			fg_format &= ~e_hidden;
			if((fg_format) || bg_format || (bg != e_null)){ // Has More?
				format += ";"; // Semi-colon delimited values
			}
		}
		if(fg_format & e_inverted){
			format += str_inverted;
			fg_format &= ~e_inverted;
			if((fg_format) || bg_format || (bg != e_null)){ // Has More?
				format += ";"; // Semi-colon delimited values
			}
		}
		if(fg_format & e_underlined){
			format += str_underlined;
			fg_format &= ~e_underlined;
			if((fg_format) || bg_format || (bg != e_null)){ // Has More?
				format += ";"; // Semi-colon delimited values
			}
		}
	}
	if(bg != c_null){ // Specify Foreground color if any
		if(bg_format & e_light){ // Light-Color Prefix
			format += str_bg_light;
			bg_format &= ~e_light; // Clear format flag
		} else {
			format += str_bg;
		}
		switch(bg){
			case e_black : format += str_black; break;
			case e_blue : format += str_blue; break;
			case e_cyan : format += str_cyan; break;
			case e_green : format += str_green; break;
			case e_grey : format += str_grey; break;
			case e_magenta : format += str_magenta; break;
			case e_red : format += str_red; break;
			case e_yellow : format += str_yellow; break;
			default : break;
		}
	}
	format += "m";
	return format;
}
