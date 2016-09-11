#include "VideoProcessor.h"

const string VideoProcessor::ALGORITHM = "MEDIANFLOW";

VideoProcessor::VideoProcessor() {
}

int VideoProcessor::initialize() {

	bool isOpened = video.open();
	if (!isOpened)
		return 1;

	tracker = cv::Tracker::create(ALGORITHM);
	if (tracker == NULL)
		return 2;

}

void VideoProcessor::drawBox(Mat &image, Rect2d &box, int thickness=4) {

	LineIterator iteratorX(image, Point(box.x, box.y), Point(box.x + box.width, box.y), 8);
	LineIterator iteratorY(image, Point(box.x, box.y), Point(box.x, box.y + box.height), 8);

	for (int i = 0; i < iteratorX.count; i++, ++iteratorX) {
		Point point = iteratorX.pos();
		for (int k = 0; k < 2; k++) {
			point.y += box.height * k;
			point.y -= thickness / 2;
			for (int j = 0; j < thickness; j++) {
				point.y++;
				Vec3b val = image.at<Vec3b>(point);
				image.at<Vec3b>(point) = Vec3b(255 - val[0], 255 - val[1], 255 - val[2]);
			}
		}
	}

	for (int i = 0; i < iteratorY.count; i++, ++iteratorY) {
		Point point = iteratorY.pos();
		for (int k = 0; k < 2; k++) {
			point.x += box.width * k;
			point.x -= thickness / 2;
			for (int j = 0; j < thickness; j++) {
				point.x++;
				Vec3b val = image.at<Vec3b>(point);
				image.at<Vec3b>(point) = Vec3b(255 - val[0], 255 - val[1], 255 - val[2]);
			}
		}
	}
}

int VideoProcessor::process() {

	if (!video.updateFrame())
		return 1;

	flip(video.getFrame(), frame, 1);
	frame.copyTo(image);

	// In tracking mode
	if (featureSelected) {

		bool tracked = tracker->update(frame, boundingBox);
		if (!tracked)
			return 2;

		drawBox(image, boundingBox);
	}

	else {
		drawBox(image, featureRegion);
	}

	return 0;
}

bool VideoProcessor::selectFeature() {

	tracker->clear();
	tracker = Tracker::create(ALGORITHM);

	featureSelected = tracker->init(frame, featureRegion);
	
	return featureSelected;
}

void VideoProcessor::dropFeature() {
	featureSelected = false;
}

void VideoProcessor::setFeatureWidth(int width) {
	featureWidth = width;
	featureRegion.x = (video.getWidth() - featureWidth) / 2;
	featureRegion.width = featureWidth;
}

void VideoProcessor::setFeatureHeight(int height) {
	featureHeight = height;
	featureRegion.y = (video.getHeight() - featureHeight) / 2;
	featureRegion.height = featureHeight;
}

int VideoProcessor::getFeatureWidth() {
	return featureWidth;
}

int VideoProcessor::getFeatureHeight() {
	return featureHeight;
}

Rect2d VideoProcessor::getBoundingBox() {
	return boundingBox;
}