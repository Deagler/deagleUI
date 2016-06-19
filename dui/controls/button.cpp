#include "button.h"
#include "../backend/controlcreator.h"
using namespace DUI;
using namespace DUI::controls;
Button::Button(BaseControl *parent) : EventControl(parent), lbl(DUI::Create::Label(this)) {
	this->type = Control::Button;
	this->ReinitializeTheme();

	this->lbl->SetText("Button");

	this->SetSize(75, 25);
}


/* 
	Base Functions
*/

void Button::Paint() {
	draw::DrawOutlinedRectangle(this->pos - 1, this->size + 2, this->fgColor);

	if (this->isHovering)
		draw::DrawRectangle(this->pos, this->size, this->hoverColor);
	else if (this->isLDown)
		draw::DrawRectangle(this->pos, this->size, this->clickCol);
	else
		draw::DrawRectangle(this->pos, this->size, this->bgColor);
}

/*
	Overwrites
*/

void Button::onSizeChanged(draw::Size &oldsize) {
	this->lbl->Center();
}

/*
	Proxies
*/

void Button::SetText(const char *text_t) {
	this->lbl->SetText(text_t);
	this->lbl->Center();
}

const char *Button::GetText() const {
	return(this->lbl->GetText());
}



/*
	Theme
*/

void Button::ReinitializeTheme() {

	this->bgColor = this->theme->button.bgCol;
	this->fgColor = this->theme->button.fgCol;
	this->hoverColor = this->theme->button.hoverCol;
	this->clickCol = this->theme->button.clickCol;

	this->lbl->SetTextColor(this->theme->button.lbl.textCol);
	this->lbl->SetFont(this->theme->button.lbl.font);
}