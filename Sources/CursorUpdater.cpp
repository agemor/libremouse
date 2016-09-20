#include "CursorUpdater.h"

CursorUpdater::CursorUpdater() {}

void CursorUpdater::update() {

	Point2D target(0, 0);
	Point2D current(0, 0);

	bool moving = false;

	double distance = INFINITY;
	double prevDistance = 0;

	while (true) {
		if (!running) break;
		if (moving) {
			prevDistance = distance;
			//distance = sqrt(pow(target.x - current.x, 2) + pow(target.y - current.y, 2));
			distance = abs(target.x - current.x) + abs(target.y - current.y);

			if (distance >= prevDistance || distance < 1) {
				if (pathQueue.size() > 0) {
					target = pathQueue.pop();
					CursorControl::getCursorPosition(current);
					distance = INFINITY;
				}
				else {
					moving = false;
				}
			}
			else {
				current.x += 0.28f * (target.x - current.x);
				current.y += 0.28f * (target.y - current.y);
				CursorControl::setCursorPosition(current);
			}
		}
		else {
			if (pathQueue.size() > 0) {
				// update target and current
				target = pathQueue.pop();
				CursorControl::getCursorPosition(current);
				distance = INFINITY;
				moving = true;

			}
		}
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

	sx = 300 * tanh(pow(sx / 1.5, 2) / 30) * (sx > 0 ? 1 : -1);
	sy = 400 * tanh(pow(sy / 1.5, 2) / 18) * (sy > 0 ? 1 : -1);

	double force = abs(sx) + abs(sy);
	if (force > 0) {

		Point2D cursorPosition = Point2D();
		CursorControl::getCursorPosition(cursorPosition);

		cursorPosition.x += sx;
		cursorPosition.y += sy;

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
