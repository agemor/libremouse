#pragma once
#include "SynchronizedQueue.h"
#include <wx/wx.h>


class Point2D {

public:
	double x;
	double y;

	Point2D(double x_, double y_) {
		x = x_;
		y = y_;
	}
};

class Point2I {

public:
	int x;
	int y;

	Point2I(int x_, int y_) {
		x = x_;
		y = y_;
	}
};

class CursorUpdater {
private:
	
	wxMouseState mouseState = wxMouseState();
	
	SynchronizedQueue<Point2D> pathQueue;

	std::thread updater;
	wxFrame* frame;

	double prevX = 0, prevY = 0;
	double speedX = 0, speedY = 0;
	double prevSpeedX = 0, prevSpeedY = 0;
	double accX = 0, accY = 0;

public:
	bool running = false;

	CursorUpdater(wxFrame* _frame);
	void addToPath(Point2D step);
	void update();
	void start();
	void stop();
};