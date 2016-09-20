#pragma once
#include <windows.h>

#include "Point2D.h"

class CursorControl {
public:
	static void getCursorPosition(Point2D &point);
	static void setCursorPosition(Point2D &point);
	static void emulateClick();
};

