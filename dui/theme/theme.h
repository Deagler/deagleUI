#pragma once
// Base
#include <unordered_map>
#include <string>

// DUI - Base Theme
#include "themes/default.h"

// Other Themes

namespace DUI {
	namespace thememanager {
		extern std::unordered_map<std::string, theme::Theme> themes;
		void Init();
		void RegisterTheme(const char*, const theme::Theme&);
		const theme::Theme* GetTheme(const char*);
	}
}