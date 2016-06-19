#include "event.h"
#include "../backend/controlhandler.h"

using namespace DUI;
using namespace DUI::controls;

/*
	Base
*/
EventControl::EventControl(BaseControl *parent_t) : BaseControl(parent_t) {
	this->hasFocus = false;
	this->isHovering = false;
	this->isLDown = false;
	this->isRDown = false;
	this->isDragging = false;

	this->isDraggable = false;
	this->dragOffset.SetPos(0, 0);
	this->dragRegion.SetSize(0, 0);
	this->_dragStart.SetPos(0, 0);
}

/*
	Focus
*/
void EventControl::_setFocus(bool focus) {
	this->hasFocus = focus;
}



bool EventControl::HasFocus() const {

	if (this->HasParent()) {
		EventControl *parent = reinterpret_cast<EventControl*>(this->GetParent());

		return (parent->HasFocus());
	}

	return (this->hasFocus);
}
/*
	Input
*/
bool EventControl::IsHovering() const {
	return (this->isHovering);
}

bool EventControl::IsLButtonDown() const {
	return (this->isLDown);
}

bool EventControl::IsRButtonDown() const {
	return (this->isRDown);
}

bool EventControl::IsDragging() const {
	return (this->isDragging);
}

/*
	Misc
*/

bool EventControl::InRegion(const DUI::draw::Point &pos) const {
	if ((pos.x >= this->GetX() && pos.y >= this->GetY()) && (pos.x <= static_cast<int>(this->GetX() + this->GetWidth()) && pos.y <= static_cast<int>(this->GetY() + this->GetHeight())))
		return true; 
	else
		return false;
	
}
/*
	Dragging
*/

void EventControl::SetDraggable(bool draggable) {
	this->isDraggable = draggable;
}

bool EventControl::IsDraggable() const {
	return (this->isDraggable);
}

void EventControl::SetDragRegion(const draw::Size &size) {
	this->dragRegion = size;
}

const draw::Size & EventControl::GetDragRegion() const {
	return (this->dragRegion);
}

void EventControl::SetDragOffset(const draw::Point &pos) {
	this->dragOffset = pos;
}

const draw::Point & EventControl::GetDragOffset() const {
	return (this->dragOffset);
}

void EventControl::HandleDragging(draw::Point &mpos) {
	DUI::draw::Point old = this->pos;
	this->SetPos(mpos - this->_dragStart);
	this->onPositionChanged(old);
	this->RefreshPosition();
}

/*
	Internal Functions
*/
void EventControl::_parseCursorEntered(const DUI::draw::Point &mpos) {
	this->isHovering = true;
	this->cursorEntered(mpos);
	this->evCursorEntered(mpos);
	this->_parseCursorMoved(mpos);
}

void EventControl::_parseCursorLeft(const DUI::draw::Point &mpos) {
	this->isHovering = false;
	this->cursorLeft(mpos);
	this->evCursorLeft(mpos);

	this->_parseCursorMoved(mpos);
}

void EventControl::_parseCursorMoved(DUI::draw::Point mpos) {
	this->cursorMoved(mpos);
	this->evCursorMoved(mpos);

	if (this->isDragging) {
		
		this->HandleDragging(mpos);
	}
}

void EventControl::_parseMouseLeftButtonDown(MouseData &m) {
	this->mouseLeftButtonDown(m);
	this->evMouseLeftDown(m);
	this->isLDown = true;

	if (this->IsDraggable() && draw::InRegion(this->pos + this->dragOffset, this->dragRegion, m.pos) && !controlhandler::globals::bDragging && !this->isDragging) {
		controlhandler::globals::bDragging = true;
		this->isDragging = true;
		this->_dragStart = m.pos - this->GetPos();
	}
	
}

void EventControl::_parseMouseRightButtonDown(MouseData &m) {
	this->mouseRightButtonDown(m);
	this->evMouseRightDown(m);
	this->isRDown = true;
}

void EventControl::_parseMouseLeftButtonUp(MouseData &m, bool inRange) {
	this->isLDown = false;

	if (this->IsDragging()) {
		this->isDragging = false;
		controlhandler::globals::bDragging = false;
	}

	if (inRange) {
		this->mouseLeftButtonUp(m);
		this->evMouseLeftUp(m);
	}
}


void EventControl::_parseMouseRightButtonUp(MouseData &m, bool inRange) {
	this->isRDown = false;
	if (inRange) {
		this->mouseRightButtonUp(m);
		this->evMouseRightUp(m);
	}
}

void EventControl::Remove() {
	bool bReset = this->hasFocus;
	BaseControl::Remove();

	if (bReset)
		controlhandler::SetFocus(nullptr);
}