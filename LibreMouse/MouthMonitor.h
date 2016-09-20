#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class MouthMonitor {
private:
	float detectTeeth(cv::Mat& src);
public:
	MouthMonitor();
	void update(cv::Mat& source);
};

