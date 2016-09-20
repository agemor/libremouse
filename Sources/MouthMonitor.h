#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MouthMonitor {
private:
public:
	MouthMonitor();
	float detect(cv::Mat& src);
};

