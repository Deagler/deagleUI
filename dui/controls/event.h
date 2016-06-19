#pragma once
// DUI - Backend
#include "../backend/events.h"

// DUI - Controls
#include "base.h"

// DUI - Utilities
#include "../utilities/input.h"

namespace DUI {
	namespace controls {
		class EventControl : public BaseControl {
		protected:
			bool hasFocus;
			bool isHovering;

			bool isLDown;
			bool isRDown;

			bool isDragging;
			bool isDraggable;
			draw::Point dragOffset;
			draw::Size dragRegion;
			draw::Point _dragStart;


			virtual void cursorEntered(const DUI::draw::Point &) {};
			virtual void cursorLeft(const DUI::draw::Point &){};
			virtual void cursorMoved(const DUI::draw::Point &) {};

			virtual void mouseLeftButtonDown(const MouseData &m) {};
			virtual void mouseLeftButtonUp(const MouseData &m) {};

			virtual void mouseRightButtonDown(const MouseData &m) {};
			virtual void mouseRightButtonUp(const MouseData &m) {};

			virtual void HandleDragging(draw::Point &m);
		public:
			EventControl(BaseControl *parent_t = nullptr);

			/*
				Events
			*/
			eventhandler::Event<const DUI::draw::Point &> evCursorEntered;
			eventhandler::Event<const DUI::draw::Point &> evCursorLeft;
			eventhandler::Event<const DUI::draw::Point &> evCursorMoved;

			eventhandler::Event<const MouseData &> evMouseLeftDown;
			eventhandler::Event<const MouseData &> evMouseLeftUp; 

			eventhandler::Event<const MouseData &> evMouseRightDown;
			eventhandler::Event<const MouseData &> evMouseRightUp;

			/*
				Internal functions
			*/
			/*TODO: Rewrite all internal functions.*/
			void _parseCursorEntered(const DUI::draw::Point &); 
			void _parseCursorLeft(const DUI::draw::Point &); 
			void _parseCursorMoved(DUI::draw::Point); 

			void _parseMouseLeftButtonDown(MouseData &m);
			void _parseMouseLeftButtonUp(MouseData &m, bool inRange);

			void _parseMouseRightButtonDown(MouseData &m);
			void _parseMouseRightButtonUp(MouseData &m, bool inRange);


			/*
				Dragging
			*/
			void SetDraggable(bool draggable);
			bool IsDraggable() const;

			void SetDragRegion(const draw::Size &);
			const draw::Size& GetDragRegion() const;

			void SetDragOffset(const draw::Point &);
			const draw::Point& GetDragOffset() const;


			/*
				Other
			*/
			void _setFocus(bool focus); 
			bool HasFocus() const;

			bool IsHovering() const;
			bool IsLButtonDown() const;
			bool IsRButtonDown() const;
			bool IsDragging() const;

			bool InRegion(const DUI::draw::Point &) const;

			void Remove();
		};
	}
}
