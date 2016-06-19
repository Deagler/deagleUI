#include "frame.h"
#include "../backend/controlcreator.h"
using namespace DUI;
using namespace DUI::controls;

Frame::Frame(BaseControl *parent) : EventControl(parent), titleLbl(DUI::Create::Label(this)), closeBtn(DUI::Create::Button(this)) {
	this->type = Control::Frame;
	this->ReinitializeTheme(); 

	
	this->SetSize(500, 300);

	this->SetTitle("DFrame");
	this->titleLbl->SizeToContents();
	this->titleLbl->SetPos(5, this->titleLbl->GetHeight() - (this->dragRegion.GetHeight() / 2));

	this->closeBtn->SetSize(31, this->dragRegion.GetHeight() - 1);
	this->closeBtn->SetPos((this->GetWidth() - 1) - this->closeBtn->GetWidth(), 1);
	this->closeBtn->SetText("r"/*X (Close Button*/);
	this->closeBtn->evMouseLeftUp = [this](const MouseData &m) { this->Remove(); };


	this->SetDragRegion(draw::Size(this->GetWidth() - this->closeBtn->GetWidth(), this->dragRegion.GetHeight()));
	this->SetDraggable(true);
}

/*
	Base
*/

void Frame::Paint() {
	draw::DrawRectangle(this->pos, this->size, this->bgColor);
	draw::DrawRectangle(this->pos, this->dragRegion, this->fgColor);

	draw::DrawOutlinedRectangle(this->pos, this->size, this->fgColor);
}

/*
	Proxies
*/

void Frame::SetCloseButtonEnabled(bool bEnabled) {
	this->closeBtn->SetVisible(bEnabled);
}

bool Frame::IsCloseButtonEnabled() const {
	return (this->closeBtn->IsVisible());
}

void Frame::SetTitle(const char *text_t) {
	this->titleLbl->SetText(text_t);
	this->titleLbl->SizeToContents();
	this->titleLbl->SetPos(5, this->titleLbl->GetHeight() - (this->dragRegion.GetHeight() / 2));
}

/*
	Overwrites
*/

void Frame::onSizeChanged(draw::Size &oldsize) {
	const draw::Size& size = this->theme->frame.dragRegion;
	draw::Size dragregion((size.GetWidth() == 0 ? this->GetWidth() : size.GetWidth()), size.GetHeight());
	this->SetDragRegion(dragregion);
}


/*
	Theme
*/

void Frame::ReinitializeTheme() {
	this->bgColor = this->theme->frame.bgCol;
	this->fgColor = this->theme->frame.fgCol;
	
	this->SetDragOffset(this->theme->frame.dragOffset);

	const draw::Size& size = this->theme->frame.dragRegion;
	draw::Size dragregion((size.GetWidth() == 0 ? this->GetWidth() : size.GetWidth()), size.GetHeight());
	this->SetDragRegion(dragregion);

	this->titleLbl->SetFont(this->theme->frame.titleLbl.font);
	this->titleLbl->SetTextColor(this->theme->frame.titleLbl.textCol);

	this->closeBtn->bgColor = this->theme->frame.closeBtn.bgCol;
	this->closeBtn->fgColor = this->theme->frame.closeBtn.fgCol;
	this->closeBtn->lbl->SetFont(this->theme->frame.closeBtn.lbl.font);
	this->closeBtn->lbl->SetTextColor(this->theme->frame.closeBtn.lbl.textCol);
}
