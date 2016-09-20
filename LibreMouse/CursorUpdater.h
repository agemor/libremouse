#pragma once
#include <iostream>

#include "CursorControl.h"
#include "SynchronizedQueue.h"
#include "Point2D.h"

class CursorUpdater {
private:

	SynchronizedQueue<Point2D> pathQueue;

	std::thread updater;

	double prevX = 0, prevY = 0;
	double speedX = 0, speedY = 0;
	double prevSpeedX = 0, prevSpeedY = 0;
	double accX = 0, accY = 0;

public:
	bool running = false;

	CursorUpdater();
	void addToPath(Point2D step);
	void update();
	void start();
	void stop();
};