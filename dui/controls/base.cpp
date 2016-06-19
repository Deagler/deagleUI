#include "base.h"
#include "../backend/controlhandler.h"
#include <algorithm>

using namespace DUI;
using namespace DUI::controls;

BaseControl::BaseControl(BaseControl *parent_t) {
	if (parent_t != nullptr) {
		this->SetParent(parent_t);
		this->SetTheme(parent_t->GetTheme());
	} else {
		this->SetParent(nullptr);
		this->SetTheme("default");
	}

	this->SetVisible(true);
	this->type = Control::None;
	
}

BaseControl::~BaseControl() {
	for (auto &child : this->children) {
		delete child;
	}
}
/* 
	Base Functions
*/

void BaseControl::Remove() {
	if (this->HasParent())
	{
		this->GetParent()->RemoveChild(this);
		delete this;
	} else {
		controlhandler::Deallocate(this);
	}
}

Control BaseControl::GetType() const {
	return(this->type);
}

void BaseControl::DoPaint(){
	if (this->evPaint)
		this->evPaint(this, this->pos, this->size);
	else
		this->Paint();

	for (auto &child : this->children) {
		child->DoPaint();
	}
}

void BaseControl::DoThink() {

	this->evThink(this);
	this->Think();

	for (auto &child : this->children) {
		child->DoThink();
	}
}



/*
	Theme functions
*/
void BaseControl::SetTheme(const thememanager::theme::Theme *newtheme) {
	const thememanager::theme::Theme* oldtheme = this->GetTheme();
	for (auto &child : this->children) {
		if (child->GetTheme() == oldtheme)
			child->SetTheme(newtheme);
	}
	this->theme = newtheme;

	this->ReinitializeTheme();
}
void BaseControl::SetTheme(const char* identity) {
	this->SetTheme(thememanager::GetTheme(identity));
}
const thememanager::theme::Theme* BaseControl::GetTheme() const {
	return (this->theme);
}


/* 
	SetPosition Proxies
*/
void BaseControl::SetPos(int x, int y) { 
	draw::Point old = this->offsetpos;
	this->offsetpos.SetPos(x, y); 
	this->RefreshPosition();
	this->onPositionChanged(old);
}
void BaseControl::SetPos(const draw::Point& pos) { 
	draw::Point old = this->offsetpos;
	this->offsetpos = pos; 
	this->RefreshPosition();
	this->onPositionChanged(old);
}
void BaseControl::SetX(int x) {
	draw::Point old = this->offsetpos;
	this->offsetpos.SetX(x);
	this->RefreshPosition();
	this->onPositionChanged(old);
}
void BaseControl::SetY(int y) {
	draw::Point old = this->offsetpos;
	this->offsetpos.SetY(y);
	this->RefreshPosition();
	this->onPositionChanged(old);
}

/* 
	SetSize Proxies 
*/
void BaseControl::SetSize(int w, int h) {
	draw::Size old = this->size;
	this->size.SetSize(w, h);
	this->onSizeChanged(old);
}
void BaseControl::SetSize(const draw::Size& size) {
	draw::Size old = this->size;
	this->size = size;
	this->onSizeChanged(old);
}
void BaseControl::SetWidth(int w) {
	draw::Size old = this->size;
	this->size.SetWidth(w);
	this->onSizeChanged(old);
}
void BaseControl::SetHeight(int h) {
	draw::Size old = this->size;
	this->size.SetHeight(h);
	this->onSizeChanged(old);
}

/*
	GetPos Proxies
*/
draw::Point BaseControl::GetPos() const {
	return (this->pos);
}
int BaseControl::GetX() const {
	return (this->pos.GetX());
}
int BaseControl::GetY() const {
	return (this->pos.GetY());
}

/*
	GetSize Proxies
*/
draw::Size BaseControl::GetSize() const {
	return (this->size);
}
unsigned int BaseControl::GetWidth() const {
	return (this->size.GetWidth());
}
unsigned int BaseControl::GetHeight() const {
	return (this->size.GetHeight());
}

/*
	Visibility
*/
void BaseControl::SetVisible(bool isVisible) {
	this->isVisible = isVisible;
}
bool BaseControl::IsVisible() const {

	if (this->HasParent() && !this->parent->IsVisible())
		return false;

	return (this->isVisible);
}

/*
	Parenting
*/

BaseControl* BaseControl::GetParent() const {
	return (this->parent);
}

BaseControl* BaseControl::GetSuperParent() const {
	BaseControl *super = this->parent;


	while (super->HasParent()) {
		super = super->GetParent();
	}

	return (super);
}

bool BaseControl::HasParent() const {
	return (this->parent != nullptr);
}

void BaseControl::SetParent(BaseControl *newparent) { /*TODO remake> everything below this*/
	if (newparent == this->GetParent())
		return;


	if (this->HasParent())  {
		this->GetParent()->RemoveChild(this);
		if (newparent == nullptr)
			DUI::controlhandler::controls.push_back(this);
		else
			newparent->AddChild(this);
	}
	else {
		DUI::controlhandler::Erase(this);
		newparent->AddChild(this);
		this->parent = newparent;
	}

	this->RefreshPosition();


}

void BaseControl::RemoveParent() {
	this->SetParent(nullptr);
}

/*
	Children
*/
void BaseControl::AddChild(BaseControl *child) {
	this->children.push_back(child);
}

void BaseControl::RemoveChild(BaseControl *child) {
	for (auto it = this->children.begin(); it != this->children.end(); ++it) {
		if ((*it) == child) {
			it = this->children.erase(it);
			break;
		}
	}
}

bool BaseControl::HasChildren() const {
	return (!this->children.empty());
}

/*
	Misc 
*/

void BaseControl::CenterX()
{
	int w = this->HasParent() ? (this->parent->GetWidth() / 2) : (draw::screenWidth / 2);
	this->SetX(w - (this->GetWidth() / 2));
}

void BaseControl::CenterY()
{
	int h = this->HasParent() ? (this->parent->GetHeight() / 2) : (draw::screenHeight / 2);
	this->SetY(h - (this->GetHeight() / 2));
}

void BaseControl::Center() {
	this->CenterX();
	this->CenterY();
}

std::vector<BaseControl *> & BaseControl::GetChildren() {
	return(this->children);
}

void BaseControl::RefreshPosition() {
	if (this->HasParent()) {
		this->pos = this->GetParent()->GetPos() + this->offsetpos;
	} else {
		this->pos = this->offsetpos;
	}

	for (auto &control : this->children) {
		control->RefreshPosition();
	}
}