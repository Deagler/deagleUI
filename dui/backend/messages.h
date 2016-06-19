#pragma once
#include "../utilities/input.h"
#include "../controls/event.h"
#include "../backend/controlhandler.h"

namespace DUI {
	namespace messagehandler {
		namespace backend {

			void MouseMove(const DUI::draw::Point & mpos, std::vector<controls::BaseControl *> & controls = controlhandler::controls);
			void MouseDown(MouseData &m, std::vector<controls::BaseControl *> & controls = controlhandler::controls);
			void MouseUp(MouseData &m, std::vector<controls::BaseControl *> & controls = controlhandler::controls);
		}
		

		void Init();
		bool ProcessMouse(MouseData &m);
	//	bool ProcessKeyboard(const KeyData &k);

	}
}