#include "CursorUpdater.h"
#include <iostream>
#include <windows.h>


double min(double a, double b) {
	return (a < b ? a : b);
}

CursorUpdater::CursorUpdater(wxFrame* _frame) {
	frame = _frame;
}

void CursorUpdater::getCursorPosition(Point2D &point) {
	int cursorX, cursorY;
	wxGetMousePosition(&cursorX, &cursorY);
	point.x = cursorX;
	point.y = cursorY;
}

void CursorUpdater::setCursorPosition(Point2D &point) {
	SetCursorPos(point.x, point.y);
}

void CursorUpdater::update() {
	
	Point2D target(0, 0);
	Point2D current(0, 0);

	bool moving = false;

	double distance = 100000;
	double prevDistance = 0;

	while (true) {

		if (!running) break;
		
		if (moving) {
			prevDistance = distance;
			distance = sqrt(pow(target.x - current.x, 2) + pow(target.y - current.y, 2));
			////double distance = abs(target.x - current.x) + abs(target.y - current.y);

			if (distance >= prevDistance || distance < 1) {
				if (pathQueue.size() > 0) {
					target = pathQueue.pop();
					getCursorPosition(current);
					distance = 100000;
				} else {
					moving = false;
				}
			} else {
				current.x += 0.3f * (target.x - current.x);
				current.y += 0.3f * (target.y - current.y);
				//::cout << current.x << "/" << current.y << std::endl;

				setCursorPosition(current);
			}
		}

		else {
			if (pathQueue.size() > 0) {
				// update target and current
				target = pathQueue.pop();
				getCursorPosition(current);
				distance = 100000;
				moving = true;

			} else {
				//std::this_thread::yield();
			}
		}

		//std::cout << distance << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void CursorUpdater::addToPath(Point2D step) {

	if (prevX == 0 && prevY == 0 && step.x > 10) {
		prevX = step.x;
		prevY = step.y;
	}

	prevSpeedX = speedX;
	prevSpeedY = speedY;
	speedX = step.x - prevX;
	speedY = step.y - prevY;
	prevX = step.x;
	prevY = step.y;
	float sx = (prevSpeedX + speedX) / 2;
	float sy = (prevSpeedY + speedY) / 2;

	//sx = min(pow(sx, 2), 6) * (sx > 0 ? 1 : -1);
	//sy = min(pow(sy, 2), 6) * (sy > 0 ? 1 : -1);

	sx = 300 * tanh(pow(sx / 1.5, 2) / 30) * (sx > 0 ? 1 : -1);
	sy = 300 * tanh(pow(sy / 1.5, 2) / 18) * (sy > 0 ? 1 : -1);

	double force = abs(sx) + abs(sy);
	if (force > 0) {
		std::cout << sx << std::endl;

		Point2D cursorPosition = Point2D();
		getCursorPosition(cursorPosition);

		cursorPosition.x -= -sx;
		cursorPosition.y -= -sy;

		pathQueue.push(cursorPosition);
	}
}

void CursorUpdater::start() {
	if (!running) {

		running = true;
		updater = std::thread([this] { this->update(); });
	}
}
void CursorUpdater::stop() {
	if (running) {
		running = false;
		updater.join();
	}
}
