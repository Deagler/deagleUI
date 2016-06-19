#pragma once

#include "controlhandler.h"

// DUI - Controls
#include "../controls/base.h"
#include "../controls/event.h"
#include "../controls/label.h"
#include "../controls/button.h"
#include "../controls/frame.h"

namespace DUI {
	namespace Create {
		namespace backend {
			void ProcessControl(controls::BaseControl *control);
		}

		controls::Label* Label(controls::BaseControl *parent = nullptr);
		controls::Button* Button(controls::BaseControl *parent = nullptr);
		controls::Frame* Frame(controls::BaseControl *parent = nullptr);

	}
}