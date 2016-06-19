#pragma once

// Base
#include <unordered_map>
#include <string>

// Source Engine
#include "../../sdk/isurface.h"

#undef CreateFont
namespace DUI {
	namespace fontmanager {
		
		struct fontData_t {
			const char* fontName;
			unsigned int size;
			unsigned int weight;
			unsigned int blursize = 0;
			unsigned int scanlines = 0;
			bool antialias = false;
			bool underline = false;
			bool italic = false;
			bool strikeout = false;
			bool symbol = false;
			bool rotary = false;
			bool shadow = false;
			bool additive = false;
			bool outline = false;
		};

		struct font_t {
			unsigned int fontID;
			fontData_t data;
		};

		extern std::unordered_map<std::string, font_t> fonts;

		void Init();
		unsigned int CreateFont(const char*, const fontData_t &);
		unsigned int GetFontID(const char*);
		const fontData_t& GetFontData(const char*);
		

		
	}
}