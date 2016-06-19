#pragma once
// DUI - Control
#include "event.h"
#include "label.h"

namespace DUI {
	namespace controls {
		class Button : public EventControl {
		private:
			virtual void Paint();
			virtual void ReinitializeTheme();
			
			virtual void onSizeChanged(draw::Size &);
		public:
			draw::Color bgColor;
			draw::Color fgColor;
			draw::Color hoverColor;
			draw::Color clickCol;
			Label *lbl;

			Button(BaseControl *parent_t = nullptr);

			/* Label Proxies */
			void SetText(const char *text_t);
			template <typename ...Args> void SetText(const char *text_t, const Args&...);
			const char *GetText() const;

		};
	}
}

template <typename ...Args>
void DUI::controls::Button::SetText(const char *text_t, const Args&... args) {
	char buf[128] = { '\0' };
	sprintf_s(buf, sizeof(buf), text_t, args...);
	this->lbl->SetText(buf);
	this->lbl->Center();
}