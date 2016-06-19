// DUI Headers
#include "drawing.h"

using namespace source::interfaces;
using namespace DUI::draw;

int DUI::draw::screenWidth;
int DUI::draw::screenHeight;

void DUI::draw::Init() {
	pEngineClient->GetScreenSize(DUI::draw::screenWidth, DUI::draw::screenHeight);
}

bool DUI::draw::InRegion(Point pos, Size size, Point tocheck) {
	if ((tocheck.x >= pos.x && tocheck.y >= pos.y) && (tocheck.x <= static_cast<int>((pos.x + size.w)) && tocheck.y <= static_cast<int>((pos.y + size.h))))
		return true;
	else
		return false;
}

void DUI::draw::DrawLine(const Point& pos, const Point& pos2, const Color& col) {
	pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
	pSurface->DrawLine(pos.GetX(), pos.GetY(), pos2.GetX(), pos2.GetY());
}

void DUI::draw::DrawOutlinedRectangle(const Point& pos, const Size& size, const Color& col) {
	pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
	pSurface->DrawOutlinedRect(pos.GetX(), pos.GetY(), pos.GetX() + size.GetWidth(), pos.GetY() + size.GetHeight());
}

void DUI::draw::DrawOutlinedRectangleRaw(const Point& pos, const Point& pos2, const Color& col) {
	pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
	pSurface->DrawOutlinedRect(pos.x, pos.y, pos2.x, pos2.y);
}

void DUI::draw::DrawRectangle(const Point& pos, const Size& size, const Color& col) {
	pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
	pSurface->DrawFilledRect(pos.GetX(), pos.GetY(), pos.GetX() + size.GetWidth(), pos.GetY() + size.GetHeight());
}

void DUI::draw::DrawRectangleRaw(const Point& pos, const Point& pos2, const Color& col) {
	pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
	pSurface->DrawFilledRect(pos.GetX(), pos.GetY(), pos2.GetX(), pos2.GetY());
}


