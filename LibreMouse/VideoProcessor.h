#pragma once
#include <opencv2/tracking.hpp>
#include <string>

#include "VideoSource.h"

using namespace std;
using namespace cv;

class VideoProcessor {

private:
	static const string ALGORITHM;

	bool initialized = false;

	VideoSource video;
	Ptr<Tracker> tracker;

	Mat frame, image;
	Rect2d boundingBox;

	Rect2d featureRegion;
	int featureWidth;
	int featureHeight;
	bool featureSelected = false;

	void drawBox(Mat &image, Rect2d &box, int thickness);

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

	Rect2d getBoundingBox();
	Mat getImage();
};