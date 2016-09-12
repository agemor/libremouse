#pragma once
#include <string>

#include "VideoSource.h"
#include "kcf/kcftracker.hpp"


class VideoProcessor {

private:
	static const std::string ALGORITHM;

	bool initialized = false;

	VideoSource video;
	KCFTracker tracker;

	cv::Mat frame, image;
	cv::Rect boundingBox;

	cv::Rect featureRegion;
	int featureWidth;
	int featureHeight;

	void drawBox(cv::Mat& image, cv::Rect& box, int thickness);

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

	cv::Rect getBoundingBox();
	cv::Mat getImage();
};