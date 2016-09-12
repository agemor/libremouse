#pragma once
#include <opencv2/tracking.hpp>
#include <string>

#include "VideoSource.h"

class VideoProcessor {

private:
	static const std::string ALGORITHM;

	bool initialized = false;

	VideoSource video;
	cv::Ptr<cv::Tracker> tracker;

	cv::Mat frame, image;
	cv::Rect2d boundingBox;

	cv::Rect2d featureRegion;
	int featureWidth;
	int featureHeight;
	bool featureSelected = false;

	void drawBox(cv::Mat &image, cv::Rect2d &box, int thickness);

public:
	VideoProcessor();

	int initialize();
	bool isInitialized();

	int process();

	void setFeatureWidth(int width);
	void setFeatureHeight(int height);
	int getFeatureWidth();
	int getFeatureHeight();

	bool selectFeature();
	void dropFeature();

	cv::Rect2d getBoundingBox();
	cv::Mat getImage();
};