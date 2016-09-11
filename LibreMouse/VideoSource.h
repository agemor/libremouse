#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class VideoSource
{
private:
	cv::VideoCapture camera;
	cv::Mat frame;

public:
	VideoSource();
	
	bool open();
	void close();

	bool updateFrame();
	cv::Mat getFrame();

	void setWidth(int width);
	void setHeight(int height);

	int getWidth();
	int getHeight();

};