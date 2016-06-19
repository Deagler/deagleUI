#pragma once

// Base
#include <unordered_map>
#include <string>
#include <functional>
namespace DUI {
	namespace eventhandler {
		template <typename... a>
		struct Event {
			void operator ()(const a&&... args) {
				if (_f != nullptr)
					_f(args...);
			}

			operator bool() const {
				return (_f != nullptr);
			}

			Event & operator=(std::function<void(a...)> ev) {
				this->_f = ev;
				return *this;
			}

			std::function<void(a...)> _f;
		};
	}
}