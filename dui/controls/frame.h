#pragma once
// DUI - Controls
#include "event.h"
#include "label.h"
#include "button.h"


namespace DUI {
	namespace controls {
		class Frame : public EventControl {
		private:
			virtual void Paint();
			virtual void ReinitializeTheme();
			virtual void onSizeChanged(draw::Size &);
		public:
			draw::Color bgColor;
			draw::Color fgColor;
			Button *closeBtn;
			Label *titleLbl;

			Frame(BaseControl *parent_t = nullptr);

			void SetCloseButtonEnabled(bool bEnabled);
			bool IsCloseButtonEnabled() const;

			/* Label */
			void SetTitle(const char *text_t);
			template<typename ...Args> void SetTitle(const char *text_t, const Args&...);
		};
	}
}

template <typename ...Args>
void DUI::controls::Frame::SetTitle(const char *text_t, const Args&... args) {
	char buf[128] = { '\0' };
	sprintf_s(buf, sizeof(buf), text_t, args...);
	this->titleLbl->SetText(buf);
	this->titleLbl->SizeToContents();
	this->titleLbl->SetPos(5, this->titleLbl->GetHeight() - (this->dragRegion.GetHeight() / 2));
}