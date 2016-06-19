#include "label.h"

using namespace DUI;
using namespace DUI::controls;

Label::Label(BaseControl *parent) : EventControl(parent) {
	this->type = Control::Label;
	this->ReinitializeTheme();
}

/* 
	Base Functions
*/
void Label::Paint() {
	draw::DrawString(this->font, this->pos, this->textColor, this->text);
}

/* 
	Font Functions 
*/
void Label::SetFont(const char* font) {
	this->font = fontmanager::GetFontID(font);
}

void Label::SetFont(unsigned int font) {
	this->font = font; 
}

unsigned int Label::GetFont() const {
	return (this->font);
}

/*
	Text Functions
*/
void Label::SetText(const char *text_t) {
	this->text = text_t;
}

const char* Label::GetText() const {
	return(this->text);
}

/*
	Color functions
*/
void Label::SetTextColor(const draw::Color &col) {
	this->textColor = col;
}

void Label::SetTextColor(int r, int g, int b, int a) {
	this->textColor.SetColor(r, g, b, a);
}
/*
	Theme
*/
void Label::ReinitializeTheme() {
	this->textColor = this->theme->label.textCol;
	this->font = this->theme->label.font;
}


/*
	Misc Functions
*/

void Label::SizeToContents() {
	this->size = draw::GetTextSize(this->font, this->text);
}

void Label::Center() {
	this->SizeToContents();
	EventControl::Center();
}

void Label::CenterX()
{
	this->SizeToContents();
	EventControl::CenterX();
}

void Label::CenterY()
{
	this->SizeToContents();
	EventControl::CenterY();
}
