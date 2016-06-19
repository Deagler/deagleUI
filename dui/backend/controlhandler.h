#pragma once
// Base
#include <vector>



// DUI - Controls
#include "../controls/base.h"
#include "../controls/event.h"

namespace DUI {
	void Init();
	namespace controlhandler {
		extern std::vector<controls::BaseControl *> controls;

		void Erase(controls::BaseControl *); // simply removes from vector
		void Deallocate(controls::BaseControl *); // removes + deallocates the memory.
		void Paint();
		void Think();

		bool InFocusedControl(const DUI::draw::Point &);
		void SetFocus(controls::BaseControl *);
		namespace globals {
			extern controls::EventControl *controlInFocus;
			extern bool bDragging;
		}
	}

	
}

