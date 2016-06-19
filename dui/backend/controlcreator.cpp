#include "controlcreator.h"

using namespace DUI;
using namespace DUI::Create;


controls::Label* Create::Label(controls::BaseControl *parent) {
	controls::Label* temp = new controls::Label(parent);
	backend::ProcessControl(temp);
	return (temp);
}

controls::Button* Create::Button(controls::BaseControl *parent) {
	controls::Button* temp = new controls::Button(parent);
	backend::ProcessControl(temp);
	return (temp);
}

controls::Frame* Create::Frame(controls::BaseControl *parent) {
	controls::Frame* temp = new controls::Frame(parent);
	backend::ProcessControl(temp);
	return (temp);
}

void Create::backend::ProcessControl(controls::BaseControl *control) {
	if (!control->HasParent())
		controlhandler::controls.push_back(control);
}
