// DUI
#include "fontmanager.h"

// Source Engine
#include "../../source_engine/source.h"

using namespace DUI;
using namespace source::interfaces;
#undef CreateFont

std::unordered_map<std::string, fontmanager::font_t> fontmanager::fonts;

void fontmanager::Init() {
	
	fontData_t font;
	font.fontName = "Arial";
	font.size = 15;
	font.weight = 200;
	font.antialias = true;
	fontmanager::CreateFont("default", font);


	font = {};
	font.fontName = "Marlett";
	font.size = 17;
	font.symbol = true;
	font.antialias = true;
	fontmanager::CreateFont("DUI_Marlett_Large", font);

	font.size = 14;
	fontmanager::CreateFont("DUI_Marlett_Medium", font);

	font.size = 11;
	fontmanager::CreateFont("DUI_Marlett_Small", font);

	
};
/*
FONTFLAG_ITALIC			= 0x001,
FONTFLAG_UNDERLINE		= 0x002,
FONTFLAG_STRIKEOUT		= 0x004,
FONTFLAG_SYMBOL			= 0x008,
FONTFLAG_ANTIALIAS		= 0x010,
FONTFLAG_ROTARY			= 0x040,
FONTFLAG_DROPSHADOW		= 0x080,
FONTFLAG_ADDITIVE		= 0x100,
FONTFLAG_OUTLINE		= 0x200,
*/

unsigned int fontmanager::CreateFont(const char *identity, const fontmanager::fontData_t &fontData) {
	fontmanager::font_t newFont;
	newFont.fontID = pSurface->CreateFont();
	unsigned int flags = 0;
	if (fontData.antialias)
		flags |= 0x010;
	if (fontData.underline)
		flags |= 0x002;
	if (fontData.strikeout)
		flags |= 0x004;
	if (fontData.symbol)
		flags |= 0x008;
	if (fontData.rotary)
		flags |= 0x040;
	if (fontData.shadow)
		flags |= 0x080;
	if (fontData.additive)
		flags |= 0x100;
	if (fontData.outline)
		flags |= 0x200;

	pSurface->SetFontGlyphSet(newFont.fontID, fontData.fontName, fontData.size, fontData.weight, fontData.blursize, fontData.scanlines, flags);
	newFont.data = fontData;

	fontmanager::fonts[identity] = newFont;



	return (newFont.fontID);
}

unsigned int fontmanager::GetFontID(const char *identifier) {
	return(fontmanager::fonts[identifier].fontID);
}

const fontmanager::fontData_t& fontmanager::GetFontData(const char *identifier) {
	return(fontmanager::fonts[identifier].data);
}