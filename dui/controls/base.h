#pragma once
// Base
#include <vector>

// DUI
#include "../backend/drawing.h"
#include "../theme/theme.h"
#include "../backend/events.h"


namespace DUI{
	enum struct Control : unsigned int {
		None,
		Label,
		Button,
		Frame,
		CheckBox
	};

	namespace controls {
		class BaseControl {
		protected:
			BaseControl *parent;
			Control type;
			std::vector<BaseControl *> children;
			draw::Point offsetpos;
			draw::Point pos;
			draw::Size size;
			bool isVisible;
			const thememanager::theme::Theme* theme;
			virtual void Paint(){};
			virtual void Think(){};

			virtual void ReinitializeTheme(){};
			void RefreshPosition();

			virtual void onSizeChanged(draw::Size &){};
			virtual void onPositionChanged(draw::Point &){};
			
		public:
			BaseControl(BaseControl *parent = nullptr);
			~BaseControl();
			void Remove();
			Control GetType() const;

			void DoPaint();
			void DoThink();

			eventhandler::Event<BaseControl *, const draw::Point &, const draw::Size &> evPaint;
			eventhandler::Event<BaseControl *> evThink;

			void SetTheme(const thememanager::theme::Theme *);
			void SetTheme(const char *);
			const thememanager::theme::Theme *GetTheme() const;

			void SetPos(int x, int y);
			void SetPos(const draw::Point&);
			void SetX(int x);
			void SetY(int y);

			void SetSize(int w, int h);
			void SetSize(const draw::Size&);
			void SetWidth(int w);
			void SetHeight(int h);

			draw::Point GetPos() const;
			int GetX() const;
			int GetY() const;

			draw::Size GetSize() const;
			unsigned int GetWidth() const;
			unsigned int GetHeight() const;

			void SetVisible(bool isVisible);
			bool IsVisible() const;

			void SetParent(BaseControl* parent);
			void RemoveParent();
			bool HasParent() const;
			BaseControl* GetParent() const;
			BaseControl* GetSuperParent() const;
			

			void AddChild(BaseControl *control);
			void RemoveChild(BaseControl *control);
			bool HasChildren() const;
			std::vector<BaseControl *> & GetChildren();

			void Center();
			void CenterX();
			void CenterY();
		};
	}
};
