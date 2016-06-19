#pragma once
// DUI
#include "event.h"

namespace DUI {
	namespace controls {
		class Label : public EventControl {
		private:
			const char *text;
			unsigned long font;
			draw::Color textColor;
			virtual void Paint();
			virtual void ReinitializeTheme();
		public:
			Label(BaseControl *parent_t = nullptr);
			
			void SetFont(const char* font);
			void SetFont(unsigned int font);
			unsigned int GetFont() const;

			void SetText(const char *text_t);

			template <typename ...Args> 
			void SetText(const char *text_t, const Args&...);

			const char *GetText() const;

			void SetTextColor(const draw::Color &col);
			void SetTextColor(int r, int g, int b, int a = 255);

			void SizeToContents();

			void CenterX();
			void CenterY();
			void Center();
		};
	}
}

template <typename ...Args>
void DUI::controls::Label::SetText(const char *text_t, const Args&... args) {
	char buf[128] = { '\0' };
	sprintf_s(buf, sizeof(buf), text_t, args...);
	this->text = buf;
}