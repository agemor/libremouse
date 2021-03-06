#include "VideoProcessor.h"

VideoProcessor::VideoProcessor() {}

int VideoProcessor::initialize() {

	bool isOpened = video.open();
	if (!isOpened)
		return 1;

	bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;

	tracker = KCFTracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);

	setFeatureWidth(60);
	setFeatureHeight(80);

	initialized = true;

	return 0;
}

bool VideoProcessor::isInitialized() {
	return initialized;
}

void VideoProcessor::drawBox(cv::Mat &image, cv::Rect box, int thickness) {

	int ht = thickness / 2;

	if (image.rows <= box.y + box.height + ht) {
		if (box.y + ht > image.rows)
			return;
		box.height = image.rows - box.y - ht;
	}

	if (box.y < ht) {
		if (box.y + box.height < 0)
			return;
		box.height += box.y - ht;
		box.y = ht;
	}

	for (int x = box.x - ht; x < box.x + box.width + ht; x++) {
		for (int y = box.y - ht; y < box.y + ht; y++) {
			cv::Vec3b v1 = image.at<cv::Vec3b>(y, x);
			cv::Vec3b v2 = image.at<cv::Vec3b>(y + box.height, x);
			image.at<cv::Vec3b>(y, x) = cv::Vec3b(255 - v1[0], 255 - v1[1], 255 - v1[2]);
			image.at<cv::Vec3b>(y + box.height, x) = cv::Vec3b(255 - v2[0], 255 - v2[1], 255 - v2[2]);
		}
	}

	for (int y = box.y + ht; y < box.y + box.height - ht; y++) {
		for (int x = box.x - ht; x < box.x + ht; x++) {
			cv::Vec3b v1 = image.at<cv::Vec3b>(y, x);
			cv::Vec3b v2 = image.at<cv::Vec3b>(y, x + box.width);
			image.at<cv::Vec3b>(y, x) = cv::Vec3b(255 - v1[0], 255 - v1[1], 255 - v1[2]);
			image.at<cv::Vec3b>(y, x + box.width) = cv::Vec3b(255 - v2[0], 255 - v2[1], 255 - v2[2]);
		}
	}
}

int VideoProcessor::process() {

	if (!video.updateFrame())
		return 1;

	flip(video.getFrame(), frame, 1);
	frame.copyTo(image);

	if (featureSelected) {
		boundingBox = tracker.update(frame);
		drawBox(image, (cv::Rect) boundingBox, 2);
	}
	else {
		drawBox(image, featureRegion, 2);
	}
	return 0;
}

float VideoProcessor::detectMouth() {
	if (frame.empty() || !featureSelected)
		return 0;
	return mouthMonitor.detect(frame(boundingBox));
}

bool VideoProcessor::selectFeature() {

	tracker.init(featureRegion, frame);
	featureSelected = true;
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

cv::Rect2f VideoProcessor::getBoundingBox() {
	return boundingBox;
}

cv::Mat VideoProcessor::getFrame() {
	return image;
}