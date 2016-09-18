#include "CursorUpdater.h"
#include <iostream>
CursorUpdater::CursorUpdater(wxFrame* _frame) {
	frame = _frame;
}

void CursorUpdater::update() {
	
	Point2D target(0, 0);
	Point2I current(0, 0);

	bool moving = false;

	while (true) {

		if (!running) break;

		if (moving) {

			double distance = sqrt(pow(target.x - current.x, 2) + pow(target.y - current.y, 2));
			if (distance < 5) {
				if (pathQueue.size() > 0) {
					// update target and current
					target = pathQueue.pop();
					wxGetMousePosition(&current.x, &current.y);

					//mouseState.GetPosition(&current.x, &current.y);
					//frame->GetMous
				} else {
					moving = false;
				}
			} else {
				current.x += 0.3f * (target.x - current.x);
				current.y += 0.3f * (target.y - current.y);
				//std::cout << current.x << "/"  << current.y<< std::endl;

				//frame->WarpPointer(current.x, current.y);

				//mouseState.SetPosition(wxPoint(current.x, current.y));
			}
		}

		else {
			if (pathQueue.size() > 0) {
				// update target and current
				target = pathQueue.pop();
				wxGetMousePosition(&current.x, &current.y);

				//mouseState.GetPosition(&current.x, &current.y);
				moving = true;

			} else {
				std::this_thread::yield();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
	accX = (speedX - prevSpeedX)*10;// *150;
	accY = (speedY - prevSpeedY)*10;// *220;

	double force = sqrt(accX * accX + accY * accY);

	if (abs(speedX) + abs(speedY) > 0) {

		std::cout << speedX << "/" << speedY << std::endl;
	}
	if (force > 35 && force < 5000) {
		//std::cout << force << std::endl;

		int cursorX, cursorY;
		wxGetMousePosition(&cursorX, &cursorY);
		//mouseState.GetPosition(&cursorX, &cursorY);

		cursorX -= accX / 10;
		cursorY -= accY / 10;

		pathQueue.push(Point2D(cursorX, cursorY));
	}
}

void CursorUpdater::start() {
	if (!running) {

		std::cout << prevX << "/" << prevY << std::endl;
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