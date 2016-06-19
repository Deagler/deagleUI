#pragma once
// Base
#include <stdio.h>

// Source Engine 
#include "../../source_engine/source.h"

namespace DUI {
	namespace draw {
		struct Point {
			int x, y;
			inline Point() {
				this->SetPos(0, 0);
			}
			inline Point(int x, int y) {
				this->SetPos(x, y);
			}

			inline void SetPos(int x, int y) { this->x = x; this->y = y; }

			inline void SetX(int x) { this->x = x; }
			inline unsigned int GetX() const { return (this->x); }

			inline void SetY(int y) { this->y = y; }
			inline unsigned int GetY() const { return (this->y); }

			inline const Point operator +(Point &pos) {
				return(Point(this->x + pos.x, this->y + pos.y));
			}

			inline const Point operator +(int n) {
				return(Point(this->x + n, this->y + n));
			}

			inline const Point operator -(const Point &pos) {
				return(Point(this->x - pos.x, this->y - pos.y));
			}

			inline const Point operator -(int n) {
				return(Point(this->x - n, this->y - n));
			}

			inline const Point operator -=(const Point & rhs) {
				this->SetPos(x - rhs.GetX(), y - rhs.GetY());

				return (*this);
			}

			

		};

		struct Size {
			unsigned int w, h;
			inline Size() {
				this->SetSize(0, 0);
			}
			inline Size(int w, int h) {
				this->SetSize(w, h);
			}

			inline void SetSize(int w, int h) { this->w = w; this->h = h; }

			inline void SetWidth(int w) { this->w = w; }
			inline unsigned int GetWidth() const { return (this->w); }

			inline void SetHeight(int h) { this->h = h; }
			inline unsigned int GetHeight() const { return (this->h); }
			
			inline const Size operator +(int n) {
				return(Size(this->w + n, this->h + n));
			}

			inline const Size operator -(int n) {
				return(Size(this->w - n, this->h - n));
			}

			inline void operator -=(const draw::Size& rhs) {
				this->SetSize(w - rhs.GetWidth(), h - rhs.GetHeight());
			}
			
		};

		class Color  {
		public:
			Color()
			{
				*(int*)this = 0;
			}
			Color(int r, int g, int b, int a = 255)
			{
				colors[0] = r;
				colors[1] = g;
				colors[2] = b;
				colors[3] = a;
			}

			inline void SetColor(int r, int g, int b, int a = 255) {
				this->colors[0] = r;
				this->colors[1] = g;
				this->colors[2] = b;
				this->colors[3] = a;
			}

			inline int r() const { return (this->colors[0]); }
			inline int g() const { return (this->colors[1]); }
			inline int b() const { return (this->colors[2]); }
			inline int a() const { return (this->colors[3]); }


		private:
			unsigned char colors[4];
		};

		void Init();

		bool InRegion(DUI::draw::Point pos, DUI::draw::Size size, DUI::draw::Point tocheck);
	

		template<typename ...Args>
		void DrawString(unsigned int font, const Point& pos, const Color& col, const char *pszText, const Args&... args);
		void DrawRectangle(const draw::Point& pos, const draw::Size& size, const draw::Color& col);
		void DrawRectangleRaw(const draw::Point& pos, const draw::Point& pos2, const draw::Color& col);
		void DrawOutlinedRectangle(const draw::Point& pos, const draw::Size& size, const draw::Color& col);
		void DrawOutlinedRectangleRaw(const draw::Point& pos, const draw::Point& pos2, const draw::Color& col);
		void DrawLine(const draw::Point& pos, const draw::Point& pos2, const draw::Color& col);
		template<typename ...Args>
		const draw::Size GetTextSize(unsigned int font, const char *pszText, const Args&... args);
		template<typename ...Args>
		int GetTextWidth(unsigned int font, const char *pszText, const Args&... args);
		template<typename ...Args>
		int GetTextHeight(unsigned int font, const char *pszText, const Args&... args);

		extern int screenWidth;
		extern int screenHeight;
		
	}
}

/*
	TODO: There is probably a better way to do the following functions, we need to find a way to make them better.
*/
template<typename ...Args>
void DUI::draw::DrawString(unsigned int font, const Point& pos, const Color& col, const char *pszText, const Args&... args) 
{
	if (!pszText)
		return;
	source::interfaces::pSurface->DrawSetTextFont(font);
	source::interfaces::pSurface->DrawSetTextColor(col.r(), col.g(), col.b(), col.a());
	source::interfaces::pSurface->DrawSetTextPos(pos.GetX(), pos.GetY());
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };
	sprintf_s(szBuffer, pszText, args...);
	wsprintfW(szString, L"%S", szBuffer);
	source::interfaces::pSurface->DrawPrintText(szString, wcslen(szString));
}

template<typename ...Args>
const DUI::draw::Size DUI::draw::GetTextSize(unsigned int font, const char *pszText, const Args&... args)
{
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };
	sprintf_s(szBuffer, pszText, args...);
	wsprintfW(szString, L"%S", szBuffer);
	int wide, tall;
	source::interfaces::pSurface->GetTextSize(font, szString, wide, tall);
	return draw::Size(wide, tall);
}

template<typename ...Args>
int DUI::draw::GetTextWidth(unsigned int font, const char *pszText, const Args&... args)
{
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };
	sprintf_s(szBuffer, pszText, args...);
	wsprintfW(szString, L"%S", szBuffer);
	int wide, tall;
	source::interfaces::pSurface->GetTextSize(font, szString, wide, tall);
	return wide;
}

template<typename ...Args>
int DUI::draw::GetTextHeight(unsigned int font, const char *pszText, const Args&... args)
{
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };
	sprintf_s(szBuffer, pszText, args...);
	wsprintfW(szString, L"%S", szBuffer);
	int wide, tall;
	source::interfaces::pSurface->GetTextSize(font, szString, wide, tall);
	return tall;
}