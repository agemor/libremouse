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
void CursorControl::click() {
	mouseDown();
	mouseUp();
}

void CursorControl::mouseDown() {
	INPUT Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
}

void CursorControl::mouseUp() {
	INPUT Input = { 0 };

	// left up
	ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));
}
