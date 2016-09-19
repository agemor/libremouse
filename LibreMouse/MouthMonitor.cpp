#include "MouthMonitor.h"
#include <iostream>

MouthMonitor::MouthMonitor(){
}
void showHistogram(cv::Mat& src);
void showGreyHistogram(cv::Mat& src);
void showCantour(cv::Mat& src);
void findCircles(cv::Mat& src);

void MouthMonitor::update(cv::Mat& source) {

	cv::Mat dst, dst2;

	cv::cvtColor(source, source, cv::COLOR_BGR2GRAY);
	//cv::HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 100, 0, 0);

	/// Apply Histogram Equalization
	cv::equalizeHist(source, dst);
	//cv::normalize(dst, dst, 0, 1., cv::NORM_MINMAX);
	//cv::threshold(dst, dst, 15, 255, cv::THRESH_BINARY);
	//cv::imshow("ss", dst);
	findCircles(dst);
	//cv::GaussianBlur(dst, dst2, cv::Size(9, 9), 2.0, 2.0);
	//showGreyHistogram(dst2);
	//showCantour(dst);
}

void findCircles(cv::Mat& src) {
	/// Reduce the noise so we avoid false circle detection
	//cv::GaussianBlur(src, src, cv::Size(9, 9), 2, 2);

	std::vector<cv::Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	cv::HoughCircles(src, circles, CV_HOUGH_GRADIENT, 1, src.rows / 1, 80, 60,  8, 400);

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
	}
	
	if(circles.size() > 0)
	std::cout << circles.size() << std::endl;
	/// Show your results
	//cv::namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	//cv::imshow("Hough Circle Transform Demo", src);
	//cvWaitKey(1);
}

cv::RNG rng(12345);
int thresh = 200;
int max_thresh = 255;
void showCantour(cv::Mat& src) {
	cv::Mat canny_output;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	/// Draw contours
	cv::Mat drawing = cv::Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
	}

	/// Show in a window
	cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	cv::imshow("Contours", drawing);
}


void showHistogram(cv::Mat& src) {
	/// Separate the image in 3 places ( B, G and R )
	std::vector<cv::Mat> bgr_planes;
	cv::split(src, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	cv::Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			cv::Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);
	}

	cv::namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	cv::imshow("calcHist Demo", histImage);
}

void showGreyHistogram(cv::Mat& src) {

	cv::MatND histogram;
	const int* channel_numbers = { 0 };
	float channel_range[] = { 0.0, 255.0 };
	const float* channel_ranges = channel_range;
	int number_bins = 255;

	cv::calcHist(&src, 1, channel_numbers, cv::Mat(), histogram, 1, &number_bins, &channel_ranges);

	// Plot the histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / number_bins);

	cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(0, 0, 0));
	normalize(histogram, histogram, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

	for (int i = 1; i < number_bins; i++)
	{
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(histogram.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);
	}

	cv::namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
	cv::imshow("Histogram", histImage);
}