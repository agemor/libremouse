#include "MouthMonitor.h"
#include <iostream>

MouthMonitor::MouthMonitor(){
}
void MouthMonitor::update(cv::Mat& source) {

	float percentage =  detectTeeth(source);

	if(percentage > 0.2f)
	std::cout << percentage << std::endl;

}

float MouthMonitor::detectTeeth(cv::Mat& src) {

	// Normalize size
	cv::Mat normalized;
	cv::resize(src, normalized, cv::Size(400, 400));

	// Crop image to fit mouse region
	cv::Mat mouth;
	cv::Rect roi(120, 120, 160, 160);
	mouth = normalized(roi);

	// Equalize histogram
	cv::Mat equalized;
	std::vector<cv::Mat> channels;
	cv::cvtColor(mouth, equalized, CV_BGR2YCrCb);
	cv::split(equalized, channels);
	cv::equalizeHist(channels[0], channels[0]);
	cv::merge(channels, equalized);

	// Thresholding teeth region
	cv::Mat thresholded;
	cv::inRange(equalized, cv::Scalar(250, 0, 0), cv::Scalar(255, 140, 255), thresholded);
	
	// Calculate white pixels
	return (float) cv::countNonZero(thresholded) / (float) (thresholded.rows * thresholded.cols) * 100;
}
