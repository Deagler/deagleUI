// DUI
#include "controlhandler.h"
#include "drawing.h"
#include "../utilities/fontmanager.h"
#include "../utilities/input.h"
#include "messages.h"
#include "../theme/theme.h"

#include <algorithm>
#include "../../toolkit/debug.h"

using namespace DUI;
using namespace DUI::controls;
using namespace DUI::controlhandler;
std::vector<BaseControl *> controlhandler::controls;
controls::EventControl *controlhandler::globals::controlInFocus;
bool controlhandler::globals::bDragging;

void DUI::Init() {
	inputmanager::Init();
	messagehandler::Init();
	fontmanager::Init();
	thememanager::Init();
	draw::Init();
}

void controlhandler::Erase(BaseControl *control) {
	for (std::vector<BaseControl *>::iterator it = controlhandler::controls.begin(); it != controlhandler::controls.end(); it++) {
		if ((*it) == control) {
			controlhandler::controls.erase(it);
			break;
		}
	}
}

void controlhandler::Deallocate(BaseControl *control) {
	controlhandler::Erase(control);
	delete control;
}

void controlhandler::Paint() {
	for (auto &control : controlhandler::controls) {
		if (control->IsVisible()) {
			control->DoPaint();
			control->DoThink();
		}
	}
}

bool controlhandler::InFocusedControl(const DUI::draw::Point &mpos) {
	if (globals::controlInFocus == nullptr)
		return false;

	if (!globals::controlInFocus->IsVisible())
		return false;
	return (globals::controlInFocus->InRegion(mpos));
}

void controlhandler::SetFocus(BaseControl *tofocus) {
	if (tofocus == nullptr) {
		controlhandler::globals::controlInFocus = nullptr;
		if (controls.size() > 0) 
			controlhandler::SetFocus(controls.back());
		return;
	}
		

	if (tofocus->HasParent())
		tofocus = tofocus->GetSuperParent();

	for (std::vector<BaseControl *>::iterator it = controls.begin(); it != controls.end(); it++) {
		EventControl *control = reinterpret_cast<EventControl *>(*it);
		
		if (control == tofocus) {
			if (controlhandler::globals::controlInFocus)
				controlhandler::globals::controlInFocus->_setFocus(false);
			std::rotate(it, it + 1, controls.end()); /*http://en.cppreference.com/w/cpp/algorithm/rotate */
			control->_setFocus(true); 
			controlhandler::globals::controlInFocus = control;
		}
			
	}
}


