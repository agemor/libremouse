#include "CursorUpdater.h"

CursorUpdater::CursorUpdater() {
}

void CursorUpdater::update() {

	Point2D target(0, 0);
	Point2D current(0, 0);

	bool moving = false;

	while (true) {

		if (!running) break;

		if (moving) {

			double distance = sqrt(pow(target.x - current.x, 2) + pow(target.y - current.y, 2));

			if (distance < 1) {
				if (pathQueue.size() > 0) {
					// update target and current
					target = pathQueue.pop();
					mouseState.GetPosition(&current.x, &current.y);
				} else {
					moving = false;
				}
			} else {
				current.x += 0.3f * (target.x - current.x);
				current.y += 0.3f * (target.y - current.y);
				mouseState.SetPosition(wxPoint(current.x, current.y));
			}
		}

		else {
			if (pathQueue.size() > 0) {
				// update target and current
				target = pathQueue.pop();
				mouseState.GetPosition(&current.x, &current.y);
				moving = true;
			} else {
				std::this_thread::yield();
			}
		}
	}
}

void CursorUpdater::addToPath(Point2D step) {

	prevSpeedX = speedX;
	prevSpeedY = speedY;
	speedX = step.x - prevX;
	speedY = step.y - prevY;
	prevX = step.x;
	prevY = step.y;
	accX = speedX - prevSpeedX;
	accY = speedY - prevSpeedY;

	double force = sqrt(accX * accX + accY * accY);

	if (force > 35 && force < 5000) {

		int cursorX, cursorY;
		mouseState.GetPosition(&cursorX, &cursorY);

		cursorX -= accX;
		cursorY -= accY;

		pathQueue.push(Point2D(cursorX, cursorY));
	}
}

void CursorUpdater::start() {
	if (!running) {

		// Init cursor prev pos
		int cursorX, cursorY;
		mouseState.GetPosition(&cursorX, &cursorY);

		prevX = cursorX;
		prevY = cursorY;

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