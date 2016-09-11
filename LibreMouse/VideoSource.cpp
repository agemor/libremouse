#include "VideoSource.h"


VideoSource::VideoSource()
{
}


/**
 * Detect possible camera port and open it.
 */
bool VideoSource::open() {

	bool cameraUnavailable = true;

	// Check all possible camera ports
	for (int i = 0; i < 15; i++) {
		bool isOpened = camera.open(i);
		if (isOpened) {
			cameraUnavailable = false;
			break;
		}
	}

	return !cameraUnavailable;
}

/**
 * Close video stream
 */
void VideoSource::close() {
	camera.release();
}

/**
 * Update video frame
 */
bool VideoSource::updateFrame() {

	// Aquire frame from camera
	camera >> frame;

	return !frame.empty();
}

/**
 * Return video frame
 */
cv::Mat VideoSource::getFrame() {
	return frame;
}

/**
* Set video frame width
*/
void VideoSource::setWidth(int width) {
	camera.set(cv::CAP_PROP_FRAME_WIDTH, width);
}

/**
* Set video frame height
*/
void VideoSource::setHeight(int height) {
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

/**
 * Get video frame width
 */
int VideoSource::getWidth() {
	return camera.get(cv::CAP_PROP_FRAME_WIDTH);
}

/**
 * Get video frame height
 */
int VideoSource::getHeight() {
	return camera.get(cv::CAP_PROP_FRAME_HEIGHT);
}