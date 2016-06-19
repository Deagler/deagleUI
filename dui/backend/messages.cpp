#include "messages.h"


using namespace DUI;
using namespace DUI::controlhandler;
using namespace DUI::controls;


void messagehandler::Init() {
	inputmanager::AddMouseCallback(messagehandler::ProcessMouse);
//	inputmanager::AddKeyboardCallback(messagehandler::ProcessKeyboard);
}

bool messagehandler::ProcessMouse(MouseData &m) {
	if (m.event == MouseEvent::Unknown)
		return false;
	
	switch (m.event) {
	case MouseEvent::Move:
		backend::MouseMove(m.pos);
		break;
	case MouseEvent::Down:
		backend::MouseDown(m);
		break;
	case MouseEvent::Up:
		backend::MouseUp(m);
	}

	return true;
}
/* 
	TODO: There has to be a better way to do the following without C+Ping loop skeleton over and over.
*/
void messagehandler::backend::MouseMove(const DUI::draw::Point & mpos,  std::vector<BaseControl *> & controls) {
	
	for (unsigned int i = controls.size(); i-- > 0;) {
		EventControl *control = reinterpret_cast<EventControl *>(controls.at(i));

		if (!control->IsVisible())
			continue;

		if (control->HasChildren())
			messagehandler::backend::MouseMove(mpos, control->GetChildren());

		if (!control->IsHovering()) {
			if (control->InRegion(mpos)) {
				if (control->HasFocus() || (!control->HasFocus() && !controlhandler::InFocusedControl(mpos)))
					control->_parseCursorEntered(mpos);
			}
				
		} else {
			if (!control->InRegion(mpos) || (!control->HasFocus() && controlhandler::InFocusedControl(mpos)))
				control->_parseCursorLeft(mpos);
			else
				control->_parseCursorMoved(mpos);
		}

		if (control->IsDragging())
			control->_parseCursorMoved(mpos);
	}
}

void messagehandler::backend::MouseDown(MouseData &m, std::vector<BaseControl *> & controls) {
	for (unsigned int i = controls.size(); i-- > 0;) {
		EventControl *control = reinterpret_cast<EventControl *>(controls.at(i));

		if (!control->IsVisible())
			continue;

		if (control->HasChildren())
			messagehandler::backend::MouseDown(m, control->GetChildren());

		if (!control->InRegion(m.pos))
			continue;

		if (control->HasFocus() || (!control->HasFocus() && !controlhandler::InFocusedControl(m.pos))) {
			if (!control->HasFocus())
				controlhandler::SetFocus(control);
			
			if (m.button == MouseButton::Left && !control->IsLButtonDown())
				control->_parseMouseLeftButtonDown(m);

			if (m.button == MouseButton::Right && !control->IsRButtonDown())
				control->_parseMouseRightButtonDown(m);
		}
	
	}

}

void messagehandler::backend::MouseUp(MouseData &m, std::vector<BaseControl *> & controls) {
	for (unsigned int i = controls.size(); i-- > 0;) {
		EventControl *control = reinterpret_cast<EventControl *>(controls.at(i));

		if (!control->IsVisible())
			continue;

		if (control->HasChildren())
			messagehandler::backend::MouseUp(m, control->GetChildren());

		bool inRegion = control->InRegion(m.pos);
	
		if (m.button == MouseButton::Left && control->IsLButtonDown())
			control->_parseMouseLeftButtonUp(m, inRegion);

		if (m.button == MouseButton::Right && control->IsRButtonDown())
			control->_parseMouseRightButtonUp(m, inRegion);
	}

}
