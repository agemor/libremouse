#include "CursorControl.h"

void CursorControl::getCursorPosition(Point2D &point) {
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	point.x = cursorPosition.x;
	point.y = cursorPosition.y;
}
void CursorControl::setCursorPosition(Point2D &point) {
	SetCursorPos(point.x, point.y);
}
void CursorControl::emulateClick() {

}