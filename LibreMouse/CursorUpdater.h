#pragma once
#include "SynchronizedQueue.h"
#include <wx/mousestate.h>

struct Point2D {
	int x;
	int y;
	Point2D(int x_, int y_) {
		x = x_;
		y = y_;
	}
} CursorPosition;

class CursorUpdater {
private:
	
	wxMouseState mouseState = wxMouseState();
	
	SynchronizedQueue<Point2D> pathQueue;

	std::thread updater;
	bool running = false;

	double prevX = 0, prevY = 0;
	double speedX = 0, speedY = 0;
	double prevSpeedX = 0, prevSpeedY = 0;
	double accX = 0, accY = 0;

	void update();
public:
	CursorUpdater();

	void addToPath(Point2D step);
	void start();
	void stop();
};