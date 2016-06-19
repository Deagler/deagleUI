#pragma once

// DUI
#include "../../backend/drawing.h"
#include "../../utilities/fontmanager.h"

/*
	Control Structures
*/
struct _label {
	DUI::draw::Color textCol;
	unsigned int font;
};

struct _button {
	DUI::draw::Color bgCol;
	DUI::draw::Color fgCol;
	DUI::draw::Color hoverCol;
	DUI::draw::Color clickCol;
	_label lbl;

};

struct _frame {
	DUI::draw::Color bgCol;
	DUI::draw::Color fgCol;

	DUI::draw::Point dragOffset;
	DUI::draw::Size dragRegion;

	_button closeBtn;
	_label titleLbl;
};

struct _checkbox : public _button {
	unsigned long checkMarkFont;
	DUI::draw::Color checkMarkColor;
};

/*
	Theme Stuff
*/
namespace DUI {
	namespace thememanager {
		namespace theme {
			struct Theme {
				_label label;
				_button button;
				_frame frame;
				_checkbox checkbox;
				Theme();
			};
		}
	}
}