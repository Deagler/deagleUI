#include "default.h"
#include "../../utilities/fontmanager.h"

using namespace DUI;


thememanager::theme::Theme::Theme() {
	/* Label */
	this->label.textCol = draw::Color(255, 255, 255);
	this->label.font = fontmanager::GetFontID("default");

	/* Button */
	this->button.bgCol = draw::Color(0, 153, 204);
	this->button.fgCol = draw::Color(204, 255, 204);
	this->button.hoverCol = draw::Color(102, 204, 255);
	this->button.clickCol = draw::Color(0, 173, 224);

	this->button.lbl.textCol = draw::Color(240, 240, 240);
	this->button.lbl.font = fontmanager::GetFontID("default");

	/* Frame */
	this->frame.bgCol = draw::Color(20, 20, 20,175);
	this->frame.fgCol = draw::Color(0, 153, 204);

	this->frame.dragOffset.SetPos(0, 0);
	this->frame.dragRegion.SetSize(0, 23);

	this->frame.titleLbl.font = fontmanager::GetFontID("default");
	this->frame.titleLbl.textCol = draw::Color(190, 190, 190);

	this->frame.closeBtn.bgCol = draw::Color(255, 0, 0);
	this->frame.closeBtn.hoverCol = draw::Color(255, 130, 130);
	this->frame.closeBtn.lbl.font = fontmanager::GetFontID("DUI_Marlett_Large");
	this->frame.closeBtn.lbl.textCol = draw::Color(0, 0, 0);

	/* Checkbox */
	this->checkbox.bgCol = draw::Color(240, 240, 240);
	this->checkbox.fgCol = draw::Color(0, 153, 204);
	this->checkbox.hoverCol = draw::Color(220, 220, 220, 200);
	this->checkbox.clickCol = draw::Color(170, 170, 170, 200);

	this->checkbox.lbl.font = fontmanager::GetFontID("default");
	this->checkbox.lbl.textCol = draw::Color(190, 190, 190);

	this->checkbox.checkMarkFont = fontmanager::GetFontID("DUI_Marlett_Medium");
	this->checkbox.checkMarkColor = draw::Color(0, 0, 0);
}

