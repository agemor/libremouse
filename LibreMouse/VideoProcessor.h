#pragma once
#include <string>

#include "VideoSource.h"
#include "MouthMonitor.h"
#include "kcf/kcftracker.hpp"


class VideoProcessor {

private:

	bool initialized = false;

	VideoSource video;
	KCFTracker tracker;
	MouthMonitor mouthMonitor;

	cv::Mat frame, image;
	cv::Rect2f boundingBox;

	cv::Rect featureRegion;
	int featureWidth;
	int featureHeight;

	void drawBox(cv::Mat& image, cv::Rect box, int thickness);

public:
	VideoProcessor();
	int kuru = 0;
	bool featureSelected = false;

	int initialize();
	bool isInitialized();

	int process();

	void setFeatureWidth(int width);
	void setFeatureHeight(int height);
	int getFeatureWidth();
	int getFeatureHeight();

	bool selectFeature();
	void dropFeature();

	cv::Rect2f getBoundingBox();
	cv::Mat getImage();
};