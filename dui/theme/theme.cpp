#include "theme.h"

using namespace DUI;
using namespace DUI::thememanager;

std::unordered_map<std::string, theme::Theme> thememanager::themes;

void thememanager::Init() {
	theme::Theme defaultTheme;
	thememanager::RegisterTheme("default", defaultTheme);
}

void thememanager::RegisterTheme(const char* identity, const theme::Theme& theme) {
	themes[identity] = theme;
}

const theme::Theme* thememanager::GetTheme(const char* identity) {
	return(&thememanager::themes[identity]);
}


